#include "py_PV_num.h"

const int typetype_type[MAX_DERIVED][MAX_DERIVED] = {
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

PyTypeObject *g_type_by_id[MAX_DERIVED];

static PyObject *register_type(PyObject *self, PyObject *args)
{
    int type_id;
    PyTypeObject *type;
    if (!PyArg_ParseTuple(args, "iO!", &type_id, &PyType_Type, &type))
        return NULL;
    if (type_id < 0 || type_id >= MAX_DERIVED) {
        PyErr_SetString(PyExc_ValueError, "invalid type_id");
        return NULL;
    }
    g_type_by_id[type_id] = type;
    Py_INCREF(type);
    Py_RETURN_NONE;
}

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

static PyTypeObject PV_num_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "PV_num.PV_num",
    .tp_doc = PyDoc_STR("PV_num Objects"),
    .tp_basicsize = sizeof(PV_num_Object),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new = (newfunc)PV_num_new,
    .tp_dealloc = (destructor)PV_num_dealloc,
    .tp_as_number = &PV_num_as_number
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

static PyMethodDef PV_num_module_method[] = {
    {"register_type", (PyCFunction)register_type, METH_VARARGS, NULL},
    {NULL},
};

static PyModuleDef PV_num_module = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "PV_num",
    .m_doc = "A module defines PV_num.",
    .m_size = 0,
    .m_slots = PV_num_module_slots,
    .m_methods = PV_num_module_method,
};

PyMODINIT_FUNC PyInit_PV_num(void)
{
    return PyModuleDef_Init(&PV_num_module);
}

