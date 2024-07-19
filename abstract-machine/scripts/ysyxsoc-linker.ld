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
  .text_bootloader : {
    _text_bootloader_start = .;
    *(entry)
    *(.text_bootloader)
    _text_bootloader_end = .;
  } > boot_flash AT> boot_flash
  .text : {
    text_start = .;
    __text_and_rodata_start__ = .;
    *(.text*)
/*  } > flash AT> flash */ 
  } > sram AT> app_flash
  etext = .;
  _etext = .;
  .rodata : {
    *(.rodata*)
  } > sram AT> app_flash
  . = ALIGN(8);
   __text_and_rodata_end__ = .;
   __app_text_and_rodata_load_start__ = LOADADDR(.text);
  .data : {
    . = ALIGN(8);
    data_start = .;
    *(.data)
    . = ALIGN(8);
  } > psram AT> app_flash
  edata = .;
  _data = .;
  .bss : {
    . = ALIGN(8);
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > psram AT> app_flash
  . = ALIGN(8);
  data_end = .;
  data_load_start = LOADADDR(.data);
  sram_start = 0x0f000000;
  end = .;
  _end = .;
  /* _stack_top and _heap_start are defined in LD_FLAGS */
}
