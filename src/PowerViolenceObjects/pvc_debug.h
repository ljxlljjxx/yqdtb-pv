#ifndef _PVC_DEBUG_H
#define _PVC_DEBUG_H

#include <stdio.h>

#define _debug

#define _DEBUG_STR_HELPER(x) #x
#define _DEBUG_STR(x) _DEBUG_STR_HELPER(x)

static FILE *__debug_file;

#define _debug_print(a) fprintf(__debug_file, _Generic((a),                     \
    int:                #a " = %d\n",                       \
    long:               #a " = %ld\n",                      \
    long long:          #a " = %lld\n",                     \
    char:               #a " = %c\n",                       \
    char *:             #a " = %s\n",                       \
    const char *:       #a " = %s\n",                       \
    unsigned:           #a " = %u\n",                       \
    unsigned long:      #a " = %lu\n",                      \
    unsigned long long: #a " = %llu\n",                     \
    double:             #a " = %f\n",                       \
    void *:             #a " = %p\n",                       \
    default:            "Line " _DEBUG_STR(__LINE__) ": unknown type: Please goto src/PowerViolenceObjects/pvc_PVC_DEBUG_H.h\n" \
), a)

#ifdef DEBUG
    #define debug_print(a) _debug_print(a)
    #define debug_printf(format, ...) fprintf(__debug_file, format, ##__VA_ARGS__)
    #define debug_puts(string) do { fputs(string, __debug_file); fputc(10, __debug_file); } while (0)
#else
    #define debug_print(a)
    #define debug_printf(...)
    #define debug_puts(string)
#endif

#endif /* _PVC_DEBUG_H */
