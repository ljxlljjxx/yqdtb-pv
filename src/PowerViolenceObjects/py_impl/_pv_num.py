from typing import Any, Union, Callable, List, Tuple


_overflow_function = None

MAX_DERIVED = 17

PVO_NUM = 0
PVI_PID = 1
PVI_SID = 2
PVI_NRS = 3
PVI_LRS = 4
PVF_11P = 5
PVF_27P = 6
PVF_55P = 7
PVF_119 = 8
PVC_64C = 9
PVC_128 = 10
PVC_256 = 11
PVH_SRT = 12
PVH_NOR = 13
PVO_NOR = 14
PVF_447 = 15
PVO_PFT = 16

PVC_POW = PVC_256
PVC_LVS = PVC_128


_TYPETYPE_TYPE: List[List[int]] = [
    [PVO_NUM, PVI_PID, PVI_SID, PVI_NRS, PVI_LRS, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT],
    [PVI_PID, PVI_PID, PVI_SID, PVI_NRS, PVI_LRS, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT],
    [PVI_SID, PVI_SID, PVI_SID, PVI_NRS, PVI_LRS, PVF_27P, PVF_27P, PVF_55P, PVF_119, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT],
    [PVI_NRS, PVI_NRS, PVI_NRS, PVI_NRS, PVI_LRS, PVF_55P, PVF_55P, PVF_55P, PVF_119, PVC_128, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT],
    [PVI_LRS, PVI_LRS, PVI_LRS, PVI_LRS, PVI_LRS, PVF_119, PVF_119, PVF_119, PVF_119, PVC_128, PVC_128, PVC_256, PVH_NOR, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT],
    [PVF_11P, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT],
    [PVF_27P, PVF_27P, PVF_27P, PVF_55P, PVF_119, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT],
    [PVF_55P, PVF_55P, PVF_55P, PVF_55P, PVF_119, PVF_11P, PVF_27P, PVF_55P, PVF_119, PVC_128, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT],
    [PVF_119, PVF_119, PVF_119, PVF_119, PVF_119, PVF_119, PVF_119, PVF_119, PVF_119, PVC_256, PVC_256, PVC_256, PVH_NOR, PVH_NOR, PVO_NOR, PVF_447, PVO_PFT],
    [PVC_64C, PVC_64C, PVC_64C, PVC_128, PVC_128, PVC_64C, PVC_64C, PVC_128, PVC_256, PVC_64C, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVO_PFT, PVO_PFT],
    [PVC_128, PVC_128, PVC_128, PVC_128, PVC_128, PVC_128, PVC_128, PVC_128, PVC_256, PVC_128, PVC_128, PVC_256, PVH_SRT, PVH_NOR, PVO_NOR, PVO_PFT, PVO_PFT],
    [PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVC_256, PVH_NOR, PVH_NOR, PVO_NOR, PVO_PFT, PVO_PFT],
    [PVH_SRT, PVH_SRT, PVH_SRT, PVH_SRT, PVH_NOR, PVH_SRT, PVH_SRT, PVH_SRT, PVH_NOR, PVH_SRT, PVH_SRT, PVH_NOR, PVH_SRT, PVH_NOR, PVO_NOR, PVO_PFT, PVO_PFT],
    [PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVH_NOR, PVO_NOR, PVO_PFT, PVO_PFT],
    [PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_NOR, PVO_PFT, PVO_PFT],
    [PVF_447, PVF_447, PVF_447, PVF_447, PVF_447, PVF_447, PVF_447, PVF_447, PVF_447, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVF_447, PVO_PFT],
    [PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT, PVO_PFT],
]


def _empty_func():  # pragma: no cover
    raise NotImplementedError


_TYPE_BY_ID: List[type] = [object] * MAX_DERIVED
_TYPE_STR: List[str] = [
    'PV_num',
    'PV_pID', 
    'PV_sID', 
    'PV_nRounds', 
    'PV_lRounds', 
    'PV_11p4', 
    'PV_27p4', 
    'PV_55p8', 
    'PV_119p8', 
    'PV_power', 
    'PV_lives', 
    'PV_com64', 
    'PV_quaternion', 
    'PV_s_quaternion', 
    'PV_octonion', 
    'PV_447p64', 
    'PV_perfect'
]


class _OverflowFunctionType_getset:
    """
    This type is of the singleton pattern.
    """
    __value: Union[bool, Callable] = False
    __pre: Union[None, Callable] = None
    __nest: bool = False

    def __new__(cls, obj: bool = False, value = False):
        if obj and not cls.__nest:
            cls.__pre = cls.__value
            cls.__value = value
        return super().__new__(cls)

    def __get__(self, obj: '_OverflowFunctionType', _objtype) -> Callable:
        if _OverflowFunctionType_getset.__value is False:
            return obj.initial
        if _OverflowFunctionType_getset.__value is True:
            return obj.default
        return _OverflowFunctionType_getset.__value
    
    def __set__(self, _obj: '_OverflowFunctionType', value: Union[bool, Callable]):
        if isinstance(value, bool) or callable(value):
            _OverflowFunctionType_getset.__value = value
        else:
            raise TypeError('overflow_function must be callable or bool')
        
    def __enter__(self):
        if _OverflowFunctionType_getset.__nest:
            raise RuntimeError('This context manager does not support nesting.')
        _OverflowFunctionType_getset.__nest = True

    def __exit__(self, exc_type, exc_value, traceback):
        _OverflowFunctionType_getset.__value = _OverflowFunctionType_getset.__pre
        _OverflowFunctionType_getset.__pre = None
        _OverflowFunctionType_getset.__nest = False


class _OverflowFunctionType:
    """
    Does not support multithreading and asynchrony.
    This type is of the singleton pattern.
    """
    func: _OverflowFunctionType_getset = _OverflowFunctionType_getset()

    @staticmethod
    def default(): raise OverflowError

    @staticmethod
    def initial(): pass

    def __call__(self):
        return self.func()
    
    def set(self, value):
        """
        warning: it only can use after keyword 'with'
        
        for example:
            
        with overflow.set(True):
            ...
        """
        if isinstance(value, bool) or callable(value):
            return _OverflowFunctionType_getset(True, value)
        else:
            raise TypeError('overflow_function must be callable or bool')
        

overflow = _OverflowFunctionType()
    

def typestr_int(__arg: str) -> int:
    if not isinstance(__arg, str):
        raise TypeError('arg must be str')
    for i in range(MAX_DERIVED):
        if _TYPE_STR[i] == __arg:
            return i
    raise ValueError('Unknown type name')


def typeint_str(__arg: int) -> str:
    if not isinstance(__arg, int):
        raise TypeError('arg must be str')
    if 0 <= __arg < MAX_DERIVED:
        return _TYPE_STR[__arg]
    else:
        raise ValueError(f'The arg must in [0, {MAX_DERIVED})')
    

def type_int(__arg: Union[type, 'PV_num']) -> int:
    if isinstance(__arg, PV_num):
        return get_type_id(__arg)
    if not isinstance(__arg, type):
        raise TypeError('arg must be type or PV_num object')
    for i in range(MAX_DERIVED):
        if _TYPE_BY_ID[i] == __arg:
            return i
    raise ValueError('Unknown type')


def type_str(__arg: Union[type, 'PV_num']) -> str:
    return _TYPE_STR[type_int(__arg)]
    

def get_type(__arg: Union[int, str]) -> type:
    if isinstance(__arg, int):
        if 0 <= __arg < MAX_DERIVED:
            if _TYPE_BY_ID[__arg] != object:
                return _TYPE_BY_ID[__arg]
            else:
                raise RuntimeError("The arg's type isn't prepared yet")
        else:
            raise ValueError(f'The arg must in [0, {MAX_DERIVED})')
    elif isinstance(__arg, str):
        return get_type(typestr_int(__arg))
    else:
        raise TypeError('arg must be str or int')
    

def typetype_type(__arg1: int, __arg2: int) -> int:
    if not isinstance(__arg1, int) or not isinstance(__arg2, int):
        raise TypeError('args must be int')
    if not 0 <= __arg1 < MAX_DERIVED or not 0 <= __arg2 < MAX_DERIVED:
        raise ValueError(f'The arg must in [0, {MAX_DERIVED})')
    return _TYPETYPE_TYPE[__arg1][__arg2]


def get_type_id(obj: 'PV_num') -> int:
    try:
        return obj._type_id
    except AttributeError:  # pragma: no cover
        pass
    raise TypeError('obj must be PV_num Object')  # pragma: no cover


def register_type(type_id: int, tp: type) -> int:
    if 0 <= type_id < MAX_DERIVED:
        _TYPE_BY_ID[type_id] = tp
        return 0
    else:  # pragma: no cover
        return 1


class PV_num:
    _type_id = 0  # const

    @staticmethod
    def _type_transform(a: 'PV_num', b: 'PV_num') -> Tuple['PV_num', 'PV_num', type]:
        if not isinstance(a, PV_num) or not isinstance(b, PV_num):
            raise TypeError
        lhs_type = get_type_id(a)
        rhs_type = get_type_id(b)
        if lhs_type and rhs_type:
            result_type = _TYPETYPE_TYPE[lhs_type][rhs_type]
            lhs_new = _TYPE_BY_ID[result_type](a)
            rhs_new = _TYPE_BY_ID[result_type](b)
            return lhs_new, rhs_new, _TYPE_BY_ID[result_type]
        elif lhs_type or rhs_type:
            raise TypeError
        else:
            return a, b, PV_num

    @staticmethod
    def _richcmp(lhs: 'PV_num', rhs: 'PV_num', op: int):
        try:
            lhs_new, rhs_new, result_type = PV_num._type_transform(lhs, rhs)
            if result_type is PV_num:
                return bool((op & 1) ^ ((op & 2) >> 1))
            return result_type._richcmp(lhs_new, rhs_new, op)
        except TypeError:
            return NotImplemented

    def __eq__(self, __value: 'PV_num') -> bool:
        return PV_num._richcmp(self, __value, 2)
    
    def __ne__(self, __value: 'PV_num') -> bool:
        return PV_num._richcmp(self, __value, 3)
    
    def __gt__(self, __value: 'PV_num') -> bool:
        return PV_num._richcmp(self, __value, 4)
    
    def __lt__(self, __value: 'PV_num') -> bool:
        return PV_num._richcmp(self, __value, 0)
    
    def __ge__(self, __value: 'PV_num') -> bool:
        return PV_num._richcmp(self, __value, 5)
    
    def __le__(self, __value: 'PV_num') -> bool:
        return PV_num._richcmp(self, __value, 1)
    

    def __hash__(self) -> int:
        return id(PV_num) if id(PV_num) != -1 else -2
    
    @staticmethod
    def _calculate(lhs: 'PV_num', rhs: 'PV_num') -> Union[Tuple['PV_num', 'PV_num'], object]:
        try:
            lhs_new, rhs_new, result_type = PV_num._type_transform(lhs, rhs)
        except TypeError:
            return NotImplemented
        if result_type is PV_num:
            return NotImplemented
        return lhs_new, rhs_new

    def __add__(self, other: 'PV_num'):
        a = PV_num._calculate(self, other)
        return a[0] + a[1] if a is not NotImplemented else NotImplemented
        
    def __sub__(self, other: 'PV_num'):       return NotImplemented
    def __mul__(self, other: 'PV_num'):       return NotImplemented
    def __mod__(self, other: 'PV_num'):       return NotImplemented
    def __pow__(self, other: 'PV_num', modulo: Union[int, None] = None):      return NotImplemented
    def __divmod__(self, other: 'PV_num'):    return NotImplemented
    def __truediv__(self, other: 'PV_num'):   return NotImplemented
    def __floordiv__(self, other: 'PV_num'):  return NotImplemented
    def __neg__(self):                      return NotImplemented
    def __pos__(self):                      return NotImplemented
    def __abs__(self):                      return NotImplemented
    def __bool__(self):                     pass
    def __abs__(self):                      return NotImplemented
    def __invert__(self):                   return NotImplemented
    def __int__(self):                      return NotImplemented
    def __float__(self):                    return NotImplemented
    def __lhsift__(self, other: 'PV_num'):    return NotImplemented
    def __rhsift__(self, other: 'PV_num'):    return NotImplemented
    def __and__(self, other: 'PV_num'):       return NotImplemented
    def __xor__(self, other: 'PV_num'):       return NotImplemented
    def __or__(self, other: 'PV_num'):        return NotImplemented

    def __iadd__(self, other: 'PV_num'):      return NotImplemented
    def __isub__(self, other: 'PV_num'):      return NotImplemented
    def __imul__(self, other: 'PV_num'):      return NotImplemented
    def __imod__(self, other: 'PV_num'):      return NotImplemented
    def __ipow__(self, n: int, p: int):     return NotImplemented
    def __idivmod__(self, other: 'PV_num'):   return NotImplemented
    def __itruediv__(self, other: 'PV_num'):  return NotImplemented
    def __ifloordiv__(self, other: 'PV_num'): return NotImplemented
    def __ilhsift__(self, other: 'PV_num'):   return NotImplemented
    def __irhsift__(self, other: 'PV_num'):   return NotImplemented
    def __iand__(self, other: 'PV_num'):      return NotImplemented
    def __ixor__(self, other: 'PV_num'):      return NotImplemented
    def __ior__(self, other: 'PV_num'):       return NotImplemented

    def __repr__(self) -> str:
        return f'<PV_num object at {id(self)}>'


_TYPE_BY_ID[0] = PV_num
