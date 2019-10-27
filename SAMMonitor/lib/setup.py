from distutils.core import setup, Extension

sammonitor = Extension('SAMMonitor', sources = ['pythonMonitor.cpp'])

setup(
    name        = 'SAMMonitor',
    version     = '1.0',
    description = 'Sample python C-API exploration',
    ext_modules = [sammonitor]
)