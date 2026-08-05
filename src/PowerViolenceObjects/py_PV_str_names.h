#ifndef _PY_PV_str_names_H
#define _PY_PV_str_names_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>
#include "py_PV_str.h"

static PyTypeObject PV_str_names_Type;

typedef struct {
    PV_str_Object base;
    size_t len;
    char value[128];
} PV_str_names_Object;

#endif /* _PY_PV_str_names_H */
