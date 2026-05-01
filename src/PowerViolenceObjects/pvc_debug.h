#ifndef _debug
#define _debug

#include <stdio.h>

#define _DEBUG_STR_HELPER(x) #x
#define _DEBUG_STR(x) _DEBUG_STR_HELPER(x)

#define deprint(a) printf(_Generic((a),                     \
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
    default:            "Line " _DEBUG_STR(__LINE__) ": unknown type: Please goto src/PowerViolenceObjects/pvc_debug.h\n" \
), a)

#endif /* _debug */
