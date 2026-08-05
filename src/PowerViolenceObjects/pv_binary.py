from typing import Self


class PV_binary:
    def __init__(self, arg: Self | int | bytes):
        if isinstance(arg, PV_binary):
            self.size: int = arg.size
            self.data: bytearray = arg.data.copy()
        elif isinstance(arg, int):
            if arg < 0:
                raise ValueError('do not allow size < 0')
            self.size: int = arg
            self.data: bytearray = bytearray(arg)
        elif isinstance(arg, bytes):
            self.size: int = len(arg)
            self.data: bytearray = bytearray(arg)
        else:
            return TypeError('arg must be PV_binary or int or bytes')
        
    def __repr__(self) -> str:
        return f'<PV_binary object at {id(self)}, size = {self.size}>: {list(self.data)}'
    