#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <ysyxsoc.h>

extern char _heap_start;
extern unsigned int _heap_size;

int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (8 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)
// warning: 0x300000 is current heap size 
#define HEAP_SIZE 0xe00000
#define HEAP_END  ((uintptr_t)&_heap_start + HEAP_SIZE)
Area heap = RANGE(&_heap_start, HEAP_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

#define ysyxsoc_trap(_code) asm volatile("mv a0, %0; ebreak" : :"r"(_code))
static bool serial_initted = 0;

void uart_16550_init() {
  // outb(UART_16550_IER, 0);
  outb(UART_16550_FCR, 0xc7u);
  outb(UART_16550_LCR, 0x83u);
  outb(SERIAL_PORT + 1, 1);
  outb(SERIAL_PORT    , 1);
  outb(UART_16550_LCR, 0b00000011);
}

void putch(char ch) {
  if (!serial_initted) {
    uart_16550_init();
    serial_initted = 1;
  }
  while ((inb(UART_16550_LSR) & 0b1000000) == 0) {
    outb(UART_16550_FCR, inb(UART_16550_FCR) | 0b110);
  }
  outb(SERIAL_PORT, ch);
}

void halt(int code) {
  ysyxsoc_trap(code);
  while (1);
}

void _trm_init() {
  if(!ioe_init()) {
    halt(1);
  }
  unsigned long long ysyx, ysyx_no;
  asm volatile(
      "csrr %[dest1], mvendorid;\
       csrr %[dest2], marchid;"
      :[dest1]"=r"(ysyx),[dest2]"=r"(ysyx_no)
  );
  for (int i = 7; i >= 0; i--) {
    putch((ysyx>>(i*8ll))&0xff);
  }
  printf("%d\n", (int)ysyx_no);
  printf("mainargs=%s\n", mainargs);
  printf("pmem start = %x\n", &_pmem_start);
  printf("heap [%x, %x], addr of _heap_start = %x %x\n", heap.start, heap.end, _heap_start, &_heap_start);
  int ret = main(mainargs);
  halt(ret);
}
