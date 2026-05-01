#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>
#include "pvc_PV_55p8.h"

typedef struct {
    PyObject_HEAD
    pvc_PV_55p8 value;
} PV_55p8Object;

static void PV_55p8dealloc(PV_55p8Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *PV_55p8new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PV_55p8Object *self;
    self = (PV_55p8Object *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->value._1 = 0;
    }
    return (PyObject *) self;
}

static int PV_55p8init(PV_55p8Object *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"value", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|L", kwlist, &self->value._1))
        return -1;
    return 0;
}

static PyObject *PV_55p8Object_strvalue(PV_55p8Object *self, PyObject *Py_UNUSED(unused))
{
    return PyUnicode_FromFormat("%s", pvc_PV_55p8_tostring(&self->value));
}

static PyMethodDef PV_55p8methods[] = {
    {"strvalue", (PyCFunction)PV_55p8Object_strvalue, METH_NOARGS, "Return the value by string"},
    {NULL, NULL, 0, NULL}
};

static PyTypeObject PV_55p8Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "py_PV_55p8.PV_55p8",
    .tp_doc = PyDoc_STR("PV_55p8 Objects"),
    .tp_basicsize = sizeof(PV_55p8Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = PV_55p8new,
    .tp_init = (initproc)PV_55p8init,
    .tp_dealloc = (destructor)PV_55p8dealloc,
    .tp_methods = PV_55p8methods
};

static int PV_55p8module_exec(PyObject *m)
{
    if (PyType_Ready(&PV_55p8Type) < 0)
    {
        return -1;
    }

    if (PyModule_AddObjectRef(m, "PV_55p8", (PyObject *)&PV_55p8Type) < 0)
    {
        return -1;
    }

    return 0;
}

static PyModuleDef_Slot PV_55p8module_slots[] = {
    {Py_mod_exec,                  PV_55p8module_exec},
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
    {0, NULL}
};

static PyModuleDef PV_55p8module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "PV_55p8",
    .m_doc = "A module defines PV_55p8.",
    .m_size = 0,
    .m_slots = PV_55p8module_slots
};

PyMODINIT_FUNC PyInit_PV_55p8(void)
{
    return PyModuleDef_Init(&PV_55p8module);
}
