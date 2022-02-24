SRCS += \
	source/6LoWPAN/adaptation_interface.c \
	source/6LoWPAN/Bootstraps/Generic/network_lib.c \
	source/6LoWPAN/Bootstraps/Generic/protocol_6lowpan.c \
	source/6LoWPAN/Bootstraps/Generic/protocol_6lowpan_bootstrap.c \
	source/6LoWPAN/Bootstraps/Generic/protocol_6lowpan_interface.c \
	source/6LoWPAN/Fragmentation/cipv6_fragmenter.c \
	source/6LoWPAN/IPHC_Decode/6lowpan_iphc.c \
	source/6LoWPAN/IPHC_Decode/iphc_compress.c \
	source/6LoWPAN/IPHC_Decode/iphc_decompress.c \
	source/6LoWPAN/IPHC_Decode/lowpan_context.c \
	source/6LoWPAN/MAC/beacon_handler.c \
	source/6LoWPAN/MAC/mac_helper.c \
	source/6LoWPAN/MAC/mac_ie_lib.c \
	source/6LoWPAN/MAC/mac_response_handler.c \
	source/6LoWPAN/MAC/mac_data_poll.c \
	source/6LoWPAN/MAC/mac_pairwise_key.c \
	source/6LoWPAN/Mesh/mesh.c \
	source/6LoWPAN/ND/nd_router_object.c \
	source/6LoWPAN/NVM/nwk_nvm.c \
	source/6LoWPAN/ws/ws_ie_lib.c \
	source/6LoWPAN/ws/ws_llc_data_service.c \
	source/6LoWPAN/ws/ws_mpx_header.c \
	source/6LoWPAN/ws/ws_neighbor_class.c \
	source/6LoWPAN/ws/ws_bootstrap.c \
	source/6LoWPAN/ws/ws_bootstrap_6lbr.c \
	source/6LoWPAN/ws/ws_bootstrap_ffn.c \
	source/6LoWPAN/ws/ws_bootstrap_lfn.c \
	source/6LoWPAN/ws/ws_common.c \
	source/6LoWPAN/ws/ws_management_api.c \
	source/6LoWPAN/ws/ws_bbr_api.c \
	source/6LoWPAN/ws/ws_test_api.c \
	source/6LoWPAN/ws/ws_empty_functions.c \
	source/6LoWPAN/ws/ws_pae_controller.c \
	source/6LoWPAN/ws/ws_pae_supp.c \
	source/6LoWPAN/ws/ws_pae_auth.c \
	source/6LoWPAN/ws/ws_pae_lib.c \
	source/6LoWPAN/ws/ws_pae_nvm_data.c \
	source/6LoWPAN/ws/ws_pae_nvm_store.c \
	source/6LoWPAN/ws/ws_pae_time.c \
	source/6LoWPAN/ws/ws_pae_timers.c \
	source/6LoWPAN/ws/ws_pae_key_storage.c \
	source/6LoWPAN/ws/ws_eapol_relay.c \
	source/6LoWPAN/ws/ws_eapol_auth_relay.c \
	source/6LoWPAN/ws/ws_eapol_relay_lib.c \
	source/6LoWPAN/ws/ws_eapol_pdu.c \
	source/6LoWPAN/ws/ws_stats.c \
	source/6LoWPAN/ws/ws_cfg_settings.c \
	source/6LoWPAN/ws/ws_phy.c \
	source/BorderRouter/border_router.c \
	source/Common_Protocols/icmpv6.c \
	source/Common_Protocols/icmpv6_prefix.c \
	source/Common_Protocols/icmpv6_radv.c \
	source/Common_Protocols/ipv6.c \
	source/Common_Protocols/ipv6_resolution.c \
	source/Common_Protocols/ipv6_fragmentation.c \
	source/Common_Protocols/ipv6_flow.c \
	source/Common_Protocols/mld.c \
	source/Common_Protocols/tcp.c \
	source/Common_Protocols/udp.c \
	source/Core/ns_address_internal.c \
	source/Core/ns_monitor.c \
	source/Core/buffer_dyn.c \
	source/Core/sockbuf.c \
	source/Core/ns_socket.c \
	source/ipv6_stack/ipv6_routing_table.c \
	source/ipv6_stack/protocol_ipv6.c \
	source/libNET/src/net_6lowpan_parameter_api.c \
	source/libNET/src/net_ipv6.c \
	source/libNET/src/net_test.c \
	source/libNET/src/net_mle.c \
	source/libNET/src/net_rpl.c \
	source/libNET/src/net_load_balance.c \
	source/libNET/src/net_dns.c \
	source/libNET/src/ns_net.c \
	source/libNET/src/socket_api.c \
	source/libNET/src/multicast_api.c \
	source/MAC/rf_driver_storage.c \
	source/MAC/IEEE802_15_4/mac_header_helper_functions.c \
	source/MAC/IEEE802_15_4/mac_indirect_data.c \
	source/MAC/IEEE802_15_4/mac_mcps_sap.c \
	source/MAC/IEEE802_15_4/mac_mlme.c \
	source/MAC/IEEE802_15_4/mac_filter.c \
	source/MAC/IEEE802_15_4/mac_pd_sap.c \
	source/MAC/IEEE802_15_4/mac_security_mib.c \
	source/MAC/IEEE802_15_4/mac_timer.c \
	source/MAC/IEEE802_15_4/sw_mac.c \
	source/MAC/IEEE802_15_4/mac_fhss_callbacks.c \
	source/MAC/IEEE802_15_4/mac_cca_threshold.c \
	source/MAC/IEEE802_15_4/mac_mode_switch.c \
	source/MAC/ethernet/ethernet_mac_api.c \
	source/MAC/serial/serial_mac_api.c \
	source/MAC/virtual_rf/virtual_rf_client.c \
	source/MAC/virtual_rf/virtual_rf_driver.c \
	source/MLE/mle.c \
	source/MLE/mle_tlv.c \
	source/MPL/mpl.c \
	source/NWK_INTERFACE/protocol_core.c \
	source/NWK_INTERFACE/protocol_core_sleep.c \
	source/NWK_INTERFACE/protocol_stats.c \
	source/NWK_INTERFACE/protocol_timer.c \
	source/RPL/rpl_control.c \
	source/RPL/rpl_data.c \
	source/RPL/rpl_upward.c \
	source/RPL/rpl_downward.c \
	source/RPL/rpl_objective.c \
	source/RPL/rpl_of0.c \
	source/RPL/rpl_mrhof.c \
	source/RPL/rpl_policy.c \
	source/Security/Common/security_lib.c \
	source/Security/eapol/eapol_helper.c \
	source/Security/eapol/kde_helper.c \
	source/Security/kmp/kmp_api.c \
	source/Security/kmp/kmp_addr.c \
	source/Security/kmp/kmp_eapol_pdu_if.c \
	source/Security/kmp/kmp_socket_if.c \
	source/Security/protocols/sec_prot_lib.c \
	source/Security/protocols/sec_prot_keys.c \
	source/Security/protocols/sec_prot_certs.c \
	source/Security/protocols/key_sec_prot/key_sec_prot.c \
	source/Security/protocols/eap_tls_sec_prot/auth_eap_tls_sec_prot.c \
	source/Security/protocols/eap_tls_sec_prot/radius_eap_tls_sec_prot.c \
	source/Security/protocols/eap_tls_sec_prot/supp_eap_tls_sec_prot.c \
	source/Security/protocols/eap_tls_sec_prot/eap_tls_sec_prot_lib.c \
	source/Security/protocols/fwh_sec_prot/auth_fwh_sec_prot.c \
	source/Security/protocols/fwh_sec_prot/supp_fwh_sec_prot.c \
	source/Security/protocols/gkh_sec_prot/auth_gkh_sec_prot.c \
	source/Security/protocols/gkh_sec_prot/supp_gkh_sec_prot.c \
	source/Security/protocols/radius_sec_prot/radius_client_sec_prot.c \
	source/Security/protocols/radius_sec_prot/avp_helper.c \
	source/Security/protocols/msg_sec_prot/msg_sec_prot.c \
	source/Security/protocols/tls_sec_prot/tls_sec_prot.c \
	source/Security/protocols/tls_sec_prot/tls_sec_prot_lib.c \
	source/Security/PANA/eap_protocol.c \
	source/Security/PANA/pana.c \
	source/Security/PANA/pana_avp.c \
	source/Security/PANA/pana_client.c \
	source/Security/PANA/pana_eap_header.c \
	source/Security/PANA/pana_header.c \
	source/Security/PANA/pana_server.c \
	source/Security/TLS/tls_lib.c \
	source/Security/TLS/tls_ccm_crypt.c \
	source/Service_Libs/CCM_lib/ccm_security.c \
	source/Service_Libs/fhss/fhss_channel.c \
	source/Service_Libs/fhss/fhss_configuration_interface.c \
	source/Service_Libs/fhss/fhss_statistics.c \
	source/Service_Libs/fhss/fhss.c \
	source/Service_Libs/fhss/fhss_ws.c \
	source/Service_Libs/fhss/fhss_ws_empty_functions.c \
	source/Service_Libs/fhss/fhss_common.c \
	source/Service_Libs/fhss/channel_functions.c \
	source/Service_Libs/fhss/channel_list.c \
	source/Service_Libs/fhss/fhss_test_api.c \
	source/Service_Libs/fnv_hash/fnv_hash.c \
	source/Service_Libs/hmac/hmac_md.c \
	source/Service_Libs/ieee_802_11/ieee_802_11.c \
	source/Service_Libs/nist_aes_kw/nist_aes_kw.c \
	source/Service_Libs/mac_neighbor_table/mac_neighbor_table.c \
	source/Service_Libs/mle_service/mle_service.c \
	source/Service_Libs/mle_service/mle_service_buffer.c \
	source/Service_Libs/mle_service/mle_service_frame_counter_table.c \
	source/Service_Libs/mle_service/mle_service_interface.c \
	source/Service_Libs/mle_service/mle_service_security.c \
	source/Service_Libs/blacklist/blacklist.c \
	source/Service_Libs/etx/etx.c \
	source/Service_Libs/Neighbor_cache/neighbor_cache.c \
	source/Service_Libs/nd_proxy/nd_proxy.c \
	source/Service_Libs/load_balance/load_balance.c \
	source/Service_Libs/SHA256_Lib/shalib.c \
	source/Service_Libs/SHA256_Lib/ns_sha256.c \
	source/Service_Libs/Trickle/trickle.c \
	source/Service_Libs/whiteboard/whiteboard.c \
	source/Service_Libs/pan_blacklist/pan_blacklist.c \
	source/Service_Libs/random_early_detection/random_early_detection.c \
	source/6LoWPAN/Thread/thread_management_if.c \
	source/6LoWPAN/Thread/thread_management_api.c \
	source/6LoWPAN/Thread/thread_commissioning_api.c \
	source/6LoWPAN/Thread/thread_border_router_api.c \
	source/6LoWPAN/Thread/thread_bbr_api.c \
	source/6LoWPAN/Thread/thread_test_api.c \
	source/6LoWPAN/Thread/thread_meshcop_lib.c \
	source/6LoWPAN/Thread/thread_common.c \
	source/6LoWPAN/Thread/thread_joiner_application.c \
	source/6LoWPAN/Thread/thread_leader_service.c \
	source/6LoWPAN/Thread/thread_neighbor_class.c \
	source/6LoWPAN/Thread/thread_management_server.c \
	source/6LoWPAN/Thread/thread_management_client.c \
	source/6LoWPAN/Thread/thread_network_synch.c \
	source/6LoWPAN/Thread/thread_bootstrap.c \
	source/6LoWPAN/Thread/thread_dhcpv6_server.c \
	source/6LoWPAN/Thread/thread_host_bootstrap.c \
	source/6LoWPAN/Thread/thread_router_bootstrap.c \
	source/6LoWPAN/Thread/thread_discovery.c \
	source/6LoWPAN/Thread/thread_commissioning_if.c \
	source/6LoWPAN/Thread/thread_bbr_commercial.c \
	source/6LoWPAN/Thread/thread_net_config_api.c \
	source/6LoWPAN/Thread/thread_network_data_lib.c \
	source/6LoWPAN/Thread/thread_network_data_storage.c \
	source/6LoWPAN/Thread/thread_nd.c \
	source/6LoWPAN/Thread/thread_diagnostic.c \
	source/6LoWPAN/Thread/thread_resolution_client.c \
	source/6LoWPAN/Thread/thread_resolution_server.c \
	source/6LoWPAN/Thread/thread_routing.c \
	source/6LoWPAN/Thread/thread_mdns.c \
	source/6LoWPAN/Thread/thread_beacon.c \
	source/6LoWPAN/Thread/thread_mle_message_handler.c \
	source/6LoWPAN/Thread/thread_lowpower_api.c \
	source/6LoWPAN/Thread/thread_lowpower_private_api.c \
	source/6LoWPAN/Thread/thread_nvm_store.c \
	source/6LoWPAN/Thread/thread_ccm.c \
	source/dhcpv6_server/dhcpv6_server_service.c \
	source/dhcpv6_client/dhcpv6_client_service.c \
	source/libDHCPv6/dhcp_service_api.c \
	source/libDHCPv6/libDHCPv6.c \
	source/libDHCPv6/libDHCPv6_vendordata.c \
	source/libDHCPv6/libDHCPv6_server.c \
	source/Service_Libs/utils/ns_crc.c \
	source/Service_Libs/utils/isqrt.c \
	source/Service_Libs/utils/ns_file_system.c \
	source/Service_Libs/utils/ns_time.c \
	source/Service_Libs/utils/ns_conf.c \
	source/Service_Libs/mdns/ns_mdns_api.c \
	source/Service_Libs/mdns/ns_fnet_port.c \
	source/Service_Libs/mdns/ns_fnet_events.c \
	source/Service_Libs/mdns/fnet/fnet_stack/services/mdns/fnet_mdns.c \
	source/Service_Libs/mdns/fnet/fnet_stack/services/poll/fnet_poll.c \
	source/Service_Libs/mdns/fnet/fnet_stack/stack/fnet_stdlib.c \
	source/Service_Libs/CCM_lib/mbedOS/aes_mbedtls_adapter.c \


#LAST ONE(S) EXPERIMENTAL (aes_mbedtls_adapter.c last real)

