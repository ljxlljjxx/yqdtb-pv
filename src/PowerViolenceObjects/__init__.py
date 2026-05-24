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
from importlib.metadata import version

__version__ = version("PowerViolenceObjects")

from .pv_num import PV_num, get_type, typestr_int, typeint_str, type_int, type_str, typetype_type, PV_OverflowWarning  # type: ignore
from .pv_55p8 import PV_55p8  # type: ignore
from .pv_119p8 import PV_119p8  # type: ignore

__all__ = [
    'PV_num', 'get_type', 'typestr_int', 'typeint_str', 'type_int', 'type_str', 'typetype_type', 'PV_OverflowWarning',
    'PV_55p8',
    'PV_119p8',
]
