#ifndef _PVC_DEFINES_H
#define _PVC_DEFINES_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#if (defined(__GNUC__) && __GNUC__ >= 5) || \
    (defined(__clang__) && __has_builtin(__builtin_add_overflow)) || \
    (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 1900)
    #define HAS_BUILTIN_ADD_OVERFLOW 1
#else
    #define HAS_BUILTIN_ADD_OVERFLOW 0
#endif

#if HAS_BUILTIN_ADD_OVERFLOW
    #define addi64_overflow __builtin_add_overflow
    #define addu64_overflow __builtin_add_overflow
#else
    static inline bool addi64_overflow(int64_t a, int64_t b, int64_t *res)
    {
        if ((b > 0 && a > INT64_MAX - b) || (b < 0 && a < INT64_MIN - b)) return true;
        *res = a + b;
        return false;
    }
    static inline bool addu64_overflow(uint64_t a, uint64_t b, uint64_t *res)
    {
        *res = a + b;
        return *res < a;
    }
#endif

#define _debug

#include "pvc_defines.h"

extern const char *quick_float[];
extern const int quick_float_len[];
extern const char *quick_float_1[];
extern const bool quick_float_co1[];
extern const char *quick_float_2[];
extern const bool quick_float_co2[];
extern const char *quick_float_3[];
extern const char *quick_float_4[];
extern const char *quick_float_5[];
extern const char *quick_float_6[];
extern const char *quick_float_7[];
extern const char *quick_float_8[];
extern const char *const *const quick_floats[];
extern const char *quick_float_e1[];
extern const char *quick_float_e2[];
extern const char *quick_float_e3[];
extern const char *quick_float_e4[];
extern const char *quick_float_e5[];
extern const char *quick_float_e6[];
extern const char *quick_float_e7[];
extern const char *quick_float_e8[];
extern const int quick_float_e[];
extern const char *const *const quick_float_es[];

extern const char *pvc_PV_119p8_max;
extern const char *pvc_PV_55p8_max;

#endif /* _PVC_DEFINES_H */
