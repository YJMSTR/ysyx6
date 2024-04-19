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
#include <ftrace.h>
// #include "sdb.h" 和 cpu.h 改为使用 sim.h
#include <sim.h>
#include <debug.h>
#include <assert.h>

extern "C" void init_disasm(const char *triple);
void init_difftest(char *ref_so_file, long img_size, int port);
extern NPC_STATES npc_state;
// static char *diff_so_file = "/home/yjmstr/ysyx-workbench/nemu/build/riscv32-nemu-interpreter-so";
static char *diff_so_file = "/home/yjmstr/ysyx-workbench/nemu/build/riscv64-nemu-interpreter-so";
static int difftest_port = 1234;
const char *log_file = "/home/yjmstr/ysyx-workbench/npc/logs/log.txt";

void assert_fail_msg() {
  npc_reg_display();
  //statistic();
}

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
  word_t addr = 0;
  char *arg = strtok(args, " ");
  assert(arg);
  int count = atoi(arg);
  char *arg2 = arg + strlen(arg) + 1;
  sscanf(arg2, "%lx", &addr);
  for (word_t i = 0; i < count; i++) {
    printf("0x%016lx: 0x%016lx , ", addr + i * 8, npc_vaddr_read(addr+i*8, 8));
    for (word_t j = 0; j < 8; j++) {
      printf("%02lx ", npc_vaddr_read(addr + i*8+j, 1));
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
extern bool difftest_is_enable;
extern bool is_itrace;
void init_monitor() {
  init_log(log_file);
  // set_ftrace_enable();
  long img_size = load_img();
  if (difftest_is_enable)
    init_difftest(diff_so_file, img_size, difftest_port);
  if (is_itrace)
    init_disasm("riscv64" "-pc-linux-gnu");
  printf("注意：RTL 中需要添加 AXI4 主设备对非对齐访存的处理，目前仅支持不跨越 8 字节的非对齐写入，形如 sd a0 addr=0x04 的写指令和全部的非对齐读还不支持\n");
}

extern bool is_batch_mode;
void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

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
