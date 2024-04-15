#include "VysyxSoCFull.h"
// #include "verilated_vcd_c.h"
// #include <nvboard.h>
#include <unistd.h>
#include "verilated.h"
#include "VysyxSoCFull__Dpi.h"
#include "svdpi.h"
#include "sim.h"
#include <ftrace.h>
#include "VysyxSoCFull___024root.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>
#include <typeinfo>
#include <debug.h>
#include <macro.h>
#include <dlfcn.h>
#include <sys/time.h>



#define MEM_BASE 0x80000000u
#define MEM_SIZE 0x8000000
#define DEVICE_BASE 0xa0000000

#define MMIO_BASE 0xa0000000

#define SERIAL_PORT     (DEVICE_BASE + 0x00003f8)
#define KBD_ADDR        (DEVICE_BASE + 0x0000060)
#define RTC_ADDR        (DEVICE_BASE + 0x0000048)
#define VGACTL_ADDR     (DEVICE_BASE + 0x0000100)
#define AUDIO_ADDR      (DEVICE_BASE + 0x0000200)
#define DISK_ADDR       (DEVICE_BASE + 0x0000300)
#define FB_ADDR         (MMIO_BASE   + 0x1000000)
#define AUDIO_SBUF_ADDR (MMIO_BASE   + 0x1200000)

#define MROM_BASE 0x20000000
#define MROM_SIZE 0x1000
#define FLASH_BASE 0x30000000
#define FLASH_SIZE 0x10000000

#define ysyxSoC

#ifndef CONFIG_ITRACE_RINGBUFFER_SIZE
  #define CONFIG_ITRACE_RINGBUFFER_SIZE 16
#endif


#ifdef VCD
  #include "verilated_vcd_c.h"
  VerilatedVcdC* tfp = nullptr;
#endif
VerilatedContext* contextp = new VerilatedContext;
VysyxSoCFull* topp = new VysyxSoCFull{contextp};
enum NPC_STATES npc_state;
word_t npc_halt_pc;
int npc_ret;
static unsigned long long cycles = 0;
bool difftest_is_enable = 0;
bool is_batch_mode = 0;
bool is_itrace = 1;
char logbuf[128];
static uint64_t boot_time = 0;
static uint64_t rtc_us = 0;
static uint64_t nz_pc = 0;
static uint64_t nz_npc = 0;

// void nvboard_bind_all_pins(VysyxSoCFull *top);
const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

word_t Rread(uint32_t idx) {
  return topp->rootp->ysyxSoCFull__DOT__asic__DOT__cpu__DOT__cpu__DOT__R_ext__DOT__Memory[idx];
}

struct Iringbuf 
{
  word_t pc[CONFIG_ITRACE_RINGBUFFER_SIZE];
  word_t inst[CONFIG_ITRACE_RINGBUFFER_SIZE];
  int cur;
} iringbuf;


typedef word_t paddr_t;
struct CPU_state {
  word_t gpr[32];
  //uint32_t gpr[32];
  vaddr_t pc;
} cpu;

enum { DIFFTEST_TO_DUT, DIFFTEST_TO_REF };

static uint8_t mrom[MROM_SIZE*10] = {
  0x93, 0x02, 0x00, 0x08, //addi	t0, zero, 128
  0xef, 0x00, 0xc0, 0x00, //jal ra, 80000010
  0x13, 0x03, 0x10, 0x08, //addi	t1, zero, 129
  0x13, 0x05, 0x10, 0x00, //li a0, 1
  0x13, 0x07, 0xb0, 0x00, //li a4, 11 
  0x13, 0x06, 0x10, 0x3a, //li a2, 929
  0x93, 0x05, 0x10, 0x3a, //li a1, 929
  0x73, 0x00, 0x10, 0x00  //ebreak
  // 如果改了这里，记得把默认的 img_size 也改了
}; 

static uint8_t flash[FLASH_SIZE] = {
  0x00, 0x01, 0x02, 0x03
};

static uint8_t mem[MEM_SIZE] = {
  0x93, 0x02, 0x00, 0x08, //addi	t0, zero, 128
  0xef, 0x00, 0xc0, 0x00, //jal ra, 80000010
  0x13, 0x03, 0x10, 0x08, //addi	t1, zero, 129
  0x13, 0x05, 0x10, 0x00, //li a0, 1
  0x13, 0x07, 0xb0, 0x00, //li a4, 11 
  0x13, 0x06, 0x10, 0x3a, //li a2, 929
  0x93, 0x05, 0x10, 0x3a, //li a1, 929
  0x73, 0x00, 0x10, 0x00  //ebreak
  // 如果改了这里，记得把默认的 img_size 也改了
}; 

void (*ref_difftest_memcpy)(paddr_t addr, void *buf, size_t n, bool direction) = NULL;
void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
void (*ref_difftest_exec)(uint64_t n) = NULL;
// void (*ref_difftest_raise_intr)(uint64_t NO) = NULL;

static bool is_skip_ref = false;
static int skip_dut_nr_inst = 0;

void difftest_skip_ref() {
  is_skip_ref = true;
  skip_dut_nr_inst = 0;
}

void difftest_skip_dut(int nr_ref, int nr_dut) {
  skip_dut_nr_inst += nr_dut;
  
  while (nr_ref -- > 0) {
    ref_difftest_exec(1);
  }
}

void init_difftest(char *ref_so_file, long img_size, int port) {
 
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

  // ref_difftest_raise_intr = dlsym(handle, "difftest_raise_intr");
  // assert(ref_difftest_raise_intr);
  
  void (*ref_difftest_init)(int) = (void (*)(int))dlsym(handle, "difftest_init");
  assert(ref_difftest_init);

  Log("Differential testing: %s", ANSI_FMT("ON", ANSI_FG_GREEN));
  Log("The result of every instruction will be compared with %s. "
      "This will help you a lot for debugging, but also significantly reduce the performance. "
      "If it is not necessary, you can turn it off in menuconfig(NPC doesn't have menuconfig now).", ref_so_file);
  ref_difftest_init(port);
  // ref_difftest_memcpy(MEM_BASE, mem, img_size, DIFFTEST_TO_REF);
  ref_difftest_memcpy(MROM_BASE, mrom, img_size, DIFFTEST_TO_REF);
  ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
}

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  assert(ref_r != NULL);
  // if (ref_r->pc != pc) {
  //   printf("difftest: reg #pc = %s err at dut pc: 0x%08x\n", ref_r->pc, pc);
  //   printf("difftest: ref_r->pc == 0x%08x\n", ref_r->pc);
  // }
  bool ret = true;
  for (int i = 0; i < 32; i++) {
    assert(typeid(ref_r->gpr[i]) == typeid(cpu.gpr[i]));
    if (ref_r->gpr[i] != cpu.gpr[i]) {
      printf("difftest: reg #%d = %s err at pc: 0x%016lx\n", i, regs[i], pc);
      printf("difftest: ref_r->gpr[%d] == 0x%016lx cpu.gpr[%d] == 0x%016lx\n", i, ref_r->gpr[i], i, cpu.gpr[i]);
      ret = false;
    }
  }
  if (!ret) {
    for (int i = 0; i < 32; i++) {
      printf("%s: ref = %lx cur = %lx\n", regs[i], ref_r->gpr[i], cpu.gpr[i]);
    }
  }
  return ret;
}

static void checkregs(CPU_state *ref, vaddr_t pc) {
  if (!isa_difftest_checkregs(ref, pc)) {
    npc_state = NPC_ABORT;
    npc_halt_pc = pc;
    npc_reg_display();
  }
}

void difftest_step(vaddr_t pc, vaddr_t npc) {
  CPU_state ref_r;
  if (skip_dut_nr_inst > 0) {
    ref_difftest_regcpy(&ref_r, DIFFTEST_TO_DUT);
    if (ref_r.pc == npc) {
      skip_dut_nr_inst = 0;
      checkregs(&ref_r, npc);
      return;
    }
    skip_dut_nr_inst --;
    if (skip_dut_nr_inst == 0)
      panic("can not catch up with ref.pc = " FMT_WORD " at pc = " FMT_WORD, ref_r.pc, pc);
    return;
  }

  if (is_skip_ref) {
    // to skip the checking of an instruction, just copy the reg state to reference design
    Log("skip ref pc=0x%08x, npc=0x%08x", pc, npc);
    ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
    is_skip_ref = false;
    return;
  }
  
  ref_difftest_exec(1);
  printf("ref pc = %08x done\n", pc);
  ref_difftest_regcpy(&ref_r, DIFFTEST_TO_DUT);
  checkregs(&ref_r, pc);
  
}

static void trace_and_difftest(vaddr_t pc, vaddr_t dnpc) {
  log_write("%s\n", logbuf);
  static vaddr_t last_pc = 0;
  
  if (difftest_is_enable && pc != last_pc) {  // 传入参数时已经保证非 0
    printf("difftest_step pc = %x dnpc = %x lastpc= %x\n", pc, dnpc, last_pc);
    difftest_step(pc, dnpc);
    last_pc = pc;
  }
}


// 接入 ysyxSoC 所需的代码
extern "C" void flash_read(int addr, int *data) {
  assert(addr >= 0 && addr < FLASH_SIZE);
  word_t res = 0;
  for (int i = 0; i < 4; i++) {
    res = res + ((word_t)flash[addr + i] << (i * 8));
  }
  *data = res;
}
extern "C" void mrom_read(int addr, long long *data) {
  // *data = 0x00100073;	//ebreak
  word_t res = 0;
  for (int i = 0; i < 8; i++) {
    res = res + ((word_t)mrom[addr-MROM_BASE+i] << (i*8));
  }
   
  *data = res;
  // Log("npc mrom read addr = %x res64 = %016lx\n res32 = %08x res16 = %08x res8 = %08x", addr, res, res & 0xFFFFFFFF, res & 0xFFFF, res & 0xFF);
  Assert(addr >= MROM_BASE && addr < MROM_BASE + MROM_SIZE, "addr = %x out of mrom", addr);
}

extern "C" void npc_pmem_read(int raddr, long long *rdata) {
  uint32_t addr = raddr;
  //addr = addr & ~0x3u;
  if (addr == RTC_ADDR + 4) {
    Log("DTRACE RTC_ADDR + 4");
    difftest_skip_ref();
    struct timeval now;
    gettimeofday(&now, NULL);
    if (boot_time == 0) {
      boot_time = now.tv_sec * 1000000 + now.tv_usec;
    }
    rtc_us = now.tv_sec * 1000000 + now.tv_usec - boot_time;
    *rdata = rtc_us >> 32ull;
    return;
  } else if (addr == RTC_ADDR) {
    Log("DTRACE RTC_ADDR");
    difftest_skip_ref();
    *rdata = (uint32_t)rtc_us;
    return;
  }
  if (!((word_t)raddr >= (word_t)MEM_BASE && ((word_t)(raddr - MEM_BASE + 7)) < (word_t)MEM_SIZE)) {
    printf("pmem_read: raddr = %lld = 0x%016llx raddr-MEM_BASE = %lld MEM_SIZE-addr+MEM_BASE-7=%ld\n", raddr, raddr, raddr-MEM_BASE, MEM_SIZE-addr+MEM_BASE-7);
    npc_reg_display();
  }
  assert((word_t)raddr >= (word_t)MEM_BASE && ((word_t)(raddr - MEM_BASE + 7)) < (word_t)MEM_SIZE);
  word_t res = 0;
  for (int i = 0; i < 8; i++) {
    res = res + ((word_t)mem[addr-MEM_BASE+i] << (i*8));
  }
  *rdata = res;
  //printf("pmem_read: *rdata = 0x%08x\n", *rdata);
}

extern "C" void npc_pmem_write(int waddr, long long wdata, char wmask) {
  //int addr = waddr & ~0x3u;
  uint32_t addr = waddr;
  //printf("pmem_write: waddr = 0x%08llx wdata = 0x%08llx wmask = 0x%x\n", waddr, wdata, 0xff & wmask);
  // if (addr == SERIAL_PORT) {
  //   difftest_skip_ref();
  //   //Log("dtrace: pc = 0x%08x serial wdata = %d, wmask = %d", topp->io_pc, wdata, wmask);
  //   if ((wmask & 0xff) == 1) {
  //     putchar(wdata);
  //   } else {
  //     Log("serial don't support wmask = 0x%x putch", wmask & 0xff);
  //   }
  //   return;
  // }
  assert((word_t)addr >= MEM_BASE && ((word_t)(addr - MEM_BASE + 7)) < MEM_SIZE);
  for (int i = 0; i < 8; i++) {
    if (wmask & (1 << i)) {
      mem[addr-MEM_BASE+i] = (wdata >> (i * 8)) & 0xff;
    }
  }
}

word_t npc_paddr_read(word_t addr, int len) {
  switch (len) {
    case 1: return mem[addr-MEM_BASE];
    case 2: return (mem[addr-MEM_BASE+1] << 8ull) + mem[addr-MEM_BASE];
    case 4: return (npc_paddr_read(addr+2, 2) << 16ull) + npc_paddr_read(addr, 2);
    case 8: return ((uint64_t)npc_paddr_read(addr+4, 4) << 32ull) + npc_paddr_read(addr, 4);
    default:
      Log("unsupport paddr read len, exit"); 
      return 0;
  }
  return 0;
}

word_t npc_vaddr_read(word_t addr, int len) {
  return npc_paddr_read(addr, len);
}


extern "C" void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);

static void single_cycle() {
  if (npc_state != NPC_RUN) return;
  char *p = logbuf;
  cycles ++;
	contextp->timeInc(1);
  topp->clock = 0;
  topp->eval();
#ifdef VCD
  tfp->dump(contextp->time());
#endif
  contextp->timeInc(1);
  topp->clock = 1;
  topp->eval();
  // #ifndef ysyxSoC
  word_t instval = topp->io_inst;
  word_t pc = topp->io_pc;
  word_t npc = topp->io_npc;
  
  //static word_t nz_pc = 0, nz_npc = 0;
  if (pc != 0) nz_pc = pc;
  if (npc != 0) nz_npc = npc;
  // #endif

#ifdef VCD
  tfp->dump(contextp->time());
#endif
// #ifndef ysyxSoC
  if (topp->reset == 0 && is_itrace) {
    //printf("[itrace] inst = 0x%08x\n", topp->io_inst);
    p += snprintf(p, sizeof(logbuf), "0x%08lx :", pc);
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
    disassemble(p, logbuf + sizeof(logbuf) - p, pc, inst, ilen);
    if (ftrace_is_enable()) {
      word_t reg_val = Rread(1);
      ftrace(pc, npc, iringbuf.inst[iringbuf.cur], reg_val);
    }
    for (int i = 0; i < 32; i++) {
      cpu.gpr[i] = Rread(i);
    }
    trace_and_difftest(nz_pc, nz_npc);
  }
  //sleep(1);
// #endif
}

extern "C" void ebreak() {
  //exit(0);
  npc_state = NPC_STOP;
  npc_ret = Rread(10);
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
  if (img_file == NULL) {
    Log("no image found, use default img");
    //记得改了 默认 img 之后，默认的 img size 也要改
    return 32;
  }
#ifndef ysyxSoC
  // load 到 sram 中
  memset(mem, 0, sizeof(mem));
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
#endif
#ifdef ysyxSoC
  // load 到 mrom 中
  memset(mrom, 0, sizeof(mrom));
  printf("mrom img == %s\n", img_file);
  FILE *fp = fopen(img_file, "rb");
	assert(fp);
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
  printf("mrom fp size = %d\n", size);
	fseek(fp, 0, SEEK_SET);
	int ret = fread(mrom, 1, size, fp);
  fclose(fp);
  assert(ret == size);
  return size;
#endif
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
    reset(2);
  }
  while (n--) {
    if (npc_state != NPC_RUN) break;
    #ifndef ysyxSoC
    cpu.pc = topp->io_pc;
    #endif
    single_cycle();
    if (npc_state != NPC_RUN) break;
  }
  switch (npc_state)
  {
  case NPC_STOP: case NPC_ABORT:
    Log("npc: %s at pc = 0x%08lx", (npc_state == NPC_ABORT ? "abort":
    (npc_ret == 0 ? ANSI_FMT("HIT GOOD TRAP", ANSI_FG_GREEN) : ANSI_FMT("HIT BAD TRAP", ANSI_FG_RED))),
     cpu.pc);
    Log("npc cycles = %llu\n", cycles);
    print_iringbuf();
    sleep(1);
  case NPC_QUIT: 
    Log("QUIT!");
    Log("npc cycles = %llu\n", cycles);
  default:
    break;
  }
} 



void npc_reg_display() {
  for (int i = 0; i < 32; i++) {
    printf("%s: %lx\n", regs[i], Rread(i));
  }
}

int sim_main(int argc, char** argv) {
  // begin：ysyxSoC 所需的代码
  Verilated::commandArgs(argc, argv);
  // end
#ifdef VCD
  //Verilated::mkdir("logs");
  Verilated::traceEverOn(true);
  tfp = new VerilatedVcdC;
  topp->trace(tfp, 99); // Trace 99 levels of hierarchy
  tfp->open("logs/wave.vcd");
#endif
	// nvboard_bind_all_pins(&top);
	// nvboard_init();
  if (argc > 1) {
    img_file = argv[1];
    if (ftrace_is_enable()) {
    elf_file = (char *)malloc(strlen(img_file)+1);
      memset(elf_file, '\0', sizeof(elf_file));
      memcpy(elf_file, img_file, strlen(img_file)-3);
      strcat(elf_file, "elf");
    }
  }
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