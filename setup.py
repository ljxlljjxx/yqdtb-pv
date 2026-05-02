import setuptools

setuptools.setup(
    packages=setuptools.find_namespace_packages('src'),
    package_dir={'': 'src'},
    ext_modules=[
        setuptools.Extension(
            'PowerViolenceObjects.PV_num',
            sources=[
                'src/PowerViolenceObjects/py_PV_num.c',
            ],
        ),
        setuptools.Extension(
            'PowerViolenceObjects.PV_55p8',
            sources=[
                'src/PowerViolenceObjects/py_PV_55p8.c',
                'src/PowerViolenceObjects/pvc_PV_55p8.c',
                'src/PowerViolenceObjects/pvc_defines.c'
            ],
        ),
    ],
    version='2.2.1'
)
