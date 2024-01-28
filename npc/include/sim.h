#ifndef __SIM_H__
#define __SIM_H__


// #include <common.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>
#include <debug.h>
#include <ftrace.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef uint64_t word_t;
typedef word_t vaddr_t;

enum NPC_STATES {
  NPC_RUN,
  NPC_STOP,
  NPC_ABORT,
  NPC_QUIT,
};

// typedef MUXDEF(CONFIG_ISA64, uint64_t, uint32_t) word_t;
// typedef MUXDEF(CONFIG_ISA64, int64_t, int32_t)  sword_t;
// #define FMT_WORD MUXDEF(CONFIG_ISA64, "0x%016" PRIx64, "0x%08" PRIx32)
#define FMT_WORD "0x%016lx"
void cpu_exec(uint32_t n);
void sdb_mainloop();
void init_monitor();
long load_img();
void init_difftest(char *ref_so_file, long img_size, int port);
void npc_reg_display();
word_t npc_paddr_read(word_t addr, int len);
word_t npc_vaddr_read(word_t addr, int len);
int sim_main(int argc, char *argv[]);

#endif