#include <klib.h>
#include <am.h>

extern char __sram_start__ [];
extern char __sram_size__ [];
extern char __boot_flash_start__ [];
extern char __boot_flash_size__ [];
extern char __text_and_rodata_start__ [];
extern char __text_and_rodata_end__ [];
extern char __app_text_and_rodata_load_start__ [];
extern char data_start [];
extern char data_end [];
extern char data_load_start [];
extern void _trm_init();


void __attribute__((section(".text_bootloader"))) copy_data(void) {
  unsigned char *src = (unsigned char*) __app_text_and_rodata_load_start__;
  unsigned char *dst = (unsigned char*) __sram_start__;
  uint32_t size =  __text_and_rodata_end__ - __text_and_rodata_start__;
  // memcpy(dst, src, size);
  for (int i = 0; i < size; i++) {
    dst[i] = src[i];
  }

  if (&data_start[0] != &data_load_start[0]) {
    unsigned char *srct = (unsigned char *)data_load_start;
    unsigned char *dstt = (unsigned char *)data_start;
    //  memcpy(dstt, srct, data_end - data_start);
    for (int i = 0; i < data_end - data_start; i++) {
      dstt[i] = srct[i];
    }
  }
}

void __attribute__((section(".text_bootloader"))) _bootloader_start(void) {
  copy_data();
  _trm_init();
}

