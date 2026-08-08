from typing import Iterable, Union


class PV_binary:
    """
    An implementation for PV_binary.
    This is an alternative option.

    the upper limit of size is UINT64_MAX(65535)

    In fact, there is no guarantee that the data
    will be all zeros at initialization.

    In the implementation using C, it is not
    guaranteed that data is a list, but it is
    guaranteed that data is an Interable, and the
    object taken out each time is of type bool.
    """

    def __init__(self, arg: Union['PV_binary', int, Iterable]):
        """
        the arg must be PV_binary or int or Interable, 
        if arg is the Interable, it must be
        Iterable[bool] or Iterable[int], and the int
        must be 0 or 1
        """
        if isinstance(arg, PV_binary):
            self._size: int = arg._size
            self._data: list = arg._data.copy()
        elif isinstance(arg, int):
            if arg < 0:
                raise ValueError('size can not be negative')
            if arg >= 65536:
                raise OverflowError('Python int too large for C unsigned short')
            self._size: int = arg
            self._data: list = [0] * self._size
        else:
            self._data = []
            try:
                for i in arg:
                    if isinstance(i, int):
                        if i == 0 or i == 1:
                            i = bool(i)
                        else:
                            raise ValueError('when arg be Iterator[int], the int must be 0 or 1')
                    if not isinstance(i, bool):
                        raise TypeError('arg must be PV_binary or int or Iterable[bool]')
                    self._data.append(i)
                self._size = len(self._data)
            except TypeError:
                raise TypeError('arg must be PV_binary or int or Iterable[bool]')
        
    @property
    def size(self) -> int:
        return self._size
    
    @property
    def data(self) -> Iterable[bool]:
        return (i for i in self._data)
        
    def __repr__(self) -> str:
        return f'<PV_binary object at {id(self)}, size = {self.size}>: {[int(i) for i in self._data]}'
        
    def __str__(self) -> str:
        return f'<PV_binary object size = {self.size}>: {[int(i) for i in self._data]}'
        
    def __eq__(self, other: 'PV_binary') -> bool:
        assert isinstance(other, PV_binary), f'can not compare {type(other)} object with PV_binary'
        return self.size == other.size and self._data == other._data
    
    def __hash__(self) -> int:
        a: int = 0
        P: int = 9985244353
        for i in self.data:
            a = (a << 1) + i
            a %= P
        return a

    def __bool__(self) -> bool:
        raise TypeError('This class does not support boolean conversion')

    def __len__(self) -> int:
        return self.size
    
    def __getitem__(self, index: int) -> bool:
        if isinstance(index, int):
            if -self.size <= index < self.size:
                return self._data[index]
            else:
                raise ValueError('index out of range')
        else:
            raise TypeError('index must be int or slice')
    
    def __setitem__(self, index: Union[int, slice], value: Union[int, bool]):
        """
        when the index is a slice, it must be [:] or [::].
        if it isn't, function will raise ValueError

        when the value is a int, it must be 0 or 1.
        if it isn't, function will raise ValueError
        """
        if isinstance(value, int):
            if value == 0 or value == 1:
                value = bool(value)
            else:
                raise ValueError('when arg be int, it must be 0 or 1')
        if not isinstance(value, bool):
            raise TypeError('value must be int or bool')
        if isinstance(index, int):
            if -self.size <= index < self.size:
                self._data[index] = value
            else:
                raise ValueError('index out of range')
        elif isinstance(index, slice):
            if index.start is index.stop is index.step is None:
                for i in range(self.size):
                    self._data[i] = value
            else:
                raise ValueError('when index be slice, it must be [:] or [::]')
        else:
            raise TypeError('index must be int or slice')
        
    def __delitem__(self, _index):
        raise TypeError('PV_binary object does not support item deletion')
        