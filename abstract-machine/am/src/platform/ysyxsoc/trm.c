#include <am.h>
#include <klib-macros.h>
#include <klib.h>
#include <ysyxsoc.h>

extern char _heap_start;
extern char data_start [];
extern char data_size [];
extern char data_load_start [];

void copy_data(void)
{
  if (&data_start[0] != &data_load_start[0])
    {
      // memcpy(data_start, data_load_start, (size_t) data_size);

      unsigned char *srct = (unsigned char *)data_load_start;
      unsigned char *dstt = (unsigned char *)data_start;
      for (int i = 0; i < (size_t)data_size; i++) {
        dstt[i] = srct[i];
      }
    }
}
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (8 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
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
  copy_data();
  if(!ioe_init()) {
    halt(1);
  }
  printf("copy_data done\n");
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
  printf("mainargs= %s\n", mainargs);
  int ret = main(mainargs);
  halt(ret);
}
