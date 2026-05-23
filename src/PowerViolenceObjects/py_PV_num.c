#include "py_PV_num.h"

static const int typetype_type[MAX_DERIVED][MAX_DERIVED] = {
    {PVO_NUM, PVI_PID, PVI_SID, PVI_NRS, PVI_LRS, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT},
    {PVI_PID, PVI_PID, PVI_SID, PVI_NRS, PVI_LRS, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT},
    {PVI_SID, PVI_SID, PVI_SID, PVI_NRS, PVI_LRS, PVF_27P, PVF_27P, PVF_55P, PVF_119, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT},
    {PVI_NRS, PVI_NRS, PVI_NRS, PVI_NRS, PVI_LRS, PVF_55P, PVF_55P, PVF_55P, PVF_119, PVC_128, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT},
    {PVI_LRS, PVI_LRS, PVI_LRS, PVI_LRS, PVI_LRS, PVF_119, PVF_119, PVF_119, PVF_119, PVC_128, PVC_128, PVC_256, PVH_NOR, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT},
    {PVF_11P, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT},
    {PVF_27P, PVF_27P, PVF_27P, PVF_55P, PVF_119, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT},
    {PVF_55P, PVF_55P, PVF_55P, PVF_55P, PVF_119, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVC_128, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT},
    {PVF_119, PVF_119, PVF_119, PVF_119, PVF_119, PVF_119, PVF_119, PVF_119, PVF_119, PVC_256, PVC_256, PVC_256, PVH_NOR, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT},
    {PVC_64C, PVC_64C, PVC_64C, PVC_128, PVC_128, PVC_64C, PVC_64C, PVC_128, PVC_256, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVO_PFT, PVO_PFT},
    {PVC_128, PVC_128, PVC_128, PVC_128, PVC_128, PVC_128, PVC_128, PVC_128, PVC_256, PVC_128, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVO_PFT, PVO_PFT},
    {PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVH_NOR, PVH_NOR, PVO_NOR, PVO_PFT, PVO_PFT},
    {PVH_SRT, PVH_SRT, PVH_SRT, PVH_SRT, PVH_NOR, PVH_SRT, PVH_SRT, PVH_SRT, PVH_NOR, PVH_SRT, PVH_SRT, PVH_NOR, PVH_SRT, PVH_NOR, PVO_NOR, PVO_PFT, PVO_PFT},
    {PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVO_NOR, PVO_PFT, PVO_PFT},
    {PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_PFT, PVO_PFT},
    {PVF_447, PVF_447, PVF_447, PVF_447, PVF_447, PVF_447, PVF_447, PVF_447, PVF_447, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVF_447, PVO_PFT},
    {PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT},
};

static const char *type_str[MAX_DERIVED] = {
    "PV_num",
    "PV_pID", 
    "PV_sID", 
    "PV_nRounds", 
    "PV_lRounds", 
    "PV_11p4", 
    "PV_27p4", 
    "PV_55p8", 
    "PV_119p8", 
    "PV_power", 
    "PV_lives", 
    "PV_com64", 
    "PV_quaternion", 
    "PV_s_quaternion", 
    "PV_octonion", 
    "PV_447p64", 
    "PV_perfect"
};

PyTypeObject *g_type_by_id[MAX_DERIVED];

static int register_type(int type_id, PyTypeObject *type)
{
    if (type_id < 0 || type_id >= MAX_DERIVED) return 1;
    g_type_by_id[type_id] = type;
    Py_INCREF(type);
    return 0;
}

static void PV_num_dealloc(PV_num_Object *self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *PV_num_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PV_num_Object *self;
    self = (PV_num_Object *)type->tp_alloc(type, 0);
    self->type_id = 0;
    return (PyObject *)self;
}

static PyObject *PV_num_add(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_sub(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_mul(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_mod(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_pow(PyObject *a, PyObject *b, PyObject *c) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_divmod(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_truediv(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_floordiv(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_neg(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_pos(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_abs(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
// int PV_num_bool(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_invert(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_int(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_float(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_lshift(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_rshift(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_and(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_xor(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_or(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }

static PyObject *PV_num_iadd(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_isub(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_imul(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_imod(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_ipow(PyObject *a, PyObject *b, PyObject *c) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_itruediv(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_ifloordiv(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_ilshift(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_irshift(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_iand(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_ixor(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
static PyObject *PV_num_ior(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }

static PyObject *PV_num_index(PyObject *a) { Py_RETURN_NOTIMPLEMENTED; }

static PyNumberMethods PV_num_as_number = {
    .nb_add = (binaryfunc)PV_num_add,
    .nb_subtract = (binaryfunc)PV_num_sub,
    .nb_multiply = (binaryfunc)PV_num_mul,
    .nb_remainder = (binaryfunc)PV_num_mod,
    .nb_divmod = (binaryfunc)PV_num_divmod,
    .nb_power = (ternaryfunc)PV_num_pow,
    .nb_negative = (unaryfunc)PV_num_neg,
    .nb_positive = (unaryfunc)PV_num_pos,
    .nb_absolute = (unaryfunc)PV_num_abs,
    // .nb_bool = (inquiry)PV_num_bool,
    .nb_invert = (unaryfunc)PV_num_invert,
    .nb_int = (unaryfunc)PV_num_int,
    .nb_float = (unaryfunc)PV_num_float,
    .nb_lshift = (binaryfunc)PV_num_lshift,
    .nb_rshift = (binaryfunc)PV_num_rshift,
    .nb_and = (binaryfunc)PV_num_and,
    .nb_xor = (binaryfunc)PV_num_xor,
    .nb_or = (binaryfunc)PV_num_or,

    .nb_inplace_add = (binaryfunc)PV_num_iadd,
    .nb_inplace_subtract = (binaryfunc)PV_num_isub,
    .nb_inplace_multiply = (binaryfunc)PV_num_imul,
    .nb_inplace_remainder = (binaryfunc)PV_num_imod,
    .nb_inplace_power = (ternaryfunc)PV_num_ipow,
    .nb_inplace_lshift = (binaryfunc)PV_num_ilshift,
    .nb_inplace_rshift = (binaryfunc)PV_num_irshift,
    .nb_inplace_and = (binaryfunc)PV_num_iand,
    .nb_inplace_xor = (binaryfunc)PV_num_ixor,
    .nb_inplace_or = (binaryfunc)PV_num_ior,

    .nb_true_divide = (binaryfunc)PV_num_truediv,
    .nb_floor_divide = (binaryfunc)PV_num_floordiv,
    .nb_inplace_true_divide = (binaryfunc)PV_num_itruediv,
    .nb_inplace_floor_divide = (binaryfunc)PV_num_ifloordiv,

    .nb_index = (unaryfunc)PV_num_index,
};

static PyObject *PV_num_typename_int(PyObject *self, PyObject *Py_UNUSED(args))
{
    return PyLong_FromLong((long)GET_TYPE_ID(self));
}

static PyObject *PV_num_typename(PyObject *self, PyObject *Py_UNUSED(args))
{
    return PyUnicode_FromString(type_str[GET_TYPE_ID(self)]);
}

static PyMethodDef PV_num_methods[] = {
    {"typename_int", PV_num_typename_int, METH_NOARGS, "return the typename by int. You can use pv_num.get_type() to get the type"},
    {"typename", PV_num_typename, METH_NOARGS, "return the typename by str.  You can use pv_num.get_type() to get the type"},
    {NULL, NULL, 0, NULL}
};

static PyTypeObject PV_num_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "PV_num.PV_num",
    .tp_doc = PyDoc_STR("PV_num Objects"),
    .tp_basicsize = sizeof(PV_num_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)PV_num_new,
    .tp_dealloc = (destructor)PV_num_dealloc,
    .tp_as_number = &PV_num_as_number,
    .tp_methods = PV_num_methods,
};

static int pv_num_exec(PyObject *m)
{
    *g_type_by_id = &PV_num_Type;
    PyObject *capsule = PyCapsule_New((void *)register_type, "pv_num.register_type", NULL);
    PyModule_AddObject(m, "_register_type_capsule", capsule);
    if (PyType_Ready(&PV_num_Type) < 0) return -1;
    if (PyModule_AddObjectRef(m, "PV_num", (PyObject *)&PV_num_Type) < 0) return -1;
    PV_OverflowWarning = PyErr_NewException("pv_num.PV_OverflowWarning", PyExc_Warning, NULL);
    if (!PV_OverflowWarning) { Py_DECREF(m); return -1; }
    capsule = PyCapsule_New((void *)PV_OverflowWarning, "pv_num.PV_OverflowWarning", NULL);
    PyModule_AddObject(m, "_PV_OverflowWarning", capsule);
    if (PyModule_AddObject(m, "PV_OverflowWarning", PV_OverflowWarning) < 0) {
        Py_DECREF(PV_OverflowWarning);
        Py_DECREF(m);
        return -1;
    }
    if (!m) return -1;
    return 0;
}

static PyModuleDef_Slot pv_num_slots[] = {
    {Py_mod_exec,                  (void *)pv_num_exec},
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
    {0, NULL}
};

static int pv_num_typestr_to_typeint(PyObject *arg)
{
    /* arg must be a PyUnicode */
    const char *s = PyUnicode_AsUTF8(arg);
    if (!s) return -1;
    for (int i = 0; i < MAX_DERIVED; i++)
    {
        if (!strcmp(s, type_str[i])) return i;
    }
    return -2;
}

static int pv_num_type_to_typeint(PyTypeObject *arg)
{
    for (int i = 0; i < MAX_DERIVED; i++)
    {
        if (g_type_by_id[i] == arg) return i;
    }
    return -1;
}

static PyObject *pv_num_typestr_int(PyObject *Py_UNUSED(self), PyObject *arg)
{
    if (PyUnicode_Check(arg))
    {
        int value = pv_num_typestr_to_typeint(arg);
        if (value == -1) return NULL;
        if (value == -2)
        {
            PyErr_SetString(PyExc_ValueError, "Unknown type name");
            return NULL;
        }
        return PyLong_FromLong((long)value);
    }
    PyErr_SetString(PyExc_TypeError, "arg must be str");
    return NULL;
}

static PyObject *pv_num_typeint_str(PyObject *Py_UNUSED(self), PyObject *arg)
{
    if (PyLong_Check(arg))
    {
        long value = PyLong_AsLong(arg);
        if (value == -1 && PyErr_Occurred()) return NULL;
        if (value < 0 || value >= MAX_DERIVED)
        {
            PyErr_Format(PyExc_ValueError, "The arg must in [0, %d)", MAX_DERIVED);
            return NULL;
        }
        return PyUnicode_FromString(type_str[value]);
    }
    PyErr_SetString(PyExc_TypeError, "arg must be int");
    return NULL;
}

static PyObject *pv_num_type_int(PyObject *Py_UNUSED(self), PyObject *arg)
{
    if (PyType_Check(arg))
    {
        int value = pv_num_type_to_typeint((PyTypeObject *)(arg));
        if (value == -1)
        {
            PyErr_SetString(PyExc_ValueError, "Unknown type");
            return NULL;
        }
        return PyLong_FromLong((long)value);
    }
    PyErr_SetString(PyExc_TypeError, "arg must be type");
    return NULL;
}

static PyObject *pv_num_type_str(PyObject *Py_UNUSED(self), PyObject *arg)
{
    if (PyType_Check(arg))
    {
        int value = pv_num_type_to_typeint((PyTypeObject *)arg);
        if (value == -1)
        {
            PyErr_SetString(PyExc_ValueError, "Unknown type");
            return NULL;
        }
        return PyUnicode_FromString(type_str[value]);
    }
    PyErr_SetString(PyExc_TypeError, "arg must be type");
    return NULL;
}

static PyObject *pv_num_get_type(PyObject *Py_UNUSED(self), PyObject *arg)
{
    if (PyLong_Check(arg))
    {
        long value = PyLong_AsLong(arg);
        if (value == -1 && PyErr_Occurred()) return NULL;
        if (value < 0 || value >= MAX_DERIVED)
        {
            PyErr_Format(PyExc_ValueError, "The arg must in [0, %d)", MAX_DERIVED);
            return NULL;
        }
        if (g_type_by_id[value]) return (PyObject *)g_type_by_id[value];
        PyErr_SetString(PyExc_RuntimeError, "The arg's type isn't prepared yet");
        return NULL;
    }
    if (PyUnicode_Check(arg))
    {
        int value = pv_num_typestr_to_typeint(arg);
        if (value == -1) return NULL;
        if (value == -2)
        {
            PyErr_SetString(PyExc_ValueError, "Unknown type name");
            return NULL;
        }
        if (g_type_by_id[value]) return (PyObject *)g_type_by_id[value];
        PyErr_SetString(PyExc_RuntimeError, "The arg's type isn't prepared yet");
        return NULL;
    }
    PyErr_SetString(PyExc_TypeError, "arg must be str or int");
    return NULL;
}

static PyObject *pv_num_typetype_type(PyObject *Py_UNUSED(self), PyObject *const *args, Py_ssize_t nargs)
{
    if (nargs != 2)
    {
        PyErr_Format(PyExc_TypeError, "function expected 2 arguments, got %d", nargs);
        return NULL;
    }
    long arg1, arg2;
    if (!PyLong_Check(args[0]))
    {
        PyErr_SetString(PyExc_TypeError, "args must be int");
        return NULL;
    }
    else
    {
        arg1 = PyLong_AsLong(args[0]);
        if (arg1 == -1 && PyErr_Occurred()) return NULL;
        if (arg1 < 0 || arg1 >= MAX_DERIVED)
        {
            PyErr_Format(PyExc_ValueError, "arg1 must in [0, %d)", MAX_DERIVED);
            return NULL;
        }
    }
    if (!PyLong_Check(args[1]))
    {
        PyErr_SetString(PyExc_TypeError, "args must be int");
        return NULL;
    }
    else
    {
        arg2 = PyLong_AsLong(args[1]);
        if (arg2 == -1 && PyErr_Occurred()) return NULL;
        if (arg2 < 0 || arg2 >= MAX_DERIVED)
        {
            PyErr_Format(PyExc_ValueError, "arg2 must in [0, %d)", MAX_DERIVED);
            return NULL;
        }
    }
    return PyLong_FromLong((long)typetype_type[arg1][arg2]);
}

static PyMethodDef pv_num_method[] = {
    {"typestr_int", (PyCFunction)pv_num_typestr_int, METH_O, "change the str to int"},
    {"typeint_str", (PyCFunction)pv_num_typeint_str, METH_O, "change the int to str"},
    {"type_int", (PyCFunction)pv_num_type_int, METH_O, "change the type to int"},
    {"type_str", (PyCFunction)pv_num_type_str, METH_O, "change the type to str"},
    {"get_type", (PyCFunction)pv_num_get_type, METH_O, "return the type"},
    {"typetype_type", (PyCFunction)(void(*)(void))pv_num_typetype_type, METH_FASTCALL, "return the result of type promotion"},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef pv_num_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "pv_num",
    .m_doc = "A module defines PV_num.",
    .m_size = 0,
    .m_slots = pv_num_slots,
    .m_methods = pv_num_method,
};

PyMODINIT_FUNC PyInit_pv_num(void)
{
    PyObject *m = PyModuleDef_Init(&pv_num_module);
    
    return m;
}

