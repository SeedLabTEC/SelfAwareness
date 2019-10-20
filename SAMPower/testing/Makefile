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

main:
	@$(MAKE) build

build: clean testing
	@echo "Application Builded"

testing:
	@$(CC) -I"$(HEADER)" -L"$(LIB_PATH)" -Wl,-rpath="$(LIB_PATH)" -o testing testing.cpp -l$(LIB_NAME_ENVMONITOR) -l$(LIB_NAME_SELFMONITOR) -l$(LIB_NAME_MODEL)

clean:
	@rm testing 2> /dev/null