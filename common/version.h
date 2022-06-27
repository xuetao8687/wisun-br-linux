/*
 * Copyright (c) 2021-2022 Silicon Laboratories Inc. (www.silabs.com)
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at [1].  This software is distributed to you in
 * Object Code format and/or Source Code format and is governed by the sections
 * of the MSLA applicable to Object Code, Source Code and Modified Open Source
 * Code. By using this software, you agree to the terms of the MSLA.
 *
 * [1]: https://www.silabs.com/about-us/legal/master-software-license-agreement
 */
#ifndef COMMON_VERSION_H
#define COMMON_VERSION_H

#include <stdint.h>
#include <stdbool.h>
#include "bits.h"

#define VERSION_MASK_MAJOR 0xFF000000
#define VERSION_MASK_MINOR 0x00FFFF00
#define VERSION_MASK_PATCH 0x000000FF

#define VERSION(major, minor, patch) (FIELD_PREP(VERSION_MASK_MAJOR, major) | \
                                      FIELD_PREP(VERSION_MASK_MINOR, minor) | \
                                      FIELD_PREP(VERSION_MASK_PATCH, patch))

static inline bool version_older_than(uint32_t version,
                                      uint8_t major, uint16_t minor, uint8_t patch)
{
    return version < VERSION(major, minor, patch);
}

#endif