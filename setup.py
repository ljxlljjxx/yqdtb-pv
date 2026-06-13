import setuptools
import sys

version = "3.1.46"
DEBUG = False

if DEBUG:
    debug_args = ['-DDEBUG']
else:
    debug_args = []

IS_MSVC = sys.platform.startswith('win') and sys.version_info.major >= 3
try:
    from setuptools import distutils
    compiler = distutils.ccompiler.new_compiler()
    IS_MSVC = compiler.compiler_type == 'msvc'
except:
    IS_MSVC = sys.platform.startswith('win')

extra_compile_args = []

if sys.platform.startswith('linux') or sys.platform == 'darwin':
    math_libs = ['m']
else:
    math_libs = []

setuptools.setup(
    packages=['PowerViolenceObjects'],
    package_dir={'': 'src'},
    ext_modules=[
        setuptools.Extension(
            'PowerViolenceObjects.pv_str',
            sources=[
                'src/PowerViolenceObjects/pvc_debug.c',
                'src/PowerViolenceObjects/py_PV_str.c',
            ],
            extra_compile_args=[*extra_compile_args, *debug_args],
            libraries=[*math_libs],
        ),
        setuptools.Extension(
            'PowerViolenceObjects.pv_str_names',
            sources=[
                'src/PowerViolenceObjects/pvc_debug.c',
                'src/PowerViolenceObjects/py_PV_str_names.c',
            ],
            extra_compile_args=[*extra_compile_args, *debug_args],
            libraries=[*math_libs],
        ),
        setuptools.Extension(
            'PowerViolenceObjects.pv_num',
            sources=[
                'src/PowerViolenceObjects/pvc_PV_num.c',
                'src/PowerViolenceObjects/pvc_debug.c',
                'src/PowerViolenceObjects/py_PV_num.c',
            ],
            extra_compile_args=[*extra_compile_args, *debug_args],
            libraries=[*math_libs],
        ),
        setuptools.Extension(
            'PowerViolenceObjects.pv_55p8',
            sources=[
                'src/PowerViolenceObjects/pvc_PV_num.c',
                'src/PowerViolenceObjects/pvc_debug.c',
                'src/PowerViolenceObjects/py_PV_55p8.c',
                'src/PowerViolenceObjects/pvc_PV_55p8.c',
                'src/PowerViolenceObjects/pvc_defines.c',
            ],
            extra_compile_args=[*extra_compile_args, *debug_args],
            libraries=[*math_libs],
        ),
        setuptools.Extension(
            'PowerViolenceObjects.pv_119p8',
            sources=[
                'src/PowerViolenceObjects/pvc_PV_num.c',
                'src/PowerViolenceObjects/pvc_debug.c',
                'src/PowerViolenceObjects/py_PV_119p8.c',
                'src/PowerViolenceObjects/pvc_PV_119p8.c',
                'src/PowerViolenceObjects/pvc_defines.c',
            ],
            extra_compile_args=[*extra_compile_args, *debug_args],
            libraries=[*math_libs],
        ),
    ],
    version=version
)