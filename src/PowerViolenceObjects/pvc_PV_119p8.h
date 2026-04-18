#include "pvc_defines.h"

typedef struct pvc_PV_119p8
{
    int64_t  _1;
    uint64_t _2;
} pvc_PV_119p8;

bool pvc_PV_119p8_add(pvc_PV_119p8 *a, pvc_PV_119p8 *b, pvc_PV_119p8 *restrict res);
bool pvc_PV_119p8_neg(pvc_PV_119p8 *a);
char *pvc_PV_119p8_tostring(pvc_PV_119p8 *a);
int pvc_PV_119p8_format(char *restrict buffer, const char *restrict format, pvc_PV_119p8 *restrict a, ...);
void pvc_PV_119p8_print(pvc_PV_119p8 *a);
