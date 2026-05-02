import setuptools

setuptools.setup(
    packages=setuptools.find_namespace_packages('src'),
    package_dir={'': 'src'},
    ext_modules=[
        setuptools.Extension(
            'PowerViolenceObjects.PV_num.PV_fixed.PV_55p8',
            sources=[
                'src/PowerViolenceObjects/PV_num/PV_fixed/py_PV_55p8.c',
                'src/PowerViolenceObjects/PV_num/PV_fixed/pvc_PV_55p8.c',
                'src/PowerViolenceObjects/PV_num/PV_fixed/pvc_defines.c'
            ],
        )
    ],
    version='2.0.1'
)
