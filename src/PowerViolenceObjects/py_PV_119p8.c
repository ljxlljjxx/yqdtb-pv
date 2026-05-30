#include "py_PV_119p8.h"

static void PV_119p8_dealloc(PV_119p8_Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *PV_119p8_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PV_num_Object *obj = (PV_num_Object *)g_PV_num_Type->tp_new(type, args, kwds);
    PV_119p8_Object *self;
    if (!obj) return NULL;
    obj->type_id = PVF_119;
    self = (PV_119p8_Object *)obj;
    if (self != NULL)
    {
        self->value._1 = 0ll;
        self->value._2 = 0ull;
    }
    return (PyObject *)self;
}

static int PV_119p8_init(PV_119p8_Object *self, PyObject *args, PyObject *kwds)
{
    PyObject *value = NULL;
    static char *kwlist[] = {"value", NULL};
    double val = 0.0;
    int ret;
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist, &value))
        return -1;
    if (value)
    {
        if (PyFloat_Check(value))
        {
            val = PyFloat_AsDouble(value);
            pvc_PV_119p8_set(&self->value, val);
            return 0;
        }
        else
        {
            int is_pv_num = PyObject_IsInstance(value, (PyObject *)g_PV_num_Type);
            if (is_pv_num == -1) return -1;
            if (is_pv_num)
            {
                if (TYPE_TRANSFORM_CHECK(PVF_119, GET_TYPE_ID(value)))
                {
                    PyErr_SetString(PyExc_RuntimeError, "uninit type transform.");
                    return -1;
                }
                ret = TYPE_TRANSFORM_TYPE(self, value, PVF_119);
                if (!ret) return 0;
                raise_overflow();
            }
            else
            {
                PyErr_SetString(PyExc_TypeError,  "value must be a float or PV_num instance");
                return -1;
            }
        }
    }
    return 0;
}

static PyObject *PV_119p8_richcmp(PyObject *lhs, PyObject *rhs, int op)
{
    int64_t a1 = ((PV_119p8_Object *)lhs)->value._1, b1 = ((PV_119p8_Object *)rhs)->value._1;
    int64_t a2 = ((PV_119p8_Object *)lhs)->value._2, b2 = ((PV_119p8_Object *)rhs)->value._2;
    int c = 0;
    PyObject *result;
    if (!PyObject_TypeCheck(lhs, &PV_119p8_Type) || !PyObject_TypeCheck(rhs, &PV_119p8_Type))
    {
        Py_RETURN_NOTIMPLEMENTED;
    }
    switch (op)
    {
    case Py_LT: c = a1 < b1 || (a1 == b1 && a2 < b2); break;
    case Py_LE: c = a1 < b1 || (a1 == b1 && a2 <= b2); break;
    case Py_EQ: c = a1 == b1 && a2 == b2; break;
    case Py_NE: c = a1 != b1 || a2 != b2; break;
    case Py_GE: c = a1 > b1 || (a1 == b1 && a2 >= b2); break;
    case Py_GT: c = a1 > b1 || (a1 == b1 && a2 > b2); break;
    default: 
        PyErr_SetString(PyExc_SystemError, "Unknown op");
        return NULL;
    }
    result = c ? Py_True : Py_False;
    return Py_NewRef(result);
}

static Py_hash_t PV_119p8_hash(PyObject *op)
{
    Py_hash_t result = (Py_hash_t)((PV_119p8_Object *)op)->value._2;
    if (result == -1) return -2;
    return result;
}

static PyObject *PV_119p8_str(PyObject *op)
{
    return PyUnicode_FromString(pvc_PV_119p8_tostring(&((PV_119p8_Object *)op)->value));
}

static PyObject *PV_119p8_Object_strvalue(PV_119p8_Object *self, PyObject *Py_UNUSED(unused))
{
    return PyUnicode_FromString(pvc_PV_119p8_tostring(&self->value));
}

static PyMethodDef PV_119p8_methods[] = {
    {"strvalue", (PyCFunction)PV_119p8_Object_strvalue, METH_NOARGS, "Return the value by string"},
    {NULL, NULL, 0, NULL}
};

static int PV_119p8_set__value(PyObject *op, PyObject *value, void *closure)
{
    PV_119p8_Object *self = (PV_119p8_Object *)op;
    unsigned char s[16];
    uint64_t high, low;
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
    if (_PyLong_AsByteArray(value, s, 16, 1, 1, 1)) return -1;
    for (int i = 7; i >= 0; --i)
    {
        low  = (low << 8) | s[i];
        high = (high << 8) | s[i + 8];
    }
    self->value._1 = (int64_t)high;
    self->value._2 = low;
    return 0;
}

static PyObject *PV_119p8_get__value(PyObject *op, void *closure)
{
    PV_119p8_Object *self = (PV_119p8_Object *)op;
    unsigned char s[16];
    for (int i = 0; i < 8; ++i)
    {
        s[i]     = self->value._2 >> (i << 3) & 0xFF;
        s[i + 8] = self->value._1 >> (i << 3) & 0xFF;
    }
    return _PyLong_FromByteArray(s, 16, 1, 1);
}

static PyGetSetDef PV_119p8_getsetters[] = {
    {"_value", PV_119p8_get__value, PV_119p8_set__value, "the precise value", NULL},
    {NULL, NULL, NULL, NULL, NULL}
};

static PyTypeObject PV_119p8_Type = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "pv_119p8.PV_119p8",
    .tp_doc = PyDoc_STR("PV_119p8 Objects"),
    .tp_basicsize = sizeof(PV_119p8_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_richcompare = (richcmpfunc)PV_119p8_richcmp,
    .tp_hash = (hashfunc)PV_119p8_hash,
    .tp_str = (reprfunc)PV_119p8_str,
    .tp_new = (newfunc)PV_119p8_new,
    .tp_init = (initproc)PV_119p8_init,
    .tp_dealloc = (destructor)PV_119p8_dealloc,
    .tp_methods = PV_119p8_methods,
    .tp_getset = PV_119p8_getsetters,
};

static int pv_119p8_exec(PyObject *m)
{
    PyObject *base_module = PyImport_ImportModule("PowerViolenceObjects.pv_num");
    if (!base_module) return -1;
    g_PV_num_Type = (PyTypeObject *)PyObject_GetAttrString(base_module, "PV_num");
    PyObject *capsule = PyObject_GetAttrString(base_module, "_register_type_capsule");
    register_type_func_t register_func = (register_type_func_t)PyCapsule_GetPointer(capsule, "pv_num.register_type");
#ifdef DEBUG
    capsule = PyObject_GetAttrString(base_module, "__debug_file");
    __debug_file = (PyObject *)PyCapsule_GetPointer(capsule, "pv_num.__debug_file");
#endif
    Py_DECREF(base_module);
    if (!g_PV_num_Type || !register_func) return -1;

    (&PV_119p8_Type)->tp_base = g_PV_num_Type;
    if (PyType_Ready(&PV_119p8_Type) < 0)
    {
        Py_DECREF(g_PV_num_Type);
        return -1;
    }
    if (register_func(PVF_119, &PV_119p8_Type)) return -1;
    if (PyModule_AddObject(m, "PV_119p8", (PyObject *)&PV_119p8_Type) < 0) return -1;
    return 0;
}

static PyModuleDef_Slot pv_119p8_slots[] = {
    {Py_mod_exec,                  (void *)pv_119p8_exec},
#if PY_VERSION_HEX >= 0x030C0000
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
#endif
    {0, NULL}
};

void pv_119p8_free(void *Py_UNUSED(module))
{
    if (g_PV_num_Type)
    {
        Py_DECREF(g_PV_num_Type);
        g_PV_num_Type = NULL;
    }
}

static PyModuleDef pv_119p8 = {
    PyModuleDef_HEAD_INIT,
    .m_name = "pv_119p8",
    .m_doc = "A module defines PV_119p8.",
    .m_size = 0,
    .m_slots = pv_119p8_slots,
    .m_free = pv_119p8_free,
};

PyMODINIT_FUNC PyInit_pv_119p8(void)
{
    return PyModuleDef_Init(&pv_119p8);
}
