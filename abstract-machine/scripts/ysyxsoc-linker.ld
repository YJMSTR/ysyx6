ENTRY(_start)
MEMORY {
/*  mrom(rx) : ORIGIN = 0x20000000, LENGTH = 4K */
  /* flash(rx): ORIGIN = 0x30000000, LENGTH = 0x10000000 */
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
  boot_flash(rx): ORIGIN = 0x30000000, LENGTH = 0x4000
  app_flash(rx): ORIGIN = 0x30004000, LENGTH = 0x0fffc000
  psram(rwx) : ORIGIN = 0x80000000, LENGTH = 4M
  sdram(rwx) : ORIGIN = 0xa0000000, LENGTH = 32M /*0x02000000*/
}

__boot_flash_start__ = ORIGIN(boot_flash);
__boot_flash_size__ = LENGTH(boot_flash);
__app_flash_start__ = ORIGIN(app_flash);
__sram_start__ = ORIGIN(sram);
__sram_size__ = LENGTH(sram);

SECTIONS {
  . = _pmem_start;
  __fsbl_start__ = .;
  .fsbl : {
    *(entry)
    *(.fsbl)
  } > boot_flash AT> boot_flash 
  __fsbl_end__ = .;
  .text_bootloader : {
    __text_bootloader_start__ = .; /*ssbl*/
    *(.text_bootloader)
    __text_bootloader_end__ = .;
  } > sram AT> boot_flash
  __text_bootloader_load_start__ = LOADADDR(.text_bootloader);
  .text : ALIGN(4) {
    text_start = .;
    __text_and_rodata_start__ = .;
    *(.text*)
/*  } > flash AT> flash */ 
  } > sdram AT> app_flash
  etext = .;
  _etext = .;
  .rodata : ALIGN(4) {
    *(.rodata*)
    . = ALIGN(4);
    *(.srodata*)
    . = ALIGN(4);
    __text_and_rodata_end__ = .;
  } > sdram AT> app_flash
   __app_text_and_rodata_load_start__ = LOADADDR(.text);
  /*. = .;*/

  data_start = .;
  .data : ALIGN(8) {
    *(.data*)
    . = ALIGN(8);
    *(.sdata*)
    . = ALIGN(8);
  } > sdram AT> app_flash
  edata = .;
  _data = .;
  .bss : {
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    _bss_end = .;
    *(.scommon)
  } > sdram AT> app_flash
  data_end = .;
  data_load_start = LOADADDR(.data);
  /*data_extra_load_start = LOADADDR(.data.extra);*/
  end = .;
  _end = .;
  /* _stack_top and _heap_start are defined in LD_FLAGS */
}
