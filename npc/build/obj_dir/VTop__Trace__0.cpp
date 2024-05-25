// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VTop__Syms.h"


void VTop___024root__trace_chg_sub_0(VTop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void VTop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_chg_top_0\n"); );
    // Init
    VTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VTop___024root*>(voidSelf);
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    VTop___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void VTop___024root__trace_chg_sub_0(VTop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgBit(oldp+0,(vlSelf->Top__DOT__pcsel));
        bufp->chgQData(oldp+1,(((IData)(vlSelf->Top__DOT__stall)
                                 ? 0x114514ULL : ((0x67U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1))
                                                   ? 
                                                  (vlSelf->Top__DOT__rs1v 
                                                   + vlSelf->Top__DOT__Decoder__DOT__casez_tmp)
                                                   : 
                                                  (((0x6fU 
                                                     == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
                                                    | ((0x63U 
                                                        == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                       | ((0xe3U 
                                                           == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                          | ((0x2e3U 
                                                              == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                             | ((0x3e3U 
                                                                 == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                                | ((0x263U 
                                                                    == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                                   | (0x363U 
                                                                      == (IData)(vlSelf->Top__DOT___GEN_1))))))))
                                                    ? 
                                                   (((IData)(vlSelf->Top__DOT__IDReg_valid)
                                                      ? vlSelf->Top__DOT__IDReg_pc
                                                      : 0ULL) 
                                                    + vlSelf->Top__DOT__Decoder__DOT__casez_tmp)
                                                    : 
                                                   ((0x30200073U 
                                                     == vlSelf->Top__DOT___GEN_0)
                                                     ? vlSelf->Top__DOT__mepc
                                                     : 
                                                    ((0x73U 
                                                      == vlSelf->Top__DOT___GEN_0)
                                                      ? vlSelf->Top__DOT__mtvec
                                                      : 0ULL)))))),64);
        bufp->chgBit(oldp+3,(vlSelf->Top__DOT__IDRegen));
        bufp->chgQData(oldp+4,(((4U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                 ? ((2U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                     ? vlSelf->Top__DOT__WBReg_rdata
                                     : ((1U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                         ? (((QData)((IData)(
                                                             (- (IData)(
                                                                        (1U 
                                                                         & (IData)(
                                                                                (vlSelf->Top__DOT__WBReg_rdata 
                                                                                >> 0x1fU))))))) 
                                             << 0x20U) 
                                            | (QData)((IData)(vlSelf->Top__DOT__WBReg_rdata)))
                                         : (((- (QData)((IData)(
                                                                (1U 
                                                                 & (IData)(
                                                                           (vlSelf->Top__DOT__WBReg_rdata 
                                                                            >> 0xfU)))))) 
                                             << 0x10U) 
                                            | (QData)((IData)(
                                                              (0xffffU 
                                                               & (IData)(vlSelf->Top__DOT__WBReg_rdata)))))))
                                 : ((2U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                     ? ((1U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                         ? (((- (QData)((IData)(
                                                                (1U 
                                                                 & (IData)(
                                                                           (vlSelf->Top__DOT__WBReg_rdata 
                                                                            >> 7U)))))) 
                                             << 8U) 
                                            | (QData)((IData)(
                                                              (0xffU 
                                                               & (IData)(vlSelf->Top__DOT__WBReg_rdata)))))
                                         : (QData)((IData)(vlSelf->Top__DOT__WBReg_rdata)))
                                     : ((1U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                         ? (QData)((IData)(
                                                           (0xffffU 
                                                            & (IData)(vlSelf->Top__DOT__WBReg_rdata))))
                                         : (QData)((IData)(
                                                           (0xffU 
                                                            & (IData)(vlSelf->Top__DOT__WBReg_rdata)))))))),64);
        bufp->chgBit(oldp+6,(vlSelf->Top__DOT__IDReg_valid));
        bufp->chgIData(oldp+7,(vlSelf->Top__DOT__IDReg_inst),32);
        bufp->chgQData(oldp+8,(vlSelf->Top__DOT__IDReg_pc),64);
        bufp->chgBit(oldp+10,(vlSelf->Top__DOT__EXReg_valid));
        bufp->chgIData(oldp+11,(vlSelf->Top__DOT__EXReg_inst),32);
        bufp->chgQData(oldp+12,(vlSelf->Top__DOT__EXReg_pc),64);
        bufp->chgQData(oldp+14,(vlSelf->Top__DOT__EXReg_rs1v),64);
        bufp->chgQData(oldp+16,(vlSelf->Top__DOT__EXReg_rs2v),64);
        bufp->chgSData(oldp+18,(vlSelf->Top__DOT__EXReg_csridx),12);
        bufp->chgQData(oldp+19,(vlSelf->Top__DOT__EXReg_csrrv),64);
        bufp->chgQData(oldp+21,(vlSelf->Top__DOT__EXReg_csrwv),64);
        bufp->chgBit(oldp+23,(vlSelf->Top__DOT__EXReg_csr_en));
        bufp->chgQData(oldp+24,(vlSelf->Top__DOT__EXReg_imm),64);
        bufp->chgCData(oldp+26,(vlSelf->Top__DOT__EXReg_dataAsel),3);
        bufp->chgCData(oldp+27,(vlSelf->Top__DOT__EXReg_dataBsel),3);
        bufp->chgCData(oldp+28,(vlSelf->Top__DOT__EXReg_aluop),5);
        bufp->chgBit(oldp+29,(vlSelf->Top__DOT__EXReg_memvalid));
        bufp->chgBit(oldp+30,(vlSelf->Top__DOT__EXReg_memwen));
        bufp->chgCData(oldp+31,(vlSelf->Top__DOT__EXReg_memwmask),8);
        bufp->chgCData(oldp+32,(vlSelf->Top__DOT__EXReg_memsext),3);
        bufp->chgBit(oldp+33,(vlSelf->Top__DOT__EXReg_isEbreak));
        bufp->chgBit(oldp+34,(vlSelf->Top__DOT__EXReg_isword));
        bufp->chgBit(oldp+35,(vlSelf->Top__DOT__EXReg_rden));
        bufp->chgCData(oldp+36,(vlSelf->Top__DOT__EXReg_rd),5);
        bufp->chgBit(oldp+37,(vlSelf->Top__DOT__LSReg_valid));
        bufp->chgIData(oldp+38,(vlSelf->Top__DOT__LSReg_inst),32);
        bufp->chgQData(oldp+39,(vlSelf->Top__DOT__LSReg_pc),64);
        bufp->chgQData(oldp+41,(vlSelf->Top__DOT__LSReg_alures),64);
        bufp->chgQData(oldp+43,(vlSelf->Top__DOT__LSReg_rs2v),64);
        bufp->chgSData(oldp+45,(vlSelf->Top__DOT__LSReg_csridx),12);
        bufp->chgQData(oldp+46,(vlSelf->Top__DOT__LSReg_csrwv),64);
        bufp->chgBit(oldp+48,(vlSelf->Top__DOT__LSReg_csr_en));
        bufp->chgBit(oldp+49,(vlSelf->Top__DOT__LSReg_memvalid));
        bufp->chgBit(oldp+50,(vlSelf->Top__DOT__LSReg_memwen));
        bufp->chgCData(oldp+51,(vlSelf->Top__DOT__LSReg_memwmask),8);
        bufp->chgCData(oldp+52,(vlSelf->Top__DOT__LSReg_memsext),3);
        bufp->chgBit(oldp+53,(vlSelf->Top__DOT__LSReg_rden));
        bufp->chgCData(oldp+54,(vlSelf->Top__DOT__LSReg_rd),5);
        bufp->chgBit(oldp+55,(vlSelf->Top__DOT__WBReg_valid));
        bufp->chgIData(oldp+56,(vlSelf->Top__DOT__WBReg_inst),32);
        bufp->chgQData(oldp+57,(vlSelf->Top__DOT__WBReg_pc),64);
        bufp->chgQData(oldp+59,(vlSelf->Top__DOT__WBReg_alures),64);
        bufp->chgSData(oldp+61,(vlSelf->Top__DOT__WBReg_csridx),12);
        bufp->chgQData(oldp+62,(vlSelf->Top__DOT__WBReg_csrwv),64);
        bufp->chgBit(oldp+64,(vlSelf->Top__DOT__WBReg_csr_en));
        bufp->chgBit(oldp+65,(vlSelf->Top__DOT__WBReg_rden));
        bufp->chgCData(oldp+66,(vlSelf->Top__DOT__WBReg_rd),5);
        bufp->chgBit(oldp+67,(vlSelf->Top__DOT__WBReg_memvalid));
        bufp->chgCData(oldp+68,(vlSelf->Top__DOT__WBReg_memsext),3);
        bufp->chgQData(oldp+69,(vlSelf->Top__DOT__WBReg_rdata),64);
        bufp->chgBit(oldp+71,(vlSelf->Top__DOT__ISReg_valid));
        bufp->chgIData(oldp+72,(vlSelf->Top__DOT__ISReg_inst),32);
        bufp->chgQData(oldp+73,(vlSelf->Top__DOT__ISReg_pc),64);
        bufp->chgQData(oldp+75,(vlSelf->Top__DOT__mstatus),64);
        bufp->chgQData(oldp+77,(vlSelf->Top__DOT__mtvec),64);
        bufp->chgQData(oldp+79,(vlSelf->Top__DOT__mepc),64);
        bufp->chgQData(oldp+81,(vlSelf->Top__DOT__mcause),64);
        bufp->chgQData(oldp+83,(vlSelf->Top__DOT__rs2v),64);
        bufp->chgQData(oldp+85,(vlSelf->Top__DOT__rs1v),64);
        bufp->chgSData(oldp+87,(vlSelf->Top__DOT__csridx),12);
        bufp->chgBit(oldp+88,(vlSelf->Top__DOT__stall));
        bufp->chgIData(oldp+89,(((IData)(vlSelf->Top__DOT__EXReg_valid)
                                  ? vlSelf->Top__DOT__EXReg_inst
                                  : 0U)),32);
        bufp->chgQData(oldp+90,(vlSelf->Top__DOT____Vcellinp__ALU__io_rs1v),64);
        bufp->chgQData(oldp+92,(vlSelf->Top__DOT____Vcellinp__ALU__io_rs2v),64);
        bufp->chgQData(oldp+94,(vlSelf->Top__DOT____Vcellinp__ALU__io_csrrv),64);
        bufp->chgQData(oldp+96,(vlSelf->Top__DOT____Vcellinp__ALU__io_pc),64);
        bufp->chgCData(oldp+98,(vlSelf->Top__DOT____Vcellinp__ALU__io_asel),3);
        bufp->chgCData(oldp+99,(vlSelf->Top__DOT____Vcellinp__ALU__io_bsel),3);
        bufp->chgCData(oldp+100,(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op),5);
        bufp->chgQData(oldp+101,(vlSelf->Top__DOT____Vcellinp__ALU__io_imm),64);
        bufp->chgBit(oldp+103,(((IData)(vlSelf->Top__DOT__EXReg_isword) 
                                & (IData)(vlSelf->Top__DOT__EXReg_valid))));
        bufp->chgQData(oldp+104,((((IData)(vlSelf->Top__DOT__EXReg_isword) 
                                   & (IData)(vlSelf->Top__DOT__EXReg_valid))
                                   ? (((QData)((IData)(
                                                       (- (IData)(
                                                                  (1U 
                                                                   & (IData)(
                                                                             (vlSelf->Top__DOT__ALU__DOT__casez_tmp_1 
                                                                              >> 0x1fU))))))) 
                                       << 0x20U) | (QData)((IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_1)))
                                   : vlSelf->Top__DOT__ALU__DOT__casez_tmp_1)),64);
        bufp->chgQData(oldp+106,(vlSelf->Top__DOT__ALU__DOT__casez_tmp),64);
        bufp->chgQData(oldp+108,(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0),64);
        bufp->chgQData(oldp+110,(vlSelf->Top__DOT__ALU__DOT__casez_tmp_1),64);
        bufp->chgIData(oldp+112,((IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__axi_reg_readAddr)),32);
        bufp->chgBit(oldp+113,((3U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state))));
        bufp->chgBit(oldp+114,((4U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state))));
        bufp->chgBit(oldp+115,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__reqr_reg));
        bufp->chgIData(oldp+116,((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_readAddr)),32);
        bufp->chgBit(oldp+117,((4U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
        bufp->chgBit(oldp+118,((5U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
        bufp->chgIData(oldp+119,((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeAddr)),32);
        bufp->chgBit(oldp+120,((6U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
        bufp->chgQData(oldp+121,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeData),64);
        bufp->chgCData(oldp+123,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_wstrb),8);
        bufp->chgBit(oldp+124,((7U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
        bufp->chgBit(oldp+125,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__reqr_reg));
        bufp->chgBit(oldp+126,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__reqw_reg));
        bufp->chgBit(oldp+127,(vlSelf->Top__DOT___XBar2_io_axi4in_arready));
        bufp->chgQData(oldp+128,(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_2),64);
        bufp->chgCData(oldp+130,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                   ? (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0)
                                   : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                       ? 0U : ((2U 
                                                == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                ? 0U
                                                : (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0))))),2);
        bufp->chgBit(oldp+131,(vlSelf->Top__DOT__XBar2__DOT___io_axi4in_rvalid_output));
        bufp->chgBit(oldp+132,((1U & ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                       ? (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_21)
                                       : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                           ? (IData)(vlSelf->Top__DOT___SRAM_io_axi4_awready)
                                           : ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                               ? ((~ (IData)(
                                                             (0U 
                                                              != (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state)))) 
                                                  | (1U 
                                                     == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state)))
                                               : (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_21)))))));
        bufp->chgBit(oldp+133,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                 ? (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_22)
                                 : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                     ? (1U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))
                                     : ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                         ? (1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))
                                         : (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_22))))));
        bufp->chgCData(oldp+134,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                   ? ((1U & ((~ (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid)) 
                                             | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_13)))
                                       ? 0U : 3U) : 0U)),2);
        bufp->chgBit(oldp+135,(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_7));
        bufp->chgBit(oldp+136,(((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h4ab110e3__0) 
                                & (IData)(vlSelf->Top__DOT___XBar2_io_axi4in_arready))));
        bufp->chgQData(oldp+137,(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_0),64);
        bufp->chgCData(oldp+139,(((0U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
                                   ? 0U : ((1U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
                                            ? ((0U 
                                                == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                ? (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0)
                                                : (
                                                   (1U 
                                                    == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                    ? 0U
                                                    : 
                                                   ((2U 
                                                     == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                     ? 0U
                                                     : (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0))))
                                            : 0U))),2);
        bufp->chgBit(oldp+140,(vlSelf->Top__DOT___AXI4Arbiter_io_ifu_bus_axi4_rvalid));
        bufp->chgBit(oldp+141,(vlSelf->Top__DOT__AXI4Arbiter__DOT__ifu_ac));
        bufp->chgBit(oldp+142,(((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0) 
                                & (IData)(vlSelf->Top__DOT___XBar2_io_axi4in_arready))));
        bufp->chgQData(oldp+143,(vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_rdata),64);
        bufp->chgCData(oldp+145,(((1U & ((~ (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2)) 
                                         | (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_3)))
                                   ? 0U : ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                            ? (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0)
                                            : ((1U 
                                                == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                ? 0U
                                                : (
                                                   (2U 
                                                    == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                    ? 0U
                                                    : (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0)))))),2);
        bufp->chgBit(oldp+146,(vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_rvalid));
        bufp->chgBit(oldp+147,(((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0) 
                                & ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                    ? (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_21)
                                    : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                        ? (IData)(vlSelf->Top__DOT___SRAM_io_axi4_awready)
                                        : ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                            ? ((~ (IData)(
                                                          (0U 
                                                           != (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state)))) 
                                               | (1U 
                                                  == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state)))
                                            : (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_21)))))));
        bufp->chgBit(oldp+148,(((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0) 
                                & ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                    ? (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_22)
                                    : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                        ? (1U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))
                                        : ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                            ? (1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))
                                            : (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_22)))))));
        bufp->chgCData(oldp+149,(((1U & ((~ (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2)) 
                                         | (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_3)))
                                   ? 0U : ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                            ? ((1U 
                                                & ((~ (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid)) 
                                                   | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_13)))
                                                ? 0U
                                                : 3U)
                                            : 0U))),2);
        bufp->chgBit(oldp+150,(vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_bvalid));
        bufp->chgBit(oldp+151,(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac));
        bufp->chgIData(oldp+152,(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1),32);
        bufp->chgBit(oldp+153,(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_arvalid));
        bufp->chgBit(oldp+154,(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready));
        bufp->chgIData(oldp+155,(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2),32);
        bufp->chgBit(oldp+156,(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid));
        bufp->chgQData(oldp+157,(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3),64);
        bufp->chgCData(oldp+159,(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_4),8);
        bufp->chgBit(oldp+160,(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready));
        bufp->chgBit(oldp+161,(((0U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
                                 ? (((~ (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__reqr_reg)) 
                                     & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__reqr_reg) 
                                        | (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__reqw_reg))) 
                                    | (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac))
                                 : ((1U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
                                     ? (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac)
                                     : ((2U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
                                         ? ((~ (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_5)) 
                                            & (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac))
                                         : ((~ (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_6)) 
                                            & (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac)))))));
        bufp->chgCData(oldp+162,(vlSelf->Top__DOT__AXI4Arbiter__DOT__state),2);
        bufp->chgIData(oldp+163,(vlSelf->Top__DOT___GEN_0),32);
        bufp->chgCData(oldp+164,(vlSelf->Top__DOT___Decoder_io_rs1),5);
        bufp->chgCData(oldp+165,(vlSelf->Top__DOT___Decoder_io_rs2),5);
        bufp->chgCData(oldp+166,(((IData)(vlSelf->Top__DOT__IDReg_valid)
                                   ? (0x1fU & (vlSelf->Top__DOT__IDReg_inst 
                                               >> 7U))
                                   : 0U)),5);
        bufp->chgBit(oldp+167,(((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_76) 
                                | ((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71)) 
                                   & ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_67) 
                                      | ((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66)) 
                                         & (IData)(vlSelf->Top__DOT___Decoder_io_csr_en)))))));
        bufp->chgBit(oldp+168,(vlSelf->Top__DOT___Decoder_io_csr_en));
        bufp->chgQData(oldp+169,(vlSelf->Top__DOT__Decoder__DOT__casez_tmp),64);
        bufp->chgCData(oldp+171,(vlSelf->Top__DOT___Decoder_io_alu_op),5);
        bufp->chgCData(oldp+172,(((0x37U == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                   ? 0U : ((0x17U == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                            ? 3U : 
                                           ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_70)
                                             ? 1U : 
                                            ((0x6fU 
                                              == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                              ? 3U : 
                                             (((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71) 
                                               | (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_67))
                                               ? 1U
                                               : ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66)
                                                   ? 3U
                                                   : 
                                                  ((IData)(vlSelf->Top__DOT___Decoder_io_csr_en)
                                                    ? 6U
                                                    : 0U)))))))),3);
        bufp->chgCData(oldp+173,((((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74) 
                                   | (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_73))
                                   ? 4U : ((0x4293U 
                                            == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                            ? 5U : 
                                           ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_72)
                                             ? 4U : 
                                            ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_69)
                                              ? 5U : 
                                             (((0x6fU 
                                                == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
                                               | (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71))
                                               ? 4U
                                               : ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_67)
                                                   ? 2U
                                                   : 
                                                  ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66) 
                                                   << 2U)))))))),3);
        bufp->chgBit(oldp+174,((0x100073U == vlSelf->Top__DOT___GEN_0)));
        bufp->chgBit(oldp+175,(((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)) 
                                & ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h8d1c1e58__0) 
                                   | ((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_75)) 
                                      & (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71))))));
        bufp->chgBit(oldp+176,(((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_76)) 
                                & (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71))));
        bufp->chgCData(oldp+177,(((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_76)
                                   ? 0U : ((0x23U == (IData)(vlSelf->Top__DOT___GEN_1))
                                            ? 1U : 
                                           ((0xa3U 
                                             == (IData)(vlSelf->Top__DOT___GEN_1))
                                             ? 3U : 
                                            ((0x123U 
                                              == (IData)(vlSelf->Top__DOT___GEN_1))
                                              ? 0xfU
                                              : (0xffU 
                                                 & (- (IData)(
                                                              (0x1a3U 
                                                               == (IData)(vlSelf->Top__DOT___GEN_1)))))))))),8);
        bufp->chgCData(oldp+178,(((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)
                                   ? 6U : ((0x83U == (IData)(vlSelf->Top__DOT___GEN_1))
                                            ? 4U : 
                                           ((0x283U 
                                             == (IData)(vlSelf->Top__DOT___GEN_1))
                                             ? 1U : 
                                            ((3U == (IData)(vlSelf->Top__DOT___GEN_1))
                                              ? 3U : 
                                             ((0x203U 
                                               == (IData)(vlSelf->Top__DOT___GEN_1))
                                               ? 0U
                                               : ((0x103U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1))
                                                   ? 5U
                                                   : 
                                                  (2U 
                                                   | ((0x303U 
                                                       != (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                      << 2U))))))))),3);
        bufp->chgBit(oldp+179,(vlSelf->Top__DOT___Decoder_io_isword));
        bufp->chgBit(oldp+180,(((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)) 
                                & ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_70) 
                                   | ((0x6fU != (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
                                      & ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h92124dc1__0) 
                                         | (IData)(vlSelf->Top__DOT___Decoder_io_csr_en)))))));
        bufp->chgBit(oldp+181,(((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_76)) 
                                & (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h92124dc1__0))));
        bufp->chgQData(oldp+182,(((IData)(vlSelf->Top__DOT__pcsel)
                                   ? ((IData)(vlSelf->Top__DOT__stall)
                                       ? 0x114514ULL
                                       : ((0x67U == (IData)(vlSelf->Top__DOT___GEN_1))
                                           ? (vlSelf->Top__DOT__rs1v 
                                              + vlSelf->Top__DOT__Decoder__DOT__casez_tmp)
                                           : (((0x6fU 
                                                == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
                                               | ((0x63U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                  | ((0xe3U 
                                                      == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                     | ((0x2e3U 
                                                         == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                        | ((0x3e3U 
                                                            == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                           | ((0x263U 
                                                               == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                              | (0x363U 
                                                                 == (IData)(vlSelf->Top__DOT___GEN_1))))))))
                                               ? (((IData)(vlSelf->Top__DOT__IDReg_valid)
                                                    ? vlSelf->Top__DOT__IDReg_pc
                                                    : 0ULL) 
                                                  + vlSelf->Top__DOT__Decoder__DOT__casez_tmp)
                                               : ((0x30200073U 
                                                   == vlSelf->Top__DOT___GEN_0)
                                                   ? vlSelf->Top__DOT__mepc
                                                   : 
                                                  ((0x73U 
                                                    == vlSelf->Top__DOT___GEN_0)
                                                    ? vlSelf->Top__DOT__mtvec
                                                    : 0ULL)))))
                                   : 0ULL)),64);
        bufp->chgBit(oldp+184,(vlSelf->Top__DOT___InstFetcher_io_out_valid));
        bufp->chgQData(oldp+185,((QData)((IData)(vlSelf->Top__DOT__InstFetcher__DOT__readAddr))),64);
        bufp->chgIData(oldp+187,(vlSelf->Top__DOT__InstFetcher__DOT__outData),32);
        bufp->chgCData(oldp+188,(vlSelf->Top__DOT__InstFetcher__DOT__state),2);
        bufp->chgQData(oldp+189,(vlSelf->Top__DOT__InstFetcher__DOT__PC),64);
        bufp->chgIData(oldp+191,(vlSelf->Top__DOT__InstFetcher__DOT__readAddr),32);
        bufp->chgIData(oldp+192,(vlSelf->Top__DOT__InstFetcher__DOT__outAddr),32);
        bufp->chgQData(oldp+193,(vlSelf->Top__DOT__InstFetcher__DOT__dnpc_reg),64);
        bufp->chgBit(oldp+195,(vlSelf->Top__DOT__InstFetcher__DOT__dnpc_valid));
        bufp->chgBit(oldp+196,((1U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__state))));
        bufp->chgBit(oldp+197,((2U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__state))));
        bufp->chgBit(oldp+198,((1U & (~ (IData)((0U 
                                                 != (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state)))))));
        bufp->chgIData(oldp+199,(((4U & vlSelf->Top__DOT__InstFetcher__DOT__readAddr)
                                   ? (IData)((vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__data_cacheline_reg 
                                              >> 0x20U))
                                   : (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__data_cacheline_reg))),32);
        bufp->chgBit(oldp+200,((2U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state))));
        bufp->chgQData(oldp+201,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__data_cacheline_reg),64);
        bufp->chgCData(oldp+203,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state),3);
        bufp->chgQData(oldp+204,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__axi_reg_readAddr),64);
        bufp->chgBit(oldp+206,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__hit));
        bufp->chgSData(oldp+207,((0x1ffU & (vlSelf->Top__DOT__InstFetcher__DOT__readAddr 
                                            >> 3U))),9);
        bufp->chgBit(oldp+208,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_2));
        bufp->chgQData(oldp+209,(((IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_data_ext__DOT___GEN)
                                   ? vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_data_ext__DOT__Memory
                                  [vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_data_ext__DOT___GEN_0]
                                   : 0ULL)),64);
        bufp->chgQData(oldp+211,((QData)((IData)((vlSelf->Top__DOT__InstFetcher__DOT__readAddr 
                                                  >> 3U)))),61);
        bufp->chgQData(oldp+213,(((IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT___GEN)
                                   ? vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT__Memory
                                  [vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT___GEN_0]
                                   : 0ULL)),61);
        bufp->chgBit(oldp+215,(((IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT___GEN) 
                                & vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT__Memory
                                [vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT___GEN_0])));
        bufp->chgIData(oldp+216,((((2U != (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)) 
                                   | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_7))
                                   ? 0U : vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1)),32);
        bufp->chgBit(oldp+217,(vlSelf->Top__DOT___XBar2_io_axi4out2_arvalid));
        bufp->chgBit(oldp+218,(((IData)(vlSelf->Top__DOT__XBar2__DOT____VdfgTmp_hb75ae2a2__0) 
                                & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready))));
        bufp->chgBit(oldp+219,((1U & (~ (IData)(vlSelf->Top__DOT__MyClint__DOT__r_state)))));
        bufp->chgQData(oldp+220,((QData)((IData)(vlSelf->Top__DOT__MyClint__DOT__rdata))),64);
        bufp->chgBit(oldp+222,(vlSelf->Top__DOT__MyClint__DOT__r_state));
        bufp->chgQData(oldp+223,(vlSelf->Top__DOT__MyClint__DOT__mtime_csr),64);
        bufp->chgIData(oldp+225,(vlSelf->Top__DOT__MyClint__DOT__rdata),32);
        bufp->chgBit(oldp+226,(vlSelf->Top__DOT___XBar2_io_axi4out0_awvalid));
        bufp->chgQData(oldp+227,((((2U != (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w)) 
                                   | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_20))
                                   ? 0ULL : vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3)),64);
        bufp->chgBit(oldp+229,(((IData)(vlSelf->Top__DOT__XBar2__DOT____VdfgTmp_hd6eae8a8__0) 
                                & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready))));
        bufp->chgBit(oldp+230,((1U & ((~ (IData)((0U 
                                                  != (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state)))) 
                                      | (1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))))));
        bufp->chgBit(oldp+231,((1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))));
        bufp->chgBit(oldp+232,((3U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))));
        bufp->chgCData(oldp+233,(vlSelf->Top__DOT__MyUart__DOT__w_state),2);
        bufp->chgQData(oldp+234,(vlSelf->Top__DOT__MyUart__DOT__writeData),64);
        bufp->chgIData(oldp+236,(((IData)(vlSelf->Top__DOT__LSReg_valid)
                                   ? vlSelf->Top__DOT__LSReg_inst
                                   : 0U)),32);
        bufp->chgQData(oldp+237,(((IData)(vlSelf->Top__DOT__LSReg_valid)
                                   ? vlSelf->Top__DOT__LSReg_pc
                                   : 0ULL)),64);
        bufp->chgQData(oldp+239,(((IData)(vlSelf->Top__DOT__LSReg_valid)
                                   ? vlSelf->Top__DOT__LSReg_alures
                                   : 0ULL)),64);
        bufp->chgBit(oldp+241,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_memvalid));
        bufp->chgBit(oldp+242,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wen));
        bufp->chgQData(oldp+243,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wmask),64);
        bufp->chgCData(oldp+245,(((IData)(vlSelf->Top__DOT__LSReg_valid)
                                   ? (IData)(vlSelf->Top__DOT__LSReg_memsext)
                                   : 6U)),3);
        bufp->chgIData(oldp+246,(vlSelf->Top__DOT___GEN_2),32);
        bufp->chgQData(oldp+247,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wdata),64);
        bufp->chgBit(oldp+249,(((IData)(vlSelf->Top__DOT__LSReg_rden) 
                                & (IData)(vlSelf->Top__DOT__LSReg_valid))));
        bufp->chgCData(oldp+250,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_rd),5);
        bufp->chgSData(oldp+251,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_csridx),12);
        bufp->chgQData(oldp+252,(((IData)(vlSelf->Top__DOT__LSReg_valid)
                                   ? vlSelf->Top__DOT__LSReg_csrwv
                                   : 0ULL)),64);
        bufp->chgBit(oldp+254,(((IData)(vlSelf->Top__DOT__LSReg_csr_en) 
                                & (IData)(vlSelf->Top__DOT__LSReg_valid))));
        bufp->chgBit(oldp+255,(vlSelf->Top__DOT___NPC_Mem_io_in_ready));
        bufp->chgBit(oldp+256,(vlSelf->Top__DOT___NPC_Mem_io_out_valid));
        bufp->chgIData(oldp+257,(vlSelf->Top__DOT__NPC_Mem__DOT__instreg),32);
        bufp->chgQData(oldp+258,(vlSelf->Top__DOT__NPC_Mem__DOT__pcreg),64);
        bufp->chgQData(oldp+260,(vlSelf->Top__DOT__NPC_Mem__DOT__aluresreg),64);
        bufp->chgBit(oldp+262,(vlSelf->Top__DOT__NPC_Mem__DOT__memvalidreg));
        bufp->chgBit(oldp+263,(vlSelf->Top__DOT__NPC_Mem__DOT__rdenreg));
        bufp->chgCData(oldp+264,(vlSelf->Top__DOT__NPC_Mem__DOT__rdreg),5);
        bufp->chgSData(oldp+265,(vlSelf->Top__DOT__NPC_Mem__DOT__csridxreg),12);
        bufp->chgQData(oldp+266,(vlSelf->Top__DOT__NPC_Mem__DOT__csrwvreg),64);
        bufp->chgBit(oldp+268,(vlSelf->Top__DOT__NPC_Mem__DOT__csrenreg));
        bufp->chgCData(oldp+269,(vlSelf->Top__DOT__NPC_Mem__DOT__memsextreg),3);
        bufp->chgQData(oldp+270,(vlSelf->Top__DOT__NPC_Mem__DOT__readData),64);
        bufp->chgIData(oldp+272,(vlSelf->Top__DOT__NPC_Mem__DOT__readAddr),32);
        bufp->chgIData(oldp+273,(vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr),32);
        bufp->chgQData(oldp+274,(vlSelf->Top__DOT__NPC_Mem__DOT__writeData),64);
        bufp->chgCData(oldp+276,(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb),8);
        bufp->chgCData(oldp+277,(vlSelf->Top__DOT__NPC_Mem__DOT__r_state),2);
        bufp->chgCData(oldp+278,(vlSelf->Top__DOT__NPC_Mem__DOT__w_state),2);
        bufp->chgCData(oldp+279,(vlSelf->Top__DOT__NPC_Mem__DOT__r_offset_reg),3);
        bufp->chgBit(oldp+280,(vlSelf->Top__DOT__NPC_Mem__DOT__w_is_sram));
        bufp->chgQData(oldp+281,((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__readAddr))),64);
        bufp->chgBit(oldp+283,((1U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state))));
        bufp->chgBit(oldp+284,((2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state))));
        bufp->chgQData(oldp+285,((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr))),64);
        bufp->chgBit(oldp+287,((1U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state))));
        bufp->chgBit(oldp+288,((2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state))));
        bufp->chgBit(oldp+289,((1U & (~ (IData)((0U 
                                                 != (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)))))));
        bufp->chgQData(oldp+290,(vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_rdata),64);
        bufp->chgBit(oldp+292,((2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
        bufp->chgBit(oldp+293,(vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_bvalid));
        bufp->chgCData(oldp+294,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__casez_tmp),3);
        bufp->chgQData(oldp+295,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__data_cacheline_reg),64);
        bufp->chgCData(oldp+297,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state),3);
        bufp->chgQData(oldp+298,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_readAddr),64);
        bufp->chgQData(oldp+300,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeAddr),64);
        bufp->chgQData(oldp+302,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeMask),64);
        bufp->chgBit(oldp+304,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__uncached_r));
        bufp->chgQData(oldp+305,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi4_readData),64);
        bufp->chgSData(oldp+307,((0x1ffU & (vlSelf->Top__DOT__NPC_Mem__DOT__readAddr 
                                            >> 3U))),9);
        bufp->chgSData(oldp+308,((0x1ffU & (vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr 
                                            >> 3U))),9);
        bufp->chgBit(oldp+309,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_5));
        bufp->chgBit(oldp+310,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_9));
        bufp->chgQData(oldp+311,((((~ vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeMask) 
                                   & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_1)
                                       ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT__Memory
                                      [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_2]
                                       : 0ULL)) | (vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeMask 
                                                   & vlSelf->Top__DOT__NPC_Mem__DOT__writeData))),64);
        bufp->chgQData(oldp+313,(((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN)
                                   ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT__Memory
                                  [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_0]
                                   : 0ULL)),64);
        bufp->chgQData(oldp+315,(((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_1)
                                   ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT__Memory
                                  [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_2]
                                   : 0ULL)),64);
        bufp->chgQData(oldp+317,((QData)((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__readAddr 
                                                  >> 3U)))),61);
        bufp->chgQData(oldp+319,((QData)((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr 
                                                  >> 3U)))),61);
        bufp->chgQData(oldp+321,(((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT___GEN)
                                   ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT__Memory
                                  [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT___GEN_0]
                                   : 0ULL)),61);
        bufp->chgBit(oldp+323,(((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT___GEN) 
                                & vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT__Memory
                                [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT___GEN_0])));
        bufp->chgBit(oldp+324,(((IData)(vlSelf->Top__DOT__WBReg_valid) 
                                & ((IData)(vlSelf->Top__DOT__WBReg_rden) 
                                   & (0U != (IData)(vlSelf->Top__DOT__WBReg_rd))))));
        bufp->chgQData(oldp+325,(((IData)(vlSelf->Top__DOT__WBReg_memvalid)
                                   ? ((IData)(vlSelf->Top__DOT__WBReg_valid)
                                       ? ((4U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                           ? ((2U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                               ? vlSelf->Top__DOT__WBReg_rdata
                                               : ((1U 
                                                   & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                                   ? 
                                                  (((QData)((IData)(
                                                                    (- (IData)(
                                                                               (1U 
                                                                                & (IData)(
                                                                                (vlSelf->Top__DOT__WBReg_rdata 
                                                                                >> 0x1fU))))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(vlSelf->Top__DOT__WBReg_rdata)))
                                                   : 
                                                  (((- (QData)((IData)(
                                                                       (1U 
                                                                        & (IData)(
                                                                                (vlSelf->Top__DOT__WBReg_rdata 
                                                                                >> 0xfU)))))) 
                                                    << 0x10U) 
                                                   | (QData)((IData)(
                                                                     (0xffffU 
                                                                      & (IData)(vlSelf->Top__DOT__WBReg_rdata)))))))
                                           : ((2U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                               ? ((1U 
                                                   & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                                   ? 
                                                  (((- (QData)((IData)(
                                                                       (1U 
                                                                        & (IData)(
                                                                                (vlSelf->Top__DOT__WBReg_rdata 
                                                                                >> 7U)))))) 
                                                    << 8U) 
                                                   | (QData)((IData)(
                                                                     (0xffU 
                                                                      & (IData)(vlSelf->Top__DOT__WBReg_rdata)))))
                                                   : (QData)((IData)(vlSelf->Top__DOT__WBReg_rdata)))
                                               : ((1U 
                                                   & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                                   ? (QData)((IData)(
                                                                     (0xffffU 
                                                                      & (IData)(vlSelf->Top__DOT__WBReg_rdata))))
                                                   : (QData)((IData)(
                                                                     (0xffU 
                                                                      & (IData)(vlSelf->Top__DOT__WBReg_rdata)))))))
                                       : 0ULL) : vlSelf->Top__DOT__WBReg_alures)),64);
        bufp->chgQData(oldp+327,(vlSelf->Top__DOT___R_ext_R0_data),64);
        bufp->chgQData(oldp+329,(vlSelf->Top__DOT___R_ext_R1_data),64);
        bufp->chgQData(oldp+331,(vlSelf->Top__DOT__R_ext__DOT__Memory[0]),64);
        bufp->chgQData(oldp+333,(vlSelf->Top__DOT__R_ext__DOT__Memory[1]),64);
        bufp->chgQData(oldp+335,(vlSelf->Top__DOT__R_ext__DOT__Memory[2]),64);
        bufp->chgQData(oldp+337,(vlSelf->Top__DOT__R_ext__DOT__Memory[3]),64);
        bufp->chgQData(oldp+339,(vlSelf->Top__DOT__R_ext__DOT__Memory[4]),64);
        bufp->chgQData(oldp+341,(vlSelf->Top__DOT__R_ext__DOT__Memory[5]),64);
        bufp->chgQData(oldp+343,(vlSelf->Top__DOT__R_ext__DOT__Memory[6]),64);
        bufp->chgQData(oldp+345,(vlSelf->Top__DOT__R_ext__DOT__Memory[7]),64);
        bufp->chgQData(oldp+347,(vlSelf->Top__DOT__R_ext__DOT__Memory[8]),64);
        bufp->chgQData(oldp+349,(vlSelf->Top__DOT__R_ext__DOT__Memory[9]),64);
        bufp->chgQData(oldp+351,(vlSelf->Top__DOT__R_ext__DOT__Memory[10]),64);
        bufp->chgQData(oldp+353,(vlSelf->Top__DOT__R_ext__DOT__Memory[11]),64);
        bufp->chgQData(oldp+355,(vlSelf->Top__DOT__R_ext__DOT__Memory[12]),64);
        bufp->chgQData(oldp+357,(vlSelf->Top__DOT__R_ext__DOT__Memory[13]),64);
        bufp->chgQData(oldp+359,(vlSelf->Top__DOT__R_ext__DOT__Memory[14]),64);
        bufp->chgQData(oldp+361,(vlSelf->Top__DOT__R_ext__DOT__Memory[15]),64);
        bufp->chgQData(oldp+363,(vlSelf->Top__DOT__R_ext__DOT__Memory[16]),64);
        bufp->chgQData(oldp+365,(vlSelf->Top__DOT__R_ext__DOT__Memory[17]),64);
        bufp->chgQData(oldp+367,(vlSelf->Top__DOT__R_ext__DOT__Memory[18]),64);
        bufp->chgQData(oldp+369,(vlSelf->Top__DOT__R_ext__DOT__Memory[19]),64);
        bufp->chgQData(oldp+371,(vlSelf->Top__DOT__R_ext__DOT__Memory[20]),64);
        bufp->chgQData(oldp+373,(vlSelf->Top__DOT__R_ext__DOT__Memory[21]),64);
        bufp->chgQData(oldp+375,(vlSelf->Top__DOT__R_ext__DOT__Memory[22]),64);
        bufp->chgQData(oldp+377,(vlSelf->Top__DOT__R_ext__DOT__Memory[23]),64);
        bufp->chgQData(oldp+379,(vlSelf->Top__DOT__R_ext__DOT__Memory[24]),64);
        bufp->chgQData(oldp+381,(vlSelf->Top__DOT__R_ext__DOT__Memory[25]),64);
        bufp->chgQData(oldp+383,(vlSelf->Top__DOT__R_ext__DOT__Memory[26]),64);
        bufp->chgQData(oldp+385,(vlSelf->Top__DOT__R_ext__DOT__Memory[27]),64);
        bufp->chgQData(oldp+387,(vlSelf->Top__DOT__R_ext__DOT__Memory[28]),64);
        bufp->chgQData(oldp+389,(vlSelf->Top__DOT__R_ext__DOT__Memory[29]),64);
        bufp->chgQData(oldp+391,(vlSelf->Top__DOT__R_ext__DOT__Memory[30]),64);
        bufp->chgQData(oldp+393,(vlSelf->Top__DOT__R_ext__DOT__Memory[31]),64);
        bufp->chgIData(oldp+395,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                   ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_5)
                                       ? 0U : vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1)
                                   : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_16)
                                       ? vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1
                                       : 0U))),32);
        bufp->chgBit(oldp+396,(vlSelf->Top__DOT___XBar2_io_axi4out1_arvalid));
        bufp->chgBit(oldp+397,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                 ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
                                    & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready))
                                 : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_18) 
                                    & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready)))));
        bufp->chgIData(oldp+398,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                   ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_5)
                                       ? 0U : vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2)
                                   : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_16)
                                       ? vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2
                                       : 0U))),32);
        bufp->chgBit(oldp+399,(vlSelf->Top__DOT___XBar2_io_axi4out1_awvalid));
        bufp->chgQData(oldp+400,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                   ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_5)
                                       ? 0ULL : vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3)
                                   : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_16)
                                       ? vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3
                                       : 0ULL))),64);
        bufp->chgCData(oldp+402,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                   ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_5)
                                       ? 0U : (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_4))
                                   : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_16)
                                       ? (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_4)
                                       : 0U))),8);
        bufp->chgBit(oldp+403,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                 ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
                                    & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready))
                                 : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_18) 
                                    & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready)))));
        bufp->chgBit(oldp+404,((0U == (IData)(vlSelf->Top__DOT__SRAM__DOT__r_state))));
        bufp->chgQData(oldp+405,(vlSelf->Top__DOT__SRAM__DOT__readData),64);
        bufp->chgBit(oldp+407,(vlSelf->Top__DOT__SRAM__DOT__rvalidReg));
        bufp->chgBit(oldp+408,(vlSelf->Top__DOT___SRAM_io_axi4_awready));
        bufp->chgBit(oldp+409,((1U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))));
        bufp->chgBit(oldp+410,((3U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))));
        bufp->chgCData(oldp+411,(vlSelf->Top__DOT__SRAM__DOT__casez_tmp),2);
        bufp->chgCData(oldp+412,(vlSelf->Top__DOT__SRAM__DOT__r_state),2);
        bufp->chgCData(oldp+413,(vlSelf->Top__DOT__SRAM__DOT__delay),8);
        bufp->chgCData(oldp+414,(vlSelf->Top__DOT__SRAM__DOT__delayCounter),8);
        bufp->chgBit(oldp+415,(vlSelf->Top__DOT__SRAM__DOT__delayDone));
        bufp->chgIData(oldp+416,(vlSelf->Top__DOT__SRAM__DOT__readAddr),32);
        bufp->chgCData(oldp+417,(vlSelf->Top__DOT__SRAM__DOT__w_state),2);
        bufp->chgIData(oldp+418,(vlSelf->Top__DOT__SRAM__DOT__writeAddr),32);
        bufp->chgQData(oldp+419,(vlSelf->Top__DOT__SRAM__DOT__writeData),64);
        bufp->chgCData(oldp+421,(vlSelf->Top__DOT__SRAM__DOT__writeStrb),8);
        bufp->chgBit(oldp+422,((((IData)(vlSelf->Top__DOT__SRAM__DOT__delayDone) 
                                 & (1U == (IData)(vlSelf->Top__DOT__SRAM__DOT__r_state))) 
                                | (2U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state)))));
        bufp->chgBit(oldp+423,((2U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))));
        bufp->chgQData(oldp+424,(vlSelf->Top__DOT__SRAM__DOT___dpic_mem_rdata),64);
        bufp->chgQData(oldp+426,(vlSelf->Top__DOT__XBar2__DOT__casez_tmp),64);
        bufp->chgCData(oldp+428,(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0),2);
        bufp->chgCData(oldp+429,(vlSelf->Top__DOT__XBar2__DOT__state_r),2);
        bufp->chgCData(oldp+430,(vlSelf->Top__DOT__XBar2__DOT__state_w),2);
    }
    bufp->chgBit(oldp+431,(vlSelf->clock));
    bufp->chgBit(oldp+432,(vlSelf->reset));
    bufp->chgIData(oldp+433,(vlSelf->io_inst),32);
    bufp->chgQData(oldp+434,(vlSelf->io_pc),64);
    bufp->chgQData(oldp+436,(vlSelf->io_npc),64);
    bufp->chgBit(oldp+438,(vlSelf->Top__DOT____Vcellinp__InstFetcher__io_in_valid));
    bufp->chgBit(oldp+439,(((~ (IData)(vlSelf->reset)) 
                            & (IData)(vlSelf->Top__DOT__IDRegen))));
}

void VTop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_cleanup\n"); );
    // Init
    VTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VTop___024root*>(voidSelf);
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
