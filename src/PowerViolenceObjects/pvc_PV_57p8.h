#ifndef _PVC_PV_57P8_H
#define _PVC_PV_57P8_H

#include "pvc_defines.h"

typedef struct pvc_PV_57p8
{
    int64_t  _1;
} pvc_PV_57p8;

bool pvc_PV_57p8_add(pvc_PV_57p8 *a, pvc_PV_57p8 *b, pvc_PV_57p8 *restrict res);
bool pvc_PV_57p8_neg(pvc_PV_57p8 *a);
char *pvc_PV_57p8_tostring(pvc_PV_57p8 *a);
int pvc_PV_57p8_format(char *restrict buffer, const char *restrict format, pvc_PV_57p8 *restrict a, int *format_length, ...);
int pvc_PV_57p8_print(pvc_PV_57p8 *a);

#endif /* _PVC_PV_57P8_H */
