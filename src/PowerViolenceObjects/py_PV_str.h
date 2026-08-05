#ifndef _PY_PV_str_H
#define _PY_PV_str_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>
#include "pvc_debug.h"

typedef struct {
    PyObject_HEAD
} PV_str_Object;

static PyTypeObject *g_PV_str_Type;

#endif /* _PY_PV_str_H */
