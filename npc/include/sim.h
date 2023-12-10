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

typedef uint32_t word_t;
typedef word_t vaddr_t;

enum NPC_STATES {
  NPC_RUN,
  NPC_STOP,
  NPC_ABORT,
  NPC_QUIT,
};

void cpu_exec(uint32_t n);
void sdb_mainloop();
void init_monitor();
void npc_reg_display();
word_t paddr_read(word_t addr, int len);
word_t vaddr_read(word_t addr, int len);
int sim_main(int argc, char *argv[]);

#endif