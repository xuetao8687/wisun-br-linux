/*
 * Copyright (c) 2014-2015 ARM Limited. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef COMMON_FUNCTIONS_H_
#define COMMON_FUNCTIONS_H_
#include <stdint.h>
#include <stdbool.h>

/*
 * Count leading zeros in a byte
 *
 * \param value byte to inspect
 *
 * \return number of leading zeros in byte (0-8)
 */
static inline uint_fast8_t common_count_leading_zeros_8(uint8_t value)
{
    return value ? __builtin_clz((unsigned int) value << 24) : 8;
}

/*
 * Compare 8-bit serial numbers
 *
 * Compare two 8-bit serial numbers, according to RFC 1982 Serial Number
 * Arithmetic.
 *
 * \param s1 first serial number
 * \param s2 second serial number
 *
 * \return true if s1 > s2
 * \return false if s1 <= s2, or the comparison is undefined
 */
static inline bool common_serial_number_greater_8(uint8_t s1, uint8_t s2)
{
    return (s1 > s2 && s1 - s2 < UINT8_C(0x80)) || (s1 < s2 && s2 - s1 > UINT8_C(0x80));
}

/*
 * Compare 16-bit serial numbers
 *
 * Compare two 16-bit serial numbers, according to RFC 1982 Serial Number
 * Arithmetic.
 *
 * \param s1 first serial number
 * \param s2 second serial number
 *
 * \return true if s1 > s2
 * \return false if s1 <= s2, or the comparison is undefined
 */
static inline bool common_serial_number_greater_16(uint16_t s1, uint16_t s2)
{
    return (s1 > s2 && s1 - s2 < UINT16_C(0x8000)) || (s1 < s2 && s2 - s1 > UINT16_C(0x8000));
}

/*
 * Compare 32-bit serial numbers
 *
 * Compare two 32-bit serial numbers, according to RFC 1982 Serial Number
 * Arithmetic.
 *
 * \param s1 first serial number
 * \param s2 second serial number
 *
 * \return true if s1 > s2
 * \return false if s1 <= s2, or the comparison is undefined
 */
static inline bool common_serial_number_greater_32(uint32_t s1, uint32_t s2)
{
    return (s1 > s2 && s1 - s2 < UINT32_C(0x80000000)) || (s1 < s2 && s2 - s1 > UINT32_C(0x80000000));
}

#endif
