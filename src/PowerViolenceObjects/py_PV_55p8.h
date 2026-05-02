#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>
#include "pvc_PV_55p8.h"

static PyTypeObject PV_55p8_Type;

typedef struct {
    PyObject_HEAD
    pvc_PV_55p8 value;
} PV_55p8_Object;
