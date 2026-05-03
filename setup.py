import setuptools

version = '2.3.0'

with open('src/PowerViolenceObjects/__init__.py', 'r') as f:
    contect: list[str] = [i if not i.startswith('__vertion__') else f'__vertion__ = {version}' for i in f]


setuptools.setup(
    packages=['PowerViolenceObjects'],
    package_dir={'': 'src'},
    ext_modules=[
        setuptools.Extension(
            'PowerViolenceObjects.PV_num',
            sources=[
                'src/PowerViolenceObjects/py_PV_num.c',
            ],
        ),
        setuptools.Extension(
            'PowerViolenceObjects.PV_fixed',
            sources=[
                'src/PowerViolenceObjects/py_PV_fixed.c',
                'src/PowerViolenceObjects/py_PV_num.c',
            ],
        ),
        setuptools.Extension(
            'PowerViolenceObjects.PV_55p8',
            sources=[
                'src/PowerViolenceObjects/py_PV_55p8.c',
                'src/PowerViolenceObjects/pvc_PV_55p8.c',
                'src/PowerViolenceObjects/pvc_defines.c',
                'src/PowerViolenceObjects/py_PV_fixed.c',
                'src/PowerViolenceObjects/py_PV_num.c',
            ],
        ),
    ],
    version=version
)