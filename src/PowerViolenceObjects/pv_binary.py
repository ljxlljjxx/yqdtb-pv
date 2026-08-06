class PV_binary:
    def __init__(self, arg: 'PV_binary' | int | bytes):
        if isinstance(arg, PV_binary):
            self.size: int = arg.size
            self._data: bytearray = arg._data.copy()
        elif isinstance(arg, int):
            if arg < 0:
                raise ValueError('do not allow size < 0')
            self.size: int = arg
            self._data: bytearray = bytearray(arg)
        elif isinstance(arg, bytes):
            self.size: int = len(arg)
            self._data: bytearray = bytearray(arg)
        else:
            return TypeError('arg must be PV_binary or int or bytes')
        
    @property
    def data(self) -> bytes:
        return bytes(self._data)
    
    @data.setter
    def data(self, value: bytes):
        self._data = bytearray(value)
        
    def __repr__(self) -> str:
        return f'<PV_binary object at {id(self)}, size = {self.size}>: {list(self._data)}'
    