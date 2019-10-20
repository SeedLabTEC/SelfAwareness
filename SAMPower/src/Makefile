CC=g++
APP=SAMPower
WD=$(shell pwd)
LIB_PATH=$(WD)/../lib
HEADER=$(WD)/../include
BIN_DIR=$(WD)/../bin
C_FILES=$(wildcard *.cpp)
LIB_NAME_ENVMONITOR=envMonitor
LIB_NAME_SELFMONITOR=selfMonitor
LIB_NAME_MODEL=powerModel
LIB_NAME_QUEUE=executionqueue

main:
	@$(MAKE) build

build: powerModel
	@echo "Application Builded"

powerModel:	
	@$(CC) -I"$(HEADER)" -L"$(LIB_PATH)" -Wl,-rpath="$(LIB_PATH)" -o "$(BIN_DIR)/$(APP)" $(C_FILES) -l$(LIB_NAME_ENVMONITOR) -l$(LIB_NAME_SELFMONITOR) -l$(LIB_NAME_MODEL) -l$(LIB_NAME_QUEUE)
