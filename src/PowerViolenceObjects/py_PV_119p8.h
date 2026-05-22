#ifndef _PY_PV_119p8_H
#define _PY_PV_119p8_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>
#include "py_PV_num.h"
#include "pvc_PV_119p8.h"

static PyTypeObject PV_119p8_Type;
static PyTypeObject *g_PV_num_Type;

typedef struct {
    PV_num_Object base;
    pvc_PV_119p8 value;
} PV_119p8_Object;

#endif /* _PY_PV_119p8_H */
