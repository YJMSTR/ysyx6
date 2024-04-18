ENTRY(_start)
/*
PHDRS {
  text PT_LOAD;
  data PT_LOAD;
}
*/
MEMORY {
/*  mrom(rx) : ORIGIN = 0x20000000, LENGTH = 4K */
  flash(rx): ORIGIN = 0x30000000, LENGTH = 0x10000000
  sram(wx) : ORIGIN = 0x0f000000, LENGTH = 8K
  
}
SECTIONS {
  . = ORIGIN(flash);
  .text : {
    *(entry)
    *(.text*)
  } > flash AT> flash
  etext = .;
  _etext = .;
  .rodata : {
    *(.rodata*)
  }
  .data : {
    . = ALIGN(8);
    data_start = .;
    *(.data)
    . = ALIGN(8);
  } > sram AT> flash
  edata = .;
  _data = .;
  .bss : {
    . = ALIGN(8);
    _bss_start = .;
    *(.bss*)
    *(.sbss*)
    *(.scommon)
  } > sram AT> flash
  . = ALIGN(8);
  data_end = .;
  data_size = data_end - data_start;
  data_load_start = LOADADDR(.data);
  end = .;
  _end = .;
}