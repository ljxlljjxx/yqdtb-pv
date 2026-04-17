/* / */

#include "../main.h"
#include "pvc_PV_119p8.h"

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

bool test_pvc_PV_119p8_neg(void)
{
    pvc_PV_119p8 a;
    bool ans;
    test_start();

    a._1 = 0, a._2 = 0;
    ans = pvc_PV_119p8_neg(&a);
    assert_equal(a._1, 0);
    assert_equal(a._2, 0);
    assert_equal(ans, false);

    a._1 = 0, a._2 = 123456789ULL;
    ans = pvc_PV_119p8_neg(&a);
    assert_equal(a._1, -1);
    assert_equal(a._2, 18446744073586094827ULL);
    assert_equal(ans, false);

    a._1 = -1, a._2 = 18446744073586094827ULL;
    ans = pvc_PV_119p8_neg(&a);
    assert_equal(a._1, 0);
    assert_equal(a._2, 123456789ULL);
    assert_equal(ans, false);

    a._1 = INT64_MAX, a._2 = UINT64_MAX;
    ans = pvc_PV_119p8_neg(&a);
    assert_equal(a._1, INT64_MIN);
    assert_equal(a._2, 1);
    assert_equal(ans, false);

    a._1 = INT64_MIN, a._2 = 0;
    ans = pvc_PV_119p8_neg(&a);
    assert_equal(a._1, INT64_MIN);
    assert_equal(a._2, 0);
    assert_equal(ans, true);

    a._1 = 123, a._2 = 0;
    ans = pvc_PV_119p8_neg(&a);
    assert_equal(a._1, -123);
    assert_equal(a._2, 0);
    assert_equal(ans, false);

    test_end();
}

bool test_int128_tostring(void)
{
    pvc_PV_119p8 a;
    char *s;
    test_start();

    a._1 = 0, a._2 = 0;
    s = pvc_PV_119p8_tostring(&a);
    assert_string_equal(s, "0");

    a._1 = 0, a._2 = 123456789ULL;
    s = pvc_PV_119p8_tostring(&a);
    assert_string_equal(s, "482253.08203125");

    a._1 = -1, a._2 = 18446744073586094827ULL;
    s = pvc_PV_119p8_tostring(&a);
    assert_string_equal(s, "-482253.08203125");

    a._1 = INT64_MAX, a._2 = UINT64_MAX;
    s = pvc_PV_119p8_tostring(&a);
    assert_string_equal(s, "664613997892457936451903530140172287.99609375");

    a._1 = INT64_MIN, a._2 = 0;
    s = pvc_PV_119p8_tostring(&a);
    assert_string_equal(s, "-664613997892457936451903530140172288");

    a._1 = 123, a._2 = 0;
    s = pvc_PV_119p8_tostring(&a);
    assert_string_equal(s, "8863084066665136128");

    test_end();
}

bool test_int128_format1(void)
{
    pvc_PV_119p8 a;
    int ans;
    char s[200];
    test_start();

    a._1 = 0, a._2 = 0;
    ans = pvc_PV_119p8_format(s, "hi", &a);
    assert_string_equal(s, "0");
    assert_equal(ans, 1);
    ans = pvc_PV_119p8_format(s, "hu", &a);
    assert_string_equal(s, "0");
    assert_equal(ans, 1);
    ans = pvc_PV_119p8_format(s, "hx", &a);
    assert_string_equal(s, "0000000000000000");
    assert_equal(ans, 16);
    ans = pvc_PV_119p8_format(s, "li", &a);
    assert_string_equal(s, "0");
    assert_equal(ans, 1);
    ans = pvc_PV_119p8_format(s, "lu", &a);
    assert_string_equal(s, "0");
    assert_equal(ans, 1);
    ans = pvc_PV_119p8_format(s, "lx", &a);
    assert_string_equal(s, "0000000000000000");
    assert_equal(ans, 16);
    ans = pvc_PV_119p8_format(s, "b", &a);
    assert_string_equal(s, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    assert_equal(ans, 128);
    ans = pvc_PV_119p8_format(s, "B", &a);
    assert_string_equal(s, "false");
    assert_equal(ans, 5);
    ans = pvc_PV_119p8_format(s, "#B", &a);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    ans = pvc_PV_119p8_format(s, "x", &a);
    assert_string_equal(s, "00000000000000000000000000000000");
    assert_equal(ans, 32);
    ans = pvc_PV_119p8_format(s, "X", &a);
    assert_string_equal(s, "00000000000000000000000000000000");
    assert_equal(ans, 32);
    ans = pvc_PV_119p8_format(s, "d", &a);
    assert_string_equal(s, "0");
    assert_equal(ans, 1);
    ans = pvc_PV_119p8_format(s, "+d", &a);
    assert_string_equal(s, "+0");
    assert_equal(ans, 2);
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_equal(s, "0");
    assert_equal(ans, 1);
    ans = pvc_PV_119p8_format(s, "???", &a);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    
    test_end();
}

bool test_int128_format2(void)
{
    pvc_PV_119p8 a;
    int ans;
    char s[200];
    test_start();

    a._1 = 0, a._2 = 114514;
    ans = pvc_PV_119p8_format(s, "hi", &a);
    assert_string_equal(s, "0");
    assert_equal(ans, 1);
    ans = pvc_PV_119p8_format(s, "hu", &a);
    assert_string_equal(s, "0");
    assert_equal(ans, 1);
    ans = pvc_PV_119p8_format(s, "hx", &a);
    assert_string_equal(s, "0000000000000000");
    assert_equal(ans, 16);
    ans = pvc_PV_119p8_format(s, "li", &a);
    assert_string_equal(s, "114514");
    assert_equal(ans, 6);
    ans = pvc_PV_119p8_format(s, "lu", &a);
    assert_string_equal(s, "114514");
    assert_equal(ans, 6);
    ans = pvc_PV_119p8_format(s, "lx", &a);
    assert_string_equal(s, "000000000001bf52");
    assert_equal(ans, 16);
    ans = pvc_PV_119p8_format(s, "b", &a);
    assert_string_equal(s, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011011111101010010");
    assert_equal(ans, 128);
    ans = pvc_PV_119p8_format(s, "B", &a);
    assert_string_equal(s, "true");
    assert_equal(ans, 5);
    ans = pvc_PV_119p8_format(s, "#B", &a);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    ans = pvc_PV_119p8_format(s, "x", &a);
    assert_string_equal(s, "0000000000000000000000000001bf52");
    assert_equal(ans, 32);
    ans = pvc_PV_119p8_format(s, "X", &a);
    assert_string_equal(s, "0000000000000000000000000001BF52");
    assert_equal(ans, 32);
    ans = pvc_PV_119p8_format(s, "d", &a);
    assert_string_equal(s, "114514");
    assert_equal(ans, 6);
    ans = pvc_PV_119p8_format(s, "+d", &a);
    assert_string_equal(s, "+114514");
    assert_equal(ans, 7);
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_equal(s, "114514.0");
    assert_equal(ans, 8);
    ans = pvc_PV_119p8_format(s, "???", &a);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    
    test_end();
}

const TestFunc c_powerobject_tests[] = {
    {"test_addi64_overflow", test_addi64_overflow,    TestFuncState_enable},
    {"test_addu64_overflow", test_addu64_overflow,    TestFuncState_enable},
    {"test_pvc_PV_119p8_neg", test_pvc_PV_119p8_neg,  TestFuncState_enable},
    {"test_int128_tostring", test_int128_tostring,    TestFuncState_enable},
    {"test_int128_format",   test_int128_format1,     TestFuncState_enable},
    {"test_int128_format",   test_int128_format2,     TestFuncState_enable},
    {NULL, NULL, 0}
};

const Test c_powerobject = {
    .file_name = __FILE__,
    .init_func = NULL,
    .test_funcs = c_powerobject_tests,
    .end_func = NULL
};

int main()
{
    return test_runner(&c_powerobject);
}
