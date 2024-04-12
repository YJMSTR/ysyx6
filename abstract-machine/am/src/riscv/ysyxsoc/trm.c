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
      memcpy(data_start, data_load_start, (size_t) data_size);
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

void putch(char ch) {
  outb(SERIAL_PORT, ch);
}

void halt(int code) {
  ysyxsoc_trap(code);
  while (1);
}

void _trm_init() {
  // copy_data();
  int ret = main(mainargs);
  halt(ret);
}