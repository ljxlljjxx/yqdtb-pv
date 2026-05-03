#include "py_PV_55p8.h"

static void PV_55p8_dealloc(PV_55p8_Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *PV_55p8_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PV_55p8_Object *self;
    self = (PV_55p8_Object *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->value._1 = 0;
    }
    return (PyObject *) self;
}

static int PV_55p8_init(PV_55p8_Object *self, PyObject *args, PyObject *kwds)
{
    static char *kwlist[] = {"value", NULL};
    double tmp;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|d", kwlist, &tmp))
        return -1;
    self->value._1 = tmp * 256;
    return 0;
}

static PyObject *PV_55p8_richcmp(PyObject *lhs, PyObject *rhs, int op)
{
    int64_t a = ((PV_55p8_Object *)lhs)->value._1, b = ((PV_55p8_Object *)rhs)->value._1;
    int c;
    PyObject *result;
    if (!PyObject_TypeCheck(lhs, &PV_55p8_Type) || !PyObject_TypeCheck(rhs, &PV_55p8_Type))
    {
        Py_RETURN_NOTIMPLEMENTED;
    }
    switch (op)
    {
    case Py_LT: c = a < b; break;
    case Py_LE: c = a <= b; break;
    case Py_EQ: c = a == b; break;
    case Py_NE: c = a != b; break;
    case Py_GE: c = a >= b; break;
    case Py_GT: c = a > b; break;
    }
    result = c ? Py_True : Py_False;
    return Py_NewRef(result);
}

static Py_hash_t PV_55p8_hash(PyObject *op)
{
    Py_hash_t result = ((PV_55p8_Object *)op)->value._1;
    if (result == -1) return -2;
    return result;
}

static PyObject *PV_55p8_str(PyObject *op)
{
    return PyUnicode_FromString(pvc_PV_55p8_tostring(&((PV_55p8_Object *)op)->value));
}

static PyObject *PV_55p8_Object_strvalue(PV_55p8_Object *self, PyObject *Py_UNUSED(unused))
{
    return PyUnicode_FromString(pvc_PV_55p8_tostring(&self->value));
}

static PyMethodDef PV_55p8_methods[] = {
    {"strvalue", (PyCFunction)PV_55p8_Object_strvalue, METH_NOARGS, "Return the value by string"},
    {NULL, NULL, 0, NULL}
};

static int PV_55p8_set__value(PyObject *op, PyObject *value, void *closure)
{
    PV_55p8_Object *self = (PV_55p8_Object *)op;
    if (value == NULL)
    {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the _value attribute");
        return -1;
    }
    if (!PyLong_Check(value))
    {
        PyErr_Format(PyExc_TypeError, "The 'first' attribute must be an int, not '%.200s'", Py_TYPE(value)->tp_name);
        return -1;
    }
    if (PyLong_AsInt64(value, &self->value._1)) return -1;
    return 0;
}

static PyObject *PV_55p8_get__value(PyObject *op, void *closure)
{
    PV_55p8_Object *self = (PV_55p8_Object *)op;
    return PyLong_FromInt64(self->value._1);
}

static PyGetSetDef PV_55p8_getsetters[] = {
    {"_value", PV_55p8_get__value, PV_55p8_set__value, NULL},
    {NULL, NULL, NULL, NULL}
};

static PyTypeObject PV_55p8_Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "PV_55p8.PV_55p8",
    .tp_doc = PyDoc_STR("PV_55p8 Objects"),
    .tp_basicsize = sizeof(PV_55p8_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_richcompare = (richcmpfunc)PV_55p8_richcmp,
    .tp_hash = (hashfunc)PV_55p8_hash,
    .tp_str = (reprfunc)PV_55p8_str,
    .tp_new = (newfunc)PV_55p8_new,
    .tp_init = (initproc)PV_55p8_init,
    .tp_dealloc = (destructor)PV_55p8_dealloc,
    .tp_methods = PV_55p8_methods,
    .tp_getset = PV_55p8_getsetters,
};

static int PV_55p8_module_exec(PyObject *m)
{
    if (PyType_Ready(&PV_55p8_Type) < 0) return -1;
    if (PyModule_AddObjectRef(m, "PV_55p8", (PyObject *)&PV_55p8_Type) < 0) return -1;
    return 0;
}

static PyModuleDef_Slot PV_55p8_module_slots[] = {
    {Py_mod_exec,                  PV_55p8_module_exec},
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
    {0, NULL}
};

static PyModuleDef PV_55p8_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "PV_55p8",
    .m_doc = "A module defines PV_55p8.",
    .m_size = 0,
    .m_slots = PV_55p8_module_slots
};

PyMODINIT_FUNC PyInit_PV_55p8(void)
{
    PyObject *base_module = PyImport_ImportModule("PowerViolenceObjects.PV_fixed");
    if (!base_module) return NULL;
    PyObject *base_type = PyObject_GetAttrString(base_module, "PV_fixed");
    Py_DECREF(base_module);
    if (!base_type) return NULL;
    
    ((PyTypeObject*)&PV_55p8_Type)->tp_base = (PyTypeObject*)base_type;
    if (PyType_Ready(&PV_55p8_Type) < 0) {
        Py_DECREF(base_type);
        return NULL;
    }
    Py_DECREF(base_type);
    return PyModuleDef_Init(&PV_55p8_module);
}
