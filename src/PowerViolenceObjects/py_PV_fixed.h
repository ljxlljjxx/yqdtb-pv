#ifndef _PY_PV_fixed_H
#define _PY_PV_fixed_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>
#include "py_PV_num.h"

extern PyTypeObject PV_fixed_Type;

typedef struct {
    PV_num_Object base
} PV_fixed_Object;

#endif /* _PY_PV_fixed_H */
