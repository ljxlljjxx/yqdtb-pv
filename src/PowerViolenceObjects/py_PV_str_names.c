#include "py_PV_str_names.h"

static void PV_str_names_dealloc(PV_str_names_Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *PV_str_names_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PV_str_Object *obj = (PV_str_Object *)g_PV_str_Type->tp_new(type, args, kwds);
    PV_str_names_Object *self;
    if (!obj) return NULL;
    self = (PV_str_names_Object *)obj;
    if (self != NULL) self->len = 0;
    return (PyObject *)self;
}

static PyTypeObject PV_str_names_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "PV_str_names.PV_str_names",
    .tp_doc = PyDoc_STR("PV_str_names Objects"),
    .tp_basicsize = sizeof(PV_str_names_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)PV_str_names_new,
    .tp_dealloc = (destructor)PV_str_names_dealloc,
};

static int pv_str_names_exec(PyObject *m)
{
    PyObject *base_module = PyImport_ImportModule("PowerViolenceObjects.pv_str");
    if (!base_module) return -1;
    g_PV_str_Type = (PyTypeObject *)PyObject_GetAttrString(base_module, "PV_str");
    if (PyType_Ready(&PV_str_names_Type) < 0) return -1;
    if (PyModule_AddObject(m, "PV_str_names", (PyObject *)&PV_str_names_Type) < 0) return -1;
#ifdef DEBUG
    PyObject *capsule = PyObject_GetAttrString(base_module, "__debug_file");
    __debug_file = (FILE *)PyCapsule_GetPointer(capsule, "pv_str.__debug_file");
#endif
    if (!m) return -1;
    return 0;
}

static PyModuleDef_Slot pv_str_names_slots[] = {
    {Py_mod_exec,                  (void *)pv_str_names_exec},
#if PY_VERSION_HEX >= 0x030C0000
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
#endif
    {0, NULL}
};

static PyModuleDef pv_str_names_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "pv_str_names",
    .m_doc = "A module defines PV_str_names.",
    .m_size = 0,
    .m_slots = pv_str_names_slots,
};

PyMODINIT_FUNC PyInit_pv_str_names(void)
{
    return PyModuleDef_Init(&pv_str_names_module);
}
