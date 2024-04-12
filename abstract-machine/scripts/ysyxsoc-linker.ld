ENTRY(_start)
PHDRS { text PT_LOAD; data PT_LOAD; }
MEMORY {
  mrom(rx) : ORIGIN = 0x20000000, LENGTH = 4K
  sram(!rx) : ORIGIN = 0x0f000000, LENGTH = 8K
}
SECTIONS {
  . = ORIGIN(mrom);
  .text : {
    *(entry)
    *(.text*)
  } > mrom AT> mrom : text
  etext = .;
  _etext = .;
  .rodata : {
    *(.rodata*)
  }
  .data : {
    data_start = .;
    *(.data)
    data_end = .;
  } > sram AT> mrom : data
  data_size = data_end - data_start;
  data_load_start = LOADADDR(.data);
}