from typing import Union


class PV_binary:
    def __init__(self, arg: Union['PV_binary', int, bytes]):
        if isinstance(arg, PV_binary):
            self._size: int = arg._size
            self._data: bytearray = arg._data.copy()
        elif isinstance(arg, int):
            if arg < 0:
                raise ValueError('do not allow size < 0')
            self._size: int = arg
            self._data: bytearray = bytearray(arg)
        elif isinstance(arg, bytes):
            self._size: int = len(arg)
            self._data: bytearray = bytearray(arg)
        else:
            return TypeError('arg must be PV_binary or int or bytes')
        
    @property
    def size(self) -> int:
        return self._size
    
    @property
    def data(self) -> bytes:
        return bytes(self._data)
    
    @data.setter
    def data(self, value: bytes):
        if len(value) != self.size:
            raise ValueError("data's len must equal size")
        self._data = bytearray(value)
        
    def __repr__(self) -> str:
        return f'<PV_binary object at {id(self)}, size = {self.size}>: {list(self._data)}'
        
    def __str__(self) -> str:
        return f'<PV_binary object size = {self.size}>: {list(self._data)}'
        
    def __bytes__(self) -> bytes:
        return self.data
    
    def __eq__(self, other: 'PV_binary') -> bool:
        return self.size == other.size and self.data == other.data
    
    def __hash__(self) -> int:
        return hash(self.data)

    def __bool__(self) -> bool:
        raise TypeError('This class does not support boolean conversion')

    def __len__(self) -> int:
        return self.size
    