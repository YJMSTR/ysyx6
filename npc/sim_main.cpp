#include "VTop.h"
// #include "verilated_vcd_c.h"
#include <nvboard.h>
#include <unistd.h>
static TOP_NAME top;

void nvboard_bind_all_pins(VTop *top);

static void single_cycle() {
	top.clock = 0; top.eval();
  //sleep(1);
  top.clock = 1; top.eval();
}

static void reset(int n) {
  top.reset = 1;
  while (n-- > 0) single_cycle();
  top.reset = 0;
}

int main(int argc, char** argv) {
  
  // Verilated::traceEverOn(true);
  // VerilatedVcdC* tfp = new VerilatedVcdC;
  // top.trace(tfp, 99); // Trace 99 levels of hierarchy
  // tfp->open("obj_dir/wave.vcd");

	nvboard_bind_all_pins(&top);
	nvboard_init();

	reset(5);

  while (1) {
    nvboard_update();
    single_cycle();  
  }
  
  nvboard_quit();
  return 0;
}
