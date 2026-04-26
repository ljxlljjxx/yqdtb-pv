#include "pvc_PV_57p8.h"

bool pvc_PV_57p8_add(pvc_PV_57p8 *a, pvc_PV_57p8 *b, pvc_PV_57p8 *restrict res)
{
    res->_1 = a->_1 + b->_1;
    if (addi64_overflow(a->_1, b->_1, &res->_1))
    {
        res->_1 = 0;
        return true;
    }
    return false;
}

bool pvc_PV_57p8_neg(pvc_PV_57p8 *a)
{
    if (a->_1 == INT64_MIN)
    {
        a->_1 = 0;
        return true;
    }
    a->_1 = -a->_1;
    return false;
}

char *pvc_PV_57p8_tostring(pvc_PV_57p8 *a)
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
        if (pvc_PV_57p8_neg(a))
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

int pvc_PV_57p8_format(char *restrict buffer, const char *restrict format, pvc_PV_57p8 *restrict a, ...);
int pvc_PV_57p8_print(pvc_PV_57p8 *a);
