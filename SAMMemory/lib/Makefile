CC=g++
MEMINFO=memInfo
MEMORYMONITOR_NAME=memoryMonitor
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
	${CC} -Wall -o ${MEMORYMONITOR_NAME}.o -c memoryMonitor.cpp ${CFLAGS} -lm -I"$(WD)/../$(HEADER)"

static-compile: static-memorymonitor 
	@echo "Static libs generated"

static-memorymonitor:
	${AR} ${AR_FLAGS} lib${MEMORYMONITOR_NAME}.a ${MEMORYMONITOR_NAME}.o

dynamic-compile: dynamic-memorymonitor
	@echo "Dynamic libs generated"

dynamic-memorymonitor:
	@$(CC) -Wall $(MEMORYMONITOR_NAME).o -o lib$(MEMORYMONITOR_NAME).so $(CFLAGS_LIB)

clean-objects:
	@rm *.a *.o 2> /dev/null
