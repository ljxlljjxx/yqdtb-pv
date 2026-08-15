#include "py_PV_num.h"

static const int _TYPETYPE_TYPE[MAX_DERIVED][MAX_DERIVED] = {
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
PvNum_TypeMake g_type_make[MAX_DERIVED];

static int register_type(int type_id, PyTypeObject *type, PvNum_TypeMake make_func)
{
    if (type_id < 0 || type_id >= MAX_DERIVED) return 1;
    g_type_by_id[type_id] = type;
    Py_INCREF(type);
    g_type_make[type_id] = make_func;
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

static PyObject *PV_num_richcmp(PyObject *lhs, PyObject *rhs, int op)
{
    int lhs_type, rhs_type, result_type;
    PyObject *lhs_new, *rhs_new;
    if (PyObject_TypeCheck(lhs, g_PV_num_Type) && PyObject_TypeCheck(rhs, g_PV_num_Type))
    {
        lhs_type = GET_TYPE_ID(lhs);
        rhs_type = GET_TYPE_ID(rhs);
        if (lhs_type && rhs_type)
        {
            result_type = _TYPETYPE_TYPE[lhs_type][rhs_type];
            lhs_new = g_type_make[result_type](NULL); TYPE_TRANSFORM_TYPE(lhs_new, lhs, result_type);
            rhs_new = g_type_make[result_type](NULL); TYPE_TRANSFORM_TYPE(rhs_new, rhs, result_type);
            info_printf("PV_num_richcmp ask %s for help (type1: %s, type2: %s)\n", type_str[result_type], type_str[lhs_type], type_str[rhs_type]);
            return g_type_by_id[result_type]->tp_richcompare(lhs_new, rhs_new, op);
        }
        if (lhs_type || rhs_type)
        {
            Py_RETURN_NOTIMPLEMENTED;
        }
        switch (op)
        {
        case Py_EQ: Py_RETURN_TRUE;
        case Py_NE: Py_RETURN_FALSE;
        case Py_LT: Py_RETURN_FALSE;
        case Py_GT: Py_RETURN_FALSE;
        case Py_LE: Py_RETURN_TRUE;
        case Py_GE: Py_RETURN_TRUE;
        default: abort();
        }
    }
    Py_RETURN_NOTIMPLEMENTED;
}

static Py_hash_t PV_num_hash(PyObject *op)
{
    Py_hash_t result = (Py_hash_t)g_PV_num_Type;
    if (result == -1) return -2;
    return result;
}

static PyObject *PV_num_repr(PyObject *_self)
{
    PV_num_Object *self = (PV_num_Object *)_self;
    return PyUnicode_FromFormat("<PV_num object at %p>", self);
}

static PyObject *PV_num_add(PyObject *lhs, PyObject *rhs)
{
    int lhs_type, rhs_type, result_type;
    PyObject *lhs_new, *rhs_new;
    if (PyObject_TypeCheck(lhs, g_PV_num_Type) && PyObject_TypeCheck(rhs, g_PV_num_Type))
    {
        lhs_type = GET_TYPE_ID(lhs);
        rhs_type = GET_TYPE_ID(rhs);
        if (lhs_type && rhs_type)
        {
            result_type = _TYPETYPE_TYPE[lhs_type][rhs_type];
            lhs_new = g_type_make[result_type](NULL); TYPE_TRANSFORM_TYPE(lhs_new, lhs, result_type);
            rhs_new = g_type_make[result_type](NULL); TYPE_TRANSFORM_TYPE(rhs_new, rhs, result_type);
            info_printf("PV_num_add ask %s for help (type1: %s, type2: %s)\n", type_str[result_type], type_str[lhs_type], type_str[rhs_type]);
            return g_type_by_id[result_type]->tp_as_number->nb_add(lhs_new, rhs_new);
        }
        else
        {
            PyErr_SetString(PyExc_TypeError, "No calculation with PV_num");
            return NULL;
        }
    }
    Py_RETURN_NOTIMPLEMENTED;
}

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

static PyTypeObject PV_num_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "PV_num.PV_num",
    .tp_doc = PyDoc_STR("PV_num Objects"),
    .tp_basicsize = sizeof(PV_num_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)PV_num_new,
    .tp_dealloc = (destructor)PV_num_dealloc,
    .tp_richcompare = PV_num_richcmp,
    .tp_hash = PV_num_hash,
    .tp_as_number = &PV_num_as_number,
    .tp_repr = PV_num_repr
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
    if (PyObject_TypeCheck(arg, g_PV_num_Type))
    {
        return PyLong_FromLong((long)((PV_num_Object *)arg)->type_id);
    }
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
    PyErr_SetString(PyExc_TypeError, "arg must be type or PV_num object");
    return NULL;
}

static PyObject *pv_num_type_str(PyObject *Py_UNUSED(self), PyObject *arg)
{
    if (PyObject_TypeCheck(arg, g_PV_num_Type))
    {
        return PyUnicode_FromString(type_str[((PV_num_Object *)arg)->type_id]);
    }
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
    PyErr_SetString(PyExc_TypeError, "arg must be type or PV_num object");
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
            PyErr_Format(PyExc_ValueError, "args must in [0, %d)", MAX_DERIVED);
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
            PyErr_Format(PyExc_ValueError, "args must in [0, %d)", MAX_DERIVED);
            return NULL;
        }
    }
    return PyLong_FromLong((long)_TYPETYPE_TYPE[arg1][arg2]);
}

static PyObject *g_value = NULL;
static PyObject *g_pre = NULL;
static int g_nest = 0;

typedef struct {
    PyObject_HEAD
} OverflowGetSetObject;

typedef struct {
    PyObject_HEAD
} OverflowFunctionObject;

static int _check_value(PyObject *v)
{
    return (v == Py_True || v == Py_False || PyCallable_Check(v));
}

static PyObject *OverflowGetSet_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    PyObject *obj = Py_False;
    PyObject *value = Py_False;
    static char *kwlist[] = {"obj", "value", NULL};
    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OO", kwlist, &obj, &value))
        return NULL;

    if (obj == Py_True && !g_nest)
    {
        Py_XSETREF(g_pre, g_value);
        Py_XINCREF(g_value);

        if (!_check_value(value))
        {
            PyErr_SetString(PyExc_TypeError, "overflow_function must be callable or bool");
            return NULL;
        }
        Py_XSETREF(g_value, value);
        Py_XINCREF(value);
    }

    return type->tp_alloc(type, 0);
}

static PyObject *OverflowGetSet_descr_get(PyObject *Py_UNUSED(self), PyObject *obj, PyObject *Py_UNUSED(type))
{
    if (g_value == Py_False)
    {
        PyObject *initial = PyObject_GetAttrString(obj, "initial");
        return initial;
    }
    else if (g_value == Py_True)
    {
        PyObject *default_ = PyObject_GetAttrString(obj, "default");
        return default_;
    }
    else
    {
        Py_XINCREF(g_value);
        return g_value;
    }
}

static int OverflowGetSet_descr_set(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(obj), PyObject *value)
{
    if (!_check_value(value))
    {
        PyErr_SetString(PyExc_TypeError, "overflow_function must be callable or bool");
        return -1;
    }
    Py_XSETREF(g_value, value);
    Py_XINCREF(value);
    return 0;
}

static PyObject *OverflowGetSet_enter(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    if (g_nest)
    {
        PyErr_SetString(PyExc_RuntimeError, "This context manager does not support nesting.");
        return NULL;
    }
    g_nest = 1;
    Py_RETURN_NONE;
}

static PyObject *OverflowGetSet_exit(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    Py_XSETREF(g_value, g_pre);
    g_pre = NULL;
    g_nest = 0;
    Py_RETURN_NONE;
}

static PyMethodDef OverflowGetSet_methods[] = {
    {"__enter__", (PyCFunction)OverflowGetSet_enter, METH_NOARGS, NULL},
    {"__exit__", (PyCFunction)OverflowGetSet_exit, METH_VARARGS, NULL},
    {NULL, NULL, 0, NULL}
};

static PyTypeObject OverflowGetSetType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "_OverflowFunctionType_getset",
    .tp_basicsize = sizeof(OverflowGetSetObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = OverflowGetSet_new,
    .tp_methods = OverflowGetSet_methods,
    .tp_descr_get = OverflowGetSet_descr_get,
    .tp_descr_set = OverflowGetSet_descr_set,
};

static PyObject *OverflowFunction_default(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    PyErr_SetString(PyExc_OverflowError, "");
    return NULL;
}

static PyObject *OverflowFunction_initial(PyObject *Py_UNUSED(self), PyObject *Py_UNUSED(args))
{
    Py_RETURN_NONE;
}

static PyObject *OverflowFunction_call(PyObject *self, PyObject *Py_UNUSED(args), PyObject *Py_UNUSED(kwds))
{
    PyObject *func = PyObject_GetAttrString(self, "func");
    if (!func) return NULL;
    PyObject *result = PyObject_CallObject(func, NULL);
    Py_DECREF(func);
    return result;
}

static PyObject *OverflowFunction_set(PyObject *self, PyObject *value)
{
    if (!_check_value(value))
    {
        PyErr_SetString(PyExc_TypeError, "overflow_function must be callable or bool");
        return NULL;
    }

    PyObject *args2 = Py_BuildValue("(OO)", Py_True, value);
    if (!args2) return NULL;
    PyObject *descr = PyObject_CallObject((PyObject *)&OverflowGetSetType, args2);
    Py_DECREF(args2);
    return descr;
}

static PyMethodDef OverflowFunction_methods[] = {
    {"set", (PyCFunction)(void*)OverflowFunction_set, METH_O,
     "warning: it only can use after with\n\nfor example:\n\nwith overflow.set(True):\n    ..."},
    {NULL, NULL, 0, NULL}
};

static PyTypeObject OverflowFunctionType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "_OverflowFunctionType",
    .tp_basicsize = sizeof(OverflowFunctionObject),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_call = OverflowFunction_call,
    .tp_methods = OverflowFunction_methods,
};

static int init_types(void)
{
    if (PyType_Ready(&OverflowGetSetType) < 0) return -1;
    if (PyType_Ready(&OverflowFunctionType) < 0) return -1;

    PyObject *dict = OverflowFunctionType.tp_dict;
    if (!dict) return -1;

    PyObject *descr_inst = PyObject_CallObject((PyObject *)&OverflowGetSetType, NULL);
    if (!descr_inst) return -1;
    if (PyDict_SetItemString(dict, "func", descr_inst) < 0)
    {
        Py_DECREF(descr_inst);
        return -1;
    }
    Py_DECREF(descr_inst);

    static PyMethodDef default_def = {"default", (PyCFunction)OverflowFunction_default, METH_NOARGS, NULL};
    static PyMethodDef initial_def = {"initial", (PyCFunction)OverflowFunction_initial, METH_NOARGS, NULL};

    PyObject *default_func = PyCFunction_New(&default_def, NULL);
    PyObject *initial_func = PyCFunction_New(&initial_def, NULL);
    if (!default_func || !initial_func)
    {
        Py_XDECREF(default_func);
        Py_XDECREF(initial_func);
        return -1;
    }

    PyObject *default_static = PyStaticMethod_New(default_func);
    PyObject *initial_static = PyStaticMethod_New(initial_func);
    Py_DECREF(default_func);
    Py_DECREF(initial_func);
    if (!default_static || !initial_static)
    {
        Py_XDECREF(default_static);
        Py_XDECREF(initial_static);
        return -1;
    }

    if (PyDict_SetItemString(dict, "default", default_static) < 0 ||
        PyDict_SetItemString(dict, "initial", initial_static) < 0)
    {
        Py_DECREF(default_static);
        Py_DECREF(initial_static);
        return -1;
    }
    Py_DECREF(default_static);
    Py_DECREF(initial_static);

    g_value = Py_False;
    Py_INCREF(g_value);
    g_pre = NULL;
    g_nest = 0;

    return 0;
}

PyObject *get_overflow_instance(void)
{
    if (!g_overflow_instance)
    {
        if (init_types() < 0) return NULL;
        g_overflow_instance = PyObject_CallObject((PyObject *)&OverflowFunctionType, NULL);
        if (!g_overflow_instance) return NULL;
    }
    Py_INCREF(g_overflow_instance);
    return g_overflow_instance;
}

// static PvNumState *pv_num_get_state(PyObject *module)
// {
//     return (PvNumState *)PyModule_GetState(module);
// }

// static PyObject *pv_num_default_overflow_function()
// {
//     PyErr_SetString(PyExc_OverflowError, "");
//     return NULL;
// }

// static PyObject *pv_num_get_global(PyObject *self, PyObject *Py_UNUSED(ig))
// {
//     PvNumState *state = pv_num_get_state(self);
//     if (state->overflow_function == Py_True) return PyUnicode_FromString("default");
//     Py_INCREF(state->overflow_function);
//     return state->overflow_function;
// }

// static PyObject *pv_num_call_global(PyObject *self, PyObject *Py_UNUSED(ig))
// {
//     PvNumState *state = pv_num_get_state(self);
//     if (state->overflow_function == Py_None) return Py_None;
//     if (state->overflow_function == Py_True)
//     {
//         PyErr_SetString(PyExc_OverflowError, "");
//         return NULL;
//     }
//     return PyObject_CallObject(state->overflow_function, NULL);
// }

// static PyObject *pv_num_set_global(PyObject *self, PyObject *value)
// {
//     PvNumState *state = pv_num_get_state(self);
//     fflush(stdout);
//     if (!value)
//     {
//         PyErr_SetString(PyExc_AttributeError, "can not remove the overflow_function");
//         return NULL;
//     }
//     if (value == Py_None)
//     {
//         Py_INCREF(Py_None);
//         Py_DECREF(state->overflow_function);
//         state->overflow_function = Py_None;
//         Py_RETURN_NONE;
//     }
//     if (PyObject_TypeCheck(value, &PyUnicode_Type))
//     {
//         switch (PyObject_RichCompareBool(value, PyUnicode_FromString("default"), Py_EQ))
//         {
//         case 0:
//             break;

//         case 1:
//             Py_INCREF(Py_True);
//             Py_DECREF(state->overflow_function);
//             state->overflow_function = Py_True;
//             Py_RETURN_NONE;
        
//         default:
//             return NULL;
//         }
//     }
//     if (!PyCallable_Check(value))
//     {
//         error_puts("set uncallable overflow_function");
//         PyErr_SetString(PyExc_TypeError, "overflow_function must be callable or None or 'default'");
//         return NULL;
//     }
//     info_puts("set new overflow_function");
//     Py_INCREF(value);
//     Py_DECREF(state->overflow_function);
//     state->overflow_function = value;
//     Py_RETURN_NONE;
// }

static PyMethodDef pv_num_methods[] = {
    {"typestr_int", (PyCFunction)pv_num_typestr_int, METH_O, "change the str to int"},
    {"typeint_str", (PyCFunction)pv_num_typeint_str, METH_O, "change the int to str"},
    {"type_int", (PyCFunction)pv_num_type_int, METH_O, "change the type to int"},
    {"type_str", (PyCFunction)pv_num_type_str, METH_O, "change the type to str"},
    {"get_type", (PyCFunction)pv_num_get_type, METH_O, "return the type"},
    {"typetype_type", (PyCFunction)(void(*)(void))pv_num_typetype_type, METH_FASTCALL, "return the result of type promotion"},
    {NULL, NULL, 0, NULL}
};

void pv_num_free(void *module)
{
#if DEBUG
    if (__debug_file) fclose(__debug_file);
#endif
    PvNumState *state = (PvNumState *)(module);
    if (state->overflow_function) Py_DECREF(state->overflow_function);
}

static int pv_num_exec(PyObject *m)
{
    g_PV_num_Type = &PV_num_Type;
    *g_type_by_id = &PV_num_Type;
    // pv_num_state = pv_num_get_state(m);
    // Py_INCREF(Py_None);
    // pv_num_state->overflow_function = Py_None;
    PyObject *capsule = PyCapsule_New((void *)register_type, "pv_num.register_type", NULL);
    PyModule_AddObject(m, "_register_type_capsule", capsule);
    if (PyType_Ready(&PV_num_Type) < 0) return -1;
    if (PyModule_AddObject(m, "PV_num", (PyObject *)&PV_num_Type) < 0) return -1;
    if (init_types() < 0) return -1;
    PyObject *inst = get_overflow_instance();
    if (!inst) return -1;
    PyModule_AddObject(m, "overflow", inst);
    // capsule = PyCapsule_New((void *)get_overflow_instance, "pv_num.overflow", NULL);
    // PyModule_AddObject(m, "_overflow", capsule);
#ifdef DEBUG
    __debug_file = fopen("pv_num_debug.log", __debug_file_open_mode);
    // __debug_file = stderr;
    capsule = PyCapsule_New((void *)__debug_file, "pv_num.__debug_file", NULL);
    PyModule_AddObject(m, "__debug_file", capsule);
#endif
    if (!m) return -1;
    return 0;
}

static PyModuleDef_Slot pv_num_slots[] = {
    {Py_mod_exec,                  (void *)pv_num_exec},
#if PY_VERSION_HEX >= 0x030C0000
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
#endif
    {0, NULL}
};

static PyModuleDef pv_num_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "pv_num",
    .m_doc = "A module defines PV_num.",
    .m_size = sizeof(PvNumState),
    .m_slots = pv_num_slots,
    .m_methods = pv_num_methods,
    .m_free = pv_num_free,
};

PyMODINIT_FUNC PyInit_pv_num(void)
{
    return PyModuleDef_Init(&pv_num_module);
}
