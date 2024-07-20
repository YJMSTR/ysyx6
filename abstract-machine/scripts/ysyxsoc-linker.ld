ENTRY(_start)
MEMORY {
/*  mrom(rx) : ORIGIN = 0x20000000, LENGTH = 4K */
  /* flash(rx): ORIGIN = 0x30000000, LENGTH = 0x10000000 */
  sram(rwx) : ORIGIN = 0x0f000000, LENGTH = 8K
  boot_flash(rx): ORIGIN = 0x30000000, LENGTH = 0x4000
  app_flash(rx): ORIGIN = 0x30004000, LENGTH = 0x0fffc000
  psram(rwx) : ORIGIN = 0x80000000, LENGTH = 4M
}

__boot_flash_start__ = ORIGIN(boot_flash);
__boot_flash_size__ = LENGTH(boot_flash);
__app_flash_start__ = ORIGIN(app_flash);
__sram_start__ = ORIGIN(sram);
__sram_size__ = LENGTH(sram);

SECTIONS {
  . = _pmem_start;
  . = ALIGN(8);
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
  . = ALIGN(8);
  __text_bootloader_load_start__ = LOADADDR(.text_bootloader);
  text_start = .;
  .text : {
    __text_and_rodata_start__ = .;
    *(.text)
/*  } > flash AT> flash */ 
  } > psram AT> app_flash
  . = ALIGN(8);
  etext = .;
  _etext = .;
  .rodata : {
    *(.rodata*)
    *(.srodata*)
  } > psram AT> app_flash
  . = ALIGN(8);
   __text_and_rodata_end__ = .;
   __app_text_and_rodata_load_start__ = LOADADDR(.text);
  . = ALIGN(8);
  data_start = .;
  . = .;
  .data : {
    *(.data)
  } > psram AT> app_flash
  . = ALIGN(8);
  edata = .;
  _data = .;
  . = ALIGN(8);
  _bss_start = .;
  .bss : {
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > psram AT> app_flash
  . = ALIGN(8);
  data_end = .;
  data_load_start = LOADADDR(.data);
  end = .;
  _end = .;
  /* _stack_top and _heap_start are defined in LD_FLAGS */
}
