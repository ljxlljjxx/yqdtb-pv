import setuptools
import sys

version = '2.5.0'
IS_MSVC = sys.platform.startswith('win') and sys.version_info.major >= 3
try:
    from setuptools import distutils
    compiler = distutils.ccompiler.new_compiler()
    IS_MSVC = compiler.compiler_type == 'msvc'
except:
    IS_MSVC = sys.platform.startswith('win')

if IS_MSVC:
    extra_compile_args = [
        '/W4', '/WX', '/we4061', '/we4715', '/wd4100', '/wd4127', '/w44265'
    ]
else:
    # GCC/Clang 编译参数（原列表）
    extra_compile_args = [
        '-Wformat=2', '-Wconversion', '-Wreturn-type', '-Wshadow',
        '-Wnull-dereference', '-Wpointer-arith', '-Wfloat-equal',
        '-Wswitch-default', '-Wswitch-enum', '-Wall', '-Wextra',
        '-Wno-unused-parameter', '-Werror'
    ]

setuptools.setup(
    packages=['PowerViolenceObjects'],
    package_dir={'': 'src'},
    ext_modules=[
        setuptools.Extension(
            'PowerViolenceObjects.pv_num',
            sources=[
                'src/PowerViolenceObjects/py_PV_num.c',
            ],
            extra_compile_args=extra_compile_args,
            libraries=['m'],
        ),
        setuptools.Extension(
            'PowerViolenceObjects.pv_55p8',
            sources=[
                'src/PowerViolenceObjects/py_PV_55p8.c',
                'src/PowerViolenceObjects/pvc_PV_55p8.c',
                'src/PowerViolenceObjects/pvc_defines.c',
            ],
            extra_compile_args=extra_compile_args,
            libraries=['m'],
        ),
        setuptools.Extension(
            'PowerViolenceObjects.pv_119p8',
            sources=[
                'src/PowerViolenceObjects/py_PV_119p8.c',
                'src/PowerViolenceObjects/pvc_PV_119p8.c',
                'src/PowerViolenceObjects/pvc_defines.c',
            ],
            extra_compile_args=extra_compile_args,
            libraries=['m'],
        ),
    ],
    version=version
)