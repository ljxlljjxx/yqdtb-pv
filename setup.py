import setuptools

version = '2.5.0'
extra_compile_args = ['-Wformat=2', '-Wconversion', '-Werror=return-type', '-Wshadow', '-Wnull-dereference', '-Wpointer-arith', '-Wfloat-equal', '-Wswitch-default', '-Wswitch-enum', '-Wall', '-Wextra', '-Wno-unused-parameter', '-Werror']

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
        ),
        setuptools.Extension(
            'PowerViolenceObjects.pv_55p8',
            sources=[
                'src/PowerViolenceObjects/py_PV_55p8.c',
                'src/PowerViolenceObjects/pvc_PV_55p8.c',
                'src/PowerViolenceObjects/pvc_defines.c',
            ],
            extra_compile_args=extra_compile_args,
        ),
    ],
    version=version
)