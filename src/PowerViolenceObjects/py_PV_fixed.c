#include "py_PV_fixed.h"

static void PV_fixed_dealloc(PV_fixed_Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *PV_fixed_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PV_fixed_Object *self;
    self = (PV_fixed_Object *)type->tp_alloc(type, 0);
    return (PyObject *) self;
}

static PyTypeObject PV_fixed_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "PV_fixed.PV_fixed",
    .tp_doc = PyDoc_STR("PV_fixed Objects"),
    .tp_basicsize = sizeof(PV_fixed_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)PV_fixed_new,
    .tp_dealloc = (destructor)PV_fixed_dealloc,
};

static int PV_fixed_module_exec(PyObject *m)
{
    if (PyType_Ready(&PV_fixed_Type) < 0) return -1;
    if (PyModule_AddObjectRef(m, "PV_fixed", (PyObject *)&PV_fixed_Type) < 0) return -1;
    return 0;
}

static PyModuleDef_Slot PV_fixed_module_slots[] = {
    {Py_mod_exec,                  PV_fixed_module_exec},
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
    {0, NULL}
};

static PyModuleDef PV_fixed_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "PV_fixed",
    .m_doc = "A module defines PV_fixed.",
    .m_size = 0,
    .m_slots = PV_fixed_module_slots
};

PyMODINIT_FUNC PyInit_PV_fixed(void)
{
    PyObject *base_module = PyImport_ImportModule("PowerViolenceObjects.PV_num");
    if (!base_module) return NULL;
    PyObject *base_type = PyObject_GetAttrString(base_module, "PV_num");
    Py_DECREF(base_module);
    if (!base_type) return NULL;
    
    ((PyTypeObject*)&PV_fixed_Type)->tp_base = (PyTypeObject*)base_type;
    if (PyType_Ready(&PV_fixed_Type) < 0) {
        Py_DECREF(base_type);
        return NULL;
    }
    Py_DECREF(base_type);
    return PyModuleDef_Init(&PV_fixed_module);
}
