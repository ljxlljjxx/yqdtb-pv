#ifndef _PY_PV_num_H
#define _PY_PV_num_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>

#include "pvc_PV_num.h"

typedef struct {
    PyObject_HEAD
    int type_id;
} PV_num_Object;

#define PVO_NUM PVC_O_NUM
#define PVI_PID PVC_I_PID
#define PVI_SID PVC_I_SID
#define PVI_NRS PVC_I_NRS
#define PVI_LRS PVC_I_LRS
#define PVF_11P PVC_F_11P
#define PVF_27P PVC_F_27P
#define PVF_55P PVC_F_55P
#define PVF_119 PVC_F_119
#define PVC_64C PVC_C_64C
#define PVC_128 PVC_C_128
#define PVC_256 PVC_C_256
#define PVH_SRT PVC_H_SRT
#define PVH_NOR PVC_H_NOR
#define PVO_NOR PVC_O_NOR
#define PVF_447 PVC_F_447
#define PVO_PFT PVC_O_PFT

#define PVC_POW PVC_C_POW
#define PVC_LVS PVC_C_LVS

#define GET_TYPE_ID(a) (((PV_num_Object *)(a))->type_id)
#define PvNUM_TypeCheck(a, b) (GET_TYPE_ID(a) == (b))

extern PyTypeObject *g_type_by_id[MAX_DERIVED];

static PyTypeObject *g_PV_num_Type;

typedef int (*register_type_func_t)(int, PyTypeObject*);

#define TYPE_TRANSFORM_CHECK(typea, typeb) (!pvc_type_trans_func[typea][typeb])
#define TYPE_TRANSFORM_TYPE(a, b, type) (pvc_type_trans_func[type][GET_TYPE_ID(b)](((int8_t *)(a) + sizeof(PV_num_Object)), ((int8_t *)(b) + sizeof(PV_num_Object))))
#define TYPE_TRANSFORM(a, b) (TYPE_TRANSFORM_TYPE((a), (b), GET_TYPE_ID(a)))

#define _GET_RESULT_TYPE_ID(a, b) (_typetype_type[GET_TYPE_ID(a)][GET_TYPE_ID(b)])

typedef struct PvNumState {
    PyObject *overflow_function;
} PvNumState;

static PvNumState *pv_num_state;

#define raise_overflow(error_ret) do { pv_deprint_overflow(); if (pv_num_state->overflow_function != Py_None) if (!PyObject_CallFunction(pv_num_state->overflow_function, NULL)) return error_ret; } while (0)

#endif /* _PY_PV_num_H */
