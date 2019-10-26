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

object-generator: object-memorymonitor 
	@echo "Object generated"

object-memorymonitor:
	${CC} -I"$(WD)/../$(HEADER)" -L"$(LIB_PATH)" -Wall -o ${MONITOR_NAME}.o -c monitor.cpp ${CFLAGS} -lm -l$(LIB_NAME_MEMORYMONITOR) -l$(LIB_NAME_CPUMONITOR) -l$(LIB_NAME_POWERMONITOR) 
static-compile: static-memorymonitor 
	@echo "Static libs generated"

static-memorymonitor:
	${AR} ${AR_FLAGS} lib${MONITOR_NAME}.a ${MONITOR_NAME}.o

dynamic-compile: dynamic-memorymonitor
	@echo "Dynamic libs generated"

dynamic-memorymonitor:
	@$(CC) -Wall $(MONITOR_NAME).o -o lib$(MONITOR_NAME).so $(CFLAGS_LIB)

clean-objects:
	@rm *.a *.o 2> /dev/null
