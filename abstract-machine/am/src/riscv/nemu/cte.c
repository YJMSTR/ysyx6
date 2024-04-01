#include <am.h>
#include <riscv/riscv.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  if (user_handler) {
    Event ev = {0};
    switch (c->mcause) {
      case 0xb: ev.event = EVENT_YIELD; break;
      default: ev.event = EVENT_ERROR; break;
    }

    c = user_handler(ev, c);
    assert(c->mepc);
    // printf("irq c->mepc == %x c->mcause=%x\n", c->mepc, c->mcause);
    
  }
  assert(user_handler != NULL);
  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  /*
  其中kstack是栈的范围, entry是内核线程的入口, arg则是内核线程的参数. 
  此外, kcontext()要求内核线程不能从entry返回, 否则其行为是未定义的. 
  你需要在kstack的底部创建一个以entry为入口的上下文结构(目前你可以先忽略arg参数), 
  然后返回这一结构的指针.

  什么叫 内核线程的入口？
  看 yield-os 的代码，其给 kcontext 传递的 entry 参数是一个函数，那么入口就是这个函数对应的地址，设为 mepc

  kstack.end 是栈底，start 是栈顶，ctx 指向的地址是栈顶，栈中只有上下文
  */
  Context *ctx = (Context *)((uintptr_t)kstack.end - sizeof(Context));
  assert((uintptr_t)ctx + sizeof(Context) == (uintptr_t)kstack.end);
  ctx->mepc = (uintptr_t)entry;
  // 恢复上下文的通用寄存器时候并不会恢复 sp 寄存器，sp 寄存器是在出栈后手动 addi 加回去的 
  // 在 trap.S 中，通过 mv sp, a0 把 ctx 指向的地址作为栈顶。ctx 存在 a0 寄存器里
  ctx->mstatus = 0xa00001800;
  ctx->mcause = 0xb;
  return ctx;
}

void yield() {
#ifdef __riscv_e
  asm volatile("li a5, -1; ecall");
#else
  asm volatile("li a7, -1; ecall");
#endif
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
