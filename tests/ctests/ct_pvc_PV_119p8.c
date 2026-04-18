/* 
Test:
gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_PV_119p8.c -o pvc_PV_119p8-macos.o
gcc -Wall -Wextra -c src/PowerViolenceObjects/pvc_defines.c -o pvc_defines-macos.o
gcc -Wall -Wextra -c tests/ctests/ct_pvc_PV_119p8.c -o ct_pvc_PV_119p8-macos.o -Isrc/PowerViolenceObjects
gcc pvc_PV_119p8-macos.o ct_pvc_PV_119p8-macos.o pvc_defines-macos.o -o ct_pvc_PV_119p8-macos
./ct_pvc_PV_119p8-macos
*/

#include "../main.h"
#include "pvc_PV_119p8.h"

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
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "hu", &a);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "hx", &a);
    assert_string_length_equal(s, ans, "0000000000000000");
    ans = pvc_PV_119p8_format(s, "li", &a);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "lu", &a);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "lx", &a);
    assert_string_length_equal(s, ans, "0000000000000000");
    ans = pvc_PV_119p8_format(s, "b", &a);
    assert_string_length_equal(s, ans, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, "B", &a);
    assert_string_length_equal(s, ans, "false");
    ans = pvc_PV_119p8_format(s, "#B", &a);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    ans = pvc_PV_119p8_format(s, "x", &a);
    assert_string_length_equal(s, ans, "00000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, "X", &a);
    assert_string_length_equal(s, ans, "00000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, "d", &a);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "+d", &a);
    assert_string_length_equal(s, ans, "+0");
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_length_equal(s, ans, "0.0");
    ans = pvc_PV_119p8_format(s, ".3f", &a);
    assert_string_length_equal(s, ans, "0.000");
    ans = pvc_PV_119p8_format(s, ".5f", &a);
    assert_string_length_equal(s, ans, "0.00000");
    ans = pvc_PV_119p8_format(s, ".7f", &a);
    assert_string_length_equal(s, ans, "0.0000000");
    ans = pvc_PV_119p8_format(s, ".100f", &a);
    assert_string_length_equal(s, ans, "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
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
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "hu", &a);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "hx", &a);
    assert_string_length_equal(s, ans, "0000000000000000");
    ans = pvc_PV_119p8_format(s, "li", &a);
    assert_string_length_equal(s, ans, "114514");
    ans = pvc_PV_119p8_format(s, "lu", &a);
    assert_string_length_equal(s, ans, "114514");
    ans = pvc_PV_119p8_format(s, "lx", &a);
    assert_string_length_equal(s, ans, "000000000001bf52");
    ans = pvc_PV_119p8_format(s, "b", &a);
    assert_string_length_equal(s, ans, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011011111101010010");
    ans = pvc_PV_119p8_format(s, "B", &a);
    assert_string_length_equal(s, ans, "true");
    ans = pvc_PV_119p8_format(s, "#B", &a);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    ans = pvc_PV_119p8_format(s, "x", &a);
    assert_string_length_equal(s, ans, "0000000000000000000000000001bf52");
    ans = pvc_PV_119p8_format(s, "X", &a);
    assert_string_length_equal(s, ans, "0000000000000000000000000001BF52");
    ans = pvc_PV_119p8_format(s, "d", &a);
    assert_string_length_equal(s, ans, "447");
    ans = pvc_PV_119p8_format(s, "+d", &a);
    assert_string_length_equal(s, ans, "+447");
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_length_equal(s, ans, "447.3203125");
    ans = pvc_PV_119p8_format(s, ".3f", &a);
    assert_string_length_equal(s, ans, "447.320");
    ans = pvc_PV_119p8_format(s, ".6f", &a);
    assert_string_length_equal(s, ans, "447.320312");
    ans = pvc_PV_119p8_format(s, ".7f", &a);
    assert_string_length_equal(s, ans, "447.3203125");
    ans = pvc_PV_119p8_format(s, ".100f", &a);
    assert_string_length_equal(s, ans, "447.3203125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, "???", &a);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    
    test_end();
}

bool test_int128_format3(void)
{
    pvc_PV_119p8 a;
    int ans;
    char s[200];
    test_start();

    a._1 = 0, a._2 = 0;
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_length_equal(s, ans, "0.0");
    ans = pvc_PV_119p8_format(s, ".3f", &a);
    assert_string_length_equal(s, ans, "0.000");
    ans = pvc_PV_119p8_format(s, ".5f", &a);
    assert_string_length_equal(s, ans, "0.00000");
    ans = pvc_PV_119p8_format(s, ".7f", &a);
    assert_string_length_equal(s, ans, "0.0000000");
    ans = pvc_PV_119p8_format(s, ".100f", &a);
    assert_string_length_equal(s, ans, "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 0, a._2 = 2432;
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_length_equal(s, ans, "9.5");
    ans = pvc_PV_119p8_format(s, ".0f", &a);
    assert_string_length_equal(s, ans, "10");
    ans = pvc_PV_119p8_format(s, ".1f", &a);
    assert_string_length_equal(s, ans, "9.5");
    ans = pvc_PV_119p8_format(s, ".2f", &a);
    assert_string_length_equal(s, ans, "9.50");
    ans = pvc_PV_119p8_format(s, ".3f", &a);
    assert_string_length_equal(s, ans, "9.500");
    ans = pvc_PV_119p8_format(s, ".5f", &a);
    assert_string_length_equal(s, ans, "9.50000");
    ans = pvc_PV_119p8_format(s, ".7f", &a);
    assert_string_length_equal(s, ans, "9.5000000");
    ans = pvc_PV_119p8_format(s, ".100f", &a);
    assert_string_length_equal(s, ans, "9.5000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 0, a._2 = 2559;
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_length_equal(s, ans, "9.99609375");
    ans = pvc_PV_119p8_format(s, ".0f", &a);
    assert_string_length_equal(s, ans, "10");
    ans = pvc_PV_119p8_format(s, ".1f", &a);
    assert_string_length_equal(s, ans, "10.0");
    ans = pvc_PV_119p8_format(s, ".2f", &a);
    assert_string_length_equal(s, ans, "10.00");
    ans = pvc_PV_119p8_format(s, ".3f", &a);
    assert_string_length_equal(s, ans, "9.996");
    ans = pvc_PV_119p8_format(s, ".5f", &a);
    assert_string_length_equal(s, ans, "9.99609");
    ans = pvc_PV_119p8_format(s, ".7f", &a);
    assert_string_length_equal(s, ans, "9.9960938");
    ans = pvc_PV_119p8_format(s, ".100f", &a);
    assert_string_length_equal(s, ans, "9.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = ~0ll, a._2 = -2559;
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_length_equal(s, ans, "-9.99609375");
    ans = pvc_PV_119p8_format(s, ".0f", &a);
    assert_string_length_equal(s, ans, "-10");
    ans = pvc_PV_119p8_format(s, ".1f", &a);
    assert_string_length_equal(s, ans, "-10.0");
    ans = pvc_PV_119p8_format(s, ".2f", &a);
    assert_string_length_equal(s, ans, "-10.00");
    ans = pvc_PV_119p8_format(s, ".3f", &a);
    assert_string_length_equal(s, ans, "-9.996");
    ans = pvc_PV_119p8_format(s, ".5f", &a);
    assert_string_length_equal(s, ans, "-9.99609");
    ans = pvc_PV_119p8_format(s, ".7f", &a);
    assert_string_length_equal(s, ans, "-9.9960938");
    ans = pvc_PV_119p8_format(s, ".100f", &a);
    assert_string_length_equal(s, ans, "-9.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
        
    a._1 = INT64_MAX, a._2 = UINT64_MAX;
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.99609375");
    ans = pvc_PV_119p8_format(s, ".0f", &a);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172288");
    ans = pvc_PV_119p8_format(s, ".1f", &a);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172288.0");
    ans = pvc_PV_119p8_format(s, ".2f", &a);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172288.00");
    ans = pvc_PV_119p8_format(s, ".3f", &a);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.996");
    ans = pvc_PV_119p8_format(s, ".5f", &a);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.99609");
    ans = pvc_PV_119p8_format(s, ".7f", &a);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.9960938");
    ans = pvc_PV_119p8_format(s, ".100f", &a);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 13877787807814ll, a._2 = 8425648038478872575ll;
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.99609375");
    ans = pvc_PV_119p8_format(s, ".0f", &a);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, ".1f", &a);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000.0");
    ans = pvc_PV_119p8_format(s, ".2f", &a);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000.00");
    ans = pvc_PV_119p8_format(s, ".3f", &a);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.996");
    ans = pvc_PV_119p8_format(s, ".5f", &a);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.99609");
    ans = pvc_PV_119p8_format(s, ".7f", &a);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.9960938");
    ans = pvc_PV_119p8_format(s, ".100f", &a);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = ~13877787807814ll, a._2 = -8425648038478872575ll;
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.99609375");
    ans = pvc_PV_119p8_format(s, ".0f", &a);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, ".1f", &a);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000.0");
    ans = pvc_PV_119p8_format(s, ".2f", &a);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000.00");
    ans = pvc_PV_119p8_format(s, ".3f", &a);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.996");
    ans = pvc_PV_119p8_format(s, ".5f", &a);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.99609");
    ans = pvc_PV_119p8_format(s, ".7f", &a);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.9960938");
    ans = pvc_PV_119p8_format(s, ".100f", &a);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 1405929648567151103ll, a._2 = 6643784628914141954ll;
    ans = pvc_PV_119p8_format(s, "f", &a);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125");
    ans = pvc_PV_119p8_format(s, ".0f", &a);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275");
    ans = pvc_PV_119p8_format(s, ".1f", &a);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0");
    ans = pvc_PV_119p8_format(s, ".2f", &a);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.01");
    ans = pvc_PV_119p8_format(s, ".3f", &a);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.008");
    ans = pvc_PV_119p8_format(s, ".5f", &a);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.00781");
    ans = pvc_PV_119p8_format(s, ".7f", &a);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125");
    ans = pvc_PV_119p8_format(s, ".100f", &a);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    for (volatile int a = 0; a < 100000; a++) for (volatile int b = 0; b < 10000; b++)
    test_end();
}

const TestFunc c_PV_119p8_tests[] = {
    {"test_pvc_PV_119p8_neg", test_pvc_PV_119p8_neg,  TestFuncState_enable},
    {"test_int128_tostring", test_int128_tostring,    TestFuncState_enable},
    {"test_int128_format1",  test_int128_format1,     TestFuncState_enable},
    {"test_int128_format2",  test_int128_format2,     TestFuncState_enable},
    {"test_int128_format3",  test_int128_format3,     TestFuncState_enable},
    {NULL, NULL, 0}
};

const Test c_PV_119p8 = {
    .file_name = __FILE__,
    .init_func = NULL,
    .test_funcs = c_PV_119p8_tests,
    .end_func = NULL
};

int main()
{
    return test_runner(&c_PV_119p8);
}
