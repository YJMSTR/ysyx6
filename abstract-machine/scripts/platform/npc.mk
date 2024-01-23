AM_SRCS := riscv/npc/start.S \
           riscv/npc/trm.c \
           riscv/npc/ioe.c \
           riscv/npc/timer.c \
           riscv/npc/input.c \
           riscv/npc/cte.c \
           riscv/npc/trap.S \
           platform/dummy/vme.c \
           platform/dummy/mpe.c

CFLAGS    += -fdata-sections -ffunction-sections
LDFLAGS   += -T $(AM_HOME)/scripts/linker.ld \
						 --defsym=_pmem_start=0x80000000 --defsym=_entry_offset=0x0
LDFLAGS   += --gc-sections -e _start
CFLAGS += -DMAINARGS=\"$(mainargs)\"
CFLAGS += -I$(AM_HOME)/am/src/platform/npc/include

.PHONY: $(AM_HOME)/am/src/riscv/npc/trm.c

IMAGE_NAME = $(basename $(notdir $(IMAGE)))
BINNAME = $(patsubst %-$(ARCH), %, $(IMAGE_NAME))
# BINNAME		= $(word 1,$(IMAGE_NAME))


image: $(IMAGE).elf
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

run: image
# $(MAKE) -C /home/yjmstr/ysyx-workbench/am-kernels/tests/cpu-tests ARCH=$(ARCH) ALL="$(BINNAME)"
	$(MAKE) -C $(shell pwd) ARCH=$(ARCH) ALL="$(BINNAME)"
	$(MAKE) -C $(NPC_HOME) ISA=$(ISA) run IMG=$(IMAGE).bin 
  # vcd=1