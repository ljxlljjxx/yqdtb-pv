def get_type(arg: int | str, /) -> type: pass
def typestr_int(arg: str, /) -> int: pass
def typeint_str(arg: int, /) -> str: pass
def type_int(arg: type, /) -> int: pass
def type_str(arg: type, /) -> str: pass
def typetype_type(arg1: int, arg2: int, /) -> int: pass

class PV_num:
    def __add__(self, other):       return NotImplemented
    def __sub__(self, other):       return NotImplemented
    def __mul__(self, other):       return NotImplemented
    def __mod__(self, other):       return NotImplemented
    def __pow__(self, n, p):        return NotImplemented
    def __divmod__(self, other):    return NotImplemented
    def __truediv__(self, other):   return NotImplemented
    def __floordiv__(self, other):  return NotImplemented
    def __neg__(self):              return NotImplemented
    def __pos__(self):              return NotImplemented
    def __abs__(self):              return NotImplemented
    # def __bool__(self):             pass
    def __abs__(self):              return NotImplemented
    def __invert__(self):           return NotImplemented
    def __int__(self):              return NotImplemented
    def __float__(self):            return NotImplemented
    def __lshift__(self, other):    return NotImplemented
    def __rshift__(self, other):    return NotImplemented
    def __and__(self, other):       return NotImplemented
    def __xor__(self, other):       return NotImplemented
    def __or__(self, other):        return NotImplemented

    def __iadd__(self, other):      return NotImplemented
    def __isub__(self, other):      return NotImplemented
    def __imul__(self, other):      return NotImplemented
    def __imod__(self, other):      return NotImplemented
    def __ipow__(self, n, p):       return NotImplemented
    def __idivmod__(self, other):   return NotImplemented
    def __itruediv__(self, other):  return NotImplemented
    def __ifloordiv__(self, other): return NotImplemented
    def __ilshift__(self, other):   return NotImplemented
    def __irshift__(self, other):   return NotImplemented
    def __iand__(self, other):      return NotImplemented
    def __ixor__(self, other):      return NotImplemented
    def __ior__(self, other):       return NotImplemented

    def __index__(self):            return NotImplemented

    def typename(self) -> str: pass
    def typename_int(self) -> int: pass
