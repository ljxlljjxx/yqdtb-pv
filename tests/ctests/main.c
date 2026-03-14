#include <time.h>
#include "main.h"

char test_format_buffer[100000];
char test_temp_buffer[100000];

const Test *list[] = {
    &c_powerobject,
    NULL
};

int main()
{
    size_t _now = 0;
    const Test *now = *list;
    const TestFunc *test_func;
    int count_fail = 0, count_ok = 0;
    clock_t start, end;
    while (now && now->file_name)
    {
        printf("\033[93mnow=%p running: \033[0m%s\n", now, now->file_name);
        if (now->init_func) now->init_func();
        test_func = now->test_funcs;
        while (test_func->name)
        {
            test_format_buffer[0] = 0;
            if (test_func->state == TestFuncState_disable) goto increase;
            start = clock();
            if (!test_func->func())
            {
                end = clock();
                count_fail++;
                printf(
                    "\033[91m%s failed: (used %lu μs)\n    \033[1m%s\n\033[0m", 
                    test_func->name, 
                    (end - start) * 1000000 / CLOCKS_PER_SEC, 
                    test_format_buffer
                );
            }
            else
            {
                end = clock();
                count_ok++;
                printf(
                    "\033[92m%-30s ok (used %lu μs)\n\033[0m", 
                    test_func->name, 
                    (end - start) * 1000000 / CLOCKS_PER_SEC
                );
            }
        increase:
            test_func++;
        }
        if (now->end_func) now->end_func();
        now = list[++_now];
    }
    printf("\033[91m%d failed\033[0m, \033[92m%d ok\n\033[0m", count_fail, count_ok);
    return 0;
}
