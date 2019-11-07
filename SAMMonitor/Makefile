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
	@sudo mkdir -p $(LOG_PATH)
	@sudo mkdir -p $(LOG_PATH)/results
	@sudo mkdir -p $(USR_PATH)
	@sudo mkdir -p $(USR_PATH)/Model
	@sudo touch $(LOG_PATH)/results/executionEngine.txt

binary:
	@cd $(LIB_PATH) && $(MAKE)
	@cd $(SRC_PATH) && $(MAKE)
	@sudo cp models/SAMModel.txt $(USR_PATH)/Model/SAMModel.txt

clean:
	@echo "Cleaning environment"
	@rm $(BIN_PATH) -rf
	