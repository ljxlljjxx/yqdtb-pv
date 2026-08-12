from ._pv_num import PV_num, get_type_id, call_overflow_function, register_type

class PV_55p8(PV_num):
    _type_id = 7  # const

    max_int = 9223372036854775807     # const
    min_int = -9223372036854775808    # const
    step_int = 256                    # const
    max_float = 2 ** 55 - 0.00390625  # const
    min_float = float(-2 ** 55)       # const
    step_float = 0.00390625           # const

    def __init__(self, value: float | PV_num = 0.0) -> None:
        if isinstance(value, float):
            self._value = int(value * 256)
        elif isinstance(value, PV_num):
            tp: int = get_type_id(value)
            if tp == 0:  # PVO_NUM
                self._value = 0
            elif tp == 1:  # PVI_PID    # pragma: no cover
                raise NotImplementedError
            elif tp == 2:  # PVI_SID    # pragma: no cover
                raise NotImplementedError
            elif tp == 3:  # PVI_NRS    # pragma: no cover
                raise NotImplementedError
            elif tp == 4:  # PVI_LRS    # pragma: no cover
                raise NotImplementedError
            elif tp == 5:  # PVF_11P    # pragma: no cover
                raise NotImplementedError
            elif tp == 6:  # PVF_27P    # pragma: no cover
                raise NotImplementedError
            elif tp == 7:  # PVF_55P
                self._value = value._value
            elif tp == 8:  # PVF_119    # pragma: no cover
                raise NotImplementedError
            elif tp == 9:  # PVC_64C    # pragma: no cover
                raise NotImplementedError
            elif tp == 10:  # PVC_128   # pragma: no cover
                raise NotImplementedError
            elif tp == 11:  # PVC_256   # pragma: no cover
                raise NotImplementedError
            elif tp == 12:  # PVH_SRT   # pragma: no cover
                raise NotImplementedError
            elif tp == 13:  # PVH_NOR   # pragma: no cover
                raise NotImplementedError
            elif tp == 14:  # PVO_NOR   # pragma: no cover
                raise NotImplementedError
            elif tp == 15:  # PVF_447   # pragma: no cover
                raise NotImplementedError
            elif tp == 16:  # PVO_PFT   # pragma: no cover
                raise NotImplementedError
            
    @property
    def _value(self) -> int:
        return self.__value
    
    @_value.setter
    def _value(self, new_val: int):
        if not isinstance(new_val, int):
            raise TypeError('_value must be int')
        if PV_55p8.min_int <= new_val <= PV_55p8.max_int:
            self.__value = new_val
        else:
            self.__value = 0
            call_overflow_function()
            
    @staticmethod
    def _richcmp(lhs: 'PV_num', rhs: 'PV_num', op: int):
        if isinstance(lhs, PV_55p8) and isinstance(rhs, PV_55p8):
            if op == 0:   return lhs._value < rhs._value
            elif op == 1: return lhs._value <= rhs._value
            elif op == 2: return lhs._value == rhs._value
            elif op == 3: return lhs._value != rhs._value
            elif op == 4: return lhs._value > rhs._value
            else:         return lhs._value >= rhs._value
        else:
            return PV_num._richcmp(lhs, rhs, op)

    def __eq__(self, __value: 'PV_num') -> bool:
        return PV_55p8._richcmp(self, __value, 2)
    
    def __ne__(self, __value: 'PV_num') -> bool:
        return PV_55p8._richcmp(self, __value, 3)
    
    def __gt__(self, __value: 'PV_num') -> bool:
        return PV_55p8._richcmp(self, __value, 4)
    
    def __lt__(self, __value: 'PV_num') -> bool:
        return PV_55p8._richcmp(self, __value, 0)
    
    def __ge__(self, __value: 'PV_num') -> bool:
        return PV_55p8._richcmp(self, __value, 5)
    
    def __le__(self, __value: 'PV_num') -> bool:
        return PV_55p8._richcmp(self, __value, 1)

    def __add__(self, other: PV_num):
        if isinstance(self, PV_55p8) and isinstance(other, PV_55p8):
            new_obj = PV_55p8()
            if PV_55p8.min_int <= self._value + other._value <= PV_55p8.max_int:
                new_obj._value = self._value + other._value
            else:
                call_overflow_function()
                new_obj._value = 0
            return new_obj
        else:
            return PV_num.__add__(self, other)

    def __sub__(self, other: PV_num):       return NotImplemented
    def __mul__(self, other: PV_num):       return NotImplemented
    def __mod__(self, other: PV_num):       return NotImplemented
    def __pow__(self, other: PV_num, modulo: int | None = None):      return NotImplemented
    def __divmod__(self, other: PV_num):    return NotImplemented
    def __truediv__(self, other: PV_num):   return NotImplemented
    def __floordiv__(self, other: PV_num):  return NotImplemented
    def __neg__(self):                      return NotImplemented
    def __pos__(self):                      return NotImplemented

    def __bool__(self):
        return bool(self._value)
    
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

    def __hash__(self) -> int:
        return self._value if self._value != -1 else -2

    def __repr__(self) -> str:
        return f'<PV_55p8 object at {id(self)}>: _value = {self._value}'

    def __str__(self) -> str:
        value: int = self._value
        ans: str = ''
        if value < 0:
            ans = '-'
            value = -value
        if value % 256 == 0:
            return ans + f'{value // 256}'
        return ans + f'{value // 256}.{str(value % 256 * 100000000 // 256).zfill(8).rstrip("0")}'


register_type(PV_55p8._type_id, PV_55p8)
