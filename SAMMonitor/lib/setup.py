from distutils.core import setup, Extension

mymodule = Extension('mymodule', sources = ['pythonMonitor.cpp'])

setup(
    name        = 'mymodule',
    version     = '1.0',
    description = 'Sample python C-API exploration',
    ext_modules = [mymodule]
)