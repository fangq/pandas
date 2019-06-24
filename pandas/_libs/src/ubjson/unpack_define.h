/*
 * UBJSON unpacking routine template
 *
 * Copyright (C) 2008-2010 FURUHASHI Sadayuki
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
#ifndef UBJSON_UNPACK_DEFINE_H__
#define UBJSON_UNPACK_DEFINE_H__

#include "ubjson/sysdep.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef UBJSON_EMBED_STACK_SIZE
#define UBJSON_EMBED_STACK_SIZE 32
#endif


// CS is first byte & 0x1f
typedef enum {
    CS_HEADER            = 'Z',  // nil

    //CS_                = 0x01,
    //CS_                = 'F',  // false
    //CS_                = 'T',  // true

    CS_BIN_32            = 'S',

    CS_FLOAT             = 'd',
    CS_DOUBLE            = 'D',
    CS_UINT_8            = 'U',
    CS_INT_8             = 'i',
    CS_INT_16            = 'I',
    CS_INT_32            = 'l',
    CS_INT_64            = 'L',

    CS_RAW_32            = 'H',
    CS_ARRAY_32          = '[',
    CS_MAP_32            = '{',

    ACS_RAW_VALUE,
    ACS_BIN_VALUE,
    ACS_EXT_VALUE,
} ubjson_unpack_state;


typedef enum {
    CT_ARRAY_ITEM,
    CT_MAP_KEY,
    CT_MAP_VALUE,
} ubjson_container_type;


#ifdef __cplusplus
}
#endif

#endif /* ubjson/unpack_define.h */
