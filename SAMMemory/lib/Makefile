CC=g++
MONITOR_NAME=memoryMonitor
AR=ar
AR_FLAGS=rvs
CFLAGS_LIB= -shared
CFLAGS= -fpic
WD=$(shell pwd)
HEADER=include

main: object-generator static-compile dynamic-compile clean-objects
	@echo "Compilation Finished"

object-generator: object-memorymonitor 
	@echo "Object generated"

object-memorymonitor:
	${CC} -Wall -o ${MONITOR_NAME}.o -c memoryMonitor.cpp ${CFLAGS} -lm -I"$(WD)/../$(HEADER)"

static-compile: static-memorymonitor 
	@echo "Static libs generated"

static-memorymonitor:
	${AR} ${AR_FLAGS} lib${MONITOR_NAME}.a ${MONITOR_NAME}.o

dynamic-compile: dynamic-memorymonitor
	@echo "Dynamic libs generated"

dynamic-memorymonitor:
	@$(CC) -Wall $(MONITOR_NAME).o -o lib$(MONITOR_NAME).so $(CFLAGS_LIB)

clean-objects:
	@rm *.o 2> /dev/null
