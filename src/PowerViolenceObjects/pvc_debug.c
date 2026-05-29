#include "pvc_debug.h"

#ifdef _WIN32
    #include <windows.h>
    long long get_microseconds()
    {
        LARGE_INTEGER freq, count;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&count);
        return (long long)(count.QuadPart * 1000000 / freq.QuadPart);
    }
#else
    #include <sys/time.h>
    long long get_microseconds()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return (long long)tv.tv_sec * 1000000 + tv.tv_usec;
    }
#endif

char *format_microsecond_time(char *buffer, size_t size)
{
    struct timeval tv;
    if (gettimeofday(&tv, NULL) == -1) return NULL;
    struct tm tm_buf;
    struct tm *tm_info = localtime_r(&tv.tv_sec, &tm_buf);
    if (tm_info == NULL) return NULL;
    int len = strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
    if (len == 0) return NULL;
    snprintf(buffer + len, size - len, ".%06"PRId32, tv.tv_usec);
    return buffer;
}
