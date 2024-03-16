BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
# NXDC_FILES = constr/top.nxdc
TOPNAME = ysyxSoCFull
# TOP_V = $(BUILD_DIR)/$(TOPNAME).v


# export PATH := $(PATH):$(abspath ./utils)

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				--trace -O3 --x-assign fast --x-initial fast --noassert -I$(abspath ../ysyxSoC/perip/spi/rtl) -I$(abspath ../ysyxSoC/perip/uart16550/rtl)
VERILATOR_CFLAGS += --timescale "1ns/1ns" --no-timing 
$(shell mkdir -p $(BUILD_DIR))

# # constraint file
# SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
# $(SRC_AUTO_BIND): $(NXDC_FILES)
# 	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source

SCALA_FILE = $(shell find $(abspath ./playground/src/) -name "*.scala")
VSRCS = $(shell find $(BUILD_DIR) -name "*.v" -or -name "*.sv")
VSRCS += $(shell find $(abspath ../ysyxSoC/perip) -name "*.v")
VSRCS += $(abspath ../ysyxSoC/generated/ysyxSoCFull.v)
CSRCS = $(shell find $(abspath ./) -name "*.c" -or -name "*.cc" -or -name "*.cpp" -not -path "./char-test/*")
CSRCS += $(SRC_AUTO_BIND)
LDFLAGS += -lreadline $(shell llvm-config --libs)
# # rules for NVBoard
# include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
vcd ?= 
ifeq ($(vcd), 1)
  CXXFLAGS += -DVCD
endif

INC_PATH := /home/yjmstr/ysyx-workbench/npc/include
INCFLAGS = $(addprefix -I, $(INC_PATH))
CXXFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\"" $(shell llvm-config --cxxflags) -fPIE

test:
	mill -i __.test

$(VSRCS): $(SCALA_FILE)

verilog: $(VSRCS)
	@echo make verilog
	$(call git_commit, "generate verilog")
	mill -i __.test.runMain Elaborate -td $(BUILD_DIR) --split-verilog 

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
	-rm -rf $(BUILD_DIR) logs

sim: clean verilog $(NVBOARD_ARCHIVE) 
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
	--top-module $(TOPNAME) $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE) \
	$(addprefix -CFLAGS , $(CXXFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
	--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))
	mkdir -p logs 
	touch logs/log.txt

run: sim
	@$(BIN) $(IMG)

-include ../Makefile
