// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VTOP__DPI_H_
#define VERILATED_VTOP__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at build/DPIC_EBREAK.v:4:32
    extern void ebreak();
    // DPI import at build/DPIC_MEM.v:10:32
    extern void npc_pmem_read(int raddr, long long* rdata);
    // DPI import at build/DPIC_MEM.v:12:32
    extern void npc_pmem_write(int waddr, long long wdata, char wmask);

#ifdef __cplusplus
}
#endif

#endif  // guard
