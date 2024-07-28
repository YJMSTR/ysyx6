#include <klib.h>
#include <am.h>

extern char __sram_start__ [];
extern char __sram_size__ [];
extern char __boot_flash_start__ [];
extern char __boot_flash_size__ [];
extern char __text_bootloader_start__ [];
extern char __text_bootloader_end__ [];
extern char __text_bootloader_load_start__ [];
extern char __text_and_rodata_start__ [];
extern char __text_and_rodata_end__ [];
extern char __app_text_and_rodata_load_start__ [];
extern char data_start [];
extern char data_end [];
extern char data_load_start [];
// extern char data_extra_load_start [];
extern char _bss_start [];
extern char _bss_end [];
extern void _trm_init();

void __attribute__((section(".fsbl"))) _fsbl(void) {

  extern void _bootloader_start();
  unsigned char *src = (unsigned char*) __text_bootloader_load_start__;
  unsigned char *dst = (unsigned char*) __text_bootloader_start__;
  uint32_t size = __text_bootloader_end__ - __text_bootloader_start__;
  for (int i = 0; i < size; i++) dst[i] = src[i];
  _bootloader_start();
}

void __attribute__((section(".text_bootloader"))) copy_data(void) {
  unsigned char *src = (unsigned char*) __app_text_and_rodata_load_start__;
  unsigned char *dst = (unsigned char*) __text_and_rodata_start__;
  if (&__app_text_and_rodata_load_start__[0] != &__text_and_rodata_start__[0]) {
    uint32_t size =  __text_and_rodata_end__ - __text_and_rodata_start__;
    // memcpy(dst, src, size);
    for (int i = 0; i < size; i++) {
      dst[i] = src[i];
    }
  }

  if (&data_start[0] != &data_load_start[0]) {
    unsigned char *srct = (unsigned char *)data_load_start;
    unsigned char *dstt = (unsigned char *)data_start;
    uint32_t sizet = data_end - data_start;
    /*if (&data_extra_load_start[0] != &data_start[0]) {
      if (data_extra_load_start[0]) {
        srct = (unsigned char *)data_extra_load_start;
      }
    }*/
    for (int i = 0; i < sizet; i++) {
      dstt[i] = srct[i];
    }
  }
  unsigned char *bss = (unsigned char*) _bss_start;
  for (int i = 0; i < _bss_end - _bss_start; i++) {
    bss[i] = 0;
  }
}

void __attribute__((section(".text_bootloader"))) _bootloader_start(void) {
  copy_data();
  _trm_init();
}

