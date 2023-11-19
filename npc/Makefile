BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
# NXDC_FILES = constr/top.nxdc
TOPNAME = Top

export PATH := $(PATH):$(abspath ./utils)

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert

$(shell mkdir -p $(BUILD_DIR))

# # constraint file
# SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
# $(SRC_AUTO_BIND): $(NXDC_FILES)
# 	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source
VSRCS = $(shell find $(BUILD_DIR) -name "*.v" -or -name "*.sv")
CSRCS = $(shell find $(abspath ./) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)

# # rules for NVBoard
# include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""

test:
	mill -i __.test

verilog: clean
	@echo make verilog
	$(call git_commit, "generate verilog")
	mill -i __.test.runMain Elaborate -td $(BUILD_DIR) --split-verilog 

$(VSRCS): $(CSRCS) verilog

help:
	mill -i __.test.runMain Elaborate --help

compile:
	mill -i __.compile

bsp:
	mill -i mill.bsp.BSP/install

reformat:
	mill -i __.reformat

checkformat:
	mill -i __.checkFormat

.PHONY: test verilog help compile bsp reformat checkformat clean sim run

clean:
	@echo make clean 
	-rm -rf $(BUILD_DIR)

sim: $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE) 
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	$(VERILATOR) $(VERILATOR_CFLAGS) \
	--top-module $(TOPNAME) $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE) \
	$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
	--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

run: sim
	@$(BIN) $(IMG)

-include ../Makefile
