CC=g++
APP=SAMMonitor
WD=$(shell pwd)
LIB_PATH=$(WD)/../lib
HEADER=$(WD)/../include
BIN_DIR=$(WD)/../bin
C_FILES=$(wildcard *.cpp)
LIB_NAME_MONITOR=monitor
LIB_NAME_MEMORYMONITOR=memoryMonitor
LIB_NAME_CPUMONITOR=selfmonitorCPU
LIB_NAME_POWERMONITOR=selfMonitor



main:
	@$(MAKE) build

build: monitorModel
	@echo "Application Builded"

monitorModel:	
	@$(CC) -I"$(HEADER)" -L"$(LIB_PATH)" -Wl,-rpath="$(LIB_PATH)" -o "$(BIN_DIR)/$(APP)" $(C_FILES) -l$(LIB_NAME_MONITOR) -l$(LIB_NAME_MEMORYMONITOR) -l$(LIB_NAME_CPUMONITOR) -l$(LIB_NAME_POWERMONITOR) 


