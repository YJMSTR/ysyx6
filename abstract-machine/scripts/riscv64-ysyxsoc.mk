include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/ysyxsoc.mk
CFLAGS  += -DISA_H=\"riscv/riscv.h\" 
LDFLAGS += --print-map