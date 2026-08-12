from .pv_num import PV_num

class PV_119p8(PV_num):
    max_int = 2 ** 127 - 1             # const
    min_int = -2 ** 127                # const
    step_int = 256                     # const
    max_float = 2 ** 119 - 0.00390625  # const
    min_float = float(-2 ** 119)       # const
    step_float = 0.00390625            # const

    def __init__(self, value: float | PV_num = 0) -> None: ...

    @property
    def _value(self) -> int: ...

    @_value.setter
    def _value(self, value: int): ...
    
    def __eq__(self, __value: PV_num) -> bool: ...
    def __ne__(self, __value: PV_num) -> bool: ...
    def __gt__(self, __value: PV_num) -> bool: ...
    def __lt__(self, __value: PV_num) -> bool: ...
    def __ge__(self, __value: PV_num) -> bool: ...
    def __le__(self, __value: PV_num) -> bool: ...

    def __hash__(self) -> int: ...
    def __bool__(self) -> bool: ...
    def __repr__(self) -> str: ...
    def __str__(self) -> str: ...

    def __add__(self, other: PV_num):       pass
    def __sub__(self, other: PV_num):       return NotImplemented
    def __mul__(self, other: PV_num):       return NotImplemented
    def __mod__(self, other: PV_num):       return NotImplemented
    def __pow__(self, other: PV_num, modulo: int | None = None):      return NotImplemented
    def __divmod__(self, other: PV_num):    return NotImplemented
    def __truediv__(self, other: PV_num):   return NotImplemented
    def __floordiv__(self, other: PV_num):  return NotImplemented
    def __neg__(self):                      return NotImplemented
    def __pos__(self):                      return NotImplemented
    def __bool__(self):                     pass
    def __abs__(self):                      return NotImplemented
    def __invert__(self):                   return NotImplemented
    def __int__(self):                      return NotImplemented
    def __float__(self):                    return NotImplemented
    def __lshift__(self, other: PV_num):    return NotImplemented
    def __rshift__(self, other: PV_num):    return NotImplemented
    def __and__(self, other: PV_num):       return NotImplemented
    def __xor__(self, other: PV_num):       return NotImplemented
    def __or__(self, other: PV_num):        return NotImplemented

    def __iadd__(self, other: PV_num):      return NotImplemented
    def __isub__(self, other: PV_num):      return NotImplemented
    def __imul__(self, other: PV_num):      return NotImplemented
    def __imod__(self, other: PV_num):      return NotImplemented
    def __ipow__(self, n: int, p: int):     return NotImplemented
    def __idivmod__(self, other: PV_num):   return NotImplemented
    def __itruediv__(self, other: PV_num):  return NotImplemented
    def __ifloordiv__(self, other: PV_num): return NotImplemented
    def __ilshift__(self, other: PV_num):   return NotImplemented
    def __irshift__(self, other: PV_num):   return NotImplemented
    def __iand__(self, other: PV_num):      return NotImplemented
    def __ixor__(self, other: PV_num):      return NotImplemented
    def __ior__(self, other: PV_num):       return NotImplemented

    def __str__(self) -> str: ...
