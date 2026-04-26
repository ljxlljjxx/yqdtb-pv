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

bool test_pvc_PV_57p8_neg(void)
{
    pvc_PV_57p8 a;
    bool ans;
    test_start();

    a._1 = 0;
    ans = pvc_PV_57p8_neg(&a);
    assert_equal(a._1, 0);
    assert_equal(ans, false);

    a._1 = 123456789LL;
    ans = pvc_PV_57p8_neg(&a);
    assert_equal(a._1, -123456789LL);
    assert_equal(ans, false);

    a._1 = -123456789LL;
    ans = pvc_PV_57p8_neg(&a);
    assert_equal(a._1, 123456789LL);
    assert_equal(ans, false);

    a._1 = INT64_MAX;
    ans = pvc_PV_57p8_neg(&a);
    assert_equal(a._1, -INT64_MAX);
    assert_equal(ans, false);

    a._1 = INT64_MIN;
    ans = pvc_PV_57p8_neg(&a);
    assert_equal(a._1, 0);
    assert_equal(ans, true);

    test_end();
}

bool test_pvc_PV_57p8_tostring(void)
{
    pvc_PV_57p8 a;
    char *s;
    test_start();

    a._1 = 0;
    s = pvc_PV_57p8_tostring(&a);
    assert_string_equal(s, "0");

    a._1 = 123456789LL;
    s = pvc_PV_57p8_tostring(&a);
    assert_string_equal(s, "482253.08203125");

    a._1 = -123456789LL;
    s = pvc_PV_57p8_tostring(&a);
    assert_string_equal(s, "-482253.08203125");

    a._1 = INT64_MAX;
    s = pvc_PV_57p8_tostring(&a);
    assert_string_equal(s, "36028797018963967.99609375");

    a._1 = INT64_MIN;
    s = pvc_PV_57p8_tostring(&a);
    assert_string_equal(s, "-36028797018963968");

    test_end();
}

const TestFunc c_PV_57p8_tests[] = {
    {"test_pvc_PV_57p8_neg",      test_pvc_PV_57p8_neg,      TestFuncState_enable},
    {"test_pvc_PV_57p8_tostring", test_pvc_PV_57p8_tostring, TestFuncState_enable},
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
