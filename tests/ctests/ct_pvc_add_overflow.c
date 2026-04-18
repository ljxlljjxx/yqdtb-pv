/* 
Test:
gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_add_overflow.c -o pvc_add_overflow-macos.o
gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_defines.c -o pvc_defines-macos.o
gcc -Wall -Wextra -c tests/ctests/ct_pvc_add_overflow.c -o ct_pvc_add_overflow-macos.o -Isrc/PowerViolenceObjects
gcc pvc_add_overflow-macos.o ct_pvc_add_overflow-macos.o pvc_defines-macos.o -o ct_pvc_add_overflow-macos
./ct_pvc_add_overflow-macos
*/

#include "../main.h"
#include "pvc_defines.h"

bool test_addi64_overflow(void)
{
    int64_t a, b, res;
    bool ans;
    test_start();

    a = 1, b = 2;
    ans = addi64_overflow(a, b, &res);
    assert_equal(ans, false);
    assert_equal(res, 3);

    a = INT64_MAX, b = 1;
    ans = addi64_overflow(a, b, &res);
    assert_equal(ans, true);
    assert_equal(res, INT64_MIN);

    a = INT64_MAX, b = -1;
    ans = addi64_overflow(a, b, &res);
    assert_equal(ans, false);
    assert_equal(res, INT64_MAX-1);

    a = INT64_MIN, b = -1;
    ans = addi64_overflow(a, b, &res);
    assert_equal(ans, true);
    assert_equal(res, INT64_MAX);

    a = INT64_MIN, b = 0;
    ans = addi64_overflow(a, b, &res);
    assert_equal(ans, false);
    assert_equal(res, INT64_MIN);

    a = INT64_MIN, b = INT64_MIN;
    ans = addi64_overflow(a, b, &res);
    assert_equal(ans, true);
    assert_equal(res, 0);

    a = INT64_MAX, b = INT64_MIN;
    ans = addi64_overflow(a, b, &res);
    assert_equal(ans, false);
    assert_equal(res, -1);

    a = 1, b = INT64_MAX;
    ans = addi64_overflow(a, b, &res);
    assert_equal(ans, true);
    assert_equal(res, INT64_MIN);

    test_end();
}

bool test_addu64_overflow(void)
{
    uint64_t a, b, res;
    bool ans;
    test_start();

    a = 0, b = 0;
    ans = addu64_overflow(a, b, &res);
    assert_equal(ans, false);
    assert_equal(res, 0);

    a = UINT64_MAX, b = 1;
    ans = addu64_overflow(a, b, &res);
    assert_equal(ans, true);
    assert_equal(res, 0);

    a = UINT64_MAX, b = 0;
    ans = addu64_overflow(a, b, &res);
    assert_equal(ans, false);
    assert_equal(res, UINT64_MAX);

    a = 1, b = UINT64_MAX;
    ans = addu64_overflow(a, b, &res);
    assert_equal(ans, true);
    assert_equal(res, 0);

    a = UINT64_MAX, b = UINT64_MAX;
    ans = addu64_overflow(a, b, &res);
    assert_equal(ans, true);
    assert_equal(res, UINT64_MAX-1);

    test_end();
}

const TestFunc c_add_overflow_tests[] = {
    {"test_addi64_overflow", test_addi64_overflow,    TestFuncState_enable},
    {"test_addu64_overflow", test_addu64_overflow,    TestFuncState_enable},
    {NULL, NULL, 0}
};

const Test c_add_overflow = {
    .file_name = __FILE__,
    .init_func = NULL,
    .test_funcs = c_add_overflow_tests,
    .end_func = NULL
};

int main()
{
    return test_runner(&c_add_overflow);
}
