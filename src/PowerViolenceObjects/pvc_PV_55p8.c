#include "pvc_PV_55p8.h"

/**
 * @brief   set *res to *a + *b
 * @param   a pvc_PV_55p8 *
 * @param   b pvc_PV_55p8 *
 * @param   res pvc_PV_55p8 *restrict
 * @return  bool
 * @retval  overflow
 * @warning This function does not check whether the parameter is null.
 * @author  ljx
 * @date    2026-04-26 11:20
 */
bool pvc_PV_55p8_add(pvc_PV_55p8 *a, pvc_PV_55p8 *b, pvc_PV_55p8 *restrict res)
{
    res->_1 = a->_1 + b->_1;
    if (addi64_overflow(a->_1, b->_1, &res->_1))
    {
        res->_1 = 0;
        return true;
    }
    return false;
}

/**
 * @brief   let *a becomes -*a.
 * @param   a pvc_PV_55p8 *
 * @return  bool
 * @retval  overflow
 * @warning This function does not check whether the parameter is null.
 * @author  ljx
 * @date    2026-04-26 11:21
 */
bool pvc_PV_55p8_neg(pvc_PV_55p8 *a)
{
    if (a->_1 == INT64_MIN)
    {
        a->_1 = 0;
        return true;
    }
    a->_1 = -a->_1;
    return false;
}

/**
 * @brief   print pvc_PV_55p8 int string
 * @param   a pvc_PV_55p8 *
 * @return  char *
 * @retval  return the string
 * @note    the return value is const.
 * @author  ljx
 * @date    2026-04-26 11:24
 */
char *pvc_PV_55p8_tostring(pvc_PV_55p8 *a)
{
    static char buffer[40];
    if (a == NULL) return strcpy(buffer, "(null)");
    if (!a->_1)
    {
        *buffer = '0';
        buffer[1] = 0;
        return buffer;
    }
    if (a->_1 & INT64_MIN)
    {
        if (pvc_PV_55p8_neg(a))
        {
            strcpy(buffer, "-36028797018963968");
            return buffer;
        }
        else
        {
            sprintf(buffer, "-%lld.%s", a->_1 >> 8, quick_float[a->_1 & 255]);
            return buffer;
        }
    }
    sprintf(buffer, "%lld.%s", a->_1 >> 8, quick_float[a->_1 & 255]);
    return buffer;
}

/**
 * @brief   use format to write pvc_PV_119p8.
 * @param   buffer char *restrict. the string will write here.
 * @param   format a string. Legal format:
        (Achieved) (Tested) b:  binary
        (Achieved) (Tested) x:  hexadecimal
        (Achieved) (Tested) X:  hexadecimal
        (Achieved) (Tested) d:  integer part
        (Achieved) (Tested)     +d: display the sign bit
        (Achieved) (Tested) f:  floating-point number.
        (Achieved) (Tested)     .{n}f: the precision
        (Achieved) (Tested)     .*f: the next parameter specified is the precision
        (Achieved) (------) e:  scientific notation. the default precision is 1.
        (Achieved) (------)     .{n}e: the precision
        (Achieved) (------)     .*e: the next parameter specified is the precision
        (Achieved) (------) E:  scientific notation. the default precision is 1.
        (Achieved) (------)     .{n}E: the precision
        (Achieved) (------)     .*E: the next parameter specified is the precision
        (--------) (------) g:  Automatically select %f or %e based on the value. Use the %e format when the exponent is less than -4 or greater than or equal to the precision.
        (--------) (------)     .{n}g: the precision
        (--------) (------)     .*g: the next parameter specified is the precision
        (--------) (------) G:  Automatically select %f or %e based on the value. Use the %E format when the exponent is less than -4 or greater than or equal to the precision.
        (--------) (------)     .{n}G: the precision
        (--------) (------)     .*G: the next parameter specified is the precision
        (Achieved) (Tested) B:  if a == 0, return "true". else return "false".
 * @param   a pvc_PV_119p8 *restrict 
 * @param   ... if format is .*f/.*e/.*E/.*g/.*G, this will give precision.
 * @return  int
 * @retval  the strlen of buffer.
 * @note    Please make sure buffer is enough for the answer.
 * @author  ljx
 * @date    2026-04-26 15:34
 */
int pvc_PV_55p8_format(char *restrict buffer, const char *restrict format, pvc_PV_55p8 *restrict a, int *format_length, ...)
{
    int cnt = 0;
    pvc_PV_55p8 format_b_b;

    int precision = 0;
    va_list argv;
    int format_d_type;
    const char *s2541;

    int exp = 0;
    uint64_t tN, tD;
    uint64_t p1, p2;

    int flag;

    if (a == NULL)
    {
        strcpy(buffer, "(null)");
        *format_length = 0;
        return -1;
    }

    if (format == NULL) return *format_length = -1;

    switch (*format)
    {
    case 'b':
        *format_length = 1;
        for (int i = 63; i >= 0; i--) buffer[cnt++] = ((a->_1 >> i) & 1) | 48;
        buffer[cnt] = 0;
        return 64;
    case 'x':
        *format_length = 1;
        return sprintf(buffer, "%016llx", a->_1);
    case 'X':
        *format_length = 1;
        return sprintf(buffer, "%016llX", a->_1);
    case 'd':
        *format_length = 1;
        format_d_type = 0;
    format_d:
        format_b_b = *a;
        if (format_b_b._1 >= 0)
        {
            cnt += sprintf(buffer + cnt, "%lld", a->_1 >> 8);
            goto format_d_return;
        }
        else
        {
            buffer[cnt++] = '-';
            if (pvc_PV_55p8_neg(&format_b_b))
            {
                strcpy(buffer+cnt, pvc_PV_55p8_max);
                cnt += 17;
                goto format_d_return;
            }
            cnt += sprintf(buffer + cnt, "%lld", format_b_b._1 >> 8);
            goto format_d_return;
        }
    format_d_return:
        switch (format_d_type)
        {
        case 0:
            goto function_return;
        case 1:
            buffer[cnt++] = '.';
            strcpy(buffer + cnt, quick_float[format_b_b._1 & 255]);
            return cnt + quick_float_len[format_b_b._1 & 255];
        case 2:
        
        case 5:
            if (precision > 0)
            {
                buffer[cnt++] = '.';
                if (precision <= 8)
                {
                    if (
                        (precision == 2 && (format_b_b._1 & 255) == 255) ||
                        (precision == 1 && quick_float_co1[format_b_b._1 & 255])
                    )
                    {
                        buffer[cnt-2]++;
                        for (int i = cnt-2; i >= 0; i--)
                        {
                            if (buffer[i] != 58)
                            {
                                if (buffer[i] != 46)
                                {
                                    break;
                                }
                                buffer[i] = '-';
                                buffer[i+1] = '1';
                                buffer[cnt-1] = '0';
                                buffer[cnt++] = '.';
                                break;
                            }
                            if (i == 0)
                            {
                                buffer[i] = '1';
                                buffer[cnt-1] = '0';
                                buffer[cnt++] = '.';
                                break;
                            }
                            buffer[i] = 48;
                            buffer[i-1]++;
                        }
                    }
                    s2541 = quick_floats[precision][format_b_b._1 & 255];
                    for (int i = 0; i < precision; i++)
                    {
                        buffer[cnt++] = s2541[i];
                    }
                }
                else
                {
                    for (int i = 0; i < 8; i++)
                    {
                        buffer[cnt++] = quick_float_8[format_b_b._1 & 255][i];
                    }
                    for (int i = 8; i < precision; i++)
                    {
                        buffer[cnt++] = '0';
                    }
                    goto function_return;
                }
            }
            else if (precision == 0)
            {
                if ((format_b_b._1 & 255) > 128 || ((format_b_b._1 & 255) == 128 && (buffer[cnt-1] & 1)))
                {
                    buffer[cnt-1]++;
                }
                goto carry;
            }
            else
            {
                if (cnt - (*buffer == '-') <= -precision)
                {
                    if (cnt - (*buffer == '-') < -precision)
                    {
                        goto format_f_negp_uncarry;
                    }
                    if (buffer[*buffer == '-'] > '5')
                    {
                    format_f_negp_carry:
                        buffer[*buffer == '-'] = '1';
                        for (int i = (*buffer == '-') + 1; i <= (*buffer == '-') - precision; i++)
                        {
                            buffer[i] = '0';
                        }
                        buffer[cnt++] = '0';
                        goto function_return;
                    }
                    else if (buffer[*buffer == '-'] == '5')
                    {
                        if ((format_b_b._1 & 255) != 0) goto format_f_negp_carry;
                        for (int i = (*buffer == '-') + 1; i < (*buffer == '-') - precision; i++)
                        {
                            if (buffer[i] != 48)
                            {
                                goto format_f_negp_carry;
                            }
                        }
                    }
                format_f_negp_uncarry:
                    buffer[0] = '0';
                    buffer[1] = 0;
                    return 1;
                }
                flag = 0;
                for (int i = cnt-1; i > cnt+precision; i--)
                {
                    if (buffer[i] != '0')
                    {
                        flag = 1;
                        buffer[i] = '0';
                    }
                }
                if (buffer[cnt+precision] > '5' || (buffer[cnt+precision] == '5' && (flag || buffer[cnt+precision-1] & 1 || format_b_b._1)))
                {
                    buffer[cnt+precision] = '0';
                    buffer[cnt+precision-1]++;
                    for (int i = cnt+precision-1; i > (*buffer == '-'); i--)
                    {
                        if (buffer[i] == 58)
                        {
                            buffer[i] = 48;
                            buffer[i-1]++;
                        }
                    }
                    if (buffer[*buffer == '-'] == 58)
                    {
                        buffer[*buffer == '-'] = '1';
                        buffer[cnt++] = '0';
                    }
                    goto function_return;
                }
                buffer[cnt+precision] = '0';
                goto function_return;
            }
        }
        goto function_return;
    case '+':
        *format_length = 2;
        switch (format[1])
        {
        case 'd':
            if (a->_1 >= 0) buffer[cnt++] = '+';
            format_d_type = 0;
            goto format_d;
        default:
            goto unknown_format;
        }
    case 'f':
        *format_length = 1;
        format_d_type = 1;
        goto format_d;
    case 'e':
        *format_length = 1;
        precision = 1;
        format_d_type = 2;
    format_e:
        precision++;
        if (precision <= 0) goto unknown_format;

        if (a->_1 < 0) buffer[cnt++] = '-';
        if (a->_1 == INT64_MIN) tN = 1ull << 63;
        else tN = a->_1 > 0 ? a->_1 : -a->_1;
        p1 = tN >> 8, p2 = tN & 255;
        tD = 1;
        if (p1 == 0)
        {
            if (precision <= 8)
            {
                strcpy(buffer + cnt, quick_float_es[precision][p2]);
                return cnt + precision + 4;
            }
            else
            {
                strcpy(buffer + cnt, quick_float_e8[p2]);
                buffer[cnt + precision + 1] = 'e';
                buffer[cnt + precision + 2] = buffer[cnt + 10];
                buffer[cnt + precision + 3] = buffer[cnt + 11];
                for (int i = cnt + 9; i <= cnt + precision; i++) buffer[i] = '0';
                cnt += precision + 4;
                goto function_return;
            }
        }
        else while (p1 / tD >= 10) tD *= 10, exp++;

        uint64_t int_part = p1 / tD;
        uint64_t rem = p1 % tD;
        buffer[cnt++] = int_part + 48;
        if (precision == 1)
        {
            if (exp == 0)
            {
                if (p2 > 128 || (p2 == 128 && (buffer[cnt-1] & 1))) goto format_e_carry;
                goto format_e_suf;
            }
            if (rem * 2 > tD || (rem * 2 == tD && (buffer[cnt-1] & 1))) goto format_e_carry;
            goto format_e_suf;
        }
        buffer[cnt++] = '.';
        if (precision <= exp)
        {
            for (int i = 0; i < precision; i++)
            {
                rem *= 10;
                buffer[cnt++] = 48 + rem / tD;
                rem %= tD;
            }
            if (precision == exp)
            {
                if (p2 < 128) goto format_e_suf;
                if (p2 > 128) goto format_e_carry;
                if (p1 & 1) goto format_e_carry;
                goto format_e_suf;
            }
            else
            {
                if (rem * 10 < 5 * tD) goto format_e_suf;
                if (rem * 10 > 5 * tD) goto format_e_carry;
                if (p2) goto format_e_carry;
                if (buffer[cnt-1] & 1) goto format_e_carry;
                goto format_e_suf;
            }
        }
        else
        {
            for (int i = 0; i < exp; i++)
            {
                rem *= 10;
                buffer[cnt++] = 48 + rem / tD;
                rem = rem % tD;
            }
            if (precision - exp <= 8)
            {
                if ((precision == 2 && (p2 & 255) == 255) ||
                    (precision == 1 && quick_float_co1[p2 & 255]))
                {
                    flag = *buffer == '-';
                    buffer[cnt-1]++;
                    for (int i = cnt-1; i > flag; i--)
                    {
                        if (buffer[i] == 58) buffer[i] = 48, buffer[i-1]++;
                        else if (buffer[i] == 47) buffer[i]--, buffer[i-1]++; /* '.' + 1 = 47 */
                        else goto format_e_next1;
                    }
                    if (buffer[flag] == 58)
                    {
                        buffer[flag] = '1';
                        buffer[cnt++] = '0';
                        exp++;
                    }
                }
            format_e_next1:
                for (int i = 0; i < precision - exp - 1; i++)
                {
                    buffer[cnt++] = quick_floats[precision][p2][i];
                }
            }
            else
            {
                for (int i = 0; i < 8; i++) buffer[cnt++] = quick_float_8[p2][i];
                for (int i = 0; i < precision - 9; i++) buffer[cnt++] = '0';
            }
        }
        goto format_e_suf;
    format_e_carry:
        flag = *buffer == '-';
        buffer[cnt-1]++;
        for (int i = cnt-1; i > flag; i--)
        {
            if (buffer[i] == 58) buffer[i] = 48, buffer[i-1]++;
            else if (buffer[i] == 47) buffer[i]--, buffer[i-1]++; /* '.' + 1 = 47 */
            goto format_e_suf;
        }
        if (buffer[flag] == 58)
        {
            buffer[flag] = '1';
            exp++;
        }
        goto format_e_suf;
    format_e_suf:
        if (format_d_type == 2) buffer[cnt++] = 'e';
        else buffer[cnt++] = 'E';
        if (exp >= 0) buffer[cnt++] = '+';
        else buffer[cnt++] = '-', exp = -exp;
        if (exp > 10) buffer[cnt++] = exp / 10 | 48;
        buffer[cnt++] = exp % 10 | 48;
        goto function_return;
    case 'E':
        *format_length = 1;
        precision = 1;
        format_d_type = 3;
        goto format_e;
    case 'B':
        *format_length = 1;
        if (a->_1)
        {
            strcpy(buffer, "true");
            return 4;
        }
        else
        {
            strcpy(buffer, "false");
            return 5;
        }
    case '.':
        *format_length = 1;
        if (format[1] == '*')
        {
            va_start(argv, format_length);
            precision = va_arg(argv, int);
            *format_length = 2;
        }
        else
        {
            flag = 1;
            while (format[*format_length] == '+' || format[*format_length] == '-')
            {
                if (format[(*format_length)++] == '-')
                {
                    flag ^= 1;
                }
            }
            while (isdigit(format[*format_length]))
            {
                precision = precision * 10 + (format[(*format_length)++] & 15);
            }
            if (!flag) precision = -precision;
        }
        switch (format[(*format_length)++])
        {
            case 'f':
                format_d_type = 5;
                goto format_d;
            case 'e':
                format_d_type = 2;
                goto format_e;
            case 'E':
                format_d_type = 3;
                goto format_e;
        }
        goto unknown_format;
    }
unknown_format:
    *format_length = 0;
    strcpy(buffer, "unknown format");
    return -1;
carry:
    if (*buffer == '-')
    {
        for (int i = cnt-1; i > 1; i--)
        {
            if (buffer[i] != 58)
            {
                goto function_return;
            }
            else
            {
                buffer[i] = 48;
                buffer[i-1]++;
            }
        }
        if (buffer[1] == 58)
        {
            if (format_d_type == 5)
            {
                buffer[1] = '1';
                buffer[cnt++] = 48;
                buffer[cnt] = 0;
            }
        }
    }
    else
    {
        for (int i = cnt-1; i > 0; i--)
        {
            if (buffer[i] != 58)
            {
                goto function_return;
            }
            else
            {
                buffer[i] = 48;
                buffer[i-1]++;
            }
        }
        if (*buffer == 58)
        {
            if (format_d_type == 5)
            {
                buffer[0] = '1';
                buffer[cnt++] = 48;
                buffer[cnt] = 0;
            }
        }
    }
function_return:
    buffer[cnt] = 0;
    return cnt;
}

int pvc_PV_55p8_print(pvc_PV_55p8 *a);
