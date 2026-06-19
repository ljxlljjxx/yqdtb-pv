from typing import Callable


def get_overflow_function() -> Callable | None: pass
def set_overflow_function(new_func: Callable, /) -> None: pass

def get_type(arg: int | str, /) -> type: pass
def typestr_int(arg: str, /) -> int: pass
def typeint_str(arg: int, /) -> str: pass
def type_int(arg: type, /) -> int: pass
def type_str(arg: type, /) -> str: pass
def typetype_type(arg1: int, arg2: int, /) -> int: pass

# All instances of PV_num that are not of its subclass are equal.
class PV_num:
    def __eq__(self, __value: PV_num) -> bool: ...
    def __ne__(self, __value: PV_num) -> bool: ...
    def __gt__(self, __value: PV_num) -> bool: ...
    def __lt__(self, __value: PV_num) -> bool: ...
    def __ge__(self, __value: PV_num) -> bool: ...
    def __le__(self, __value: PV_num) -> bool: ...

    def __hash__(self) -> int: ...  # return id(PV_num)

    def __add__(self, other: PV_num):       pass
    def __sub__(self, other: PV_num):       return NotImplemented
    def __mul__(self, other: PV_num):       return NotImplemented
    def __mod__(self, other: PV_num):       return NotImplemented
    def __pow__(self, n: int, p: int):      return NotImplemented
    def __divmod__(self, other: PV_num):    return NotImplemented
    def __truediv__(self, other: PV_num):   return NotImplemented
    def __floordiv__(self, other: PV_num):  return NotImplemented
    def __neg__(self):                      return NotImplemented
    def __pos__(self):                      return NotImplemented
    def __abs__(self):                      return NotImplemented
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

    def typename(self) -> str: pass
    def typename_int(self) -> int: pass
