#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>

static PyTypeObject PV_num_Type;

typedef struct {
    PyObject_HEAD
} PV_num_Object;
