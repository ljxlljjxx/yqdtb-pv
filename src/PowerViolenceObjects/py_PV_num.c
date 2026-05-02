#include "py_PV_num.h"

static void PV_num_dealloc(PV_num_Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *PV_num_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PV_num_Object *self;
    self = (PV_num_Object *)type->tp_alloc(type, 0);
    return (PyObject *) self;
}

static PyTypeObject PV_num_Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "PV_num.PV_num",
    .tp_doc = PyDoc_STR("PV_num Objects"),
    .tp_basicsize = sizeof(PV_num_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)PV_num_new,
    .tp_dealloc = (destructor)PV_num_dealloc
};

static int PV_num_module_exec(PyObject *m)
{
    if (PyType_Ready(&PV_num_Type) < 0) return -1;
    if (PyModule_AddObjectRef(m, "PV_num", (PyObject *)&PV_num_Type) < 0) return -1;
    return 0;
}

static PyModuleDef_Slot PV_num_module_slots[] = {
    {Py_mod_exec,                  PV_num_module_exec},
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
    {0, NULL}
};

static PyModuleDef PV_num_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "PV_num",
    .m_doc = "A module defines PV_num.",
    .m_size = 0,
    .m_slots = PV_num_module_slots
};

PyMODINIT_FUNC PyInit_PV_num(void)
{
    return PyModuleDef_Init(&PV_num_module);
}

