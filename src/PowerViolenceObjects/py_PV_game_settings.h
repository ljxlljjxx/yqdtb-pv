#ifndef _PY_PV_GAME_SETTING_H
#define _PY_PV_GAME_SETTING_H

#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stddef.h>

typedef struct {
    PyObject_HEAD
    PV_str_names_Object value[256];
} _PV_str_names_array_Object;

#endif /* _PY_PV_GAME_SETTING_H */
