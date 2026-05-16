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
int PV_num_bool(PyObject *a) { return (a != 0); }
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
static PyObject *PV_num_idivmod(PyObject *a, PyObject *b) { Py_RETURN_NOTIMPLEMENTED; }
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
    .nb_bool = (inquiry)PV_num_bool,
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
    {NULL}
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
    PyObject *capsule = PyCapsule_New(register_type, "pv_num.register_type", NULL);
    PyModule_AddObject(m, "_register_type_capsule", capsule);
    if (PyType_Ready(&PV_num_Type) < 0) return -1;
    if (PyModule_AddObjectRef(m, "PV_num", (PyObject *)&PV_num_Type) < 0) return -1;
    return 0;
}

static PyModuleDef_Slot pv_num_slots[] = {
    {Py_mod_exec,                  pv_num_exec},
    {Py_mod_multiple_interpreters, Py_MOD_MULTIPLE_INTERPRETERS_NOT_SUPPORTED},
    {0, NULL}
};

static PyMethodDef pv_num_method[] = {
    // {"register_type", (PyCFunction)register_type, METH_VARARGS, NULL},
    {NULL}
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
    return PyModuleDef_Init(&pv_num_module);
}

