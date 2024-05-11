include $(AM_HOME)/scripts/isa/riscv.mk
include $(AM_HOME)/scripts/platform/npc.mk
CFLAGS  += -DISA_H=\"riscv/riscv.h\"
LDFLAGS += --print-map

# AM_SRCS += riscv/npc/start.S \
#            riscv/npc/trm.c \
#            riscv/npc/ioe.c \
#            riscv/npc/timer.c \
#            riscv/npc/input.c \
#            riscv/npc/cte.c \
#            riscv/npc/trap.S \
#            platform/dummy/vme.c \
#            platform/dummy/mpe.c

# AM_SRCS += riscv/npc/libgcc/div.S \
#            riscv/npc/libgcc/muldi3.S \
#            riscv/npc/libgcc/multi3.c \
#            riscv/npc/libgcc/ashldi3.c \
#            riscv/npc/libgcc/unused.c