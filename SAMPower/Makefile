WD=$(shell pwd)
BIN_PATH=bin/
SRC_PATH=$(WD)/src
LIB_PATH=$(WD)/lib

.PHONY: clean 

build:
	@$(MAKE) main --no-print-directory

main: structure binary
	@echo "Build binaries"

structure:
	@mkdir -p $(BIN_PATH)

binary:
	@cd $(LIB_PATH) && $(MAKE)
	@cd $(SRC_PATH) && $(MAKE)

clean:
	@echo "Cleaning environment"
	@rm $(BIN_PATH) -rf
	