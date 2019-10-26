from ctypes import *
# either

lpath = "../lib"
monitor = cdll.LoadLibrary(lpath+"libmonitor.so")
monitor.monitorProcess(10)