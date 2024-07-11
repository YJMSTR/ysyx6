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

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
#ifdef CONFIG_ETRACE
  Log("[ETRACE] isa_raise_intr NO = "FMT_WORD" epc = "FMT_WORD"  ", NO, epc);
  // sleep(1);
#endif
  if (NO == 1) {
    cpu.csrs[CSR_MCAUSE] = 11; // ecall from M mode
    cpu.csrs[CSR_MEPC] = epc;

    #ifdef CONFIG_ETRACE
      Log("isa_raise_intr csr_mtvec: "FMT_WORD" csr_mepc: "FMT_WORD" ", cpu.csrs[CSR_MTVEC], cpu.csrs[CSR_MEPC]);
    #endif
    
    return cpu.csrs[CSR_MTVEC];
  } else {
    return 0;
  }
  return 0;
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
