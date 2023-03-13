/*
 * Copyright (c) 2016-2021, Pelion and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "common/log_legacy.h"
#include "common/endian.h"
#include "stack/mac/mac_api.h"
#include "stack/mac/mac_common_defines.h"
#include "stack/mac/mlme.h"

#include "app_wsbrd/rcp_api.h"
#include "app_wsbrd/dbus.h"
#include "app_wsbrd/wsbr.h"
#include "nwk_interface/protocol.h"

#include "6lowpan/mac/mac_helper.h"

#define TRACE_GROUP "MACh"

static const uint8_t mac_helper_default_key_source[8] = {0xff, 0, 0, 0, 0, 0, 0, 0};

static uint8_t mac_helper_header_security_aux_header_length(uint8_t keyIdmode);
static uint8_t mac_helper_security_mic_length_get(uint8_t security_level);

uint16_t mac_helper_mac16_address_get(const struct net_if *interface)
{
    uint16_t shortAddress = 0xfffe;
    if (interface) {
        shortAddress = interface->mac_parameters.mac_short_address;
    }
    return shortAddress;
}

uint16_t mac_helper_panid_get(const struct net_if *interface)
{
    uint16_t panId = 0xffff;
    if (interface) {
        panId = interface->mac_parameters.pan_id;
    }
    return panId;
}

uint8_t mac_helper_default_key_index_get(struct net_if *interface)
{
    return interface->mac_parameters.mac_default_key_index;
}

void mac_helper_set_default_key_source(struct net_if *interface)
{
    rcp_set_default_key_source(mac_helper_default_key_source);
}

uint8_t mac_helper_default_security_level_get(struct net_if *interface)
{
    return interface->mac_parameters.mac_security_level;
}

uint8_t mac_helper_default_security_key_id_mode_get(struct net_if *interface)
{
    return interface->mac_parameters.mac_key_id_mode;
}

int8_t mac_helper_security_key_to_descriptor_set(struct net_if *interface, const uint8_t *key, uint8_t id, uint8_t slot)
{
    uint8_t lookup_data[9];

    BUG_ON(!id);
    memcpy(lookup_data, mac_helper_default_key_source, 8);
    lookup_data[8] = id;
    rcp_set_key(slot, lookup_data, key);
    dbus_emit_keys_change(&g_ctxt);
    return 0;
}

int8_t mac_helper_security_key_descriptor_clear(struct net_if *interface, uint8_t slot)
{
    rcp_set_key(slot, NULL, NULL);
    return 0;
}

static bool mac_helper_write_16bit(uint16_t temp16, uint8_t *addrPtr)
{
    write_be16(addrPtr, temp16);
    return temp16 != 0xffff;
}

/* Write functions return "false" if they write an "odd" address, true if they
 * write a "normal" address. They still write odd addresses, as certain special
 * packets may want them, but this allows normal data paths to check and block
 * odd cases.
 * "Odd" is currently defined as PAN ID == 0xffff, or short address > 0xfffd.
 */
bool mac_helper_write_our_addr(struct net_if *interface, sockaddr_t *ptr)
{
    bool normal = true;

    //Set First PANID
    normal &= mac_helper_write_16bit(interface->mac_parameters.pan_id, ptr->address);

    if (ptr->addr_type != ADDR_802_15_4_LONG && ptr->addr_type != ADDR_802_15_4_SHORT) {
        if (interface->mac_parameters.shortAdressValid) {
            ptr->addr_type = ADDR_802_15_4_SHORT;
        } else {
            ptr->addr_type = ADDR_802_15_4_LONG;
        }
    }

    if (ptr->addr_type == ADDR_802_15_4_SHORT) {
        normal &= mac_helper_write_16bit(interface->mac_parameters.mac_short_address, &ptr->address[2]);
    } else {
        memcpy(&ptr->address[2], interface->mac, 8);
    }

    return normal;
}

int8_t mac_helper_mac64_set(struct net_if *interface, const uint8_t *mac64)
{
    memcpy(interface->mac, mac64, 8);
    if (interface->mac_api) {
        interface->mac_api->mac64_set(interface->mac_api, mac64);
    }
    return 0;
}


/*
 * Given a buffer, with address and security flags set, compute the maximum
 * MAC payload that could be put in that buffer.
 */
uint_fast16_t mac_helper_max_payload_size(struct net_if *cur, uint_fast16_t frame_overhead)
{
    return cur->mac_api->mtu - frame_overhead;
}

/*
 * Given a buffer, with address and security flags set, compute the MAC overhead
 * size once MAC header and footer are added.
 * May not be accurate if MAC_MAX_PHY_PACKET_SIZE isn't set, implying a
 * non-standard MAC.
 */
uint_fast8_t mac_helper_frame_overhead(struct net_if *cur, const buffer_t *buf)
{
    uint_fast8_t length = 15;

    /*8bytes src address, 2 frame control, 1 sequence, 2 pan-id, 2 FCS*/
    if (buf->src_sa.addr_type == ADDR_NONE) {
        if (cur->mac_parameters.shortAdressValid) {
            length -= 6; //Cut 6 bytes from src address
        }
    } else if (buf->src_sa.addr_type == ADDR_802_15_4_SHORT) {
        length -= 6; //Cut 6 bytes from src address
    }

    if (memcmp(buf->dst_sa.address, buf->src_sa.address, 2) == 0) {
        length -= 2; // Cut Pan-id
    }

    if (buf->dst_sa.addr_type == ADDR_802_15_4_LONG) {
        length += 10;
    } else if (buf->dst_sa.addr_type == ADDR_802_15_4_SHORT || buf->dst_sa.addr_type == ADDR_BROADCAST) {
        length += 4;
    }

    if (cur->mac_parameters.mac_security_level && (!buf->options.ll_security_bypass_tx)) {
        length += mac_helper_header_security_aux_header_length(cur->mac_parameters.mac_key_id_mode);
        length += mac_helper_security_mic_length_get(cur->mac_parameters.mac_security_level);
    }

    return length;
}

static uint8_t mac_helper_security_mic_length_get(uint8_t security_level)
{
    uint8_t mic_length;
    switch (security_level) {
        case SEC_MIC32:
        case SEC_ENC_MIC32:
            mic_length = 4;
            break;
        case SEC_MIC64:
        case SEC_ENC_MIC64:
            mic_length = 8;
            break;
        case SEC_MIC128:
        case SEC_ENC_MIC128:
            mic_length = 16;
            break;
        case SEC_NONE:
        case SEC_ENC:
        default:
            mic_length = 0;
            break;
    }

    return mic_length;
}

static uint8_t mac_helper_header_security_aux_header_length(uint8_t keyIdmode)
{

    uint8_t header_length = 5; //Header + 32-bit counter
    switch (keyIdmode) {
        case MAC_KEY_ID_MODE_SRC8_IDX:
            header_length += 4; //64-bit key source first part
        /* fall through  */
        case MAC_KEY_ID_MODE_SRC4_IDX:
            header_length += 4; //32-bit key source inline
        /* fall through  */
        case MAC_KEY_ID_MODE_IDX:
            header_length += 1;
            break;
        default:
            break;
    }
    return header_length;
}

int8_t mac_helper_link_frame_counter_read(int8_t interface_id, uint32_t *seq_ptr)
{
    struct net_if *cur = protocol_stack_interface_info_get_by_id(interface_id);

    if (!cur || !cur->mac_api || !seq_ptr) {
        return -1;
    }

    return mac_helper_key_link_frame_counter_read(interface_id, seq_ptr, cur->mac_parameters.mac_default_key_attribute_id);
}

int8_t mac_helper_key_link_frame_counter_read(int8_t interface_id, uint32_t *seq_ptr, uint8_t descriptor)
{
    struct net_if *cur = protocol_stack_interface_info_get_by_id(interface_id);

    if (!cur || !cur->mac_api || !seq_ptr) {
        return -1;
    }
    mlme_get_t get_req;
    get_req.attr = macFrameCounter;
    get_req.attr_index = descriptor;
    cur->mac_api->mlme_req(cur->mac_api, MLME_GET, &get_req);
    *seq_ptr = cur->mac_parameters.security_frame_counter;

    return 0;
}

int8_t mac_helper_start_auto_cca_threshold(int8_t interface_id, uint8_t number_of_channels, int8_t default_dbm, int8_t high_limit, int8_t low_limit)
{
    struct net_if *cur;
    cur = protocol_stack_interface_info_get_by_id(interface_id);
    if (!cur || !cur->mac_api) {
        return -1;
    }

    rcp_set_cca_threshold(number_of_channels, default_dbm, high_limit, low_limit);
    return 0;
}

int8_t mac_helper_mac_mlme_filter_start(int8_t interface_id, int16_t lqi_m, int16_t lqi_add, int16_t dbm_m, int16_t dbm_add)
{
    struct net_if *cur = protocol_stack_interface_info_get_by_id(interface_id);
    mlme_set_t set_req;
    mlme_request_mac_filter_start_t args = {
        .lqi_m = lqi_m,
        .lqi_add = lqi_add,
        .dbm_m = dbm_m,
        .dbm_add = dbm_add
    };

    if (!cur || !cur->mac_api) {
        return -1;
    }

    set_req.attr = macFilterStart;
    set_req.value_pointer = &args;
    set_req.value_size = sizeof(mlme_request_mac_filter_start_t);
    cur->mac_api->mlme_req(cur->mac_api, MLME_SET, &set_req);
    return 0;
}

int8_t mac_helper_mac_mlme_filter_clear(int8_t interface_id)
{
    struct net_if *cur = protocol_stack_interface_info_get_by_id(interface_id);
    mlme_set_t set_req;

    if (!cur || !cur->mac_api) {
        return -1;
    }

    set_req.attr = macFilterClear;
    set_req.value_pointer = NULL;
    set_req.value_size = 0;
    cur->mac_api->mlme_req(cur->mac_api, MLME_SET, &set_req);
    return 0;
}

int8_t mac_helper_mac_mlme_filter_add_long(int8_t interface_id, uint8_t mac64[8], int16_t lqi_m, int16_t lqi_add, int16_t dbm_m, int16_t dbm_add)
{
    struct net_if *cur = protocol_stack_interface_info_get_by_id(interface_id);
    mlme_set_t set_req;
    mlme_request_mac_filter_add_long_t args = {
        .mac64 = { 0 },
        .lqi_m = lqi_m,
        .lqi_add = lqi_add,
        .dbm_m = dbm_m,
        .dbm_add = dbm_add
    };

    if (!cur || !cur->mac_api) {
        return -1;
    }

    memcpy(&args.mac64, mac64, 8);
    set_req.attr = macFilterAddLong;
    set_req.value_pointer = &args;
    set_req.value_size = sizeof(mlme_request_mac_filter_add_long_t);
    cur->mac_api->mlme_req(cur->mac_api, MLME_SET, &set_req);
    return 0;
}

int8_t mac_helper_mac_mlme_filter_stop(int8_t interface_id)
{
    struct net_if *cur = protocol_stack_interface_info_get_by_id(interface_id);
    mlme_set_t set_req;

    if (!cur || !cur->mac_api) {
        return -1;
    }

    set_req.attr = macFilterStop;
    set_req.value_pointer = NULL;
    set_req.value_size = 0;
    cur->mac_api->mlme_req(cur->mac_api, MLME_SET, &set_req);
    return 0;
}

int8_t mac_helper_set_regional_regulation(const struct net_if *cur, uint32_t regulation)
{
    mlme_set_t set_req;

    set_req.attr = macRegionalRegulation;
    set_req.value_pointer = &regulation;
    set_req.value_size = sizeof(uint32_t);
    cur->mac_api->mlme_req(cur->mac_api, MLME_SET, &set_req);

    return 0;
}
