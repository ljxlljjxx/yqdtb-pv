from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import os
import shutil

# 定义 C 扩展模块
ext_module = Extension(
    'PV_55p8',
    sources=[
        'src/PowerViolenceObjects/py_PV_55p8.c',
        'src/PowerViolenceObjects/pvc_PV_55p8.c',
        'src/PowerViolenceObjects/pvc_defines.c'
    ],
)

# 自定义 build_ext 命令，在编译后复制 .pyi 到构建目录
class CustomBuildExt(build_ext):
    def run(self):
        # 先执行原有的编译过程
        build_ext.run(self)
        # 获取扩展模块的完整路径（.so 文件）
        ext_fullpath = self.get_ext_fullpath(ext_module.name)
        dest_dir = os.path.dirname(ext_fullpath)
        # 源 .pyi 文件的路径
        src_pyi = os.path.join('src', 'PowerViolenceObjects', 'PV_55p8.pyi')
        if os.path.exists(src_pyi):
            dest_pyi = os.path.join(dest_dir, 'PV_55p8.pyi')
            self.copy_file(src_pyi, dest_pyi)
            print(f"Copied stub file: {dest_pyi}")
        else:
            print(f"Warning: stub file not found at {src_pyi}")

setup(
    name='PV_55p8',
    version='0.1.1',
    ext_modules=[ext_module],
    cmdclass={'build_ext': CustomBuildExt},
)
