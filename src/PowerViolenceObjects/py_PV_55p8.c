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

static PyObject *PV_55p8_add(PyObject *a, PyObject *b)
{
    if (!PyObject_TypeCheck(a, g_PV_num_Type) || !PyObject_TypeCheck(b, g_PV_num_Type))
    {
        Py_RETURN_NOTIMPLEMENTED;
    }
}

static PyObject *PV_55p8_sub(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_mul(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_mod(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_pow(PyObject *a, PyObject *b, PyObject *c) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_divmod(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_truediv(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_floordiv(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_neg(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_pos(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_abs(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
int PV_55p8_bool(PyObject *a) { return (a != 0); }
static PyObject *PV_55p8_invert(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_int(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_float(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_lshift(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_rshift(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_and(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_xor(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_or(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }

static PyObject *PV_55p8_iadd(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_isub(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_imul(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_imod(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_ipow(PyObject *a, PyObject *b, PyObject *c) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_idivmod(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_itruediv(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_ifloordiv(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_ilshift(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_irshift(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_iand(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_ixor(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_55p8_ior(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }

static PyObject *PV_55p8_index(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }

static PyNumberMethods PV_55p8_as_number = {
    .nb_add = (binaryfunc)PV_55p8_add,
    .nb_subtract = (binaryfunc)PV_55p8_sub,
    .nb_multiply = (binaryfunc)PV_55p8_mul,
    .nb_remainder = (binaryfunc)PV_55p8_mod,
    .nb_divmod = (binaryfunc)PV_55p8_divmod,
    .nb_power = (ternaryfunc)PV_55p8_pow,
    .nb_negative = (unaryfunc)PV_55p8_neg,
    .nb_positive = (unaryfunc)PV_55p8_pos,
    .nb_absolute = (unaryfunc)PV_55p8_abs,
    .nb_bool = (inquiry)PV_55p8_bool,
    .nb_invert = (unaryfunc)PV_55p8_invert,
    .nb_int = (unaryfunc)PV_55p8_int,
    .nb_float = (unaryfunc)PV_55p8_float,
    .nb_lshift = (binaryfunc)PV_55p8_lshift,
    .nb_rshift = (binaryfunc)PV_55p8_rshift,
    .nb_and = (binaryfunc)PV_55p8_and,
    .nb_xor = (binaryfunc)PV_55p8_xor,
    .nb_or = (binaryfunc)PV_55p8_or,

    .nb_inplace_add = (binaryfunc)PV_55p8_iadd,
    .nb_inplace_subtract = (binaryfunc)PV_55p8_isub,
    .nb_inplace_multiply = (binaryfunc)PV_55p8_imul,
    .nb_inplace_remainder = (binaryfunc)PV_55p8_imod,
    .nb_inplace_power = (ternaryfunc)PV_55p8_ipow,
    .nb_inplace_lshift = (binaryfunc)PV_55p8_ilshift,
    .nb_inplace_rshift = (binaryfunc)PV_55p8_irshift,
    .nb_inplace_and = (binaryfunc)PV_55p8_iand,
    .nb_inplace_xor = (binaryfunc)PV_55p8_ixor,
    .nb_inplace_or = (binaryfunc)PV_55p8_ior,

    .nb_true_divide = (binaryfunc)PV_55p8_truediv,
    .nb_floor_divide = (binaryfunc)PV_55p8_floordiv,
    .nb_inplace_true_divide = (binaryfunc)PV_55p8_itruediv,
    .nb_inplace_floor_divide = (binaryfunc)PV_55p8_ifloordiv,

    .nb_index = (unaryfunc)PV_55p8_index,
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
    if (PyModule_AddObjectRef(m, "PV_55p8", (PyObject *)&PV_55p8_Type) < 0) return -1;
    return 0;
}

static PyModuleDef_Slot PV_55p8_module_slots[] = {
    {Py_mod_exec,                  PV_55p8_module_exec},
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
    {0, NULL}
};

void PV_55p8_module_free(void *Py_UNUSED(module))
{
    if (g_PV_num_Type)
    {
        Py_DECREF(g_PV_num_Type);
        g_PV_num_Type = NULL;
    }
}

static PyModuleDef PV_55p8_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "PV_55p8",
    .m_doc = "A module defines PV_55p8.",
    .m_size = 0,
    .m_slots = PV_55p8_module_slots,
    .m_free = PV_55p8_module_free,
};

PyMODINIT_FUNC PyInit_PV_55p8(void)
{
    PyObject *base_module = PyImport_ImportModule("PowerViolenceObjects.PV_num");
    if (!base_module) return NULL;
    g_PV_num_Type = (PyTypeObject *)PyObject_GetAttrString(base_module, "PV_num");
    PyObject *capsule = PyObject_GetAttrString(base_module, "_register_type_capsule");
    register_type_func_t register_func = (register_type_func_t)PyCapsule_GetPointer(capsule, "PV_num.register_type");
    Py_DECREF(base_module);
    if (!g_PV_num_Type || !register_func) return NULL;

    (&PV_55p8_Type)->tp_base = g_PV_num_Type;
    if (PyType_Ready(&PV_55p8_Type) < 0)
    {
        Py_DECREF(g_PV_num_Type);
        return NULL;
    }

    if (!register_func(PVF_55P, &PV_55p8_Type)) return NULL;

    return PyModuleDef_Init(&PV_55p8_module);
}
