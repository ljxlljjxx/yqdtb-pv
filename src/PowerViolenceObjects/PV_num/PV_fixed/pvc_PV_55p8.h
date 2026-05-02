#ifndef _PVC_PV_55P8_H
#define _PVC_PV_55P8_H

#include "pvc_defines.h"

typedef struct pvc_PV_55p8
{
    int64_t  _1;
} pvc_PV_55p8;

bool pvc_PV_55p8_add(const pvc_PV_55p8 *a, const pvc_PV_55p8 *b, pvc_PV_55p8 *restrict res);
bool pvc_PV_55p8_neg(pvc_PV_55p8 *a);
char *pvc_PV_55p8_tostring(const pvc_PV_55p8 *a);
int pvc_PV_55p8_format(char *restrict buffer, const char *restrict format, const pvc_PV_55p8 *restrict a, int *format_length, ...);
int pvc_PV_55p8_print(const pvc_PV_55p8 *a);

#endif /* _PVC_PV_55P8_H */
