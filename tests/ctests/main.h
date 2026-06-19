#ifndef _CTESTS_MAIN_H
#define _CTESTS_MAIN_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#ifdef _WIN32
    #define got_time() (uint64_t)0ULL
#else
    #define got_time() (uint64_t)clock()
#endif

#define TestFuncState_enable  1
#define TestFuncState_disable 0

char test_format_buffer[100000];
char test_temp_buffer[100000];
double ok_time_use, __time_max;

typedef int (*const testfunc_type)(void);

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

#define useful_functest(ans, func, ...) \
    do { \
        uint64_t start, end; \
        start = got_time(); \
        ans = func(__VA_ARGS__); \
        end = got_time(); \
        __used_time += (end - start); \
        __tests_count++; \
    } while (0)

#define useful_functest_noreturnvalue(func, ...) \
    do { \
        uint64_t start, end; \
        start = got_time(); \
        func(__VA_ARGS__); \
        end = got_time(); \
        __used_time += (end - start); \
        __tests_count++; \
    } while (0)

#define test_start(_time_max) __time_max = _time_max; uint64_t __used_time = 0; int __tests_count = 0
#define test_end() if ((double)__used_time * 1000000 > __time_max * CLOCKS_PER_SEC * __tests_count) \
        { \
            sprintf(test_temp_buffer, "    in line %u (%s): TLE: average %.3lfμs > %.0lfμs\n", __LINE__, __func__, (double)__used_time * 1000000 / CLOCKS_PER_SEC / __tests_count, __time_max); \
            strcat(test_format_buffer, test_temp_buffer); \
            return 2; \
        } \
        else \
        { \
            ok_time_use = (double)__used_time * 1000000 / __tests_count / CLOCKS_PER_SEC; \
            return 1; \
        }

#define assert_equal(a, b) \
    do \
    { \
        if (a != b) \
        { \
            sprintf(test_temp_buffer, "    in line %u assert_equal: ", __LINE__); \
            strcat(test_format_buffer, test_temp_buffer); \
            print(a); \
            strcat(test_format_buffer, " is not "); \
            print(b); \
            strcat(test_format_buffer, "\n"); \
            return false; \
        } \
    } while (0)

#define assert_string_equal(a, b) \
    do \
    { \
        if (strcmp(a, b)) \
        { \
            sprintf(test_temp_buffer, "    in line %u assert_string_equal: `", __LINE__); \
            strcat(test_format_buffer, test_temp_buffer); \
            strcat(test_format_buffer, a); \
            strcat(test_format_buffer, "` is not `"); \
            strcat(test_format_buffer, b); \
            strcat(test_format_buffer, "`\n"); \
            return false; \
        } \
    } while (0)

#define assert_string_length_equal(str, len, ans) \
    do \
    { \
        assert_string_equal(str, ans); \
        assert_equal(len, strlen(ans)); \
    } while (0)

#define string_strict_print(s) for (char *i = s; *i; i++) printf("%d(%c) ", *i, *i); putchar(10);

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
    default: return sprintf(test_temp_buffer, "unknown type");
    }
    va_end(args);
    return 0;
}

#define print(a) do { \
    strcat(test_format_buffer, "    " #a "("); \
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
    strcat(test_format_buffer, ")\n"); \
} while (0)

int test_runner(const Test *now)
{
    const TestFunc *test_func;
    int ret_val;
    int count_fail = 0, count_ok = 0, count_tle = 0;
    printf("running: \033[0m%s\n", now->file_name);
    if (now->init_func) now->init_func();
    test_func = now->test_funcs;
    while (test_func->name)
    {
        test_format_buffer[0] = 0;
        if (test_func->state == TestFuncState_disable) goto increase;
        ret_val = test_func->func();
        if (!ret_val)
        {
            count_fail++;
            printf(
                "\033[91m%s failed:\n\033[1m%s\033[0m", 
                test_func->name, 
                test_format_buffer
            );
        }
        else if (ret_val == 1)
        {
            count_ok++;
            printf(
                "\033[92m%-40s Accepted (%.3lf μs in average < %.0lf)\n\033[0m", 
                test_func->name, 
                ok_time_use,
                __time_max
            );
        }
        else
        {
            count_tle++;
            printf(
                "\033[93m%-40s TLE\n\033[1m%s\033[0m", 
                test_func->name, 
                test_format_buffer
            );
        }
    increase:
        test_func++;
    }
    if (now->end_func) now->end_func();
    printf("\033[91m%d failed\033[0m, \033[93m%d TLE\033[0m, \033[92m%d ok\n\033[0m", count_fail, count_tle, count_ok);
    return count_fail || count_tle;
}

#define CAPTURE_STROUT(buffer, sentence) \
    do {\
        fflush(stdout); \
        int orig_stdout = dup(fileno(stdout)); \
        if (orig_stdout == -1) return false; \
        FILE *temp = tmpfile(); \
        dup2(fileno(temp), fileno(stdout)); \
        sentence; \
        fflush(stdout); \
        dup2(orig_stdout, fileno(stdout)); \
        close(orig_stdout); \
        rewind(temp); \
        fseek(temp, 0, SEEK_END); \
        long size = ftell(temp); \
        rewind(temp); \
        size_t read_size = fread(buffer, 1, (size_t)size, temp); \
        buffer[read_size] = '\0'; \
        fclose(temp);  \
    } while (0);

#define CAPTURE_STROUT_functest(buffer, ans, func, ...) \
    do {\
        fflush(stdout); \
        int orig_stdout = dup(fileno(stdout)); \
        uint64_t start, end; \
        if (orig_stdout == -1) return false; \
        FILE *temp = tmpfile(); \
        dup2(fileno(temp), fileno(stdout)); \
        start = got_time(); \
        ans = func(__VA_ARGS__); \
        end = got_time(); \
        fflush(stdout); \
        dup2(orig_stdout, fileno(stdout)); \
        close(orig_stdout); \
        rewind(temp); \
        fseek(temp, 0, SEEK_END); \
        long size = ftell(temp); \
        rewind(temp); \
        size_t read_size = fread(buffer, 1, (size_t)size, temp); \
        buffer[read_size] = '\0'; \
        fclose(temp);  \
        __used_time += (end - start); \
        __tests_count++; \
    } while (0);

#endif /* _CTESTS_MAIN_H */
