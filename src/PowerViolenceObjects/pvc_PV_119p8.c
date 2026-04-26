#include "pvc_PV_119p8.h"

/**
 * @brief   use __int128_t to set pvc_PV_119p8
 * @param   res pvc_PV_119p8 *
 * @param   a __int128_t *
 * @warning This function does not check whether the parameter is null.
 * @author  ljx
 * @date    2026-04-24 20:12
 */
void pvc_PV_119p8_set(pvc_PV_119p8 *res, __int128_t *a)
{
    const __int128_t pos = (__int128_t)1 << 64;
    res->_2 = *a % pos;
    res->_1 = *a / pos;
}

/**
 * @brief   set *res to *a + *b
 * @param   a pvc_PV_119p8 *
 * @param   b 参数pvc_PV_119p8 *
 * @param   res pvc_PV_119p8 *restrict
 * @return  bool
 * @retval  overflow
 * @warning This function does not check whether the parameter is null.
 * @author  ljx
 * @date    2026-04-24 20:14
 */
bool pvc_PV_119p8_add(pvc_PV_119p8 *a, pvc_PV_119p8 *b, pvc_PV_119p8 *restrict res)
{
    res->_2 = a->_2 + b->_2;
    res->_1 = a->_1 + b->_1 + (res->_2 < a->_2);
    if ((!((a->_1 ^ b->_1) & INT64_MIN)) && ((a->_1 ^ res->_1) & INT64_MIN))
    {
        res->_1 = res->_2 = 0;
        return true;
    }
    return false;
}

/**
 * @brief   let *a becomes -*a.
 * @param   a pvc_PV_119p8 *
 * @return  bool
 * @retval  overflow
 * @warning This function does not check whether the parameter is null.
 * @author  ljx
 * @date    2026-04-17 21:48
 */
bool pvc_PV_119p8_neg(pvc_PV_119p8 *a)
{
    if (a->_2) a->_2 = -a->_2, a->_1 = ~a->_1;
    else if (a->_1 == INT64_MIN) return true;
    else a->_1 = -a->_1;
    return false;
}

/**
 * @brief   print pvc_PV_119p8 int string
 * @param   a pvc_PV_119p8 *
 * @return  char *
 * @retval  return the string
 * @note    the return value is const.
 * @author  ljx
 * @date    2026-04-26 11:22
 */
char *pvc_PV_119p8_tostring(pvc_PV_119p8 *a)
{
    static char buffer[40];
    static char temp[40];
    size_t temp_size = 0, cnt = 0;
    uint64_t high, low, tmp;
    pvc_PV_119p8 b;
    if (a == NULL) return strcpy(buffer, "(null)");
    if (!a->_1)
    {
        if (!a->_2)
        {
            *buffer = 48;
            buffer[1] = 0;
            return buffer;
        }
        tmp = a->_2 >> 8;
        while (tmp)
        {
            temp[temp_size++] = tmp % 10 | 48;
            tmp /= 10;
        }
        while (temp_size)
        {
            buffer[cnt++] = temp[--temp_size];
        }
        if (a->_2 & 255)
        {
            buffer[cnt++] = '.';
            strcpy(buffer + cnt, quick_float[a->_2 & 255]);
        }
        else buffer[cnt] = 0;
        return buffer;
    }
    b = *a;
    if (b._1 & INT64_MIN)
    {
        buffer[cnt++] = '-';
        if (pvc_PV_119p8_neg(&b))
        {
            strcpy(buffer+1, pvc_PV_119p8_max);
            return buffer;
        }
    }
    high = b._1;
    low = b._2 >> 8;
    while (low || high)
    {
        tmp = high % 10;
        temp[temp_size++] = (6 * tmp + low) % 10 | 48;
        low = ((tmp << 56) + low) / 10;
        high /= 10;
    }
    while (temp_size)
    {
        buffer[cnt++] = temp[--temp_size];
    }
    if (b._2 & 255)
    {
        buffer[cnt++] = '.';
        strcpy(buffer + cnt, quick_float[b._2 & 255]);
    }
    else
    {
        buffer[cnt] = 0;
    }
    return buffer;
}

/**
 * @brief   use format to write pvc_PV_119p8.
 * @param   buffer char *restrict. the string will write here.
 * @param   format a string. Legal format:
        (Achieved) (Tested) hi: high, int64_t
        (Achieved) (Tested) hu: high, uint64_t
        (Achieved) (Tested) hx: high, hexadecimal
        (Achieved) (Tested) li: low,  int64_t
        (Achieved) (Tested) lu: low,  uint64_t
        (Achieved) (Tested) lx: low,  hexadecimal
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
 * @date    2026-04-26 11:28
 */
int pvc_PV_119p8_format(char *restrict buffer, const char *restrict format, pvc_PV_119p8 *restrict a, int *format_length, ...)
{
    int cnt = 0;
    static char format_b_temp[40];
    int format_b_temp_size = 0;
    uint64_t format_b_high, format_b_low, format_b_tmp;
    pvc_PV_119p8 format_b_b;

    int precision = 0;
    va_list argv;
    int format_d_type;
    const char *s2541;

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
    case 'h':
        *format_length = 2;
        switch (format[1])
        {
        case 'i': return sprintf(buffer, "%lld", a->_1);
        case 'u': return sprintf(buffer, "%llu", a->_1);
        case 'x': return sprintf(buffer, "%016llx", a->_1);;
        default: goto unknown_format;
        }
    case 'l':
        *format_length = 2;
        switch (format[1])
        {
        case 'i': return sprintf(buffer, "%lld", a->_2);
        case 'u': return sprintf(buffer, "%llu", a->_2);
        case 'x': return sprintf(buffer, "%016llx", a->_2);
        default:  goto unknown_format;
        }
    case 'b':
        *format_length = 1;
        for (int i = 63; i >= 0; i--) buffer[cnt++] = ((a->_1 >> i) & 1) | 48;
        for (int i = 63; i >= 0; i--) buffer[cnt++] = ((a->_2 >> i) & 1) | 48;
        buffer[cnt] = 0;
        return 128;
    case 'x':
        *format_length = 1;
        return sprintf(buffer, "%016llx%016llx", a->_1, a->_2);
    case 'X':
        *format_length = 1;
        return sprintf(buffer, "%016llX%016llX", a->_1, a->_2);
    case 'd':
        *format_length = 1;
        format_d_type = 0;
    format_d:
        format_b_b = *a;
        if (!a->_1)
        {
            if (!a->_2)
            {
                buffer[cnt++] = 48;
                buffer[cnt] = 0;
                goto format_d_return;
            }
            format_b_tmp = a->_2 >> 8;
            while (format_b_tmp)
            {
                format_b_temp[format_b_temp_size++] = format_b_tmp % 10 | 48;
                format_b_tmp /= 10;
            }
            while (format_b_temp_size)
            {
                buffer[cnt++] = format_b_temp[--format_b_temp_size];
            }
            buffer[cnt] = 0;
            goto format_d_return;
        }
        if (format_b_b._1 < 0)
        {
            buffer[cnt++] = '-';
            if (pvc_PV_119p8_neg(&format_b_b))
            {
                strcpy(buffer+cnt, pvc_PV_119p8_max);
                cnt += 36;
                goto format_d_return;
            }
        }
        format_b_high = format_b_b._1;
        format_b_low = format_b_b._2 >> 8;
        while (format_b_low || format_b_high)
        {
            format_b_tmp = format_b_high % 10;
            format_b_temp[format_b_temp_size++] = (6 * format_b_tmp + format_b_low) % 10 | 48;
            format_b_low = ((format_b_tmp << 56) + format_b_low) / 10;
            format_b_high /= 10;
        }
        while (format_b_temp_size)
        {
            buffer[cnt++] = format_b_temp[--format_b_temp_size];
        }
    format_d_return:
        switch (format_d_type)
        {
        case 0:
            goto function_return;
        case 1:
            buffer[cnt++] = '.';
            strcpy(buffer + cnt, quick_float[format_b_b._2 & 255]);
            return cnt + quick_float_len[format_b_b._2 & 255];
        case 2:
        
        case 5:
            if (precision > 0)
            {
                buffer[cnt++] = '.';
                if (precision <= 8)
                {
                    if (
                        (precision == 2 && (format_b_b._2 & 255) == 255) ||
                        (precision == 1 && quick_float_co1[format_b_b._2 & 255])
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
                    s2541 = quick_floats[precision][format_b_b._2 & 255];
                    for (int i = 0; i < precision; i++)
                    {
                        buffer[cnt++] = s2541[i];
                    }
                }
                else
                {
                    for (int i = 0; i < 8; i++)
                    {
                        buffer[cnt++] = quick_float_8[format_b_b._2 & 255][i];
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
                if ((format_b_b._2 & 255) > 128 || ((format_b_b._2 & 255) == 128 && (buffer[cnt-1] & 1)))
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
                        if ((format_b_b._2 & 255) != 0) goto format_f_negp_carry;
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
                if (buffer[cnt+precision] > '5' || (buffer[cnt+precision] == '5' && (flag || buffer[cnt+precision-1] & 1 || format_b_b._2)))
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
        precision += 1;
        if (precision <= 0) goto unknown_format;
        format_b_b = *a;
        if (a->_1 < 0)
        {
            buffer[cnt++] = '-';
            if (pvc_PV_119p8_neg(&format_b_b))
            {
                buffer[cnt++] = '6';
                flag = 35;
                if (precision > 1) buffer[cnt++] = '.';
                else goto format_e_suf;
                if (precision >= 36)
                {
                    strcpy(buffer + cnt, pvc_PV_119p8_max + 1);
                    cnt += 35;
                    for (int i = 37; i <= precision; i++)
                    {
                        buffer[cnt++] = '0';
                    }
                    goto format_e_suf;
                }
                else
                {
                    strncpy(buffer + cnt, pvc_PV_119p8_max + 1, precision - 1);
                    cnt += precision - 1;
                    goto format_e_suf;
                }
            }
        }
        format_b_high = format_b_b._1;
        format_b_low = format_b_b._2 >> 8;
        while (format_b_low || format_b_high)
        {
        _debug printf("format_b_temp_size = %d\n", format_b_temp_size);
        _debug printf("format_b_temp = %s\n", format_b_temp);
            format_b_tmp = format_b_high % 10;
            format_b_temp[format_b_temp_size++] = (6 * format_b_tmp + format_b_low) % 10 | 48;
            format_b_low = ((format_b_tmp << 56) + format_b_low) / 10;
            format_b_high /= 10;
        }
        flag = format_b_temp_size - 1;
        if (flag < 0)
        {
            if (precision >= 8)
            {
                buffer[cnt++] = *quick_float_8[format_b_b._2 & 255];
                buffer[cnt++] = '.';
                buffer[cnt++] = quick_float_8[format_b_b._2 & 255][1];
                buffer[cnt++] = quick_float_8[format_b_b._2 & 255][2];
                buffer[cnt++] = quick_float_8[format_b_b._2 & 255][3];
                buffer[cnt++] = quick_float_8[format_b_b._2 & 255][4];
                buffer[cnt++] = quick_float_8[format_b_b._2 & 255][5];
                buffer[cnt++] = quick_float_8[format_b_b._2 & 255][6];
                buffer[cnt++] = quick_float_8[format_b_b._2 & 255][7];
                for (int i = 8; i < precision; i++)
                {
                    buffer[cnt++] = '0';
                }
                flag = quick_float_e[format_b_b._2 & 255];
                goto format_e_suf;
            }
            else
            {
                strcpy(buffer + cnt, quick_float_es[precision][format_b_b._2 & 255]);
                cnt += precision + 4;
                goto function_return;
            }
        }
        _debug printf("precision = %d\n", precision);
        _debug printf("format_b_temp_size = %d\n", format_b_temp_size);
        _debug printf("flag = %d\n", flag);
        _debug printf("format_b_temp = %s\n", format_b_temp);
        if (precision >= format_b_temp_size)
        {
            for (int i = flag; i >= 0; i--)
            {
                buffer[cnt++] = format_b_temp[i];
        _debug printf("buffer = %s\n", buffer);
            }
            if (precision - format_b_temp_size == 0)
            {
                goto format_e_suf;
            }
            if (precision - format_b_temp_size <= 8)
            {
                buffer[cnt++] = '.';
                strcpy(buffer + cnt, quick_floats[precision - format_b_temp_size][format_b_b._2 & 255]);
                cnt += precision - format_b_temp_size;
                goto format_e_suf;
            }
            strcpy(buffer + cnt, quick_float_8[format_b_b._2 & 255]);
            cnt += 8;
            while (precision - format_b_temp_size - 8 >= 0)
            {
                buffer[cnt++] = '0';
                precision--;
            }
            goto format_e_suf;
        }
    format_e_suf:
        if (format_d_type == 2) buffer[cnt++] = 'e';
        else buffer[cnt++] = 'E';
        if (flag >= 0) buffer[cnt++] = '+';
        else buffer[cnt++] = '-', flag = -flag;
        if (flag > 10) buffer[cnt++] = flag / 10 | 48;
        buffer[cnt++] = flag % 10 | 48;
        goto function_return;
    case 'E':
        *format_length = 1;
        precision = 1;
        format_d_type = 3;
        goto format_e;
    case 'B':
        *format_length = 1;
        if (a->_2 || a->_1)
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
        switch (format[*format_length])
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

int pvc_PV_119p8_print(pvc_PV_119p8 *a)
{
    static char temp[40];
    size_t temp_size = 0, cnt = 0;
    uint64_t high, low, tmp;
    pvc_PV_119p8 b;
    if (a == NULL) return printf("(null)");
    if (!a->_1)
    {
        if (!a->_2) return printf("0");
        tmp = a->_2 >> 8;
        while (tmp)
        {
            temp[temp_size++] = tmp % 10 | 48;
            tmp /= 10;
        }
        while (temp_size)
        {
            cnt++;
            putchar(temp[--temp_size]);
        }
        // _debug printf("cnt = %zu\n", cnt + printf(".%s", quick_float[a->_2 & 255]));
        if (a->_2 & 255) return cnt + printf(".%s", quick_float[a->_2 & 255]);
        return cnt;
    }
    b = *a;
    if (b._1 & INT64_MIN)
    {
        cnt++;
        putchar('-');
        if (pvc_PV_119p8_neg(&b)) return 1 + printf("%s", pvc_PV_119p8_max);
    }
    high = b._1;
    low = b._2 >> 8;
    while (low || high)
    {
        tmp = high % 10;
        temp[temp_size++] = (6 * tmp + low) % 10 | 48;
        low = ((tmp << 56) + low) / 10;
        high /= 10;
    }
    while (temp_size)
    {
        cnt++;
        putchar(temp[--temp_size]);
    }
    if (b._2 & 255) return cnt + printf(".%s", quick_float[b._2 & 255]);
    else return cnt;
}
