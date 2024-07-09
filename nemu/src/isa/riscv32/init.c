/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <memory/paddr.h>

// this is not consistent with uint8_t
// but it is ok since we do not access the array directly
static const uint32_t img [] = {
  // 0x00000297,  // auipc t0,0
  // 0x00028823,  // sb  zero,16(t0)
  // 0x0102c503,  // lbu a0,16(t0)
  // 0x00100073,  // ebreak (used as nemu_trap)
  // 0xdeadbeef,  // some data
  0x08000293, //addi	t0, zero, 128
  0x00c000ef, //jal ra, 80000010
  0x08100313, //addi	t1, zero, 129
  0x00100513, //li a0, 1
  0x00b00713, //li a4, 11 
  0x3a100613, //li a2, 929
  0x3a100593, //li a1, 929
  0x00100073  //ebreak
};

static void restart() {
  /* Set the initial program counter. */
  #ifdef CONFIG_HAS_MROM
  cpu.pc = CONFIG_MROM_BASE;
  #elif CONFIG_HAS_FLASH
  cpu.pc = CONFIG_FLASH_BASE;
  #else
  cpu.pc = RESET_VECTOR;
  Log("nemu pc = %lx", cpu.pc);
  #endif

  /* The zero register is always 0. */
  cpu.gpr[0] = 0;
  cpu.csrs[0x300] = 0xa00001800;
}

void init_isa() {
  /* Load built-in image. */
  memcpy(guest_to_host(RESET_VECTOR), img, sizeof(img));

  /* Initialize this virtual computer system. */
  restart();
}
