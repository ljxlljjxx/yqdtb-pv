#include "py_PV_str.h"

static void PV_str_dealloc(PV_str_Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *PV_str_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PV_str_Object *self;
    self = (PV_str_Object *)type->tp_alloc(type, 0);
    return (PyObject *)self;
}

static PyTypeObject PV_str_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "PV_str.PV_str",
    .tp_doc = PyDoc_STR("PV_str Objects"),
    .tp_basicsize = sizeof(PV_str_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)PV_str_new,
    .tp_dealloc = (destructor)PV_str_dealloc,
};

static int pv_str_exec(PyObject *m)
{
    if (PyType_Ready(&PV_str_Type) < 0) return -1;
    if (PyModule_AddObject(m, "PV_str", (PyObject *)&PV_str_Type) < 0) return -1;
#ifdef DEBUG
    __debug_file = fopen("pv_str_debug.log", "a");
    printf("__debug_file: %p\n", __debug_file);
    PyObject *capsule = PyCapsule_New((void *)__debug_file, "pv_str.__debug_file", NULL);
    PyModule_AddObject(m, "__debug_file", capsule);
#endif
    if (!m) return -1;
    return 0;
}

static PyModuleDef_Slot pv_str_slots[] = {
    {Py_mod_exec,                  (void *)pv_str_exec},
#if PY_VERSION_HEX >= 0x030C0000
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
#endif
    {0, NULL}
};

static PyModuleDef pv_str_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "pv_str",
    .m_doc = "A module defines PV_str.",
    .m_size = 0,
    .m_slots = pv_str_slots,
};

PyMODINIT_FUNC PyInit_pv_str(void)
{
    return PyModuleDef_Init(&pv_str_module);
}
