#ifndef _PY_PV_num_H
#define _PY_PV_num_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>

extern PyTypeObject PV_num_Type;

typedef struct {
    PyObject_HEAD
} PV_num_Object;

#endif /* _PY_PV_num_H */
