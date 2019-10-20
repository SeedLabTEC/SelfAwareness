CC=g++
APP=SAMMemory
WD=$(shell pwd)
LIB_PATH=$(WD)/../lib
HEADER=$(WD)/../include
BIN_DIR=$(WD)/../bin
C_FILES=$(wildcard *.cpp)
LIB_NAME_MEMORYMONITOR=memoryMonitor




main:
	@$(MAKE) build

build: memoryModel
	@echo "Application Builded"

memoryModel:	
	@$(CC) -I"$(HEADER)" -L"$(LIB_PATH)" -Wl,-rpath="$(LIB_PATH)" -o "$(BIN_DIR)/$(APP)" $(C_FILES) -l$(LIB_NAME_MEMORYMONITOR)


