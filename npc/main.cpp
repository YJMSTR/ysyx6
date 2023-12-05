#include "sim.h"
#include <cstdio>
#include <readline/readline.h>
#include <readline/history.h>

extern enum NPC_STATES npc_state;

int main(int argc, char *argv[]) {
  if(sim_main(argc, argv) == 0) {
    printf("\033[0m\033[1;34mPASS\033[0m\n");
  } else {
    printf("\033[0m\033[1;31mFAIL\033[0m\n");
  }
  return 0;
}