"""
PowerViolenceObjects:
|_  PV_num
|   |_ PV_pID
|   |_ PV_sID
|   |_ PV_nRounds
|   |_ PV_lRounds
|   |_ PV_11p4
|   |_ PV_27p4
|   |_ PV_55p8
|   |_ PV_119p8
|   |_ PV_power
|   |_ PV_lives
|   |_ PV_com64
|   |_ PV_quaternion
|   |_ PV_s_quaternion
|   |_ PV_octonion
|   |_ PV_447p64
|   |_ PV_perfect
|
|_  PV_str
|
|_  PV_binary
|
|_  PV_struct
"""

__version__ = "3.1.83"

from typing import Union
from .pv_str import PV_str  # type: ignore
from .pv_str_names import PV_str_names  # type: ignore

from .pv_num import PV_num, get_type, typestr_int, typeint_str, type_int, type_str, typetype_type, get_overflow_function, set_overflow_function  # type: ignore
from .pv_55p8 import PV_55p8  # type: ignore
from .pv_119p8 import PV_119p8  # type: ignore

class _Constant:
    def __getattribute__(self, __name: str) -> Union[type, int, float]:
        name: list[str] = __name.lower().split('__')
        if len(name) != 2:
            return AttributeError
        name0, name1 = name[0], name[1]
        
        if name0 == 'pv_str':
            if name1 == 'type':
                return PV_str
        elif name0 == 'pv_str_name':
            if name1 == 'type':
                return PV_str_names
        elif name0 == 'pv_num':
            if name1 == 'type':
                return PV_num
            elif name1 == 'serial_number':
                return 0
        elif name0 == 'pv_55p8':
            if name1 == 'type':
                return PV_55p8
            elif name1 == 'serial_number':
                return 7
            elif name1 == 'max_int':
                return 9223372036854775807
            elif name1 == 'min_int':
                return -9223372036854775808
            elif name1 == 'step_int':
                return 256
            elif name1 == 'max_float':
                return 2 ** 55 - 0.00390625
            elif name1 == 'min_float':
                return float(-2 ** 55)
            elif name1 == 'step_float':
                return 0.00390625
        elif name0 == 'pv_119p8':
            if name1 == 'type':
                return PV_119p8
            elif name1 == 'serial_number':
                return 8
            elif name1 == 'max_int':
                return 2 ** 127 - 1
            elif name1 == 'min_int':
                return -2 ** 127
            elif name1 == 'step_int':
                return 256
            elif name1 == 'max_float':
                return 2 ** 119 - 0.00390625
            elif name1 == 'min_float':
                return float(-2 ** 119)
            elif name1 == 'step_float':
                return 0.00390625
        else:
            return AttributeError


constant: _Constant = _Constant()

__all__ = [
    'constant',
    'PV_str',
    'PV_str_names',
    'PV_num', 'get_type', 'typestr_int', 'typeint_str', 'type_int', 'type_str', 'typetype_type', 'get_overflow_function', 'set_overflow_function',
    'PV_55p8',
    'PV_119p8',
]