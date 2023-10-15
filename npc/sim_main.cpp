#include "VTOP.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char** argv) {
  VerilatedContext* contextp = new VerilatedContext;
  Verilated::traceEverOn(true);
  contextp->commandArgs(argc, argv);
  VTOP* top = new VTOP{contextp};
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace(tfp, 99); // Trace 99 levels of hierarchy
  tfp->open("obj_dir/wave.vcd");
	int sim_time = 25;
  top->reset = 1;
  while (contextp->time() < sim_time && !contextp->gotFinish()) {
    int a = rand() & 1;
    int b = rand() & 1;
    top->io_a = a;
    top->io_b = b;
    contextp->timeInc(1);
    top->clock ^= 1;
    top->eval();
    tfp->dump(contextp->time());
    printf("a = %d b = %d f = %d\n", a, b, top->io_f);
    top->reset = 0;
    assert(top->io_f == (a ^ b));
  }
  tfp->close();
  delete top;
  delete contextp;
  return 0;
}
