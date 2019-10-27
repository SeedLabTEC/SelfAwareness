from distutils.core import setup, Extension

sammonitor = Extension('sammonitor', sources = ['pythonMonitor.cpp'])

setup(
    name        = 'sammonitor',
    version     = '1.0',
    description = 'Sample python C-API exploration',
    ext_modules = [sammonitor]
)