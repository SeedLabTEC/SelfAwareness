WD=$(shell pwd)
BIN_PATH=bin/
SRC_PATH=$(WD)/src
LIB_PATH=$(WD)/lib
LOG_PATH=/var/log/SAM
USR_PATH=/usr/SAM

.PHONY: clean 

build:
	@$(MAKE) main --no-print-directory

main: structure binary
	@echo "Build binaries"

structure:
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(BIN_PATH)/X86
	@mkdir -p $(BIN_PATH)/ARM
	@mkdir -p $(BIN_PATH)
	@mkdir -p $(LOG_PATH)
	@mkdir -p $(LOG_PATH)/results
	@mkdir -p $(USR_PATH)
	@mkdir -p $(USR_PATH)/Model
	@touch $(LOG_PATH)/results/executionEngine.txt

binary:
	@cd $(LIB_PATH) && $(MAKE)
	@cd $(SRC_PATH) && $(MAKE)
	@cp models/SAMModel.txt $(USR_PATH)/Model/SAMModel.txt

clean:
	@echo "Cleaning environment"
	@rm $(BIN_PATH) -rf
	