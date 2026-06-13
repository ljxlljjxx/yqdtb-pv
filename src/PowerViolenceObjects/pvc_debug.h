#ifndef _PVC_DEBUG_H
#define _PVC_DEBUG_H

#include <stdio.h>
#include <time.h>
#include <inttypes.h>

#define _debug

#define _DEBUG_STR_HELPER(x) #x
#define _DEBUG_STR(x) _DEBUG_STR_HELPER(x)

long long get_microseconds();
char *format_microsecond_time(char *, size_t);

#ifdef DEBUG
    #include <time.h>
    static FILE *__debug_file;
    static char __debug_time_buf[64];

    #define __debug_file_open_mode "w"

    #define pv_deprint_forstr_info    "\033[92m[Info\033[0m] "
    #define pv_deprint_forstr_debug   "\033[94m[Debug\033[0m]"
    #define pv_deprint_forstr_warning "\033[93m[Warn\033[0m] "
    #define pv_deprint_forstr_error   "\033[91m[Error\033[0m]"

    #define pv_deprint_gettime() format_microsecond_time(__debug_time_buf, get_microseconds())

    #define pv_deprint_defo(string) fprintf(__debug_file, "%s \033[95m%s\033[0m: \033[93m%-40s\033[0m , Line% -5d(\033[93m%-20s\033[0m): ", string, pv_deprint_gettime(), __FILE__, __LINE__, __func__)

    #define pv_deprint_getformat(a) _Generic((a),                   \
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
            )
    #define debug_printf(format, ...) do { pv_deprint_defo(pv_deprint_forstr_debug); fprintf(__debug_file, format, ##__VA_ARGS__); fflush(__debug_file); } while (0)
    #define debug_puts(string) do { pv_deprint_defo(pv_deprint_forstr_debug); fputs(string, __debug_file); fputc(10, __debug_file); fflush(__debug_file); } while (0)
    #define debug_print(a) do { pv_deprint_defo(pv_deprint_forstr_debug); fprintf(__debug_file, pv_deprint_getformat(a), a); fflush(__debug_file); } while (0)

    #define info_printf(format, ...) do { pv_deprint_defo(pv_deprint_forstr_info); fprintf(__debug_file, format, ##__VA_ARGS__); fflush(__debug_file); } while (0)
    #define info_puts(string) do { pv_deprint_defo(pv_deprint_forstr_info); fputs(string, __debug_file); fputc(10, __debug_file); fflush(__debug_file); } while (0)
    #define info_print(a) do { pv_deprint_defo(pv_deprint_forstr_info); fprintf(__debug_file, pv_deprint_getformat(a), a); fflush(__debug_file); } while (0)

    #define warning_printf(format, ...) do { pv_deprint_defo(pv_deprint_forstr_warning); fprintf(__debug_file, format, ##__VA_ARGS__); fflush(__debug_file); } while (0)
    #define warning_puts(string) do { pv_deprint_defo(pv_deprint_forstr_warning); fputs(string, __debug_file); fputc(10, __debug_file); fflush(__debug_file); } while (0)
    #define warning_print(a) do { pv_deprint_defo(pv_deprint_forstr_warning); fprintf(__debug_file, pv_deprint_getformat(a), a); fflush(__debug_file); } while (0)

    #define error_printf(format, ...) do { pv_deprint_defo(pv_deprint_forstr_error); fprintf(__debug_file, format, ##__VA_ARGS__); fflush(__debug_file); } while (0)
    #define error_puts(string) do { pv_deprint_defo(pv_deprint_forstr_error); fputs(string, __debug_file); fputc(10, __debug_file); fflush(__debug_file); } while (0)
    #define error_print(a) do { pv_deprint_defo(pv_deprint_forstr_error); fprintf(__debug_file, pv_deprint_getformat(a), a); fflush(__debug_file); } while (0)

    #define pv_deprint_overflow() warning_puts("overflow")
#else
    #define debug_print(a)
    #define debug_printf(...)
    #define debug_puts(string)
    #define info_print(a)
    #define info_printf(...)
    #define info_puts(string)
    #define warning_print(a)
    #define warning_printf(...)
    #define warning_puts(string)
    #define error_print(a)
    #define error_printf(...)
    #define error_puts(string)
    #define pv_deprint_overflow()
#endif

#endif /* _PVC_DEBUG_H */
