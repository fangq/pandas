/*
 * UBJSON packing routine template
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

#if defined(__LITTLE_ENDIAN__)
#define TAKE8_8(d)  ((uint8_t*)&d)[0]
#define TAKE8_16(d) ((uint8_t*)&d)[0]
#define TAKE8_32(d) ((uint8_t*)&d)[0]
#define TAKE8_64(d) ((uint8_t*)&d)[0]
#elif defined(__BIG_ENDIAN__)
#define TAKE8_8(d)  ((uint8_t*)&d)[0]
#define TAKE8_16(d) ((uint8_t*)&d)[1]
#define TAKE8_32(d) ((uint8_t*)&d)[3]
#define TAKE8_64(d) ((uint8_t*)&d)[7]
#endif

#ifndef ubjson_pack_append_buffer
#error ubjson_pack_append_buffer callback is not defined
#endif


/*
 * Integer
 */

#define ubjson_pack_real_uint8(x, d) \
do { \
        /* unsigned 8 */ \
        unsigned char buf[2] = {'U', TAKE8_8(d)}; \
        ubjson_pack_append_buffer(x, buf, 2); \
} while(0)

#define ubjson_pack_real_uint16(x, d) \
do { \
    if(d < (1<<8)) { \
        /* unsigned 8 */ \
        unsigned char buf[2] = {'U', TAKE8_16(d)}; \
        ubjson_pack_append_buffer(x, buf, 2); \
    } else { \
        /* unsigned 16 */ \
        unsigned char buf[3]; \
        buf[0] = 'I'; _ubjson_store16(&buf[1], (uint16_t)d); \
        ubjson_pack_append_buffer(x, buf, 3); \
    } \
} while(0)

#define ubjson_pack_real_uint32(x, d) \
do { \
    if(d < (1<<8)) { \
            /* unsigned 8 */ \
            unsigned char buf[2] = {'U', TAKE8_32(d)}; \
            ubjson_pack_append_buffer(x, buf, 2); \
    } else { \
        if(d < (1<<16)) { \
            /* unsigned 16 */ \
            unsigned char buf[3]; \
            buf[0] = 'I'; _ubjson_store16(&buf[1], (uint16_t)d); \
            ubjson_pack_append_buffer(x, buf, 3); \
        } else { \
            /* unsigned 32 */ \
            unsigned char buf[5]; \
            buf[0] = 'l'; _ubjson_store32(&buf[1], (uint32_t)d); \
            ubjson_pack_append_buffer(x, buf, 5); \
        } \
    } \
} while(0)

#define ubjson_pack_real_uint64(x, d) \
do { \
    if(d < (1ULL<<8)) { \
            /* unsigned 8 */ \
            unsigned char buf[2] = {'U', TAKE8_64(d)}; \
            ubjson_pack_append_buffer(x, buf, 2); \
    } else { \
        if(d < (1ULL<<16)) { \
            /* unsigned 16 */ \
            unsigned char buf[3]; \
            buf[0] = 'i'; _ubjson_store16(&buf[1], (uint16_t)d); \
            ubjson_pack_append_buffer(x, buf, 3); \
        } else if(d < (1ULL<<32)) { \
            /* unsigned 32 */ \
            unsigned char buf[5]; \
            buf[0] = 'l'; _ubjson_store32(&buf[1], (uint32_t)d); \
            ubjson_pack_append_buffer(x, buf, 5); \
        } else { \
            /* unsigned 64 */ \
            unsigned char buf[9]; \
            buf[0] = 'L'; _ubjson_store64(&buf[1], d); \
            ubjson_pack_append_buffer(x, buf, 9); \
        } \
    } \
} while(0)

#define ubjson_pack_real_int8(x, d) \
do { \
        /* signed 8 */ \
        unsigned char buf[2] = {'i', TAKE8_8(d)}; \
        ubjson_pack_append_buffer(x, buf, 2); \
} while(0)

#define ubjson_pack_real_int16(x, d) \
do { \
    if(d < -(1<<5)) { \
        if(d < -(1<<7)) { \
            /* signed 16 */ \
            unsigned char buf[3]; \
            buf[0] = 'I'; _ubjson_store16(&buf[1], (int16_t)d); \
            ubjson_pack_append_buffer(x, buf, 3); \
        } else { \
            /* signed 8 */ \
            unsigned char buf[2] = {'i', TAKE8_16(d)}; \
            ubjson_pack_append_buffer(x, buf, 2); \
        } \
    } else { \
        if(d < (1<<8)) { \
            /* unsigned 8 */ \
            unsigned char buf[2] = {'U', TAKE8_16(d)}; \
            ubjson_pack_append_buffer(x, buf, 2); \
        } else { \
            /* unsigned 16 */ \
            unsigned char buf[3]; \
            buf[0] = 'I'; _ubjson_store16(&buf[1], (uint16_t)d); \
            ubjson_pack_append_buffer(x, buf, 3); \
        } \
    } \
} while(0)

#define ubjson_pack_real_int32(x, d) \
do { \
    if(d < -(1<<5)) { \
        if(d < -(1<<15)) { \
            /* signed 32 */ \
            unsigned char buf[5]; \
            buf[0] = 'l'; _ubjson_store32(&buf[1], (int32_t)d); \
            ubjson_pack_append_buffer(x, buf, 5); \
        } else if(d < -(1<<7)) { \
            /* signed 16 */ \
            unsigned char buf[3]; \
            buf[0] = 'I'; _ubjson_store16(&buf[1], (int16_t)d); \
            ubjson_pack_append_buffer(x, buf, 3); \
        } else { \
            /* signed 8 */ \
            unsigned char buf[2] = {'i', TAKE8_32(d)}; \
            ubjson_pack_append_buffer(x, buf, 2); \
        } \
    } else { \
        if(d < (1<<8)) { \
            /* unsigned 8 */ \
            unsigned char buf[2] = {'U', TAKE8_32(d)}; \
            ubjson_pack_append_buffer(x, buf, 2); \
        } else if(d < (1<<16)) { \
            /* unsigned 16 */ \
            unsigned char buf[3]; \
            buf[0] = 'I'; _ubjson_store16(&buf[1], (uint16_t)d); \
            ubjson_pack_append_buffer(x, buf, 3); \
        } else { \
            /* unsigned 32 */ \
            unsigned char buf[5]; \
            buf[0] = 'l'; _ubjson_store32(&buf[1], (uint32_t)d); \
            ubjson_pack_append_buffer(x, buf, 5); \
        } \
    } \
} while(0)

#define ubjson_pack_real_int64(x, d) \
do { \
    if(d < -(1LL<<5)) { \
        if(d < -(1LL<<15)) { \
            if(d < -(1LL<<31)) { \
                /* signed 64 */ \
                unsigned char buf[9]; \
                buf[0] = 'L'; _ubjson_store64(&buf[1], d); \
                ubjson_pack_append_buffer(x, buf, 9); \
            } else { \
                /* signed 32 */ \
                unsigned char buf[5]; \
                buf[0] = 'l'; _ubjson_store32(&buf[1], (int32_t)d); \
                ubjson_pack_append_buffer(x, buf, 5); \
            } \
        } else { \
            if(d < -(1<<7)) { \
                /* signed 16 */ \
                unsigned char buf[3]; \
                buf[0] = 'I'; _ubjson_store16(&buf[1], (int16_t)d); \
                ubjson_pack_append_buffer(x, buf, 3); \
            } else { \
                /* signed 8 */ \
                unsigned char buf[2] = {'i', TAKE8_64(d)}; \
                ubjson_pack_append_buffer(x, buf, 2); \
            } \
        } \
    } else { \
        if(d < (1LL<<16)) { \
            if(d < (1<<8)) { \
                /* unsigned 8 */ \
                unsigned char buf[2] = {'U', TAKE8_64(d)}; \
                ubjson_pack_append_buffer(x, buf, 2); \
            } else { \
                /* unsigned 16 */ \
                unsigned char buf[3]; \
                buf[0] = 'I'; _ubjson_store16(&buf[1], (uint16_t)d); \
                ubjson_pack_append_buffer(x, buf, 3); \
            } \
        } else { \
            if(d < (1LL<<32)) { \
                /* unsigned 32 */ \
                unsigned char buf[5]; \
                buf[0] = 'l'; _ubjson_store32(&buf[1], (uint32_t)d); \
                ubjson_pack_append_buffer(x, buf, 5); \
            } else { \
                /* unsigned 64 */ \
                unsigned char buf[9]; \
                buf[0] = 'L'; _ubjson_store64(&buf[1], d); \
                ubjson_pack_append_buffer(x, buf, 9); \
            } \
        } \
    } \
} while(0)


static inline int ubjson_pack_uint8(ubjson_packer* x, uint8_t d)
{
    ubjson_pack_real_uint8(x, d);
}

static inline int ubjson_pack_uint16(ubjson_packer* x, uint16_t d)
{
    ubjson_pack_real_uint16(x, d);
}

static inline int ubjson_pack_uint32(ubjson_packer* x, uint32_t d)
{
    ubjson_pack_real_uint32(x, d);
}

static inline int ubjson_pack_uint64(ubjson_packer* x, uint64_t d)
{
    ubjson_pack_real_uint64(x, d);
}

static inline int ubjson_pack_int8(ubjson_packer* x, int8_t d)
{
    ubjson_pack_real_int8(x, d);
}

static inline int ubjson_pack_int16(ubjson_packer* x, int16_t d)
{
    ubjson_pack_real_int16(x, d);
}

static inline int ubjson_pack_int32(ubjson_packer* x, int32_t d)
{
    ubjson_pack_real_int32(x, d);
}

static inline int ubjson_pack_int64(ubjson_packer* x, int64_t d)
{
    ubjson_pack_real_int64(x, d);
}


//#ifdef ubjson_pack_inline_func_cint

static inline int ubjson_pack_short(ubjson_packer* x, short d)
{
#if defined(SIZEOF_SHORT)
#if SIZEOF_SHORT == 2
    ubjson_pack_real_int16(x, d);
#elif SIZEOF_SHORT == 4
    ubjson_pack_real_int32(x, d);
#else
    ubjson_pack_real_int64(x, d);
#endif

#elif defined(SHRT_MAX)
#if SHRT_MAX == 0x7fff
    ubjson_pack_real_int16(x, d);
#elif SHRT_MAX == 0x7fffffff
    ubjson_pack_real_int32(x, d);
#else
    ubjson_pack_real_int64(x, d);
#endif

#else
if(sizeof(short) == 2) {
    ubjson_pack_real_int16(x, d);
} else if(sizeof(short) == 4) {
    ubjson_pack_real_int32(x, d);
} else {
    ubjson_pack_real_int64(x, d);
}
#endif
}

static inline int ubjson_pack_int(ubjson_packer* x, int d)
{
#if defined(SIZEOF_INT)
#if SIZEOF_INT == 2
    ubjson_pack_real_int16(x, d);
#elif SIZEOF_INT == 4
    ubjson_pack_real_int32(x, d);
#else
    ubjson_pack_real_int64(x, d);
#endif

#elif defined(INT_MAX)
#if INT_MAX == 0x7fff
    ubjson_pack_real_int16(x, d);
#elif INT_MAX == 0x7fffffff
    ubjson_pack_real_int32(x, d);
#else
    ubjson_pack_real_int64(x, d);
#endif

#else
if(sizeof(int) == 2) {
    ubjson_pack_real_int16(x, d);
} else if(sizeof(int) == 4) {
    ubjson_pack_real_int32(x, d);
} else {
    ubjson_pack_real_int64(x, d);
}
#endif
}

static inline int ubjson_pack_long(ubjson_packer* x, long d)
{
#if defined(SIZEOF_LONG)
#if SIZEOF_LONG == 2
    ubjson_pack_real_int16(x, d);
#elif SIZEOF_LONG == 4
    ubjson_pack_real_int32(x, d);
#else
    ubjson_pack_real_int64(x, d);
#endif

#elif defined(LONG_MAX)
#if LONG_MAX == 0x7fffL
    ubjson_pack_real_int16(x, d);
#elif LONG_MAX == 0x7fffffffL
    ubjson_pack_real_int32(x, d);
#else
    ubjson_pack_real_int64(x, d);
#endif

#else
if(sizeof(long) == 2) {
    ubjson_pack_real_int16(x, d);
} else if(sizeof(long) == 4) {
    ubjson_pack_real_int32(x, d);
} else {
    ubjson_pack_real_int64(x, d);
}
#endif
}

static inline int ubjson_pack_long_long(ubjson_packer* x, long long d)
{
#if defined(SIZEOF_LONG_LONG)
#if SIZEOF_LONG_LONG == 2
    ubjson_pack_real_int16(x, d);
#elif SIZEOF_LONG_LONG == 4
    ubjson_pack_real_int32(x, d);
#else
    ubjson_pack_real_int64(x, d);
#endif

#elif defined(LLONG_MAX)
#if LLONG_MAX == 0x7fffL
    ubjson_pack_real_int16(x, d);
#elif LLONG_MAX == 0x7fffffffL
    ubjson_pack_real_int32(x, d);
#else
    ubjson_pack_real_int64(x, d);
#endif

#else
if(sizeof(long long) == 2) {
    ubjson_pack_real_int16(x, d);
} else if(sizeof(long long) == 4) {
    ubjson_pack_real_int32(x, d);
} else {
    ubjson_pack_real_int64(x, d);
}
#endif
}

static inline int ubjson_pack_unsigned_short(ubjson_packer* x, unsigned short d)
{
#if defined(SIZEOF_SHORT)
#if SIZEOF_SHORT == 2
    ubjson_pack_real_uint16(x, d);
#elif SIZEOF_SHORT == 4
    ubjson_pack_real_uint32(x, d);
#else
    ubjson_pack_real_uint64(x, d);
#endif

#elif defined(USHRT_MAX)
#if USHRT_MAX == 0xffffU
    ubjson_pack_real_uint16(x, d);
#elif USHRT_MAX == 0xffffffffU
    ubjson_pack_real_uint32(x, d);
#else
    ubjson_pack_real_uint64(x, d);
#endif

#else
if(sizeof(unsigned short) == 2) {
    ubjson_pack_real_uint16(x, d);
} else if(sizeof(unsigned short) == 4) {
    ubjson_pack_real_uint32(x, d);
} else {
    ubjson_pack_real_uint64(x, d);
}
#endif
}

static inline int ubjson_pack_unsigned_int(ubjson_packer* x, unsigned int d)
{
#if defined(SIZEOF_INT)
#if SIZEOF_INT == 2
    ubjson_pack_real_uint16(x, d);
#elif SIZEOF_INT == 4
    ubjson_pack_real_uint32(x, d);
#else
    ubjson_pack_real_uint64(x, d);
#endif

#elif defined(UINT_MAX)
#if UINT_MAX == 0xffffU
    ubjson_pack_real_uint16(x, d);
#elif UINT_MAX == 0xffffffffU
    ubjson_pack_real_uint32(x, d);
#else
    ubjson_pack_real_uint64(x, d);
#endif

#else
if(sizeof(unsigned int) == 2) {
    ubjson_pack_real_uint16(x, d);
} else if(sizeof(unsigned int) == 4) {
    ubjson_pack_real_uint32(x, d);
} else {
    ubjson_pack_real_uint64(x, d);
}
#endif
}

static inline int ubjson_pack_unsigned_long(ubjson_packer* x, unsigned long d)
{
#if defined(SIZEOF_LONG)
#if SIZEOF_LONG == 2
    ubjson_pack_real_uint16(x, d);
#elif SIZEOF_LONG == 4
    ubjson_pack_real_uint32(x, d);
#else
    ubjson_pack_real_uint64(x, d);
#endif

#elif defined(ULONG_MAX)
#if ULONG_MAX == 0xffffUL
    ubjson_pack_real_uint16(x, d);
#elif ULONG_MAX == 0xffffffffUL
    ubjson_pack_real_uint32(x, d);
#else
    ubjson_pack_real_uint64(x, d);
#endif

#else
if(sizeof(unsigned long) == 2) {
    ubjson_pack_real_uint16(x, d);
} else if(sizeof(unsigned long) == 4) {
    ubjson_pack_real_uint32(x, d);
} else {
    ubjson_pack_real_uint64(x, d);
}
#endif
}

static inline int ubjson_pack_unsigned_long_long(ubjson_packer* x, unsigned long long d)
{
#if defined(SIZEOF_LONG_LONG)
#if SIZEOF_LONG_LONG == 2
    ubjson_pack_real_uint16(x, d);
#elif SIZEOF_LONG_LONG == 4
    ubjson_pack_real_uint32(x, d);
#else
    ubjson_pack_real_uint64(x, d);
#endif

#elif defined(ULLONG_MAX)
#if ULLONG_MAX == 0xffffUL
    ubjson_pack_real_uint16(x, d);
#elif ULLONG_MAX == 0xffffffffUL
    ubjson_pack_real_uint32(x, d);
#else
    ubjson_pack_real_uint64(x, d);
#endif

#else
if(sizeof(unsigned long long) == 2) {
    ubjson_pack_real_uint16(x, d);
} else if(sizeof(unsigned long long) == 4) {
    ubjson_pack_real_uint32(x, d);
} else {
    ubjson_pack_real_uint64(x, d);
}
#endif
}

//#undef ubjson_pack_inline_func_cint
//#endif



/*
 * Float
 */

static inline int ubjson_pack_float(ubjson_packer* x, float d)
{
    union { float f; uint32_t i; } mem;
    mem.f = d;
    unsigned char buf[5];
    buf[0] = 'd'; _ubjson_store32(&buf[1], mem.i);
    ubjson_pack_append_buffer(x, buf, 5);
}

static inline int ubjson_pack_double(ubjson_packer* x, double d)
{
    union { double f; uint64_t i; } mem;
    mem.f = d;
    unsigned char buf[9];
    buf[0] = 'D';
#if defined(__arm__) && !(__ARM_EABI__) // arm-oabi
    // https://github.com/ubjson/ubjson-perl/pull/1
    mem.i = (mem.i & 0xFFFFFFFFUL) << 32UL | (mem.i >> 32UL);
#endif
    _ubjson_store64(&buf[1], mem.i);
    ubjson_pack_append_buffer(x, buf, 9);
}


/*
 * Nil
 */

static inline int ubjson_pack_nil(ubjson_packer* x)
{
    static const unsigned char d = 'Z';
    ubjson_pack_append_buffer(x, &d, 1);
}


/*
 * Boolean
 */

static inline int ubjson_pack_true(ubjson_packer* x)
{
    static const unsigned char d = 'T';
    ubjson_pack_append_buffer(x, &d, 1);
}

static inline int ubjson_pack_false(ubjson_packer* x)
{
    static const unsigned char d = 'F';
    ubjson_pack_append_buffer(x, &d, 1);
}


/*
 * Array
 */

static inline int ubjson_pack_array(ubjson_packer* x, unsigned int n)
{
        unsigned char buf[6]={'[','#'};
        _ubjson_store32(&buf[1], (uint32_t)n);
        ubjson_pack_append_buffer(x, buf, 6);
}


/*
 * Map
 */

static inline int ubjson_pack_map(ubjson_packer* x, unsigned int n)
{
        unsigned char buf[6]={'{','#'};
        _ubjson_store32(&buf[1], (uint32_t)n);
        ubjson_pack_append_buffer(x, buf, 5);
}


/*
 * String
 */

static inline int ubjson_pack_raw(ubjson_packer* x, size_t l)
{
    if (x->use_bin_type && l < 256) {  // str8 is new format introduced with bin.
        unsigned char buf[] = {'S','U', (uint8_t)l};
        ubjson_pack_append_buffer(x, buf, 3);
    } else if (l < 65536) {
        unsigned char buf[4];
        buf[0] = 'S'; ubjson_pack_real_uint16(&buf[1], (uint16_t)l);
        ubjson_pack_append_buffer(x, buf, 4);
    } else if (l < 0xffffffffU) {
        unsigned char buf[6];
        buf[0] = 'S'; ubjson_pack_real_uint32(&buf[1], (uint32_t)l);
        ubjson_pack_append_buffer(x, buf, 6);
    }else {
        unsigned char buf[10];
        buf[0] = 'S'; ubjson_pack_real_uint64(&buf[1], (uint64_t)l);
        ubjson_pack_append_buffer(x, buf, 10);
    }
}

/*
 * bin
 */
static inline int ubjson_pack_bin(ubjson_packer *x, size_t l)
{
    if (!x->use_bin_type) {
        return ubjson_pack_raw(x, l);
    }
    if (l < 256) {
        unsigned char buf[] = {'H', 'U', (unsigned char)l};
        ubjson_pack_append_buffer(x, buf, 3);
    } else if (l < 65536) {
        unsigned char buf[4] = {'H','I'};
        _ubjson_store16(&buf[2], (uint16_t)l);
        ubjson_pack_append_buffer(x, buf, 4);
    } else if (l < 0xffffffffU) {
        unsigned char buf[5] = {'H','l'};
        _ubjson_store32(&buf[2], (uint32_t)l);
        ubjson_pack_append_buffer(x, buf, 6);
    } else {
        unsigned char buf[10] = {'H','L'};
        _ubjson_store64(&buf[2], (uint64_t)l);
        ubjson_pack_append_buffer(x, buf, 10);
    }
}

static inline int ubjson_pack_raw_body(ubjson_packer* x, const void* b, size_t l)
{
    if (l > 0) ubjson_pack_append_buffer(x, (const unsigned char*)b, l);
    return 0;
}


#undef ubjson_pack_append_buffer

#undef TAKE8_8
#undef TAKE8_16
#undef TAKE8_32
#undef TAKE8_64

#undef ubjson_pack_real_uint8
#undef ubjson_pack_real_uint16
#undef ubjson_pack_real_uint32
#undef ubjson_pack_real_uint64
#undef ubjson_pack_real_int8
#undef ubjson_pack_real_int16
#undef ubjson_pack_real_int32
#undef ubjson_pack_real_int64
