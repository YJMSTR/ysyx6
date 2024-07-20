.section entry, "ax"
.globl _start
.type _start, @function
.globl _fsbl
.type _fsbl, @function

_start:
  mv s0, zero
  la sp, _stack_pointer
#  jal _trm_init
  jal _fsbl

