#include "VTop.h"
// #include "verilated_vcd_c.h"
// #include <nvboard.h>
#include <unistd.h>
#include "verilated.h"
#include "VTop__Dpi.h"
#include "svdpi.h"
#include "sim.h"
#include <ftrace.h>
#include "VTop___024root.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <debug.h>
#include <macro.h>
#include <dlfcn.h>

#ifndef CONFIG_RVE
#define CONFIG_RVE
#endif
typedef uint32_t paddr_t;
typedef struct {
  word_t gpr[MUXDEF(CONFIG_RVE, 16, 32)];
  vaddr_t pc;
} CPU_state;

void (*ref_difftest_memcpy)(paddr_t addr, void *buf, size_t n, bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
void (*ref_difftest_exec)(uint64_t n) = NULL;
// void (*ref_difftest_raise_intr)(uint64_t NO) = NULL;

void init_difftest(char *ref_so_file, long img_size, int port) {
  Log("------------------------init difftest!----------------------------");
  assert(ref_so_file != NULL);

  void *handle;
  handle = dlopen(ref_so_file, RTLD_LAZY);
  assert(handle);

  ref_difftest_memcpy = (void (*)(paddr_t, void*, size_t, bool))dlsym(handle, "difftest_memcpy");
  assert(ref_difftest_memcpy);

  ref_difftest_regcpy = (void (*)(void*, bool))dlsym(handle, "difftest_regcpy");
  assert(ref_difftest_regcpy);

  ref_difftest_exec = (void (*)(uint64_t))dlsym(handle, "difftest_exec");
  assert(ref_difftest_exec);
}

#define MEM_BASE 0x80000000
#define MEM_SIZE 0x8000000

#ifndef CONFIG_ITRACE_RINGBUFFER_SIZE
  #define CONFIG_ITRACE_RINGBUFFER_SIZE 16
#endif


#ifdef VCD
  #include "verilated_vcd_c.h"
  VerilatedVcdC* tfp = nullptr;
#endif
VerilatedContext* contextp = new VerilatedContext;
VTop* topp = new VTop{contextp};
enum NPC_STATES npc_state;
int npc_ret;

// void nvboard_bind_all_pins(VTop *top);
const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

word_t Rread(uint32_t idx) {
  return topp->rootp->Top__DOT__R_ext__DOT__Memory[idx];
}

struct Iringbuf 
{
  word_t pc[CONFIG_ITRACE_RINGBUFFER_SIZE];
  word_t inst[CONFIG_ITRACE_RINGBUFFER_SIZE];
  int cur;
} iringbuf;


static uint8_t mem[MEM_SIZE] = {
  0x93, 0x02, 0x00, 0x08, 
  0x13, 0x03, 0x10, 0x08,
  0x73, 0x00, 0x10, 0x00
}; 

word_t pmem_read(word_t addr) {
  //printf("addr = 0x%08x\n", addr);
  return mem[addr-MEM_BASE]+(mem[addr-MEM_BASE+1]<<8)+(mem[addr-MEM_BASE+2]<<16)+(mem[addr-MEM_BASE+3]<<24);
}

word_t paddr_read(word_t addr, int len) {
  switch (len) {
    case 1: return mem[addr-MEM_BASE];
    case 2: return mem[addr+-MEM_BASE]*16+mem[addr-MEM_BASE];
    case 4: return paddr_read(addr+2, 2)*256+paddr_read(addr, 2);
    case 8: return (paddr_read(addr+4, 4) << 32) + paddr_read(addr, 4);
    default: return 0;
  }
  return 0;
}

word_t vaddr_read(word_t addr, int len) {
  return paddr_read(addr, len);
}

char logbuf[128];
static void single_cycle() {
  if (npc_state != NPC_RUN) return;
  char *p = logbuf;
	contextp->timeInc(1);
  topp->clock = 0;
  //Log("dnpc in low = 0x%08x", topp->io_npc);
  topp->eval();
  //Log("dnpc in low2 = 0x%08x", topp->io_npc);
#ifdef VCD
  tfp->dump(contextp->time());
#endif
  contextp->timeInc(1);
  topp->io_inst = topp->reset ? 0 : pmem_read(topp->io_pc);
  topp->clock = 1;
  word_t pc = topp->io_pc, instval = topp->io_inst, npc;
  topp->eval();
  npc = topp->io_pc;
  if (topp->reset == 0) {
    //printf("[itrace] inst = 0x%08x\n", topp->io_inst);
    p += snprintf(p, sizeof(logbuf), "0x%08x :", pc);
    int ilen = 4;
    uint8_t *inst = (uint8_t *)&instval;
    for (int i = ilen - 1; i >= 0; i--) {
      p += snprintf(p, 4, " %02x", inst[i]);
    }
    iringbuf.cur = (iringbuf.cur + 1) % CONFIG_ITRACE_RINGBUFFER_SIZE;
    iringbuf.pc[iringbuf.cur] = pc;
    iringbuf.inst[iringbuf.cur] = instval;
    int space_len = 4 * 3 + 1;
    memset(p, ' ', space_len);
    p += space_len;
    // void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
    // disassemble(p, logbuf + sizeof(logbuf) - p, topp->io_pc, inst, ilen);
    if (ftrace_is_enable()) {
      word_t reg_val = Rread(1);
      ftrace(pc, npc, iringbuf.inst[iringbuf.cur], reg_val);
    }
  }
  
#ifdef VCD
  tfp->dump(contextp->time());
#endif
  //sleep(1);
}

extern "C" void ebreak() {
  //exit(0);
  npc_state = NPC_STOP;
  npc_ret = 0;
}


static bool resetted = false;
static void reset(int n) {  
  npc_state = NPC_RUN;
  topp->reset = 1;
  while (n-- > 0) {
    puts("Resetting");
    single_cycle();
  }
  for (int i = 0; i < 1; i++) {
    printf("sleep %ds\n", i);
    sleep(1);
  }
  topp->reset = 0;
  topp->eval();
}

static char *elf_file = NULL;
static char *img_file = NULL;
// difftest 的文件放在 sdb.c 里了，上面这两个之后也要移动过去


long load_img() {
	printf("img == %s\n", img_file);
	FILE *fp = fopen(img_file, "rb");
	assert(fp);
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	int ret = fread(mem, 1, size, fp);
	fclose(fp);
  assert(ret == size);
	return size;
}

void print_iringbuf() {
  for (int i = 1; i <= CONFIG_ITRACE_RINGBUFFER_SIZE; i++) {
    if (i == CONFIG_ITRACE_RINGBUFFER_SIZE) {
      int pos = (iringbuf.cur + i) % CONFIG_ITRACE_RINGBUFFER_SIZE;
      Log("     -->0x%08x : 0x%08x", iringbuf.pc[pos], iringbuf.inst[pos]);
    } else {
      int pos = (iringbuf.cur + i) % CONFIG_ITRACE_RINGBUFFER_SIZE;
      Log("\t0x%08x : 0x%08x", iringbuf.pc[pos], iringbuf.inst[pos]);
    }   
  }
}

void cpu_exec(uint32_t n) {
  if (!resetted) {
    resetted = true;
    reset(5);
  }
  while (n--) {
    if (npc_state != NPC_RUN) break;
    single_cycle();
  }
  switch (npc_state)
  {
  case NPC_STOP: case NPC_ABORT:
    Log("npc: %s at pc = 0x%08x", (npc_state == NPC_ABORT ? "abort":
    (npc_ret == 0 ? "HIT GOOD TRAP" : "HIT BAD TRAP")),
     topp->io_pc);
    print_iringbuf();
  case NPC_QUIT: 
    Log("QUIT!");
  default:
    break;
  }
} 



void npc_reg_display() {
  for (int i = 0; i < 32; i++) {
    printf("%s: %x\n", regs[i], Rread(i));
  }
}

int sim_main(int argc, char** argv) {
  
#ifdef VCD
  Verilated::mkdir("logs");
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  topp->trace(tfp, 99); // Trace 99 levels of hierarchy
  tfp->open("logs/wave.vcd");
#endif
	// nvboard_bind_all_pins(&top);
	// nvboard_init();
  
  img_file = argv[1];
  elf_file = (char *)malloc(strlen(img_file));
  memcpy(elf_file, img_file, strlen(img_file)-3);
  strcat(elf_file, "elf");
  init_monitor();
  Log("argv[1] = %s", argv[1]);
  Log("elf_file = %s", elf_file);
  if (ftrace_is_enable())
    init_ftrace(elf_file);

  printf("\033[0m\033[1;34mnpc将会先进行reset\033[0m\n");
  npc_ret = 1;
  
  sdb_mainloop();

  // while (npc_state == NPC_RUN) {
  // //  nvboard_update(); 
  //   single_cycle();  
  // }

  topp->final();
#ifdef VCD
  tfp->close();
  tfp = nullptr;
#endif
  // nvboard_quit();
  return npc_ret;
}
