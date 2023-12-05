/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/


#include <readline/readline.h>
#include <readline/history.h>
#include <cstdlib>
// #include "sdb.h" 和 cpu.h 改为使用 sim.h
#include "sim.h"
#include <assert.h>

extern NPC_STATES npc_state;

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(npc) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}


static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}

static int cmd_q(char *args) {
  npc_state = NPC_QUIT;
  return -1;
}

static int cmd_si(char *args) {
  if (args == NULL) {
    cpu_exec(1);
    return 0;
  }
  int s = atoi(args);
  cpu_exec(s);
  return 0;
}

static int cmd_info(char *args) {
  if (strcmp(args, "r") == 0) {
    npc_reg_display();
  }
  return 0;
}

static int cmd_x(char *args) {
  // little-endian
  // usage：x $count $expr
  // expr 必须是 0x 开头的16进制数
  uint32_t addr = 0;
  char *arg = strtok(args, " ");
  assert(arg);
  int count = atoi(arg);
  char *arg2 = arg + strlen(arg) + 1;
  sscanf(arg2, "%x", &addr);
  for (uint32_t i = 0; i < count; i++) {
    printf("0x%08x: 0x%08x , ", addr + i * 4, vaddr_read(addr+i*4, 4));
    for (uint32_t j = 0; j < 4; j++) {
      printf("%02x ", vaddr_read(addr + i*4+j, 1));
    }
    printf("\n");
  }
  return 0;
}

static int cmd_help(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NPC", cmd_q },
  { "si", "Single step", cmd_si}, 
  { "info", "Print program status", cmd_info},
  { "x", "Print memory status", cmd_x},
  // { "p", "expr", cmd_p},
  // { "w", "new watch point", cmd_w},
  // { "d", "delete watch point", cmd_d},
  /* TODO: Add more commands */

};
// calculate the length of an array
#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))
#define NR_CMD ARRLEN(cmd_table)


static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}



void sdb_mainloop() {

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      } 
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}