#include "VTop.h"
// #include "verilated_vcd_c.h"
// #include <nvboard.h>
#include <unistd.h>
#include "VTop__Dpi.h"
#include "svdpi.h"
#include <string.h>
#define MEM_BASE 0x80000000
#define MEM_SIZE 0x8000000

static TOP_NAME top;

// void nvboard_bind_all_pins(VTop *top);
// addi t0, $0, 128
//     0x5, 0x0, 0x80
// 0000100 00000  00000 000 00101 00100 11
// 0x08000293
// addi t1, %0, 129
// 000010000001 00000 000 00110 00100 11
// 0x08 10 03 13
// ebreak
// 00 10 00 73 
static uint8_t mem[MEM_SIZE] = {
  0x93, 0x02, 0x00, 0x08, 
  0x13, 0x03, 0x10, 0x08,
  0x73, 0x00, 0x10, 0x00
}; 

uint32_t pmem_read(uint32_t pc) {
  printf("pc = 0x%08x\n", pc);
  return mem[pc-MEM_BASE]+(mem[pc-MEM_BASE+1]<<8)+(mem[pc-MEM_BASE+2]<<16)+(mem[pc-MEM_BASE+3]<<24);
}

static void single_cycle() {
	top.clock = 0;
  top.eval();
  top.clock = 1;
  top.io_inst = top.reset ? 0 : pmem_read(top.io_pc);
  top.eval();
  printf("t0 = %d, t1 = %d\n", top.io_t0, top.io_t1);
  //sleep(1);
}

extern "C" void ebreak() {
  exit(0);
}

static void reset(int n) {
  top.reset = 1;
  while (n-- > 0) {
    puts("Resetting");
    single_cycle();
  }
  for (int i = 0; i < 3; i++) {
    printf("sleep %ds\n", i);
    sleep(1);
  }
  top.reset = 0;
}

char *img_file;

static long load_img() {
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

int main(int argc, char** argv) {
  
  // Verilated::traceEverOn(true);
  // VerilatedVcdC* tfp = new VerilatedVcdC;
  // top.trace(tfp, 99); // Trace 99 levels of hierarchy
  // tfp->open("obj_dir/wave.vcd");

	// nvboard_bind_all_pins(&top);
	// nvboard_init();
  img_file = argv[1];
  printf("argv[1] = %s\n", argv[1]);
  long img_size = load_img();
	for (long i = 0; i < img_size; i += 4) {
		for (long j = i; j < i + 4; j++) {
			printf("%02x ", mem[j]);
		}
		printf("\n");
	}
	reset(5);

  while (1) {
  //  nvboard_update(); 
    single_cycle();  
  }
  
  // nvboard_quit();
  return 0;
}
