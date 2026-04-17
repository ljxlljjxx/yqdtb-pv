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
        *res = a + b;
        if (a > 0 && b > 0 && *res < 0)  return true;
        if (a < 0 && b < 0 && *res >= 0) return true;
        return false;
    }
    static inline bool addu64_overflow(uint64_t a, uint64_t b, uint64_t *res)
    {
        *res = a + b;
        return *res < a;
    }
#endif
    

typedef struct pvc_PV_119p8
{
    int64_t  _1;
    uint64_t _2;
} pvc_PV_119p8;

bool pvc_PV_119p8_add(pvc_PV_119p8 *a, pvc_PV_119p8 *b, pvc_PV_119p8 *restrict res);
bool pvc_PV_119p8_neg(pvc_PV_119p8 *a);
char *pvc_PV_119p8_tostring(pvc_PV_119p8 *a);
int pvc_PV_119p8_format(char *restrict buffer, const char *restrict format, pvc_PV_119p8 *restrict a, ...);
void pvc_PV_119p8_print(pvc_PV_119p8 *a);
