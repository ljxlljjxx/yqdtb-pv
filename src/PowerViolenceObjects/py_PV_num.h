#ifndef _PY_PV_num_H
#define _PY_PV_num_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>

typedef struct {
    PyObject_HEAD
    int type_id;
} PV_num_Object;

#define MAX_DERIVED 17

#define PVO_NUM 0
#define PVI_PID 1
#define PVI_SID 2
#define PVI_NRS 3
#define PVI_LRS 4
#define PVF_11P 5
#define PVF_27P 6
#define PVF_55P 7
#define PVF_119 8
#define PVC_64C 9
#define PVC_128 10
#define PVC_256 11
#define PVH_SRT 12
#define PVH_NOR 13
#define PVO_NOR 14
#define PVF_447 15
#define PVO_PFT 16

#define PVC_POW PVC_256
#define PVC_LVS PVC_128

#define GET_TYPE_ID(a) (((PV_num_Object *)(a))->type_id)
#define GET_RESULT_TYPE_ID(a, b) (typetype_type[GET_TYPE_ID(a)][GET_TYPE_ID(b)])


extern PyTypeObject *g_type_by_id[MAX_DERIVED];

typedef int (*register_type_func_t)(int, PyTypeObject*);

#endif /* _PY_PV_num_H */
