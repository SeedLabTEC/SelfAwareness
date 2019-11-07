CCA=arm-poky-linux-gnueabi-gcc -march=armv7ve -marm -mfpu=neon-vfpv4 -mfloat-abi=hard -mcpu=cortex-a7 --sysroot=/opt/poky/2.5.1/sysroots/cortexa7hf-neon-vfpv4-poky-linux-gnueabi
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
LIB_NAME_PTHREAD=pthread

.PHONY: arm

main:
	@$(MAKE) build

build: monitorModel
	@echo "Application Builded"

monitorModel:	
	@$(CC) -I"$(HEADER)" -L"$(LIB_PATH)" -Wl,-rpath="$(LIB_PATH)" -o "$(BIN_DIR)/X86/$(APP)" $(C_FILES) -l$(LIB_NAME_PTHREAD) 

arm:
	@$(CCA) -I"$(HEADER)" -L"$(LIB_PATH)" -Wl,-rpath="$(LIB_PATH)" -o "$(BIN_DIR)/ARM/$(APP)" $(C_FILES) -l$(LIB_NAME_PTHREAD)
