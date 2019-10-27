CC=g++
MONITOR_NAME=monitor
AR=ar
AR_FLAGS=rvs
CFLAGS_LIB= -shared
CFLAGS= -fpic
WD=$(shell pwd)
HEADER=include
LIB_NAME_MEMORYMONITOR=memoryMonitor
LIB_NAME_CPUMONITOR=selfmonitorCPU
LIB_NAME_POWERMONITOR=selfMonitor
LIB_PATH=$(WD)/

main: object-generator static-compile dynamic-compile clean-objects
	@echo "Compilation Finished"

object-generator: object-monitor 
	@echo "Object generated"

object-monitor:
	${CC} ${CFLAGS} -I"$(WD)/../$(HEADER)" -Wall -o ${MONITOR_NAME}.o -c monitor.cpp 

static-compile: static-monitor 
	@echo "Static libs generated"

static-monitor:
	${AR} ${AR_FLAGS} lib${MONITOR_NAME}.a ${MONITOR_NAME}.o

dynamic-compile: dynamic-monitor
	@echo "Dynamic libs generated"

dynamic-monitor:
	@$(CC) $(CFLAGS_LIB) -Wall $(MONITOR_NAME).o -o lib$(MONITOR_NAME).so 

clean-objects:
	@rm *.a *.o 2> /dev/null
