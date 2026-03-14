#ifndef _CTESTS_MAIN_H
#define _CTESTS_MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#define TestFuncState_enable  1
#define TestFuncState_disable 0

extern char test_format_buffer[100000];
extern char test_temp_buffer[100000];

typedef bool (*const testfunc_type)(void);

typedef struct
{
    const char *name;
    testfunc_type func;
    const int state;
} TestFunc;

typedef struct Test
{
    const char *file_name;
    int (*const init_func)(void);
    const TestFunc *test_funcs;
    int (*const end_func)(void);
} Test;

#define test_start()
#define test_end() return true
#define assert_equal(a, b) \
    do \
    { \
        if (a != b) \
        { \
            sprintf(test_temp_buffer, "in line %u assert_equal: ", __LINE__); \
            strcat(test_format_buffer, test_temp_buffer); \
            print(a); \
            strcat(test_format_buffer, " is not "); \
            print(b); \
            return false; \
        } \
    } while (0)

#define assert_string_equal(a, b) \
    do \
    { \
        if (strcmp(a, b)) \
        { \
            sprintf(test_temp_buffer, "in line %u assert_string_equal: `", __LINE__); \
            strcat(test_format_buffer, test_temp_buffer); \
            strcat(test_format_buffer, a); \
            strcat(test_format_buffer, "` is not `"); \
            strcat(test_format_buffer, b); \
            strcat(test_format_buffer, "`"); \
            return false; \
        } \
    } while (0)

static int _ctest_sprintf(int s, ...)
{
    va_list args;
    va_start(args, s);
    switch (s)
    {
    case 'b': return sprintf(test_temp_buffer, va_arg(args, int) ? "true" : "false");    
    case 'i': return sprintf(test_temp_buffer, "%d",                   va_arg(args, int));                
    case 'u': return sprintf(test_temp_buffer, "%u",                   va_arg(args, unsigned));           
    case 'L': return sprintf(test_temp_buffer, "%lld",                 va_arg(args, long long));          
    case 'K': return sprintf(test_temp_buffer, "%llu",                 va_arg(args, unsigned long long)); 
    case 'l': return sprintf(test_temp_buffer, "%ld",                  va_arg(args, long));               
    case 'k': return sprintf(test_temp_buffer, "%lu",                  va_arg(args, unsigned long));      
    case 'h': return sprintf(test_temp_buffer, "%hd",  (short)         va_arg(args, int));              
    case 'H': return sprintf(test_temp_buffer, "%hu",  (unsigned short)va_arg(args, int));     
    case 'c': return sprintf(test_temp_buffer, "%c",   (char)          va_arg(args, int));      
    case 'a': return sprintf(test_temp_buffer, "%hhd", (signed char)   va_arg(args, int));        
    case 'A': return sprintf(test_temp_buffer, "%hhu", (unsigned char) va_arg(args, int));      
    case 's': return sprintf(test_temp_buffer, "%s",                   va_arg(args, const char *));       
    case 'f': return sprintf(test_temp_buffer, "%f",   (float)         va_arg(args, double));              
    case 'd': return sprintf(test_temp_buffer, "%lf",                  va_arg(args, double));             
    case 'p': return sprintf(test_temp_buffer, "%p",                   va_arg(args, const void *));       
    case '?': return sprintf(test_temp_buffer, "unknown type");
    }
    va_end(args);
    return 0;
}

#define print(a) do { \
    strcat(test_format_buffer, #a "("); \
    _Generic((a), \
        bool:      _ctest_sprintf('b', a), \
        int:       _ctest_sprintf('i', a),  unsigned:           _ctest_sprintf('u', a), \
        long long: _ctest_sprintf('L', a),  unsigned long long: _ctest_sprintf('K', a), \
        long:      _ctest_sprintf('l', a),  unsigned long:      _ctest_sprintf('k', a), \
        short:     _ctest_sprintf('h', a),  unsigned short:     _ctest_sprintf('H', a), \
        char:      _ctest_sprintf('c', a),  unsigned char:      _ctest_sprintf('a', a),  signed char: _ctest_sprintf('A', a), \
        char *:    _ctest_sprintf('s', a),  const char *:       _ctest_sprintf('s', a), \
        float:     _ctest_sprintf('f', a),  double:             _ctest_sprintf('d', a), \
        void *:    _ctest_sprintf('p', a),  const void *:       _ctest_sprintf('p', a), \
        default:   _ctest_sprintf('?', a) \
    ); \
    strcat(test_format_buffer, test_temp_buffer); \
    strcat(test_format_buffer, ")"); \
} while (0)

extern const Test c_powerobject;

#endif /* _CTESTS_MAIN_H */
