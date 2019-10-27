import sammonitor as samm
import os
import time
from multiprocessing import Process

def monitorProcess(pid):
    if os.fork() != 0:
        return
    samm.monitorApp(pid)

def startProcess(pid):
    p = Process(target=monitorProcess,args=(pid,))
    p.start()
    p.join()
    print('exiting main')
    exit(0)


startProcess(10)