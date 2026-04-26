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

bool test_pvc_PV_119p8_set(void)
{
    pvc_PV_119p8 a;
    __int128_t b, ccc = (__int128_t)1 << 64;
    test_start();

    b = (__int128_t)0 * ccc + 0;
    pvc_PV_119p8_set(&a, &b);
    assert_equal(a._1, 0);
    assert_equal(a._2, 0);

    b = (__int128_t)0 * ccc + 123456789ULL;
    pvc_PV_119p8_set(&a, &b);
    assert_equal(a._1, 0);
    assert_equal(a._2, 123456789ULL);

    b = (__int128_t)-1 * ccc + 18446744073586094827ULL;
    pvc_PV_119p8_set(&a, &b);
    assert_equal(a._1, 0);
    assert_equal(a._2, 18446744073586094827ULL);

    b = (__int128_t)INT64_MAX * ccc + UINT64_MAX;
    pvc_PV_119p8_set(&a, &b);
    assert_equal(a._1, INT64_MAX);
    assert_equal(a._2, UINT64_MAX);

    b = (__int128_t)INT64_MIN * ccc + 0;
    pvc_PV_119p8_set(&a, &b);
    assert_equal(a._1, INT64_MIN);
    assert_equal(a._2, 0);

    b = (__int128_t)123 * ccc + 0;
    pvc_PV_119p8_set(&a, &b);
    assert_equal(a._1, 123);
    assert_equal(a._2, 0);

    test_end();
}

bool test_pvc_PV_119p8_add(void)
{
    pvc_PV_119p8 a, b, res;
    bool s;
    test_start();
    
    // 1. 零 + 零
    a._1 = 0, a._2 = 0;
    b._1 = 0, b._2 = 0;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, 0);
    assert_equal(res._2, 0);
    assert_equal(s, false);

    // 2. 小正数相加，无进位
    a._1 = 0, a._2 = 1;
    b._1 = 0, b._2 = 2;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, 0);
    assert_equal(res._2, 3);
    assert_equal(s, false);

    // 3. 低位全F加1，进位到高位，无溢出
    a._1 = 0, a._2 = UINT64_MAX;
    b._1 = 0, b._2 = 1;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, 1);
    assert_equal(res._2, 0);
    assert_equal(s, false);

    // 4. 低64位最高位相加进位，无溢出
    a._1 = 0, a._2 = 0x8000000000000000ULL;
    b._1 = 0, b._2 = 0x8000000000000000ULL;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, 1);
    assert_equal(res._2, 0);
    assert_equal(s, false);

    // 5. -1 + 1 = 0
    a._1 = -1, a._2 = UINT64_MAX;
    b._1 = 0, b._2 = 1;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, 0);
    assert_equal(res._2, 0);
    assert_equal(s, false);

    // 6. -2 + 2 = 0
    a._1 = -1, a._2 = UINT64_MAX - 1;   // -2 的低位
    b._1 = 0, b._2 = 2;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, 0);
    assert_equal(res._2, 0);
    assert_equal(s, false);

    // 7. 最大正数 (2^127-1) 加 1 → 正溢出
    a._1 = INT64_MAX, a._2 = UINT64_MAX;
    b._1 = 0, b._2 = 1;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, 0);
    assert_equal(res._2, 0);
    assert_equal(s, true);

    // 8. 最小负数 (-2^127) 加 -1 → 负溢出
    a._1 = INT64_MIN, a._2 = 0;
    b._1 = -1, b._2 = UINT64_MAX;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, 0);
    assert_equal(res._2, 0);
    assert_equal(s, true);

    // 9. 接近最大正数加2 → 正溢出
    a._1 = INT64_MAX, a._2 = UINT64_MAX - 1;
    b._1 = 0, b._2 = 2;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, 0);
    assert_equal(res._2, 0);
    assert_equal(s, true);

    // 10. 最小负数加0，无溢出
    a._1 = INT64_MIN, a._2 = 0;
    b._1 = 0, b._2 = 0;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, INT64_MIN);
    assert_equal(res._2, 0);
    assert_equal(s, false);

    // 11. 最小负数加1，无溢出（结果=-2^127+1）
    a._1 = INT64_MIN, a._2 = 0;
    b._1 = 0, b._2 = 1;
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, INT64_MIN);
    assert_equal(res._2, 1);
    assert_equal(s, false);

    // 12. 5 + (-5) = 0
    a._1 = 0, a._2 = 5;
    b._1 = -1, b._2 = UINT64_MAX - 4;   // -5 的低位：UINT64_MAX-4
    s = pvc_PV_119p8_add(&a, &b, &res);
    assert_equal(res._1, 0);
    assert_equal(res._2, 0);
    assert_equal(s, false);

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

bool test_pvc_PV_119p8_tostring(void)
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

bool test_pvc_PV_119p8_format_normal_1(void)
{
    pvc_PV_119p8 a;
    int ans, format_length;
    char s[200];
    test_start();

    a._1 = 0, a._2 = 0;
    ans = pvc_PV_119p8_format(s, "hi", &format_length, &a);
    assert_string_equal(format_length, 2);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "hu", &format_length, &a);
    assert_string_equal(format_length, 2);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "hx", &format_length, &a);
    assert_string_equal(format_length, 2);
    assert_string_length_equal(s, ans, "0000000000000000");
    ans = pvc_PV_119p8_format(s, "li", &format_length, &a);
    assert_string_equal(format_length, 2);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "lu", &format_length, &a);
    assert_string_equal(format_length, 2);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "lx", &format_length, &a);
    assert_string_equal(format_length, 2);
    assert_string_length_equal(s, ans, "0000000000000000");
    ans = pvc_PV_119p8_format(s, "b", &format_length, &a);
    assert_string_equal(format_length, 1);
    assert_string_length_equal(s, ans, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, "B", &format_length, &a);
    assert_string_equal(format_length, 1);
    assert_string_length_equal(s, ans, "false");
    ans = pvc_PV_119p8_format(s, "#B", &format_length, &a);
    assert_string_equal(format_length, 2);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    ans = pvc_PV_119p8_format(s, "x", &format_length, &a);
    assert_string_equal(format_length, 1);
    assert_string_length_equal(s, ans, "00000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, "X", &format_length, &a);
    assert_string_equal(format_length, 1);
    assert_string_length_equal(s, ans, "00000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, "d", &format_length, &a);
    assert_string_equal(format_length, 1);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "+d", &format_length, &a);
    assert_string_equal(format_length, 2);
    assert_string_length_equal(s, ans, "+0");
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 1);
    assert_string_length_equal(s, ans, "0.0");
    ans = pvc_PV_119p8_format(s, ".3f", &format_length, &a);
    assert_string_equal(format_length, 3);
    assert_string_length_equal(s, ans, "0.000");
    ans = pvc_PV_119p8_format(s, ".5f", &format_length, &a);
    assert_string_equal(format_length, 3);
    assert_string_length_equal(s, ans, "0.00000");
    ans = pvc_PV_119p8_format(s, ".7f", &format_length, &a);
    assert_string_equal(format_length, 3);
    assert_string_length_equal(s, ans, "0.0000000");
    ans = pvc_PV_119p8_format(s, ".100f", &format_length, &a);
    assert_string_equal(format_length, 5);
    assert_string_length_equal(s, ans, "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, "???", &format_length, &a);
    assert_string_equal(format_length, -1);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    
    test_end();
}

bool test_pvc_PV_119p8_format_normal_2(void)
{
    pvc_PV_119p8 a;
    int ans, format_length;
    char s[200];
    test_start();

    a._1 = 0, a._2 = 114514;
    ans = pvc_PV_119p8_format(s, "hi", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "hu", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, "hx", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0000000000000000");
    ans = pvc_PV_119p8_format(s, "li", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "114514");
    ans = pvc_PV_119p8_format(s, "lu", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "114514");
    ans = pvc_PV_119p8_format(s, "lx", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "000000000001bf52");
    ans = pvc_PV_119p8_format(s, "b", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000011011111101010010");
    ans = pvc_PV_119p8_format(s, "B", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "true");
    ans = pvc_PV_119p8_format(s, "#B", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    ans = pvc_PV_119p8_format(s, "x", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0000000000000000000000000001bf52");
    ans = pvc_PV_119p8_format(s, "X", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0000000000000000000000000001BF52");
    ans = pvc_PV_119p8_format(s, "d", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "447");
    ans = pvc_PV_119p8_format(s, "+d", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "+447");
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "447.3203125");
    ans = pvc_PV_119p8_format(s, ".3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "447.320");
    ans = pvc_PV_119p8_format(s, ".6f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "447.320312");
    ans = pvc_PV_119p8_format(s, ".7f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "447.3203125");
    ans = pvc_PV_119p8_format(s, ".100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "447.3203125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, "???", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_equal(s, "unknown format");
    assert_equal(ans, -1);
    
    test_end();
}

bool test_pvc_PV_119p8_format_pointf(void)
{
    pvc_PV_119p8 a;
    int ans, format_length;
    char s[200];
    test_start();

    a._1 = 0, a._2 = 0;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.0");
    ans = pvc_PV_119p8_format(s, ".3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.000");
    ans = pvc_PV_119p8_format(s, ".5f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.00000");
    ans = pvc_PV_119p8_format(s, ".7f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.0000000");
    ans = pvc_PV_119p8_format(s, ".100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 0, a._2 = 2432;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5");
    ans = pvc_PV_119p8_format(s, ".0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "10");
    ans = pvc_PV_119p8_format(s, ".1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5");
    ans = pvc_PV_119p8_format(s, ".2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.50");
    ans = pvc_PV_119p8_format(s, ".3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.500");
    ans = pvc_PV_119p8_format(s, ".5f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.50000");
    ans = pvc_PV_119p8_format(s, ".7f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5000000");
    ans = pvc_PV_119p8_format(s, ".100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 0, a._2 = 2559;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.99609375");
    ans = pvc_PV_119p8_format(s, ".0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "10");
    ans = pvc_PV_119p8_format(s, ".1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "10.0");
    ans = pvc_PV_119p8_format(s, ".2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "10.00");
    ans = pvc_PV_119p8_format(s, ".3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.996");
    ans = pvc_PV_119p8_format(s, ".5f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.99609");
    ans = pvc_PV_119p8_format(s, ".7f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.9960938");
    ans = pvc_PV_119p8_format(s, ".100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = ~0ll, a._2 = -2559;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.99609375");
    ans = pvc_PV_119p8_format(s, ".0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-10");
    ans = pvc_PV_119p8_format(s, ".1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-10.0");
    ans = pvc_PV_119p8_format(s, ".2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-10.00");
    ans = pvc_PV_119p8_format(s, ".3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.996");
    ans = pvc_PV_119p8_format(s, ".5f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.99609");
    ans = pvc_PV_119p8_format(s, ".7f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.9960938");
    ans = pvc_PV_119p8_format(s, ".100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
        
    a._1 = INT64_MAX, a._2 = UINT64_MAX;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.99609375");
    ans = pvc_PV_119p8_format(s, ".0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172288");
    ans = pvc_PV_119p8_format(s, ".1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172288.0");
    ans = pvc_PV_119p8_format(s, ".2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172288.00");
    ans = pvc_PV_119p8_format(s, ".3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.996");
    ans = pvc_PV_119p8_format(s, ".5f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.99609");
    ans = pvc_PV_119p8_format(s, ".7f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.9960938");
    ans = pvc_PV_119p8_format(s, ".100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 13877787807814ll, a._2 = 8425648038478872575ll;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.99609375");
    ans = pvc_PV_119p8_format(s, ".0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, ".1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000.0");
    ans = pvc_PV_119p8_format(s, ".2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000.00");
    ans = pvc_PV_119p8_format(s, ".3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.996");
    ans = pvc_PV_119p8_format(s, ".5f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.99609");
    ans = pvc_PV_119p8_format(s, ".7f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.9960938");
    ans = pvc_PV_119p8_format(s, ".100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = ~13877787807814ll, a._2 = -8425648038478872575ll;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.99609375");
    ans = pvc_PV_119p8_format(s, ".0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, ".1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000.0");
    ans = pvc_PV_119p8_format(s, ".2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000.00");
    ans = pvc_PV_119p8_format(s, ".3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.996");
    ans = pvc_PV_119p8_format(s, ".5f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.99609");
    ans = pvc_PV_119p8_format(s, ".7f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.9960938");
    ans = pvc_PV_119p8_format(s, ".100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 1405929648567151103ll, a._2 = 6643784628914141954ll;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125");
    ans = pvc_PV_119p8_format(s, ".0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275");
    ans = pvc_PV_119p8_format(s, ".1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0");
    ans = pvc_PV_119p8_format(s, ".2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.01");
    ans = pvc_PV_119p8_format(s, ".3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.008");
    ans = pvc_PV_119p8_format(s, ".5f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.00781");
    ans = pvc_PV_119p8_format(s, ".7f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125");
    ans = pvc_PV_119p8_format(s, ".100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    test_end();
}

bool test_pvc_PV_119p8_format_starf(void)
{
    pvc_PV_119p8 a;
    int ans, format_length;
    char s[200];
    test_start();

    a._1 = 0, a._2 = 0;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 5);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.00000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 7);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.0000000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 100);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 0, a._2 = 2432;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "10");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.50");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 5);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.50000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 7);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5000000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 100);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 0, a._2 = 2559;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.99609375");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "10");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "10.0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "10.00");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.996");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 5);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.99609");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 7);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.9960938");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 100);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = ~0ll, a._2 = -2559;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.99609375");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-10");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-10.0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-10.00");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.996");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 5);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.99609");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 7);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.9960938");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 100);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
        
    a._1 = INT64_MAX, a._2 = UINT64_MAX;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.99609375");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172288");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172288.0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172288.00");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.996");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 5);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.99609");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 7);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.9960938");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 100);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 13877787807814ll, a._2 = 8425648038478872575ll;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.99609375");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000.0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000.00");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.996");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 5);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.99609");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 7);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.9960938");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 100);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = ~13877787807814ll, a._2 = -8425648038478872575ll;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.99609375");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000.0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000.00");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.996");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 5);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.99609");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 7);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.9960938");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 100);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 1405929648567151103ll, a._2 = 6643784628914141954ll;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.01");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.008");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 5);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.00781");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 7);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125");
    ans = pvc_PV_119p8_format(s, ".*f", &a, 100);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    test_end();
}

bool test_pvc_PV_119p8_format_negf(void)
{
    pvc_PV_119p8 a;
    int ans, format_length;
    char s[200];
    test_start();

    a._1 = 0, a._2 = 0;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.0");
    ans = pvc_PV_119p8_format(s, ".-3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".-100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -100);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");

    a._1 = 0, a._2 = 2541;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.92578125");
    ans = pvc_PV_119p8_format(s, ".-1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "10");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "10");
    ans = pvc_PV_119p8_format(s, ".-100f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -100);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");

    a._1 = 1405929648567151103ll, a._2 = 6643784628914141954ll+2560;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609285.0078125");
    ans = pvc_PV_119p8_format(s, ".-0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609285");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609285");
    ans = pvc_PV_119p8_format(s, ".-1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609290");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609290");
    ans = pvc_PV_119p8_format(s, ".-10f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935860000000000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -10);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935860000000000");
    ans = pvc_PV_119p8_format(s, ".-20f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338500000000000000000000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -20);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338500000000000000000000");

    a._1 = 0, a._2 = 29315584;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "114514.0");
    ans = pvc_PV_119p8_format(s, ".-0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "114514");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "114514");
    ans = pvc_PV_119p8_format(s, ".-1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "114510");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "114510");
    ans = pvc_PV_119p8_format(s, ".-2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "114500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "114500");
    ans = pvc_PV_119p8_format(s, ".-3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "115000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "115000");
    ans = pvc_PV_119p8_format(s, ".-4f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "110000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -4);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "110000");
    ans = pvc_PV_119p8_format(s, ".-5f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "100000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -5);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "100000");
    ans = pvc_PV_119p8_format(s, ".-6f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -6);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");

    a._1 = 0, a._2 = 384000;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1500.0");
    ans = pvc_PV_119p8_format(s, ".-0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1500");
    ans = pvc_PV_119p8_format(s, ".-1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1500");
    ans = pvc_PV_119p8_format(s, ".-2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1500");
    ans = pvc_PV_119p8_format(s, ".-3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "2000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "2000");
    ans = pvc_PV_119p8_format(s, ".-4f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -4);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");

    a._1 = 0, a._2 = 128000;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500.0");
    ans = pvc_PV_119p8_format(s, ".-0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500");
    ans = pvc_PV_119p8_format(s, ".-1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500");
    ans = pvc_PV_119p8_format(s, ".-2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500");
    ans = pvc_PV_119p8_format(s, ".-3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".-4f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -4);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");

    a._1 = 0, a._2 = 128256;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "501.0");
    ans = pvc_PV_119p8_format(s, ".-0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "501");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "501");
    ans = pvc_PV_119p8_format(s, ".-1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500");
    ans = pvc_PV_119p8_format(s, ".-2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "500");
    ans = pvc_PV_119p8_format(s, ".-3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000");
    ans = pvc_PV_119p8_format(s, ".-4f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -4);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");

    a._1 = ~0, a._2 = -384000;
    ans = pvc_PV_119p8_format(s, "f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1500.0");
    ans = pvc_PV_119p8_format(s, ".-0f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -0);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1500");
    ans = pvc_PV_119p8_format(s, ".-1f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -1);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1500");
    ans = pvc_PV_119p8_format(s, ".-2f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1500");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -2);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1500");
    ans = pvc_PV_119p8_format(s, ".-3f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-2000");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -3);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-2000");
    ans = pvc_PV_119p8_format(s, ".-4f", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    ans = pvc_PV_119p8_format(s, ".*f", &a, -4);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0");
    test_end();
}

bool test_pvc_PV_119p8_format_pointe(void)
{
    pvc_PV_119p8 a;
    int ans, format_length;
    char s[200];
    test_start();

    a._1 = 0, a._2 = 0;
    ans = pvc_PV_119p8_format(s, "e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.0e+0");
    ans = pvc_PV_119p8_format(s, ".3e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.000e+0");
    ans = pvc_PV_119p8_format(s, ".5e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.00000e+0");
    ans = pvc_PV_119p8_format(s, ".7e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.0000000e+0");
    ans = pvc_PV_119p8_format(s, ".100e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e+0");
    
    a._1 = 0, a._2 = 2432;
    ans = pvc_PV_119p8_format(s, "e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5e+0");
    ans = pvc_PV_119p8_format(s, ".0e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1e+1");
    ans = pvc_PV_119p8_format(s, ".1e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5e+0");
    ans = pvc_PV_119p8_format(s, ".2e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.50e+0");
    ans = pvc_PV_119p8_format(s, ".3e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.500e+0");
    ans = pvc_PV_119p8_format(s, ".5e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.50000e+0");
    ans = pvc_PV_119p8_format(s, ".7e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5000000e+0");
    ans = pvc_PV_119p8_format(s, ".100e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.5000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e+0");
    
    a._1 = 0, a._2 = 2559;
    ans = pvc_PV_119p8_format(s, "e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.99609375e+0");
    ans = pvc_PV_119p8_format(s, ".0e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1e+1");
    ans = pvc_PV_119p8_format(s, ".1e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1.0e+1");
    ans = pvc_PV_119p8_format(s, ".2e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1.00e+1");
    ans = pvc_PV_119p8_format(s, ".3e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.996e+0");
    ans = pvc_PV_119p8_format(s, ".5e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.99609e+0");
    ans = pvc_PV_119p8_format(s, ".7e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.9960938e+0");
    ans = pvc_PV_119p8_format(s, ".100e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "9.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e+0");
    
    a._1 = ~0ll, a._2 = -2559;
    ans = pvc_PV_119p8_format(s, "e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1.0e+1");
    ans = pvc_PV_119p8_format(s, ".0e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1e+1");
    ans = pvc_PV_119p8_format(s, ".1e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1.0e+1");
    ans = pvc_PV_119p8_format(s, ".2e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1.00e+1");
    ans = pvc_PV_119p8_format(s, ".3e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.996e+0");
    ans = pvc_PV_119p8_format(s, ".5e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.99609e+0");
    ans = pvc_PV_119p8_format(s, ".7e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.9960938e+0");
    ans = pvc_PV_119p8_format(s, ".100e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-9.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e+0");
        
    a._1 = INT64_MAX, a._2 = UINT64_MAX;
    ans = pvc_PV_119p8_format(s, "e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "6.6e+35");
    ans = pvc_PV_119p8_format(s, ".0e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "6e+35");
    ans = pvc_PV_119p8_format(s, ".1e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "6.6e+35");
    ans = pvc_PV_119p8_format(s, ".2e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "6.65e+35");
    ans = pvc_PV_119p8_format(s, ".3e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "6.646e+35");
    ans = pvc_PV_119p8_format(s, ".5e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "6.64614e+35");
    ans = pvc_PV_119p8_format(s, ".7e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "6.6461400e+35");
    ans = pvc_PV_119p8_format(s, ".100e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "6.64613997892457936451903530140172287996093750000000000000000000000000000000000000000000000000000000000000000000e+35");
    
    a._1 = 13877787807814ll, a._2 = 8425648038478872575ll;
    ans = pvc_PV_119p8_format(s, "e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.99609375");
    ans = pvc_PV_119p8_format(s, ".0e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, ".1e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000.0");
    ans = pvc_PV_119p8_format(s, ".2e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "1000000000000000000000000000000.00");
    ans = pvc_PV_119p8_format(s, ".3e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.996");
    ans = pvc_PV_119p8_format(s, ".5e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.99609");
    ans = pvc_PV_119p8_format(s, ".7e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.9960938");
    ans = pvc_PV_119p8_format(s, ".100e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "999999999999999999999999999999.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = ~13877787807814ll, a._2 = -8425648038478872575ll;
    ans = pvc_PV_119p8_format(s, "e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.99609375");
    ans = pvc_PV_119p8_format(s, ".0e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000");
    ans = pvc_PV_119p8_format(s, ".1e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000.0");
    ans = pvc_PV_119p8_format(s, ".2e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-1000000000000000000000000000000.00");
    ans = pvc_PV_119p8_format(s, ".3e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.996");
    ans = pvc_PV_119p8_format(s, ".5e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.99609");
    ans = pvc_PV_119p8_format(s, ".7e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.9960938");
    ans = pvc_PV_119p8_format(s, ".100e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "-999999999999999999999999999999.9960937500000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    a._1 = 1405929648567151103ll, a._2 = 6643784628914141954ll;
    ans = pvc_PV_119p8_format(s, "e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125");
    ans = pvc_PV_119p8_format(s, ".0e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275");
    ans = pvc_PV_119p8_format(s, ".1e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0");
    ans = pvc_PV_119p8_format(s, ".2e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.01");
    ans = pvc_PV_119p8_format(s, ".3e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.008");
    ans = pvc_PV_119p8_format(s, ".5e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.00781");
    ans = pvc_PV_119p8_format(s, ".7e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125");
    ans = pvc_PV_119p8_format(s, ".100e", &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_string_length_equal(s, ans, "101307907862338465673935864443609275.0078125000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    
    test_end();
}

bool test_pvc_PV_119p8_print(void)
{
    pvc_PV_119p8 a;
    char s[1000];
    int ans;
    test_start();

    a._1 = 0, a._2 = 0;
    CAPTURE_STROUT(s, ans = pvc_PV_119p8_print(&a));
    assert_string_length_equal(s, ans, "0");

    a._1 = 0, a._2 = 123456789ULL;
    CAPTURE_STROUT(s, ans = pvc_PV_119p8_print(&a));
    assert_string_length_equal(s, ans, "482253.08203125");

    a._1 = -1, a._2 = 18446744073586094827ULL;
    CAPTURE_STROUT(s, ans = pvc_PV_119p8_print(&a));
    assert_string_length_equal(s, ans, "-482253.08203125");

    a._1 = INT64_MAX, a._2 = UINT64_MAX;
    CAPTURE_STROUT(s, ans = pvc_PV_119p8_print(&a));
    assert_string_length_equal(s, ans, "664613997892457936451903530140172287.99609375");

    a._1 = INT64_MIN, a._2 = 0;
    CAPTURE_STROUT(s, ans = pvc_PV_119p8_print(&a));
    assert_string_length_equal(s, ans, "-664613997892457936451903530140172288");

    a._1 = 123, a._2 = 0;
    CAPTURE_STROUT(s, ans = pvc_PV_119p8_print(&a));
    assert_string_length_equal(s, ans, "8863084066665136128");

    test_end();
}

bool test_pvc_PV_119p8_null(void)
{
    pvc_PV_119p8 a;
    char s[1000];
    char *s2;
    int ans;
    test_start();

    char *pvc_PV_119p8_tostring(pvc_PV_119p8 *a);
    int pvc_PV_119p8_format(char *restrict buffer, const char *restrict format, pvc_PV_119p8 *restrict a, ...);
    int pvc_PV_119p8_print(pvc_PV_119p8 *a);

    s2 = pvc_PV_119p8_tostring(NULL);
    assert_string_equal(s2, "(null)");

    ans = pvc_PV_119p8_format(s, NULL, &format_length, &a);
    assert_string_equal(format_length, 2222);
    assert_equal(ans, -1);

    ans = pvc_PV_119p8_format(s, s2, NULL);
    assert_string_equal(format_length, 2222);
    assert_string_equal(s, "(null)");
    assert_equal(ans, -1);

    CAPTURE_STROUT(s, ans = pvc_PV_119p8_print(NULL));
    assert_string_length_equal(s, ans, "(null)");

    test_end();
}

const TestFunc c_PV_119p8_tests[] = {
    {"test_pvc_PV_119p8_set",              test_pvc_PV_119p8_set,             TestFuncState_enable},
    {"test_pvc_PV_119p8_add",              test_pvc_PV_119p8_add,             TestFuncState_enable},
    {"test_pvc_PV_119p8_neg",              test_pvc_PV_119p8_neg,             TestFuncState_enable},
    {"test_pvc_PV_119p8_tostring",         test_pvc_PV_119p8_tostring,        TestFuncState_enable},
    {"test_pvc_PV_119p8_format_normal_1",  test_pvc_PV_119p8_format_normal_1, TestFuncState_enable},
    {"test_pvc_PV_119p8_format_normal_2",  test_pvc_PV_119p8_format_normal_2, TestFuncState_enable},
    {"test_pvc_PV_119p8_format_pointf",    test_pvc_PV_119p8_format_pointf,   TestFuncState_enable},
    {"test_pvc_PV_119p8_format_starf",     test_pvc_PV_119p8_format_starf,    TestFuncState_enable},
    {"test_pvc_PV_119p8_format_negf",      test_pvc_PV_119p8_format_negf,     TestFuncState_enable},
    {"test_pvc_PV_119p8_format_pointe",    test_pvc_PV_119p8_format_pointe,   TestFuncState_disable},
    {"test_pvc_PV_119p8_print",            test_pvc_PV_119p8_print,           TestFuncState_enable},
    {"test_pvc_PV_119p8_null",             test_pvc_PV_119p8_null,            TestFuncState_enable},
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
