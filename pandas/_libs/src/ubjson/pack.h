/*
 * UBJSON for Python packing routine
 *
 * Copyright (C) 2009 Naoki INADA
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

#include <stddef.h>
#include <stdlib.h>
#include "sysdep.h"
#include <limits.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER) && (_MSC_VER < 1900)
#define inline __inline
#endif

typedef struct ubjson_packer {
    char *buf;
    size_t length;
    size_t buf_size;
    bool use_bin_type;
} ubjson_packer;

typedef struct Packer Packer;

static inline int ubjson_pack_int(ubjson_packer* pk, int d);
static inline int ubjson_pack_long(ubjson_packer* pk, long d);
static inline int ubjson_pack_long_long(ubjson_packer* pk, long long d);
static inline int ubjson_pack_unsigned_short(ubjson_packer* pk, unsigned short d);
static inline int ubjson_pack_unsigned_int(ubjson_packer* pk, unsigned int d);
static inline int ubjson_pack_unsigned_long(ubjson_packer* pk, unsigned long d);
//static inline int ubjson_pack_unsigned_long_long(ubjson_packer* pk, unsigned long long d);

static inline int ubjson_pack_uint8(ubjson_packer* pk, uint8_t d);
static inline int ubjson_pack_uint16(ubjson_packer* pk, uint16_t d);
static inline int ubjson_pack_uint32(ubjson_packer* pk, uint32_t d);
static inline int ubjson_pack_uint64(ubjson_packer* pk, uint64_t d);
static inline int ubjson_pack_int8(ubjson_packer* pk, int8_t d);
static inline int ubjson_pack_int16(ubjson_packer* pk, int16_t d);
static inline int ubjson_pack_int32(ubjson_packer* pk, int32_t d);
static inline int ubjson_pack_int64(ubjson_packer* pk, int64_t d);

static inline int ubjson_pack_float(ubjson_packer* pk, float d);
static inline int ubjson_pack_double(ubjson_packer* pk, double d);

static inline int ubjson_pack_nil(ubjson_packer* pk);
static inline int ubjson_pack_true(ubjson_packer* pk);
static inline int ubjson_pack_false(ubjson_packer* pk);

static inline int ubjson_pack_array(ubjson_packer* pk, unsigned int n);

static inline int ubjson_pack_map(ubjson_packer* pk, unsigned int n);

static inline int ubjson_pack_raw(ubjson_packer* pk, size_t l);
static inline int ubjson_pack_bin(ubjson_packer* pk, size_t l);
static inline int ubjson_pack_raw_body(ubjson_packer* pk, const void* b, size_t l);

static inline int ubjson_pack_ext(ubjson_packer* pk, char typecode, size_t l);

static inline int ubjson_pack_write(ubjson_packer* pk, const char *data, size_t l)
{
    char* buf = pk->buf;
    size_t bs = pk->buf_size;
    size_t len = pk->length;

    if (len + l > bs) {
        bs = (len + l) * 2;
        buf = (char*)realloc(buf, bs);
        if (!buf) return -1;
    }
    memcpy(buf + len, data, l);
    len += l;

    pk->buf = buf;
    pk->buf_size = bs;
    pk->length = len;
    return 0;
}

#define ubjson_pack_append_buffer(user, buf, len) \
        return ubjson_pack_write(user, (const char*)buf, len)

#include "pack_template.h"

#ifdef __cplusplus
}
#endif
