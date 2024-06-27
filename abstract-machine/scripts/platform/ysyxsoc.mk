# AM_SRCS := riscv/ysyxsoc/start.S \
#            riscv/ysyxsoc/trm.c \
#            riscv/ysyxsoc/ioe.c \
#            riscv/ysyxsoc/timer.c \
#            riscv/ysyxsoc/input.c \
#            riscv/ysyxsoc/cte.c \
#            riscv/ysyxsoc/trap.S \
#            riscv/ysyxsoc/audio.c \
#            riscv/ysyxsoc/gpu.c \
#            platform/dummy/vme.c \
#            platform/dummy/mpe.c

AM_SRCS := platform/ysyxsoc/trm.c \
					 riscv/ysyxsoc/start.S \
					 platform/ysyxsoc/ioe/ioe.c \
					 platform/ysyxsoc/ioe/timer.c \
           riscv/ysyxsoc/input.c \
           riscv/ysyxsoc/cte.c \
           riscv/ysyxsoc/trap.S \
           riscv/ysyxsoc/audio.c \
           riscv/ysyxsoc/gpu.c \
           platform/dummy/vme.c \
           platform/dummy/mpe.c

CFLAGS    += -fdata-sections -ffunction-sections
LDFLAGS   += -T $(AM_HOME)/scripts/ysyxsoc-linker.ld \
						 --defsym=_pmem_start=0x30000000 --defsym=_entry_offset=0x0
LDFLAGS   += --gc-sections -e _start
LDFLAGS 	+= --defsym=_stack_top=0x0f001000 --defsym=_stack_pointer=0x0f002000 --defsym=_heap_start=0x0f000000 --defsym=_heap_size=0x1000
CFLAGS += -DMAINARGS=\"$(mainargs)\"
CFLAGS += -I$(AM_HOME)/am/src/platform/ysyxsoc/include

.PHONY: $(AM_HOME)/am/src/platform/ysyxsoc/trm.c

IMAGE_NAME = $(basename $(notdir $(IMAGE)))
BINNAME = $(patsubst %-$(ARCH), %, $(IMAGE_NAME))

image: $(IMAGE).elf
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

run: image
# $(MAKE) -C /home/yjmstr/ysyx-workbench/am-kernels/tests/cpu-tests ARCH=$(ARCH) ALL="$(BINNAME)"
	$(MAKE) -C $(shell pwd) ARCH=$(ARCH) ALL="$(BINNAME)"
	@echo mainargs=$(mainargs)
	$(MAKE) -C $(NPC_HOME) ISA=$(ISA) run IMG=$(IMAGE).bin 
  # vcd=1
