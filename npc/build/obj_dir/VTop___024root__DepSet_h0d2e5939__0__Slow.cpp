// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VTop.h for the primary calling header

#include "verilated.h"
#include "verilated_dpi.h"

#include "VTop___024root.h"

VL_ATTR_COLD void VTop___024root___eval_static(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___eval_static\n"); );
}

VL_ATTR_COLD void VTop___024root___eval_initial(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigrprev__TOP__clock = vlSelf->clock;
}

VL_ATTR_COLD void VTop___024root___eval_final(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___eval_final\n"); );
}

VL_ATTR_COLD void VTop___024root___eval_triggers__stl(VTop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void VTop___024root___dump_triggers__stl(VTop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void VTop___024root___eval_stl(VTop___024root* vlSelf);

VL_ATTR_COLD void VTop___024root___eval_settle(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        VTop___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VstlIterCount))) {
#ifdef VL_DEBUG
                VTop___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("build/Top.sv", 85, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            VTop___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VTop___024root___dump_triggers__stl(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

extern const VlUnpacked<CData/*1:0*/, 16> VTop__ConstPool__TABLE_ha024a6da_0;

VL_ATTR_COLD void VTop___024root___stl_sequent__TOP__0(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___stl_sequent__TOP__0\n"); );
    // Init
    VlWide<3>/*95:0*/ __Vtemp_hb1f78123__0;
    VlWide<3>/*95:0*/ __Vtemp_hd4884bb4__0;
    VlWide<3>/*95:0*/ __Vtemp_h58a7e692__0;
    // Body
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN = (0U 
                                                == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state));
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_0 = (1U 
                                                  == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state));
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_1 = (2U 
                                                  == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state));
    vlSelf->Top__DOT___SRAM_io_axi4_arready = (0U == (IData)(vlSelf->Top__DOT__SRAM__DOT__r_state));
    vlSelf->Top__DOT__SRAM__DOT___GEN_0 = (1U == (IData)(vlSelf->Top__DOT__SRAM__DOT__r_state));
    vlSelf->Top__DOT__XBar2__DOT___GEN_10 = (0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w));
    vlSelf->Top__DOT__XBar2__DOT___GEN = (0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r));
    vlSelf->Top__DOT__XBar2__DOT___GEN_4 = (1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r));
    vlSelf->Top__DOT__XBar2__DOT___GEN_6 = (2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r));
    vlSelf->Top__DOT__XBar2__DOT___GEN_15 = (1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w));
    vlSelf->Top__DOT__XBar2__DOT___GEN_19 = (2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w));
    vlSelf->Top__DOT__InstFetcher__DOT___io_out_valid_T 
        = (0U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__state));
    vlSelf->Top__DOT__InstFetcher__DOT___icache_io_io_raddr_valid_T 
        = (1U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__state));
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN 
        = (1U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state));
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___io_io_rdata_valid_T 
        = (2U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state));
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___io_axi4_arvalid_T 
        = (3U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state));
    vlSelf->Top__DOT__NPC_Mem__DOT___io_out_valid_T 
        = (0U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state));
    vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_raddr_valid_T 
        = (1U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state));
    vlSelf->Top__DOT__NPC_Mem__DOT___io_out_valid_T_1 
        = (0U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state));
    vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_wdata_valid_T 
        = (1U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state));
    vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_bready_T 
        = (2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state));
    vlSelf->Top__DOT__MyUart__DOT___GEN = (2U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state));
    vlSelf->Top__DOT__MyUart__DOT___io_axi4_wready_T 
        = (1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state));
    if (vlSelf->Top__DOT__WBReg_valid) {
        vlSelf->io_npc = vlSelf->Top__DOT__LSReg_pc;
        vlSelf->Top__DOT___WB_RS2_Hazard_T = vlSelf->Top__DOT__WBReg_rd;
        vlSelf->Top__DOT___GEN_3 = vlSelf->Top__DOT__WBReg_csr_en;
    } else {
        vlSelf->io_npc = 0ULL;
        vlSelf->Top__DOT___WB_RS2_Hazard_T = 0U;
        vlSelf->Top__DOT___GEN_3 = 0U;
    }
    if (vlSelf->Top__DOT__LSReg_valid) {
        vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wmask 
            = (QData)((IData)(vlSelf->Top__DOT__LSReg_memwmask));
        vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wdata 
            = vlSelf->Top__DOT__LSReg_rs2v;
        vlSelf->Top__DOT__NPC_Mem__DOT____VdfgTmp_h21929fc2__0 
            = (7U & (IData)(vlSelf->Top__DOT__LSReg_alures));
        vlSelf->Top__DOT___GEN_2 = (IData)(vlSelf->Top__DOT__LSReg_alures);
        vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_rd 
            = vlSelf->Top__DOT__LSReg_rd;
        vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_csridx 
            = vlSelf->Top__DOT__LSReg_csridx;
    } else {
        vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wmask = 0ULL;
        vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wdata = 0ULL;
        vlSelf->Top__DOT__NPC_Mem__DOT____VdfgTmp_h21929fc2__0 = 0U;
        vlSelf->Top__DOT___GEN_2 = 0U;
        vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_rd = 0U;
        vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_csridx = 0U;
    }
    vlSelf->Top__DOT__SRAM__DOT__delayDone = ((IData)(vlSelf->Top__DOT__SRAM__DOT__delay) 
                                              == (IData)(vlSelf->Top__DOT__SRAM__DOT__delayCounter));
    vlSelf->Top__DOT__NPC_Mem__DOT___GEN_2 = ((2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state)) 
                                              & (2U 
                                                 == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)));
    if (vlSelf->Top__DOT__ISReg_valid) {
        vlSelf->io_inst = vlSelf->Top__DOT__ISReg_inst;
        vlSelf->io_pc = vlSelf->Top__DOT__ISReg_pc;
    } else {
        vlSelf->io_inst = 0U;
        vlSelf->io_pc = 0ULL;
    }
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___cache_data_ext_R1_data 
        = ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_1)
            ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT__Memory
           [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_2]
            : 0ULL);
    vlSelf->Top__DOT__XBar2__DOT___GEN_5 = ((1U != (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)) 
                                            | (0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)));
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__hit 
        = (((IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT___GEN) 
            & vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT__Memory
            [vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT___GEN_0]) 
           & (((IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT___GEN)
                ? vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT__Memory
               [vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT___GEN_0]
                : 0ULL) == (QData)((IData)((vlSelf->Top__DOT__InstFetcher__DOT__readAddr 
                                            >> 3U)))));
    vlSelf->Top__DOT__XBar2__DOT___GEN_20 = ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w)) 
                                             | (1U 
                                                == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w)));
    vlSelf->Top__DOT__XBar2__DOT___GEN_7 = ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)) 
                                            | (1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)));
    if (vlSelf->Top__DOT__EXReg_valid) {
        vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op 
            = vlSelf->Top__DOT__EXReg_aluop;
        vlSelf->Top__DOT____Vcellinp__ALU__io_asel 
            = vlSelf->Top__DOT__EXReg_dataAsel;
        vlSelf->Top__DOT____Vcellinp__ALU__io_bsel 
            = vlSelf->Top__DOT__EXReg_dataBsel;
        vlSelf->Top__DOT____Vcellinp__ALU__io_rs1v 
            = vlSelf->Top__DOT__EXReg_rs1v;
        vlSelf->Top__DOT____Vcellinp__ALU__io_rs2v 
            = vlSelf->Top__DOT__EXReg_rs2v;
        vlSelf->Top__DOT____Vcellinp__ALU__io_csrrv 
            = vlSelf->Top__DOT__EXReg_csrrv;
        vlSelf->Top__DOT____Vcellinp__ALU__io_imm = vlSelf->Top__DOT__EXReg_imm;
        vlSelf->Top__DOT____Vcellinp__ALU__io_pc = vlSelf->Top__DOT__EXReg_pc;
        vlSelf->Top__DOT___EX_RS2_Hazard_T = vlSelf->Top__DOT__EXReg_rd;
    } else {
        vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op = 0U;
        vlSelf->Top__DOT____Vcellinp__ALU__io_asel = 0U;
        vlSelf->Top__DOT____Vcellinp__ALU__io_bsel = 0U;
        vlSelf->Top__DOT____Vcellinp__ALU__io_rs1v = 0ULL;
        vlSelf->Top__DOT____Vcellinp__ALU__io_rs2v = 0ULL;
        vlSelf->Top__DOT____Vcellinp__ALU__io_csrrv = 0ULL;
        vlSelf->Top__DOT____Vcellinp__ALU__io_imm = 0ULL;
        vlSelf->Top__DOT____Vcellinp__ALU__io_pc = 0ULL;
        vlSelf->Top__DOT___EX_RS2_Hazard_T = 0U;
    }
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_1 
        = ((2U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state)) 
           | (3U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state)));
    vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h4ab110e3__0 
        = ((0U != (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)) 
           & (1U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)));
    vlSelf->Top__DOT__XBar2__DOT___GEN_8 = ((0U != (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)) 
                                            & ((1U 
                                                == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r))
                                                ? (0U 
                                                   == (IData)(vlSelf->Top__DOT__SRAM__DOT__r_state))
                                                : (
                                                   (~ (IData)(vlSelf->Top__DOT__MyClint__DOT__r_state)) 
                                                   & (2U 
                                                      == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)))));
    vlSelf->Top__DOT___SRAM_io_axi4_awready = ((0U 
                                                == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state)) 
                                               | (1U 
                                                  == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state)));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__uncached_r 
        = ((0x80000000U > vlSelf->Top__DOT__NPC_Mem__DOT__readAddr) 
           | (0x88000000U < vlSelf->Top__DOT__NPC_Mem__DOT__readAddr));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_1 
        = (1U & ((~ (IData)((0U != (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)))) 
                 | (2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT____VdfgTmp_h58a209da__0 
        = ((1U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)) 
           | (4U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)));
    vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wen 
        = ((IData)(vlSelf->Top__DOT__LSReg_memwen) 
           & (IData)(vlSelf->Top__DOT__LSReg_valid));
    vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_memvalid 
        = ((IData)(vlSelf->Top__DOT__LSReg_memvalid) 
           & (IData)(vlSelf->Top__DOT__LSReg_valid));
    vlSelf->Top__DOT___NPC_Mem_io_out_valid = ((0U 
                                                == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state)) 
                                               & (0U 
                                                  == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state)));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_13 
        = ((0xf0U & ((- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 7U)))) << 4U)) 
           | (0xfU & (- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 6U))))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_14 
        = ((0xf0U & ((- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 6U)))) << 4U)) 
           | (0xfU & (- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 5U))))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_15 
        = ((0xf0U & ((- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 5U)))) << 4U)) 
           | (0xfU & (- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 4U))))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_16 
        = ((0xf0U & ((- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 4U)))) << 4U)) 
           | (0xfU & (- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 3U))))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_17 
        = ((0xf0U & ((- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 3U)))) << 4U)) 
           | (0xfU & (- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 2U))))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_18 
        = ((0xf0U & ((- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 2U)))) << 4U)) 
           | (0xfU & (- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 1U))))));
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_3 = ((0U 
                                                   == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)) 
                                                  | (1U 
                                                     == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_19 
        = ((0xf0U & ((- (IData)((1U & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                       >> 1U)))) << 4U)) 
           | (0xfU & (- (IData)((1U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb))))));
    if (vlSelf->Top__DOT__IDReg_valid) {
        vlSelf->Top__DOT___Decoder_io_rs2 = (0x1fU 
                                             & (vlSelf->Top__DOT__IDReg_inst 
                                                >> 0x14U));
        vlSelf->Top__DOT___Decoder_io_rs1 = (0x1fU 
                                             & (vlSelf->Top__DOT__IDReg_inst 
                                                >> 0xfU));
        vlSelf->Top__DOT___GEN_0 = vlSelf->Top__DOT__IDReg_inst;
        vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0 
            = (0x7fU & vlSelf->Top__DOT__IDReg_inst);
    } else {
        vlSelf->Top__DOT___Decoder_io_rs2 = 0U;
        vlSelf->Top__DOT___Decoder_io_rs1 = 0U;
        vlSelf->Top__DOT___GEN_0 = 0U;
        vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0 = 0U;
    }
    vlSelf->Top__DOT__XBar2__DOT___GEN_17 = ((0U != (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)) 
                                             & (1U 
                                                == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)));
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2 = ((2U 
                                                   == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)) 
                                                  | (3U 
                                                     == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)));
    vlSelf->Top__DOT__XBar2__DOT___GEN_16 = (1U & (
                                                   (~ (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_5)) 
                                                   | (1U 
                                                      == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))));
    vlSelf->Top__DOT__NPC_Mem__DOT__w_is_sram = ((IData)(vlSelf->Top__DOT__LSReg_valid) 
                                                 & ((IData)(
                                                            (vlSelf->Top__DOT__LSReg_alures 
                                                             >> 0x1fU)) 
                                                    & (0x88000000U 
                                                       > vlSelf->Top__DOT___GEN_2)));
    vlSelf->Top__DOT__XBar2__DOT____VdfgTmp_hd6eae8a8__0 
        = ((~ (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_20)) 
           & (2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w)));
    vlSelf->Top__DOT__XBar2__DOT____VdfgTmp_hb75ae2a2__0 
        = ((~ (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_7)) 
           & (2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)));
    vlSelf->Top__DOT__XBar2__DOT__casez_tmp = ((0U 
                                                == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r))
                                                ? 0ULL
                                                : (
                                                   (1U 
                                                    == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r))
                                                    ? vlSelf->Top__DOT__SRAM__DOT__readData
                                                    : 
                                                   ((2U 
                                                     == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r))
                                                     ? (QData)((IData)(vlSelf->Top__DOT__MyClint__DOT__rdata))
                                                     : 0ULL)));
    vlSelf->Top__DOT__XBar2__DOT__casez_tmp_2 = ((0U 
                                                  == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                  ? vlSelf->Top__DOT__XBar2__DOT__casez_tmp
                                                  : 
                                                 ((1U 
                                                   == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                   ? vlSelf->Top__DOT__SRAM__DOT__readData
                                                   : 
                                                  ((2U 
                                                    == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                    ? 0ULL
                                                    : vlSelf->Top__DOT__XBar2__DOT__casez_tmp)));
    vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_rdata 
        = (((0U != (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)) 
            & ((2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)) 
               & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__uncached_r)))
            ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi4_readData
            : vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__data_cacheline_reg);
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_0 
        = (((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT___GEN) 
            & vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT__Memory
            [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT___GEN_0]) 
           & ((~ (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__uncached_r)) 
              & (((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT___GEN)
                   ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT__Memory
                  [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT___GEN_0]
                   : 0ULL) == (QData)((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__readAddr 
                                               >> 3U))))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_4 
        = ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_1) 
           | (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT____VdfgTmp_h58a209da__0));
    vlSelf->Top__DOT__NPC_Mem__DOT___GEN = ((IData)(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_memvalid) 
                                            & (IData)(vlSelf->Top__DOT__LSReg_valid));
    vlSelf->Top__DOT__ALU__DOT__casez_tmp = ((4U & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_asel))
                                              ? ((2U 
                                                  & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_asel))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_asel))
                                                   ? 0ULL
                                                   : vlSelf->Top__DOT____Vcellinp__ALU__io_csrrv)
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_asel))
                                                   ? 0ULL
                                                   : vlSelf->Top__DOT____Vcellinp__ALU__io_imm))
                                              : ((2U 
                                                  & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_asel))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_asel))
                                                   ? vlSelf->Top__DOT____Vcellinp__ALU__io_pc
                                                   : vlSelf->Top__DOT____Vcellinp__ALU__io_rs2v)
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_asel))
                                                   ? vlSelf->Top__DOT____Vcellinp__ALU__io_rs1v
                                                   : 0ULL)));
    vlSelf->Top__DOT__ALU__DOT__casez_tmp_0 = ((4U 
                                                & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_bsel))
                                                ? (
                                                   (2U 
                                                    & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_bsel))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_bsel))
                                                     ? 0ULL
                                                     : vlSelf->Top__DOT____Vcellinp__ALU__io_csrrv)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_bsel))
                                                     ? (QData)((IData)(
                                                                       (0x3fU 
                                                                        & (((IData)(vlSelf->Top__DOT__EXReg_valid)
                                                                             ? vlSelf->Top__DOT__EXReg_inst
                                                                             : 0U) 
                                                                           >> 0x14U))))
                                                     : vlSelf->Top__DOT____Vcellinp__ALU__io_imm))
                                                : (
                                                   (2U 
                                                    & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_bsel))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_bsel))
                                                     ? vlSelf->Top__DOT____Vcellinp__ALU__io_pc
                                                     : vlSelf->Top__DOT____Vcellinp__ALU__io_rs2v)
                                                    : 
                                                   ((1U 
                                                     & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_bsel))
                                                     ? vlSelf->Top__DOT____Vcellinp__ALU__io_rs1v
                                                     : 0ULL)));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_28 
        = ((0xcU & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_19)) 
           | (3U & (- (IData)((1U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb))))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_20 
        = (0x33333333333333ULL & (((QData)((IData)(
                                                   (0xfU 
                                                    & (- (IData)(
                                                                 (1U 
                                                                  & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                                                     >> 7U))))))) 
                                   << 0x32U) | (((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_13)) 
                                                 << 0x2aU) 
                                                | (((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_14)) 
                                                    << 0x22U) 
                                                   | (((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_15)) 
                                                       << 0x1aU) 
                                                      | (QData)((IData)(
                                                                        (((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_16) 
                                                                          << 0x12U) 
                                                                         | (((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_17) 
                                                                             << 0xaU) 
                                                                            | (((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_18) 
                                                                                << 2U) 
                                                                               | (3U 
                                                                                & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_19) 
                                                                                >> 6U))))))))))));
    vlSelf->Top__DOT___R_ext_R1_data = vlSelf->Top__DOT__R_ext__DOT__Memory
        [vlSelf->Top__DOT___Decoder_io_rs2];
    vlSelf->Top__DOT___R_ext_R0_data = vlSelf->Top__DOT__R_ext__DOT__Memory
        [vlSelf->Top__DOT___Decoder_io_rs1];
    if ((0U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))) {
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3 = 0ULL;
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_4 = 0U;
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2 = 0U;
    } else if ((1U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))) {
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3 = 0ULL;
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_4 = 0U;
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2 = 0U;
    } else {
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3 
            = vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeData;
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_4 
            = vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_wstrb;
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2 
            = (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeAddr);
    }
    vlSelf->Top__DOT__XBar2__DOT___GEN_11 = ((vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2 
                                              >> 0x1fU) 
                                             & (0x88000000U 
                                                > vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2));
    vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1 
        = ((0U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
            ? 0U : ((1U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
                     ? (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__axi_reg_readAddr)
                     : (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_readAddr)));
    vlSelf->Top__DOT__XBar2__DOT___GEN_0 = ((vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1 
                                             >> 0x1fU) 
                                            & (0x88000000U 
                                               > vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1));
    vlSelf->Top__DOT__XBar2__DOT___GEN_1 = ((0xa0000048U 
                                             == vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1) 
                                            | (0xa000004cU 
                                               == vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1));
    vlSelf->Top__DOT__XBar2__DOT___GEN_21 = ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
                                             & (IData)(vlSelf->Top__DOT___SRAM_io_axi4_awready));
    vlSelf->Top__DOT__XBar2__DOT___GEN_22 = ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
                                             & (1U 
                                                == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state)));
    vlSelf->Top__DOT__XBar2__DOT___GEN_18 = ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w)) 
                                             | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17));
    vlSelf->Top__DOT__XBar2__DOT___GEN_23 = ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
                                             & (3U 
                                                == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state)));
    vlSelf->Top__DOT__csridx = ((0x73U == vlSelf->Top__DOT___GEN_0)
                                 ? 0x305U : ((IData)(vlSelf->Top__DOT__IDReg_valid)
                                              ? (vlSelf->Top__DOT__IDReg_inst 
                                                 >> 0x14U)
                                              : 0U));
    vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready 
        = ((0U != (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)) 
           & ((1U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
               ? (4U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state))
               : ((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2) 
                  & (5U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)))));
    vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_arvalid 
        = ((0U != (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)) 
           & ((1U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
               ? (3U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state))
               : ((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2) 
                  & (4U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)))));
    vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h64195d75__0 
        = ((0U != (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)) 
           & ((1U != (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)) 
              & (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2)));
    vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0 
        = ((~ (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_3)) 
           & (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2));
    vlSelf->Top__DOT__Decoder__DOT___GEN_74 = ((0x37U 
                                                == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
                                               | (0x17U 
                                                  == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)));
    vlSelf->Top__DOT___GEN_1 = ((((IData)(vlSelf->Top__DOT__IDReg_valid)
                                   ? (7U & (vlSelf->Top__DOT__IDReg_inst 
                                            >> 0xcU))
                                   : 0U) << 7U) | (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0));
    vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_rdata 
        = ((1U & ((~ (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2)) 
                  | (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_3)))
            ? 0ULL : vlSelf->Top__DOT__XBar2__DOT__casez_tmp_2);
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_30 
        = ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_4) 
           | (5U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)));
    vlSelf->Top__DOT__NPC_Mem__DOT___GEN_0 = ((~ (IData)(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wen)) 
                                              & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT___GEN));
    vlSelf->Top__DOT__NPC_Mem__DOT___GEN_1 = ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT___GEN) 
                                              & (IData)(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wen));
    vlSelf->Top__DOT__ALU__DOT___GEN = (vlSelf->Top__DOT__ALU__DOT__casez_tmp 
                                        * vlSelf->Top__DOT__ALU__DOT__casez_tmp_0);
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_21 
        = (0xffU & ((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_20 
                             >> 0x2eU)) | (0x33U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_13))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_22 
        = (0xffU & ((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_20 
                             >> 0x26U)) | (0x33U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_14))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_23 
        = (0xffU & ((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_20 
                             >> 0x1eU)) | (0x33U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_15))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_24 
        = (0xffU & ((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_20 
                             >> 0x16U)) | (0x33U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_16))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_25 
        = (0xffU & ((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_20 
                             >> 0xeU)) | (0x33U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_17))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_26 
        = (0xffU & ((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_20 
                             >> 6U)) | (0x33U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_18))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_27 
        = ((0xfcU & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_20) 
                     << 2U)) | (0x33U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_19)));
    vlSelf->Top__DOT__rs2v = ((0U == (IData)(vlSelf->Top__DOT___Decoder_io_rs2))
                               ? 0ULL : vlSelf->Top__DOT___R_ext_R1_data);
    vlSelf->Top__DOT__rs1v = ((0U == (IData)(vlSelf->Top__DOT___Decoder_io_rs1))
                               ? 0ULL : vlSelf->Top__DOT___R_ext_R0_data);
    vlSelf->Top__DOT__XBar2__DOT___GEN_13 = ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_11) 
                                             | (0xa00003f8U 
                                                == vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2));
    vlSelf->Top__DOT__XBar2__DOT___GEN_2 = ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_0) 
                                            | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_1));
    vlSelf->Top__DOT____VdfgTmp_h8812001b__0 = ((0x341U 
                                                 == (IData)(vlSelf->Top__DOT__csridx)) 
                                                | (0x342U 
                                                   == (IData)(vlSelf->Top__DOT__csridx)));
    vlSelf->Top__DOT__SRAM__DOT___GEN = ((2U == (IData)(vlSelf->Top__DOT__SRAM__DOT__r_state)) 
                                         & ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                             ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
                                                & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready))
                                             : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_18) 
                                                & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready))));
    vlSelf->Top__DOT___XBar2_io_axi4out2_arvalid = 
        ((IData)(vlSelf->Top__DOT__XBar2__DOT____VdfgTmp_hb75ae2a2__0) 
         & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_arvalid));
    vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready 
        = ((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h64195d75__0) 
           & (7U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)));
    vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid 
        = ((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h64195d75__0) 
           & (6U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)));
    vlSelf->Top__DOT__Decoder__DOT___GEN_72 = ((0x393U 
                                                == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                               | ((0x313U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                  | (0x213U 
                                                     == (IData)(vlSelf->Top__DOT___GEN_1))));
    vlSelf->Top__DOT___Decoder_io_csr_en = ((0x173U 
                                             == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                            | (0xf3U 
                                               == (IData)(vlSelf->Top__DOT___GEN_1)));
    vlSelf->Top__DOT__Decoder__DOT___GEN_66 = ((0x63U 
                                                == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                               | ((0xe3U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                  | ((0x2e3U 
                                                      == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                     | ((0x263U 
                                                         == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                        | ((0x363U 
                                                            == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                           | (0x3e3U 
                                                              == (IData)(vlSelf->Top__DOT___GEN_1)))))));
    vlSelf->Top__DOT__Decoder__DOT___GEN_71 = ((0x23U 
                                                == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                               | ((0xa3U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                  | ((0x123U 
                                                      == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                     | (0x1a3U 
                                                        == (IData)(vlSelf->Top__DOT___GEN_1)))));
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h8d1c1e58__0 
        = ((0x83U == (IData)(vlSelf->Top__DOT___GEN_1)) 
           | ((0x283U == (IData)(vlSelf->Top__DOT___GEN_1)) 
              | ((3U == (IData)(vlSelf->Top__DOT___GEN_1)) 
                 | ((0x203U == (IData)(vlSelf->Top__DOT___GEN_1)) 
                    | ((0x103U == (IData)(vlSelf->Top__DOT___GEN_1)) 
                       | ((0x303U == (IData)(vlSelf->Top__DOT___GEN_1)) 
                          | (0x183U == (IData)(vlSelf->Top__DOT___GEN_1))))))));
    vlSelf->Top__DOT__Decoder__DOT___GEN_29 = ((((IData)(vlSelf->Top__DOT__IDReg_valid)
                                                  ? 
                                                 (vlSelf->Top__DOT__IDReg_inst 
                                                  >> 0x19U)
                                                  : 0U) 
                                                << 0xaU) 
                                               | (IData)(vlSelf->Top__DOT___GEN_1));
    vlSelf->Top__DOT__Decoder__DOT___GEN_14 = ((((IData)(vlSelf->Top__DOT__IDReg_valid)
                                                  ? 
                                                 (vlSelf->Top__DOT__IDReg_inst 
                                                  >> 0x1aU)
                                                  : 0U) 
                                                << 0xaU) 
                                               | (IData)(vlSelf->Top__DOT___GEN_1));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT____VdfgTmp_ha260658d__0 
        = (1U & (~ ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_30) 
                    | ((3U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)) 
                       | (6U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))))));
    vlSelf->Top__DOT__ALU__DOT____VdfgExtracted_h750bc5e8__0 
        = (((QData)((IData)((- (IData)((1U & (IData)(
                                                     (vlSelf->Top__DOT__ALU__DOT___GEN 
                                                      >> 0x3fU))))))) 
            << 0x20U) | (QData)((IData)((vlSelf->Top__DOT__ALU__DOT___GEN 
                                         >> 0x20U))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_29 
        = (0x555555555555555ULL & (((QData)((IData)(
                                                    (3U 
                                                     & (- (IData)(
                                                                  (1U 
                                                                   & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb) 
                                                                      >> 7U))))))) 
                                    << 0x39U) | (((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_21)) 
                                                  << 0x31U) 
                                                 | (((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_22)) 
                                                     << 0x29U) 
                                                    | (((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_23)) 
                                                        << 0x21U) 
                                                       | (((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_24)) 
                                                           << 0x19U) 
                                                          | (QData)((IData)(
                                                                            (((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_25) 
                                                                              << 0x11U) 
                                                                             | (((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_26) 
                                                                                << 9U) 
                                                                                | (((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_27) 
                                                                                << 1U) 
                                                                                | (1U 
                                                                                & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_28) 
                                                                                >> 3U)))))))))))));
    vlSelf->Top__DOT__XBar2__DOT___GEN_3 = (1U & ((~ (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_arvalid)) 
                                                  | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_2)));
    vlSelf->Top__DOT__XBar2__DOT___GEN_9 = ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r))
                                             ? ((~ (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_2)) 
                                                & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_arvalid))
                                             : ((1U 
                                                 == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r))
                                                 ? (IData)(vlSelf->Top__DOT__SRAM__DOT__rvalidReg)
                                                 : 
                                                ((2U 
                                                  == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)) 
                                                 & (IData)(vlSelf->Top__DOT__MyClint__DOT__r_state))));
    if ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))) {
        vlSelf->Top__DOT___XBar2_io_axi4in_arready 
            = vlSelf->Top__DOT__XBar2__DOT___GEN_8;
        vlSelf->Top__DOT___XBar2_io_axi4out1_arvalid 
            = ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
               & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_arvalid));
        vlSelf->Top__DOT___XBar2_io_axi4out1_awvalid 
            = ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
               & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid));
        vlSelf->Top__DOT__XBar2__DOT__casez_tmp_7 = 
            (((IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid) 
              & (~ (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_13))) 
             | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_23));
        vlSelf->Top__DOT__XBar2__DOT___io_axi4in_rvalid_output 
            = vlSelf->Top__DOT__XBar2__DOT___GEN_9;
    } else {
        if ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))) {
            vlSelf->Top__DOT___XBar2_io_axi4in_arready 
                = (0U == (IData)(vlSelf->Top__DOT__SRAM__DOT__r_state));
            vlSelf->Top__DOT__XBar2__DOT__casez_tmp_7 
                = (3U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state));
            vlSelf->Top__DOT__XBar2__DOT___io_axi4in_rvalid_output 
                = vlSelf->Top__DOT__SRAM__DOT__rvalidReg;
        } else {
            vlSelf->Top__DOT___XBar2_io_axi4in_arready 
                = ((2U != (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w)) 
                   & (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_8));
            vlSelf->Top__DOT__XBar2__DOT__casez_tmp_7 
                = ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                    ? (3U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))
                    : (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_23));
            vlSelf->Top__DOT__XBar2__DOT___io_axi4in_rvalid_output 
                = ((2U != (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w)) 
                   & (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_9));
        }
        vlSelf->Top__DOT___XBar2_io_axi4out1_arvalid 
            = ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_18) 
               & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_arvalid));
        vlSelf->Top__DOT___XBar2_io_axi4out1_awvalid 
            = ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_18) 
               & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid));
    }
    vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0 = ((0U 
                                                  == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r))
                                                  ? 
                                                 ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_3)
                                                   ? 0U
                                                   : 3U)
                                                  : 0U);
    vlSelf->Top__DOT___XBar2_io_axi4out0_awvalid = 
        ((IData)(vlSelf->Top__DOT__XBar2__DOT____VdfgTmp_hd6eae8a8__0) 
         & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid));
    vlSelf->Top__DOT__Decoder__DOT___GEN_73 = ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h8d1c1e58__0) 
                                               | ((0x13U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                  | ((0x113U 
                                                      == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                     | ((0x193U 
                                                         == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                        | ((0x67U 
                                                            == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                           | (0x1bU 
                                                              == (IData)(vlSelf->Top__DOT___GEN_1)))))));
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_hf6825b5d__0 
        = ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74) 
           | (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h8d1c1e58__0));
    vlSelf->Top__DOT__Decoder__DOT___GEN_67 = ((0x33U 
                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                               | ((0x8033U 
                                                   == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                  | ((0x3bU 
                                                      == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                     | ((0x803bU 
                                                         == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                        | ((0xb3U 
                                                            == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                           | ((0xbbU 
                                                               == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                              | ((0x3b3U 
                                                                  == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                 | ((0x1b3U 
                                                                     == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                    | ((0x333U 
                                                                        == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                       | ((0x233U 
                                                                           == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                          | ((0x433U 
                                                                              == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                             | ((0x4b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x43bU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x5b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x6b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x633U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x63bU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x6bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x733U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x7b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x73bU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x7bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x133U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x82b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x82bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x2b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | (0x2bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)))))))))))))))))))))))))));
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h24b557b3__0 
        = ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71) 
           | (0x33U == vlSelf->Top__DOT__Decoder__DOT___GEN_29));
    vlSelf->Top__DOT__Decoder__DOT___GEN_75 = ((0x13U 
                                                == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                               | ((0x113U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                  | ((0x193U 
                                                      == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                     | ((0x67U 
                                                         == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                        | ((0x1bU 
                                                            == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                           | ((0x4293U 
                                                               == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                              | ((0x393U 
                                                                  == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                                 | ((0x313U 
                                                                     == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                                    | ((0x213U 
                                                                        == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                                       | ((0x93U 
                                                                           == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                                          | ((0x293U 
                                                                              == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                                             | ((0x9bU 
                                                                                == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                                                | ((0x429bU 
                                                                                == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                                                | ((0x29bU 
                                                                                == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                                                | (0x6fU 
                                                                                == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))))))))))))))));
    vlSelf->Top__DOT__Decoder__DOT___GEN_68 = ((0x9bU 
                                                == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                               | ((0x429bU 
                                                   == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                  | (0x29bU 
                                                     == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))));
    __Vtemp_hb1f78123__0[0U] = (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp);
    __Vtemp_hb1f78123__0[1U] = (IData)((vlSelf->Top__DOT__ALU__DOT__casez_tmp 
                                        >> 0x20U));
    __Vtemp_hb1f78123__0[2U] = (1U & (IData)((vlSelf->Top__DOT__ALU__DOT__casez_tmp 
                                              >> 0x3fU)));
    __Vtemp_hd4884bb4__0[0U] = (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0);
    __Vtemp_hd4884bb4__0[1U] = (IData)((vlSelf->Top__DOT__ALU__DOT__casez_tmp_0 
                                        >> 0x20U));
    __Vtemp_hd4884bb4__0[2U] = (1U & (IData)((vlSelf->Top__DOT__ALU__DOT__casez_tmp_0 
                                              >> 0x3fU)));
    VL_DIVS_WWW(65, __Vtemp_h58a7e692__0, __Vtemp_hb1f78123__0, __Vtemp_hd4884bb4__0);
    vlSelf->Top__DOT__ALU__DOT__casez_tmp_1 = ((0x10U 
                                                & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                ? (
                                                   (8U 
                                                    & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                    ? 0ULL
                                                    : 
                                                   ((4U 
                                                     & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? (QData)((IData)(
                                                                         VL_MODDIV_III(32, (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp), (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0))))
                                                       : (QData)((IData)(
                                                                         VL_MODDIVS_III(32, (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp), (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)))))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? (QData)((IData)(
                                                                         ((0x1fU 
                                                                           >= 
                                                                           (0x1fU 
                                                                            & (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)))
                                                                           ? 
                                                                          ((IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp) 
                                                                           >> 
                                                                           (0x1fU 
                                                                            & (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)))
                                                                           : 0U)))
                                                       : (QData)((IData)(
                                                                         ((0x1fU 
                                                                           >= 
                                                                           (0x1fU 
                                                                            & (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)))
                                                                           ? 
                                                                          VL_SHIFTRS_III(32,32,32, (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp), 
                                                                                (0x1fU 
                                                                                & (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)))
                                                                           : 
                                                                          (- 
                                                                           ((IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp) 
                                                                            >> 0x1fU)))))))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? vlSelf->Top__DOT__ALU__DOT____VdfgExtracted_h750bc5e8__0
                                                       : 
                                                      VL_MODDIVS_QQQ(64, vlSelf->Top__DOT__ALU__DOT__casez_tmp, vlSelf->Top__DOT__ALU__DOT__casez_tmp_0))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? 
                                                      VL_MODDIV_QQQ(64, vlSelf->Top__DOT__ALU__DOT__casez_tmp, vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)
                                                       : 
                                                      VL_DIV_QQQ(64, vlSelf->Top__DOT__ALU__DOT__casez_tmp, vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)))))
                                                : (
                                                   (8U 
                                                    & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                    ? 
                                                   ((4U 
                                                     & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? 
                                                      (((QData)((IData)(
                                                                        __Vtemp_h58a7e692__0[1U])) 
                                                        << 0x20U) 
                                                       | (QData)((IData)(
                                                                         __Vtemp_h58a7e692__0[0U])))
                                                       : vlSelf->Top__DOT__ALU__DOT____VdfgExtracted_h750bc5e8__0)
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? vlSelf->Top__DOT__ALU__DOT___GEN
                                                       : 
                                                      (vlSelf->Top__DOT__ALU__DOT__casez_tmp 
                                                       - vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? 
                                                      (vlSelf->Top__DOT__ALU__DOT__casez_tmp 
                                                       ^ vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)
                                                       : 
                                                      (vlSelf->Top__DOT__ALU__DOT__casez_tmp 
                                                       | vlSelf->Top__DOT__ALU__DOT__casez_tmp_0))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? 
                                                      (vlSelf->Top__DOT__ALU__DOT__casez_tmp 
                                                       & vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)
                                                       : 
                                                      (vlSelf->Top__DOT__ALU__DOT__casez_tmp 
                                                       << 
                                                       (0x3fU 
                                                        & (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0))))))
                                                    : 
                                                   ((4U 
                                                     & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                     ? 
                                                    ((2U 
                                                      & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? 
                                                      VL_SHIFTR_QQQ(64,64,64, vlSelf->Top__DOT__ALU__DOT__casez_tmp, (QData)((IData)(
                                                                                (0x3fU 
                                                                                & (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)))))
                                                       : 
                                                      VL_SHIFTRS_QQQ(64,64,64, vlSelf->Top__DOT__ALU__DOT__casez_tmp, (QData)((IData)(
                                                                                (0x3fU 
                                                                                & (IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0))))))
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? (QData)((IData)(
                                                                         (vlSelf->Top__DOT__ALU__DOT__casez_tmp 
                                                                          < vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)))
                                                       : (QData)((IData)(
                                                                         VL_LTS_IQQ(64, vlSelf->Top__DOT__ALU__DOT__casez_tmp, vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)))))
                                                     : 
                                                    ((2U 
                                                      & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                      ? 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? 
                                                      (4ULL 
                                                       + vlSelf->Top__DOT____Vcellinp__ALU__io_pc)
                                                       : 0ULL)
                                                      : 
                                                     ((1U 
                                                       & (IData)(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op))
                                                       ? 
                                                      (vlSelf->Top__DOT__ALU__DOT__casez_tmp 
                                                       + vlSelf->Top__DOT__ALU__DOT__casez_tmp_0)
                                                       : 0ULL)))));
    vlSelf->__Vtableidx1 = ((((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                               ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
                                  & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready))
                               : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_18) 
                                  & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready))) 
                             << 3U) | (((IData)(vlSelf->Top__DOT___XBar2_io_axi4out1_awvalid) 
                                        << 2U) | (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state)));
    vlSelf->Top__DOT__SRAM__DOT__casez_tmp = VTop__ConstPool__TABLE_ha024a6da_0
        [vlSelf->__Vtableidx1];
    vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_bvalid 
        = ((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0) 
           & (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_7));
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_hfe7a8b0a__0 
        = ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_hf6825b5d__0) 
           | (0x13U == (IData)(vlSelf->Top__DOT___GEN_1)));
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h92124dc1__0 
        = ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h24b557b3__0) 
           | ((0x8033U == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
              | ((0x3bU == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                 | ((0x803bU == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                    | ((0xb3U == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                       | ((0xbbU == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                          | ((0x3b3U == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                             | ((0x1b3U == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                | ((0x333U == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                   | ((0x233U == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                      | ((0x433U == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                         | ((0x4b3U 
                                             == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                            | ((0x43bU 
                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                               | ((0x5b3U 
                                                   == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                  | ((0x6b3U 
                                                      == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                     | ((0x633U 
                                                         == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                        | ((0x63bU 
                                                            == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                           | ((0x6bbU 
                                                               == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                              | ((0x733U 
                                                                  == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                 | ((0x7b3U 
                                                                     == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                    | ((0x73bU 
                                                                        == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                       | ((0x7bbU 
                                                                           == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                          | ((0x133U 
                                                                              == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                             | ((0x82b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x82bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x2b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x2bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66))))))))))))))))))))))))))));
    vlSelf->Top__DOT__Decoder__DOT___GEN_76 = ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_hf6825b5d__0) 
                                               | (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_75));
    vlSelf->Top__DOT__Decoder__DOT___GEN_69 = ((0x93U 
                                                == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                               | ((0x293U 
                                                   == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                  | (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_68)));
    vlSelf->Top__DOT___AXI4Arbiter_io_ifu_bus_axi4_rvalid 
        = ((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h4ab110e3__0) 
           & (IData)(vlSelf->Top__DOT__XBar2__DOT___io_axi4in_rvalid_output));
    vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_rvalid 
        = ((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0) 
           & (IData)(vlSelf->Top__DOT__XBar2__DOT___io_axi4in_rvalid_output));
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_6 = ((3U 
                                                   == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state)) 
                                                  & ((7U 
                                                      == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)) 
                                                     & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_bvalid)));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_8 
        = ((7U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)) 
           & ((IData)(vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_bvalid) 
              & (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac)));
    vlSelf->Top__DOT___Decoder_io_isword = ((~ ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_hfe7a8b0a__0) 
                                                | ((0x113U 
                                                    == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                   | ((0x193U 
                                                       == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                      | (0x67U 
                                                         == (IData)(vlSelf->Top__DOT___GEN_1)))))) 
                                            & ((0x1bU 
                                                == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                               | ((~ 
                                                   ((0x4293U 
                                                     == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                    | ((0x393U 
                                                        == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                       | ((0x313U 
                                                           == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                          | ((0x213U 
                                                              == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                             | ((0x93U 
                                                                 == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                                | (0x293U 
                                                                   == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)))))))) 
                                                  & ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_68) 
                                                     | ((~ 
                                                         ((0x6fU 
                                                           == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
                                                          | ((0x23U 
                                                              == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                             | ((0xa3U 
                                                                 == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                                | ((0x123U 
                                                                    == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                                   | ((0x1a3U 
                                                                       == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                                      | ((0x33U 
                                                                          == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                         | (0x8033U 
                                                                            == vlSelf->Top__DOT__Decoder__DOT___GEN_29)))))))) 
                                                        & ((0x3bU 
                                                            == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                           | ((0x803bU 
                                                               == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                              | ((0xb3U 
                                                                  != vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                 & ((0xbbU 
                                                                     == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                    | ((~ 
                                                                        ((0x3b3U 
                                                                          == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                         | ((0x1b3U 
                                                                             == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                            | ((0x333U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                               | ((0x233U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x433U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | (0x4b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29))))))) 
                                                                       & ((0x43bU 
                                                                           == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                          | ((~ 
                                                                              ((0x5b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                               | ((0x6b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | (0x633U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)))) 
                                                                             & ((0x63bU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x6bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((~ 
                                                                                ((0x733U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | (0x7b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29))) 
                                                                                & ((0x73bU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x7bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((~ 
                                                                                ((0x133U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | (0x82b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29))) 
                                                                                & ((0x82bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                | ((0x2b3U 
                                                                                != vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                                & (0x2bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)))))))))))))))))))));
    vlSelf->Top__DOT___Decoder_io_alu_op = ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_hfe7a8b0a__0)
                                             ? 1U : 
                                            ((0x113U 
                                              == (IData)(vlSelf->Top__DOT___GEN_1))
                                              ? 4U : 
                                             ((0x193U 
                                               == (IData)(vlSelf->Top__DOT___GEN_1))
                                               ? 5U
                                               : ((0x67U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1))
                                                   ? 3U
                                                   : 
                                                  ((0x1bU 
                                                    == (IData)(vlSelf->Top__DOT___GEN_1))
                                                    ? 1U
                                                    : 
                                                   ((0x4293U 
                                                     == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                     ? 6U
                                                     : 
                                                    ((0x393U 
                                                      == (IData)(vlSelf->Top__DOT___GEN_1))
                                                      ? 9U
                                                      : 
                                                     ((0x313U 
                                                       == (IData)(vlSelf->Top__DOT___GEN_1))
                                                       ? 0xaU
                                                       : 
                                                      ((0x213U 
                                                        == (IData)(vlSelf->Top__DOT___GEN_1))
                                                        ? 0xbU
                                                        : 
                                                       ((0x93U 
                                                         == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                         ? 8U
                                                         : 
                                                        ((0x293U 
                                                          == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                          ? 7U
                                                          : 
                                                         ((0x9bU 
                                                           == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                           ? 8U
                                                           : 
                                                          ((0x429bU 
                                                            == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                            ? 0x14U
                                                            : 
                                                           ((0x29bU 
                                                             == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                             ? 0x15U
                                                             : 
                                                            ((0x6fU 
                                                              == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                                              ? 3U
                                                              : 
                                                             ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h24b557b3__0)
                                                               ? 1U
                                                               : 
                                                              ((0x8033U 
                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                ? 0xcU
                                                                : 
                                                               ((0x3bU 
                                                                 == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                 ? 1U
                                                                 : 
                                                                ((0x803bU 
                                                                  == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                  ? 0xcU
                                                                  : 
                                                                 (((0xb3U 
                                                                    == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                   | (0xbbU 
                                                                      == vlSelf->Top__DOT__Decoder__DOT___GEN_29))
                                                                   ? 8U
                                                                   : 
                                                                  ((0x3b3U 
                                                                    == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                    ? 9U
                                                                    : 
                                                                   ((0x1b3U 
                                                                     == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                     ? 5U
                                                                     : 
                                                                    ((0x333U 
                                                                      == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                      ? 0xaU
                                                                      : 
                                                                     ((0x233U 
                                                                       == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                       ? 0xbU
                                                                       : 
                                                                      ((0x433U 
                                                                        == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                        ? 0xdU
                                                                        : 
                                                                       ((0x4b3U 
                                                                         == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                         ? 0xeU
                                                                         : 
                                                                        ((0x43bU 
                                                                          == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                          ? 0xdU
                                                                          : 
                                                                         ((0x5b3U 
                                                                           == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                           ? 0x13U
                                                                           : 
                                                                          ((0x6b3U 
                                                                            == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                            ? 0x10U
                                                                            : 
                                                                           (((0x633U 
                                                                              == vlSelf->Top__DOT__Decoder__DOT___GEN_29) 
                                                                             | (0x63bU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29))
                                                                             ? 0xfU
                                                                             : 
                                                                            ((0x6bbU 
                                                                              == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                              ? 0x10U
                                                                              : 
                                                                             ((0x733U 
                                                                               == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                               ? 0x12U
                                                                               : 
                                                                              ((0x7b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                                ? 0x11U
                                                                                : 
                                                                               ((0x73bU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                                 ? 0x16U
                                                                                 : 
                                                                                ((0x7bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                                 ? 0x17U
                                                                                 : 
                                                                                ((0x133U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                                 ? 4U
                                                                                 : 
                                                                                ((0x82b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                                 ? 6U
                                                                                 : 
                                                                                ((0x82bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                                 ? 0x14U
                                                                                 : 
                                                                                ((0x2b3U 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                                 ? 7U
                                                                                 : 
                                                                                ((0x2bbU 
                                                                                == vlSelf->Top__DOT__Decoder__DOT___GEN_29)
                                                                                 ? 0x15U
                                                                                 : 
                                                                                ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66) 
                                                                                | (IData)(vlSelf->Top__DOT___Decoder_io_csr_en))))))))))))))))))))))))))))))))))))))))));
    vlSelf->Top__DOT__Decoder__DOT__casez_tmp = (((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)
                                                   ? 0U
                                                   : 
                                                  ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_73)
                                                    ? 0U
                                                    : 
                                                   ((0x4293U 
                                                     == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                     ? 0U
                                                     : 
                                                    ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_72)
                                                      ? 0U
                                                      : 
                                                     ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_69)
                                                       ? 0U
                                                       : 
                                                      ((0x6fU 
                                                        == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                                        ? 0U
                                                        : 
                                                       ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71)
                                                         ? 4U
                                                         : 
                                                        ((1U 
                                                          & ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_67) 
                                                             | (~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66))))
                                                          ? 0U
                                                          : 4U))))))))
                                                  ? 
                                                 (((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)
                                                    ? 2U
                                                    : 
                                                   ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_73)
                                                     ? 0U
                                                     : 
                                                    ((0x4293U 
                                                      == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                      ? 0U
                                                      : 
                                                     ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_72)
                                                       ? 0U
                                                       : 
                                                      ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_69)
                                                        ? 0U
                                                        : 
                                                       ((0x6fU 
                                                         == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                                         ? 2U
                                                         : 0U))))))
                                                   ? 0ULL
                                                   : 
                                                  (((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)
                                                     ? 1U
                                                     : 
                                                    ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_73)
                                                      ? 1U
                                                      : 
                                                     ((0x4293U 
                                                       == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                       ? 0U
                                                       : 
                                                      ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_72)
                                                        ? 1U
                                                        : 
                                                       ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_69)
                                                         ? 0U
                                                         : 
                                                        ((0x6fU 
                                                          == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                                          ? 0U
                                                          : 
                                                         ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71)
                                                           ? 0U
                                                           : 
                                                          ((1U 
                                                            & ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_67) 
                                                               | (~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66))))
                                                            ? 0U
                                                            : 1U))))))))
                                                    ? 
                                                   (((- (QData)((IData)(
                                                                        (vlSelf->Top__DOT___GEN_0 
                                                                         >> 0x1fU)))) 
                                                     << 0xcU) 
                                                    | (QData)((IData)(
                                                                      ((0x800U 
                                                                        & (vlSelf->Top__DOT___GEN_0 
                                                                           << 4U)) 
                                                                       | ((0x7e0U 
                                                                           & (vlSelf->Top__DOT___GEN_0 
                                                                              >> 0x14U)) 
                                                                          | (0x1eU 
                                                                             & (vlSelf->Top__DOT___GEN_0 
                                                                                >> 7U)))))))
                                                    : 
                                                   (((- (QData)((IData)(
                                                                        (vlSelf->Top__DOT___GEN_0 
                                                                         >> 0x1fU)))) 
                                                     << 0xcU) 
                                                    | (QData)((IData)(
                                                                      ((0xfe0U 
                                                                        & (vlSelf->Top__DOT___GEN_0 
                                                                           >> 0x14U)) 
                                                                       | (0x1fU 
                                                                          & (vlSelf->Top__DOT___GEN_0 
                                                                             >> 7U))))))))
                                                  : 
                                                 (((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)
                                                    ? 2U
                                                    : 
                                                   ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_73)
                                                     ? 0U
                                                     : 
                                                    ((0x4293U 
                                                      == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                      ? 0U
                                                      : 
                                                     ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_72)
                                                       ? 0U
                                                       : 
                                                      ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_69)
                                                        ? 0U
                                                        : 
                                                       ((0x6fU 
                                                         == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                                         ? 2U
                                                         : 0U))))))
                                                   ? 
                                                  (((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)
                                                     ? 1U
                                                     : 
                                                    ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_73)
                                                      ? 1U
                                                      : 
                                                     ((0x4293U 
                                                       == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                       ? 0U
                                                       : 
                                                      ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_72)
                                                        ? 1U
                                                        : 
                                                       ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_69)
                                                         ? 0U
                                                         : 
                                                        ((0x6fU 
                                                          == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                                          ? 0U
                                                          : 
                                                         ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71)
                                                           ? 0U
                                                           : 
                                                          ((1U 
                                                            & ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_67) 
                                                               | (~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66))))
                                                            ? 0U
                                                            : 1U))))))))
                                                    ? 
                                                   (((QData)((IData)(
                                                                     (- (IData)(
                                                                                (vlSelf->Top__DOT___GEN_0 
                                                                                >> 0x1fU))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(
                                                                      (0xfffff000U 
                                                                       & vlSelf->Top__DOT___GEN_0))))
                                                    : 
                                                   (((- (QData)((IData)(
                                                                        (vlSelf->Top__DOT___GEN_0 
                                                                         >> 0x1fU)))) 
                                                     << 0x14U) 
                                                    | (QData)((IData)(
                                                                      ((0xff000U 
                                                                        & vlSelf->Top__DOT___GEN_0) 
                                                                       | ((0x800U 
                                                                           & (vlSelf->Top__DOT___GEN_0 
                                                                              >> 9U)) 
                                                                          | (0x7feU 
                                                                             & (vlSelf->Top__DOT___GEN_0 
                                                                                >> 0x14U))))))))
                                                   : 
                                                  (((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)
                                                     ? 1U
                                                     : 
                                                    ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_73)
                                                      ? 1U
                                                      : 
                                                     ((0x4293U 
                                                       == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                                       ? 0U
                                                       : 
                                                      ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_72)
                                                        ? 1U
                                                        : 
                                                       ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_69)
                                                         ? 0U
                                                         : 
                                                        ((0x6fU 
                                                          == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                                          ? 0U
                                                          : 
                                                         ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71)
                                                           ? 0U
                                                           : 
                                                          ((1U 
                                                            & ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_67) 
                                                               | (~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66))))
                                                            ? 0U
                                                            : 1U))))))))
                                                    ? 
                                                   (((- (QData)((IData)(
                                                                        (vlSelf->Top__DOT___GEN_0 
                                                                         >> 0x1fU)))) 
                                                     << 0xcU) 
                                                    | (QData)((IData)(
                                                                      (vlSelf->Top__DOT___GEN_0 
                                                                       >> 0x14U))))
                                                    : 0ULL)));
    vlSelf->Top__DOT__Decoder__DOT___GEN_70 = ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_73) 
                                               | ((0x4293U 
                                                   == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14)) 
                                                  | ((0x393U 
                                                      == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                     | ((0x313U 
                                                         == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                        | ((0x213U 
                                                            == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                           | (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_69))))));
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_7 = ((4U 
                                                   == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state)) 
                                                  & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_ifu_bus_axi4_rvalid));
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_3 
        = ((4U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state)) 
           & ((IData)(vlSelf->Top__DOT___AXI4Arbiter_io_ifu_bus_axi4_rvalid) 
              & (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__ifu_ac)));
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_5 = ((5U 
                                                   == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)) 
                                                  & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_rvalid));
    if ((0U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))) {
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_0 = 0ULL;
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_5 
            = (((~ (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__reqr_reg)) 
                & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__reqr_reg) 
                   | (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__reqw_reg))) 
               | (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac));
    } else if ((1U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))) {
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_0 
            = vlSelf->Top__DOT__XBar2__DOT__casez_tmp_2;
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_5 
            = vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac;
    } else {
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_0 = 0ULL;
        vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_5 
            = ((2U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
                ? ((~ (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_5)) 
                   & (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac))
                : ((~ (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_6)) 
                   & (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac)));
    }
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_2 
        = ((IData)(vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_rvalid) 
           & (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_9 
        = ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT____VdfgTmp_ha260658d__0) 
           & ((~ ((0x80000000U > vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr) 
                  | (0x88000000U < vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr))) 
              & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_8)));
    if (vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_8) {
        vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_10 = 0U;
        vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_bvalid 
            = vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT____VdfgTmp_ha260658d__0;
    } else {
        vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_10 
            = vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state;
        vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_bvalid = 0U;
    }
    vlSelf->Top__DOT__stall = ((((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)) 
                                 & ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_70) 
                                    | ((0x6fU != (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
                                       & ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h92124dc1__0) 
                                          | (IData)(vlSelf->Top__DOT___Decoder_io_csr_en))))) 
                                & ((IData)(vlSelf->Top__DOT__IDReg_valid) 
                                   & ((0U != (0x1fU 
                                              & (vlSelf->Top__DOT__IDReg_inst 
                                                 >> 0xfU))) 
                                      & ((((IData)(vlSelf->Top__DOT___Decoder_io_rs1) 
                                           == (IData)(vlSelf->Top__DOT___EX_RS2_Hazard_T)) 
                                          & (IData)(vlSelf->Top__DOT__EXReg_rden)) 
                                         | ((((IData)(vlSelf->Top__DOT___Decoder_io_rs1) 
                                              == (IData)(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_rd)) 
                                             & (IData)(vlSelf->Top__DOT__LSReg_rden)) 
                                            | ((((IData)(vlSelf->Top__DOT___Decoder_io_rs1) 
                                                 == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__rdreg)) 
                                                & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__rdenreg)) 
                                               | (((IData)(vlSelf->Top__DOT___Decoder_io_rs1) 
                                                   == (IData)(vlSelf->Top__DOT___WB_RS2_Hazard_T)) 
                                                  & (IData)(vlSelf->Top__DOT__WBReg_rden)))))))) 
                               | ((((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_76)) 
                                    & (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h92124dc1__0)) 
                                   & ((IData)(vlSelf->Top__DOT__IDReg_valid) 
                                      & ((0U != (0x1fU 
                                                 & (vlSelf->Top__DOT__IDReg_inst 
                                                    >> 0x14U))) 
                                         & ((((IData)(vlSelf->Top__DOT___Decoder_io_rs2) 
                                              == (IData)(vlSelf->Top__DOT___EX_RS2_Hazard_T)) 
                                             & (IData)(vlSelf->Top__DOT__EXReg_rden)) 
                                            | ((((IData)(vlSelf->Top__DOT___Decoder_io_rs2) 
                                                 == (IData)(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_rd)) 
                                                & (IData)(vlSelf->Top__DOT__LSReg_rden)) 
                                               | ((((IData)(vlSelf->Top__DOT___Decoder_io_rs2) 
                                                    == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__rdreg)) 
                                                   & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__rdenreg)) 
                                                  | (((IData)(vlSelf->Top__DOT___Decoder_io_rs2) 
                                                      == (IData)(vlSelf->Top__DOT___WB_RS2_Hazard_T)) 
                                                     & (IData)(vlSelf->Top__DOT__WBReg_rden)))))))) 
                                  | ((IData)(vlSelf->Top__DOT___Decoder_io_csr_en) 
                                     & ((((IData)(vlSelf->Top__DOT__csridx) 
                                          == ((IData)(vlSelf->Top__DOT__EXReg_valid)
                                               ? (IData)(vlSelf->Top__DOT__EXReg_csridx)
                                               : 0U)) 
                                         & (IData)(vlSelf->Top__DOT__EXReg_csr_en)) 
                                        | (((0x73U 
                                             == vlSelf->Top__DOT__EXReg_inst) 
                                            & ((IData)(vlSelf->Top__DOT__EXReg_valid) 
                                               & (IData)(vlSelf->Top__DOT____VdfgTmp_h8812001b__0))) 
                                           | ((((IData)(vlSelf->Top__DOT__csridx) 
                                                == (IData)(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_csridx)) 
                                               & (IData)(vlSelf->Top__DOT__LSReg_csr_en)) 
                                              | (((0x73U 
                                                   == vlSelf->Top__DOT__LSReg_inst) 
                                                  & ((IData)(vlSelf->Top__DOT__LSReg_valid) 
                                                     & (IData)(vlSelf->Top__DOT____VdfgTmp_h8812001b__0))) 
                                                 | ((((IData)(vlSelf->Top__DOT__csridx) 
                                                      == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__csridxreg)) 
                                                     & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__csrenreg)) 
                                                    | (((0x73U 
                                                         == vlSelf->Top__DOT__NPC_Mem__DOT__instreg) 
                                                        & ((IData)(vlSelf->Top__DOT___NPC_Mem_io_out_valid) 
                                                           & (IData)(vlSelf->Top__DOT____VdfgTmp_h8812001b__0))) 
                                                       | ((((IData)(vlSelf->Top__DOT__csridx) 
                                                            == 
                                                            ((IData)(vlSelf->Top__DOT__WBReg_valid)
                                                              ? (IData)(vlSelf->Top__DOT__WBReg_csridx)
                                                              : 0U)) 
                                                           & (IData)(vlSelf->Top__DOT__WBReg_csr_en)) 
                                                          | ((0x73U 
                                                              == vlSelf->Top__DOT__WBReg_inst) 
                                                             & ((IData)(vlSelf->Top__DOT__WBReg_valid) 
                                                                & (IData)(vlSelf->Top__DOT____VdfgTmp_h8812001b__0)))))))))))));
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_4 
        = (1U & ((~ (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_3)) 
                 | (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_1)));
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_2 
        = ((~ ((~ (IData)((0U != (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state)))) 
               | ((1U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state)) 
                  | (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_1)))) 
           & (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_3));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_3 
        = ((5U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)) 
           & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_2));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__casez_tmp 
        = ((4U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))
            ? ((2U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))
                ? ((1U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))
                    ? (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_10)
                    : ((((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0) 
                         & (((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                              ? (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_21)
                              : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                  ? (IData)(vlSelf->Top__DOT___SRAM_io_axi4_awready)
                                  : ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                      ? ((~ (IData)(
                                                    (0U 
                                                     != (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state)))) 
                                         | (1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state)))
                                      : (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_21)))) 
                            & ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                ? (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_22)
                                : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                    ? (1U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))
                                    : ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                        ? (1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))
                                        : (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_22)))))) 
                        & (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac))
                        ? 7U : (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)))
                : ((1U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))
                    ? ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_2)
                        ? 2U : (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))
                    : (((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac) 
                        & ((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0) 
                           & (IData)(vlSelf->Top__DOT___XBar2_io_axi4in_arready)))
                        ? 5U : (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))))
            : ((2U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))
                ? ((1U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))
                    ? 6U : (((2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state)) 
                             | (2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state)))
                             ? 0U : (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)))
                : ((1U & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))
                    ? ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_0)
                        ? 2U : 4U) : (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_10))));
    vlSelf->Top__DOT___NPC_Mem_io_in_ready = (1U & 
                                              (((0U 
                                                 == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state))
                                                 ? 
                                                (~ (IData)(vlSelf->Top__DOT__NPC_Mem__DOT___GEN_0))
                                                 : 
                                                ((1U 
                                                  != (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state)) 
                                                 & ((2U 
                                                     != (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state)) 
                                                    | (2U 
                                                       == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))))) 
                                               & ((0U 
                                                   == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state))
                                                   ? 
                                                  (~ (IData)(vlSelf->Top__DOT__NPC_Mem__DOT___GEN_1))
                                                   : 
                                                  ((1U 
                                                    != (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state)) 
                                                   & ((2U 
                                                       != (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state)) 
                                                      | (IData)(vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_bvalid))))));
    vlSelf->Top__DOT__InstFetcher__DOT___GEN_1 = (1U 
                                                  & ((~ (IData)(vlSelf->Top__DOT__stall)) 
                                                     & (~ (IData)(
                                                                  (0U 
                                                                   != (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state))))));
    vlSelf->Top__DOT__InstFetcher__DOT___GEN_2 = ((2U 
                                                   == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__state)) 
                                                  & ((~ (IData)(vlSelf->Top__DOT__stall)) 
                                                     & (2U 
                                                        == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state))));
    vlSelf->Top__DOT____Vcellinp__InstFetcher__io_in_valid 
        = (1U & ((~ (IData)(vlSelf->Top__DOT__stall)) 
                 & (~ (IData)(vlSelf->reset))));
    vlSelf->Top__DOT__pcsel = ((~ (IData)(vlSelf->Top__DOT__stall)) 
                               & ((0x67U == (IData)(vlSelf->Top__DOT___GEN_1)) 
                                  | ((0x6fU == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
                                     | ((0x63U == (IData)(vlSelf->Top__DOT___GEN_1))
                                         ? (vlSelf->Top__DOT__rs1v 
                                            == vlSelf->Top__DOT__rs2v)
                                         : ((0xe3U 
                                             == (IData)(vlSelf->Top__DOT___GEN_1))
                                             ? (vlSelf->Top__DOT__rs1v 
                                                != vlSelf->Top__DOT__rs2v)
                                             : ((0x2e3U 
                                                 == (IData)(vlSelf->Top__DOT___GEN_1))
                                                 ? 
                                                VL_GTES_IQQ(64, vlSelf->Top__DOT__rs1v, vlSelf->Top__DOT__rs2v)
                                                 : 
                                                ((0x3e3U 
                                                  == (IData)(vlSelf->Top__DOT___GEN_1))
                                                  ? 
                                                 (vlSelf->Top__DOT__rs1v 
                                                  >= vlSelf->Top__DOT__rs2v)
                                                  : 
                                                 ((0x263U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1))
                                                   ? 
                                                  VL_LTS_IQQ(64, vlSelf->Top__DOT__rs1v, vlSelf->Top__DOT__rs2v)
                                                   : 
                                                  ((0x363U 
                                                    == (IData)(vlSelf->Top__DOT___GEN_1))
                                                    ? 
                                                   (vlSelf->Top__DOT__rs1v 
                                                    < vlSelf->Top__DOT__rs2v)
                                                    : 
                                                   ((0x30200073U 
                                                     == vlSelf->Top__DOT___GEN_0) 
                                                    | (0x73U 
                                                       == vlSelf->Top__DOT___GEN_0)))))))))));
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_5 
        = ((~ (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_4)) 
           & ((~ (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__uncached_r)) 
              & (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_3)));
    vlSelf->Top__DOT__IDRegen = ((~ (IData)(vlSelf->Top__DOT__stall)) 
                                 & (IData)(vlSelf->Top__DOT___NPC_Mem_io_in_ready));
    vlSelf->Top__DOT___InstFetcher_io_out_valid = (
                                                   (0U 
                                                    == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__state)) 
                                                   & ((~ (IData)(vlSelf->Top__DOT__pcsel)) 
                                                      & (IData)(vlSelf->Top__DOT__InstFetcher__DOT__dnpc_valid)));
    vlSelf->Top__DOT__InstFetcher__DOT___GEN_3 = ((IData)(vlSelf->Top__DOT__pcsel) 
                                                  & ((~ (IData)(vlSelf->Top__DOT__stall)) 
                                                     & (IData)(vlSelf->Top__DOT____Vcellinp__InstFetcher__io_in_valid)));
    vlSelf->Top__DOT__InstFetcher__DOT___GEN_0 = ((IData)(vlSelf->Top__DOT____Vcellinp__InstFetcher__io_in_valid) 
                                                  & (((~ (IData)(vlSelf->reset)) 
                                                      & (~ (IData)(vlSelf->Top__DOT__stall))) 
                                                     & (IData)(vlSelf->Top__DOT__IDRegen)));
}

VL_ATTR_COLD void VTop___024root___eval_stl(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        VTop___024root___stl_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VTop___024root___dump_triggers__ico(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VicoTriggered.at(0U)) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VTop___024root___dump_triggers__act(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void VTop___024root___dump_triggers__nba(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clock)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void VTop___024root___ctor_var_reset(VTop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clock = 0;
    vlSelf->reset = 0;
    vlSelf->io_inst = 0;
    vlSelf->io_pc = 0;
    vlSelf->io_npc = 0;
    vlSelf->Top__DOT__pcsel = 0;
    vlSelf->Top__DOT__IDRegen = 0;
    vlSelf->Top__DOT___GEN_0 = 0;
    vlSelf->Top__DOT___NPC_Mem_io_in_ready = 0;
    vlSelf->Top__DOT___NPC_Mem_io_out_valid = 0;
    vlSelf->Top__DOT___Decoder_io_rs1 = 0;
    vlSelf->Top__DOT___Decoder_io_rs2 = 0;
    vlSelf->Top__DOT___Decoder_io_csr_en = 0;
    vlSelf->Top__DOT___Decoder_io_alu_op = 0;
    vlSelf->Top__DOT___Decoder_io_isword = 0;
    vlSelf->Top__DOT___R_ext_R0_data = 0;
    vlSelf->Top__DOT___R_ext_R1_data = 0;
    vlSelf->Top__DOT___InstFetcher_io_out_valid = 0;
    vlSelf->Top__DOT___XBar2_io_axi4in_arready = 0;
    vlSelf->Top__DOT___XBar2_io_axi4out0_awvalid = 0;
    vlSelf->Top__DOT___XBar2_io_axi4out1_arvalid = 0;
    vlSelf->Top__DOT___XBar2_io_axi4out1_awvalid = 0;
    vlSelf->Top__DOT___XBar2_io_axi4out2_arvalid = 0;
    vlSelf->Top__DOT___SRAM_io_axi4_arready = 0;
    vlSelf->Top__DOT___SRAM_io_axi4_awready = 0;
    vlSelf->Top__DOT___AXI4Arbiter_io_ifu_bus_axi4_rvalid = 0;
    vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_rdata = 0;
    vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_rvalid = 0;
    vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_bvalid = 0;
    vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_arvalid = 0;
    vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready = 0;
    vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid = 0;
    vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready = 0;
    vlSelf->Top__DOT__IDReg_valid = 0;
    vlSelf->Top__DOT__IDReg_inst = 0;
    vlSelf->Top__DOT__IDReg_pc = 0;
    vlSelf->Top__DOT__EXReg_valid = 0;
    vlSelf->Top__DOT__EXReg_inst = 0;
    vlSelf->Top__DOT__EXReg_pc = 0;
    vlSelf->Top__DOT__EXReg_rs1v = 0;
    vlSelf->Top__DOT__EXReg_rs2v = 0;
    vlSelf->Top__DOT__EXReg_csridx = 0;
    vlSelf->Top__DOT__EXReg_csrrv = 0;
    vlSelf->Top__DOT__EXReg_csrwv = 0;
    vlSelf->Top__DOT__EXReg_csr_en = 0;
    vlSelf->Top__DOT__EXReg_imm = 0;
    vlSelf->Top__DOT__EXReg_dataAsel = 0;
    vlSelf->Top__DOT__EXReg_dataBsel = 0;
    vlSelf->Top__DOT__EXReg_aluop = 0;
    vlSelf->Top__DOT__EXReg_memvalid = 0;
    vlSelf->Top__DOT__EXReg_memwen = 0;
    vlSelf->Top__DOT__EXReg_memwmask = 0;
    vlSelf->Top__DOT__EXReg_memsext = 0;
    vlSelf->Top__DOT__EXReg_isEbreak = 0;
    vlSelf->Top__DOT__EXReg_isword = 0;
    vlSelf->Top__DOT__EXReg_rden = 0;
    vlSelf->Top__DOT__EXReg_rd = 0;
    vlSelf->Top__DOT__LSReg_valid = 0;
    vlSelf->Top__DOT__LSReg_inst = 0;
    vlSelf->Top__DOT__LSReg_pc = 0;
    vlSelf->Top__DOT__LSReg_alures = 0;
    vlSelf->Top__DOT__LSReg_rs2v = 0;
    vlSelf->Top__DOT__LSReg_csridx = 0;
    vlSelf->Top__DOT__LSReg_csrwv = 0;
    vlSelf->Top__DOT__LSReg_csr_en = 0;
    vlSelf->Top__DOT__LSReg_memvalid = 0;
    vlSelf->Top__DOT__LSReg_memwen = 0;
    vlSelf->Top__DOT__LSReg_memwmask = 0;
    vlSelf->Top__DOT__LSReg_memsext = 0;
    vlSelf->Top__DOT__LSReg_rden = 0;
    vlSelf->Top__DOT__LSReg_rd = 0;
    vlSelf->Top__DOT__WBReg_valid = 0;
    vlSelf->Top__DOT__WBReg_inst = 0;
    vlSelf->Top__DOT__WBReg_pc = 0;
    vlSelf->Top__DOT__WBReg_alures = 0;
    vlSelf->Top__DOT__WBReg_csridx = 0;
    vlSelf->Top__DOT__WBReg_csrwv = 0;
    vlSelf->Top__DOT__WBReg_csr_en = 0;
    vlSelf->Top__DOT__WBReg_rden = 0;
    vlSelf->Top__DOT__WBReg_rd = 0;
    vlSelf->Top__DOT__WBReg_memvalid = 0;
    vlSelf->Top__DOT__WBReg_memsext = 0;
    vlSelf->Top__DOT__WBReg_rdata = 0;
    vlSelf->Top__DOT__ISReg_valid = 0;
    vlSelf->Top__DOT__ISReg_inst = 0;
    vlSelf->Top__DOT__ISReg_pc = 0;
    vlSelf->Top__DOT__mstatus = 0;
    vlSelf->Top__DOT__mtvec = 0;
    vlSelf->Top__DOT__mepc = 0;
    vlSelf->Top__DOT__mcause = 0;
    vlSelf->Top__DOT__rs2v = 0;
    vlSelf->Top__DOT__rs1v = 0;
    vlSelf->Top__DOT__csridx = 0;
    vlSelf->Top__DOT___GEN_1 = 0;
    vlSelf->Top__DOT___GEN_2 = 0;
    vlSelf->Top__DOT___GEN_3 = 0;
    vlSelf->Top__DOT___EX_RS2_Hazard_T = 0;
    vlSelf->Top__DOT___WB_RS2_Hazard_T = 0;
    vlSelf->Top__DOT__stall = 0;
    vlSelf->Top__DOT____Vcellinp__InstFetcher__io_in_valid = 0;
    vlSelf->Top__DOT____Vcellinp__ALU__io_imm = 0;
    vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op = 0;
    vlSelf->Top__DOT____Vcellinp__ALU__io_bsel = 0;
    vlSelf->Top__DOT____Vcellinp__ALU__io_asel = 0;
    vlSelf->Top__DOT____Vcellinp__ALU__io_pc = 0;
    vlSelf->Top__DOT____Vcellinp__ALU__io_csrrv = 0;
    vlSelf->Top__DOT____Vcellinp__ALU__io_rs2v = 0;
    vlSelf->Top__DOT____Vcellinp__ALU__io_rs1v = 0;
    vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_csridx = 0;
    vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_rd = 0;
    vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wdata = 0;
    vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wmask = 0;
    vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wen = 0;
    vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_memvalid = 0;
    vlSelf->Top__DOT____VdfgTmp_h8812001b__0 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_0 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_4 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_5 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT__state = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT__ifu_ac = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_0 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_1 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_3 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_5 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_6 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_7 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h4ab110e3__0 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0 = 0;
    vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h64195d75__0 = 0;
    vlSelf->Top__DOT__SRAM__DOT___dpic_mem_rdata = 0;
    vlSelf->Top__DOT__SRAM__DOT__casez_tmp = 0;
    vlSelf->Top__DOT__SRAM__DOT__r_state = 0;
    vlSelf->Top__DOT__SRAM__DOT__delay = 0;
    vlSelf->Top__DOT__SRAM__DOT__delayCounter = 0;
    vlSelf->Top__DOT__SRAM__DOT__delayDone = 0;
    vlSelf->Top__DOT__SRAM__DOT__readData = 0;
    vlSelf->Top__DOT__SRAM__DOT__readAddr = 0;
    vlSelf->Top__DOT__SRAM__DOT__rvalidReg = 0;
    vlSelf->Top__DOT__SRAM__DOT__w_state = 0;
    vlSelf->Top__DOT__SRAM__DOT__writeAddr = 0;
    vlSelf->Top__DOT__SRAM__DOT__writeData = 0;
    vlSelf->Top__DOT__SRAM__DOT__writeStrb = 0;
    vlSelf->Top__DOT__SRAM__DOT___GEN = 0;
    vlSelf->Top__DOT__SRAM__DOT___GEN_0 = 0;
    vlSelf->Top__DOT__XBar2__DOT__casez_tmp = 0;
    vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0 = 0;
    vlSelf->Top__DOT__XBar2__DOT__casez_tmp_2 = 0;
    vlSelf->Top__DOT__XBar2__DOT__casez_tmp_7 = 0;
    vlSelf->Top__DOT__XBar2__DOT__state_r = 0;
    vlSelf->Top__DOT__XBar2__DOT__state_w = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_0 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_1 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_2 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_3 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_4 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_5 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_6 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_7 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_8 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_9 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_10 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_11 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_13 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_15 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_16 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_17 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_18 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_19 = 0;
    vlSelf->Top__DOT__XBar2__DOT___io_axi4in_rvalid_output = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_20 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_21 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_22 = 0;
    vlSelf->Top__DOT__XBar2__DOT___GEN_23 = 0;
    vlSelf->Top__DOT__XBar2__DOT____VdfgTmp_hd6eae8a8__0 = 0;
    vlSelf->Top__DOT__XBar2__DOT____VdfgTmp_hb75ae2a2__0 = 0;
    vlSelf->Top__DOT__MyUart__DOT__w_state = 0;
    vlSelf->Top__DOT__MyUart__DOT__writeData = 0;
    vlSelf->Top__DOT__MyUart__DOT___io_axi4_wready_T = 0;
    vlSelf->Top__DOT__MyUart__DOT___GEN = 0;
    vlSelf->Top__DOT__MyClint__DOT__r_state = 0;
    vlSelf->Top__DOT__MyClint__DOT__mtime_csr = 0;
    vlSelf->Top__DOT__MyClint__DOT__rdata = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__state = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__PC = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__readAddr = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__outAddr = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__outData = 0;
    vlSelf->Top__DOT__InstFetcher__DOT___icache_io_io_raddr_valid_T = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__dnpc_reg = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__dnpc_valid = 0;
    vlSelf->Top__DOT__InstFetcher__DOT___io_out_valid_T = 0;
    vlSelf->Top__DOT__InstFetcher__DOT___GEN_0 = 0;
    vlSelf->Top__DOT__InstFetcher__DOT___GEN_1 = 0;
    vlSelf->Top__DOT__InstFetcher__DOT___GEN_2 = 0;
    vlSelf->Top__DOT__InstFetcher__DOT___GEN_3 = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__data_cacheline_reg = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__reqr_reg = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__axi_reg_readAddr = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___io_io_rdata_valid_T = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___io_axi4_arvalid_T = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_1 = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_2 = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_3 = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_4 = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__hit = 0;
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_data_ext__DOT__Memory[__Vi0] = 0;
    }
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_data_ext__DOT___GEN = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_data_ext__DOT___GEN_0 = 0;
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT__Memory[__Vi0] = 0;
    }
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT___GEN = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT___GEN_0 = 0;
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT__Memory[__Vi0] = 0;
    }
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT___GEN = 0;
    vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT___GEN_0 = 0;
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->Top__DOT__R_ext__DOT__Memory[__Vi0] = 0;
    }
    vlSelf->Top__DOT__Decoder__DOT__casez_tmp = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_14 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_29 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_66 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_67 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_68 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_69 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_70 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_71 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_72 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_73 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_74 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_75 = 0;
    vlSelf->Top__DOT__Decoder__DOT___GEN_76 = 0;
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_hfe7a8b0a__0 = 0;
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h24b557b3__0 = 0;
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h8d1c1e58__0 = 0;
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h92124dc1__0 = 0;
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0 = 0;
    vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_hf6825b5d__0 = 0;
    vlSelf->Top__DOT__ALU__DOT__casez_tmp = 0;
    vlSelf->Top__DOT__ALU__DOT__casez_tmp_0 = 0;
    vlSelf->Top__DOT__ALU__DOT__casez_tmp_1 = 0;
    vlSelf->Top__DOT__ALU__DOT___GEN = 0;
    vlSelf->Top__DOT__ALU__DOT____VdfgExtracted_h750bc5e8__0 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_rdata = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_bvalid = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__readAddr = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__readData = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__writeData = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__r_state = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__w_state = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_raddr_valid_T = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_wdata_valid_T = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_bready_T = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__r_offset_reg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___io_out_valid_T = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___GEN = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___GEN_0 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___io_out_valid_T_1 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___GEN_1 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__instreg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__pcreg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__memvalidreg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__aluresreg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__rdenreg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__rdreg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__memsextreg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__csridxreg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__csrwvreg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__csrenreg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__w_is_sram = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT___GEN_2 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT____VdfgTmp_h21929fc2__0 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___cache_data_ext_R1_data = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__casez_tmp = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__data_cacheline_reg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__reqr_reg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__reqw_reg = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_readAddr = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeAddr = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeData = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeMask = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_wstrb = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__uncached_r = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi4_readData = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_0 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_1 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_2 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_3 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_4 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_5 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_8 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_9 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_10 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_13 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_14 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_15 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_16 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_17 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_18 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_19 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_20 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_21 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_22 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_23 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_24 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_25 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_26 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_27 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_28 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_29 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_30 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT____VdfgTmp_ha260658d__0 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT____VdfgTmp_h58a209da__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT__Memory[__Vi0] = 0;
    }
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_0 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_1 = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_2 = 0;
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT__Memory[__Vi0] = 0;
    }
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT___GEN = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT___GEN_0 = 0;
    for (int __Vi0 = 0; __Vi0 < 512; ++__Vi0) {
        vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT__Memory[__Vi0] = 0;
    }
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT___GEN = 0;
    vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT___GEN_0 = 0;
    vlSelf->__Vtableidx1 = 0;
    vlSelf->__Vtrigrprev__TOP__clock = 0;
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
