from io import TextIOWrapper
from typing import Self


class VertionType:
    def __init__(self, value: str | tuple[int, int, int] | Self | None = None) -> None:
        if isinstance(value, tuple):
            self.major = value[0]
            self.minor = value[1]
            self.patch = value[2]
        elif isinstance(value, str):
            vertion = tuple(map(int, value.split('.')))
            self.major = vertion[0]
            self.minor = vertion[1]
            self.patch = vertion[2]
        elif isinstance(value, VertionType):
            self.major = value.major
            self.minor = value.minor
            self.patch = value.patch
        elif value is None:
            self.major = -1
            self.minor = -1
            self.patch = -1
        else:
            raise TypeError("'value' must be VertionType or tuple[int, int, int] or str.")

    def __tuple__(self) -> tuple[int, int, int]:
        return (self.major, self.minor, self.patch)
    
    def __str__(self) -> str:
        if self.major == self.minor == self.patch == -1:
            raise ValueError
        return f'{self.major}.{self.minor}.{self.patch}'
    
    def __add__(self, other: Self | int) -> Self:
        if self.major == self.minor == self.patch == -1:
            raise ValueError
        major = self.major
        minor = self.minor
        patch = self.patch
        if isinstance(other, VertionType):
            major += other.major
            minor += other.minor
            patch += other.patch
        elif isinstance(other, int):
            patch += other
        else:
            raise TypeError("'other' must be VertionType or int.")
        return VertionType((major, minor, patch))
    
    def __eq__(self, __value: Self) -> bool:
        return self.major == __value.major and self.minor == __value.minor and self.patch == __value.patch
            

def get_version(file: TextIOWrapper) -> VertionType:
    for line in file:
        if line.startswith('version = '):
            return VertionType(line[11:-2])
        elif line.startswith('__version__ = '):
            return VertionType(line[15:-2])
    return VertionType()

def change_version(file: TextIOWrapper, version: VertionType) -> str:
    new_content: list[str] = []
    for line in file:
        newline: str = line
        if line.startswith('version = '):
            newline = f'version = "{version}"\n'
        elif line.startswith('__version__ = '):
            newline = f'__version__ = "{version}"\n'
        elif line.startswith('DEBUG = '):
            newline = 'DEBUG = True\n'
        new_content.append(newline)
    return ''.join(new_content)

def true_change(filename: str) -> VertionType:
    with open(filename) as file:
        version: VertionType = get_version(file)
        print('now version = ', version)
        version = version + 1
        print('new version = ', version)
    with open(filename) as file:
        content = change_version(file, version)
    with open(filename, 'w') as file:
        file.write(content)
    return version


if __name__ == '__main__':
    a = true_change('setup.py')
    b = true_change('src/PowerViolenceObjects/__init__.py')
    if a != b:
        raise ValueError
