/* 
Test:
gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_PV_57p8.c -o pvc_PV_57p8-macos.o
gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_defines.c -o pvc_defines-macos.o
gcc -Wall -Wextra -c tests/ctests/ct_pvc_PV_57p8.c -o ct_pvc_PV_57p8-macos.o -Isrc/PowerViolenceObjects
gcc pvc_PV_57p8-macos.o ct_pvc_PV_57p8-macos.o pvc_defines-macos.o -o ct_pvc_PV_57p8-macos
./ct_pvc_PV_57p8-macos
*/

#include "../main.h"
#include "pvc_PV_57p8.h"

const TestFunc c_PV_57p8_tests[] = {
    {NULL, NULL, 0}
};

const Test c_PV_57p8 = {
    .file_name = __FILE__,
    .init_func = NULL,
    .test_funcs = c_PV_57p8_tests,
    .end_func = NULL
};

int main()
{
    return test_runner(&c_PV_57p8);
}
