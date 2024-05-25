// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VTop__Syms.h"


VL_ATTR_COLD void VTop___024root__trace_init_sub__TOP__0(VTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declBus(c+434,"io_inst", false,-1, 31,0);
    tracep->declQuad(c+435,"io_pc", false,-1, 63,0);
    tracep->declQuad(c+437,"io_npc", false,-1, 63,0);
    tracep->pushNamePrefix("Top ");
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declBus(c+434,"io_inst", false,-1, 31,0);
    tracep->declQuad(c+435,"io_pc", false,-1, 63,0);
    tracep->declQuad(c+437,"io_npc", false,-1, 63,0);
    tracep->declBit(c+1,"pcsel", false,-1);
    tracep->declQuad(c+2,"ifu_dnpc", false,-1, 63,0);
    tracep->declBit(c+4,"IDRegen", false,-1);
    tracep->declQuad(c+5,"casez_tmp", false,-1, 63,0);
    tracep->declBit(c+7,"IDReg_valid", false,-1);
    tracep->declBus(c+8,"IDReg_inst", false,-1, 31,0);
    tracep->declQuad(c+9,"IDReg_pc", false,-1, 63,0);
    tracep->declBit(c+11,"EXReg_valid", false,-1);
    tracep->declBus(c+12,"EXReg_inst", false,-1, 31,0);
    tracep->declQuad(c+13,"EXReg_pc", false,-1, 63,0);
    tracep->declQuad(c+15,"EXReg_rs1v", false,-1, 63,0);
    tracep->declQuad(c+17,"EXReg_rs2v", false,-1, 63,0);
    tracep->declBus(c+19,"EXReg_csridx", false,-1, 11,0);
    tracep->declQuad(c+20,"EXReg_csrrv", false,-1, 63,0);
    tracep->declQuad(c+22,"EXReg_csrwv", false,-1, 63,0);
    tracep->declBit(c+24,"EXReg_csr_en", false,-1);
    tracep->declQuad(c+25,"EXReg_imm", false,-1, 63,0);
    tracep->declBus(c+27,"EXReg_dataAsel", false,-1, 2,0);
    tracep->declBus(c+28,"EXReg_dataBsel", false,-1, 2,0);
    tracep->declBus(c+29,"EXReg_aluop", false,-1, 4,0);
    tracep->declBit(c+30,"EXReg_memvalid", false,-1);
    tracep->declBit(c+31,"EXReg_memwen", false,-1);
    tracep->declBus(c+32,"EXReg_memwmask", false,-1, 7,0);
    tracep->declBus(c+33,"EXReg_memsext", false,-1, 2,0);
    tracep->declBit(c+34,"EXReg_isEbreak", false,-1);
    tracep->declBit(c+35,"EXReg_isword", false,-1);
    tracep->declBit(c+36,"EXReg_rden", false,-1);
    tracep->declBus(c+37,"EXReg_rd", false,-1, 4,0);
    tracep->declBit(c+38,"LSReg_valid", false,-1);
    tracep->declBus(c+39,"LSReg_inst", false,-1, 31,0);
    tracep->declQuad(c+40,"LSReg_pc", false,-1, 63,0);
    tracep->declQuad(c+42,"LSReg_alures", false,-1, 63,0);
    tracep->declQuad(c+44,"LSReg_rs2v", false,-1, 63,0);
    tracep->declBus(c+46,"LSReg_csridx", false,-1, 11,0);
    tracep->declQuad(c+47,"LSReg_csrwv", false,-1, 63,0);
    tracep->declBit(c+49,"LSReg_csr_en", false,-1);
    tracep->declBit(c+50,"LSReg_memvalid", false,-1);
    tracep->declBit(c+51,"LSReg_memwen", false,-1);
    tracep->declBus(c+52,"LSReg_memwmask", false,-1, 7,0);
    tracep->declBus(c+53,"LSReg_memsext", false,-1, 2,0);
    tracep->declBit(c+54,"LSReg_rden", false,-1);
    tracep->declBus(c+55,"LSReg_rd", false,-1, 4,0);
    tracep->declBit(c+56,"WBReg_valid", false,-1);
    tracep->declBus(c+57,"WBReg_inst", false,-1, 31,0);
    tracep->declQuad(c+58,"WBReg_pc", false,-1, 63,0);
    tracep->declQuad(c+60,"WBReg_alures", false,-1, 63,0);
    tracep->declBus(c+62,"WBReg_csridx", false,-1, 11,0);
    tracep->declQuad(c+63,"WBReg_csrwv", false,-1, 63,0);
    tracep->declBit(c+65,"WBReg_csr_en", false,-1);
    tracep->declBit(c+66,"WBReg_rden", false,-1);
    tracep->declBus(c+67,"WBReg_rd", false,-1, 4,0);
    tracep->declBit(c+68,"WBReg_memvalid", false,-1);
    tracep->declBus(c+69,"WBReg_memsext", false,-1, 2,0);
    tracep->declQuad(c+70,"WBReg_rdata", false,-1, 63,0);
    tracep->declBit(c+72,"ISReg_valid", false,-1);
    tracep->declBus(c+73,"ISReg_inst", false,-1, 31,0);
    tracep->declQuad(c+74,"ISReg_pc", false,-1, 63,0);
    tracep->declQuad(c+76,"mstatus", false,-1, 63,0);
    tracep->declQuad(c+78,"mtvec", false,-1, 63,0);
    tracep->declQuad(c+80,"mepc", false,-1, 63,0);
    tracep->declQuad(c+82,"mcause", false,-1, 63,0);
    tracep->declQuad(c+84,"rs2v", false,-1, 63,0);
    tracep->declQuad(c+86,"rs1v", false,-1, 63,0);
    tracep->declBus(c+88,"csridx", false,-1, 11,0);
    tracep->declBit(c+89,"stall", false,-1);
    tracep->pushNamePrefix("ALU ");
    tracep->declBus(c+90,"io_inst", false,-1, 31,0);
    tracep->declQuad(c+91,"io_rs1v", false,-1, 63,0);
    tracep->declQuad(c+93,"io_rs2v", false,-1, 63,0);
    tracep->declQuad(c+95,"io_csrrv", false,-1, 63,0);
    tracep->declQuad(c+97,"io_pc", false,-1, 63,0);
    tracep->declBus(c+99,"io_asel", false,-1, 2,0);
    tracep->declBus(c+100,"io_bsel", false,-1, 2,0);
    tracep->declBus(c+101,"io_alu_op", false,-1, 4,0);
    tracep->declQuad(c+102,"io_imm", false,-1, 63,0);
    tracep->declBit(c+104,"io_isword", false,-1);
    tracep->declQuad(c+105,"io_res", false,-1, 63,0);
    tracep->declQuad(c+107,"casez_tmp", false,-1, 63,0);
    tracep->declQuad(c+109,"casez_tmp_0", false,-1, 63,0);
    tracep->declQuad(c+111,"casez_tmp_1", false,-1, 63,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("AXI4Arbiter ");
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declBus(c+113,"io_ifu_bus_axi4_araddr", false,-1, 31,0);
    tracep->declBit(c+114,"io_ifu_bus_axi4_arvalid", false,-1);
    tracep->declBit(c+115,"io_ifu_bus_axi4_rready", false,-1);
    tracep->declBit(c+116,"io_ifu_bus_bus_reqr", false,-1);
    tracep->declBus(c+117,"io_lsu_bus_axi4_araddr", false,-1, 31,0);
    tracep->declBit(c+118,"io_lsu_bus_axi4_arvalid", false,-1);
    tracep->declBit(c+119,"io_lsu_bus_axi4_rready", false,-1);
    tracep->declBus(c+120,"io_lsu_bus_axi4_awaddr", false,-1, 31,0);
    tracep->declBit(c+121,"io_lsu_bus_axi4_awvalid", false,-1);
    tracep->declQuad(c+122,"io_lsu_bus_axi4_wdata", false,-1, 63,0);
    tracep->declBus(c+124,"io_lsu_bus_axi4_wstrb", false,-1, 7,0);
    tracep->declBit(c+121,"io_lsu_bus_axi4_wvalid", false,-1);
    tracep->declBit(c+125,"io_lsu_bus_axi4_bready", false,-1);
    tracep->declBit(c+126,"io_lsu_bus_bus_reqr", false,-1);
    tracep->declBit(c+127,"io_lsu_bus_bus_reqw", false,-1);
    tracep->declBit(c+128,"io_xbar_bus_arready", false,-1);
    tracep->declQuad(c+129,"io_xbar_bus_rdata", false,-1, 63,0);
    tracep->declBus(c+131,"io_xbar_bus_rresp", false,-1, 1,0);
    tracep->declBit(c+132,"io_xbar_bus_rvalid", false,-1);
    tracep->declBit(c+133,"io_xbar_bus_awready", false,-1);
    tracep->declBit(c+134,"io_xbar_bus_wready", false,-1);
    tracep->declBus(c+135,"io_xbar_bus_bresp", false,-1, 1,0);
    tracep->declBit(c+136,"io_xbar_bus_bvalid", false,-1);
    tracep->declBit(c+137,"io_ifu_bus_axi4_arready", false,-1);
    tracep->declQuad(c+138,"io_ifu_bus_axi4_rdata", false,-1, 63,0);
    tracep->declBus(c+140,"io_ifu_bus_axi4_rresp", false,-1, 1,0);
    tracep->declBit(c+141,"io_ifu_bus_axi4_rvalid", false,-1);
    tracep->declBit(c+142,"io_ifu_bus_bus_ac", false,-1);
    tracep->declBit(c+143,"io_lsu_bus_axi4_arready", false,-1);
    tracep->declQuad(c+144,"io_lsu_bus_axi4_rdata", false,-1, 63,0);
    tracep->declBus(c+146,"io_lsu_bus_axi4_rresp", false,-1, 1,0);
    tracep->declBit(c+147,"io_lsu_bus_axi4_rvalid", false,-1);
    tracep->declBit(c+148,"io_lsu_bus_axi4_awready", false,-1);
    tracep->declBit(c+149,"io_lsu_bus_axi4_wready", false,-1);
    tracep->declBus(c+150,"io_lsu_bus_axi4_bresp", false,-1, 1,0);
    tracep->declBit(c+151,"io_lsu_bus_axi4_bvalid", false,-1);
    tracep->declBit(c+152,"io_lsu_bus_bus_ac", false,-1);
    tracep->declBus(c+153,"io_xbar_bus_araddr", false,-1, 31,0);
    tracep->declBit(c+154,"io_xbar_bus_arvalid", false,-1);
    tracep->declBit(c+155,"io_xbar_bus_rready", false,-1);
    tracep->declBus(c+156,"io_xbar_bus_awaddr", false,-1, 31,0);
    tracep->declBit(c+157,"io_xbar_bus_awvalid", false,-1);
    tracep->declQuad(c+158,"io_xbar_bus_wdata", false,-1, 63,0);
    tracep->declBus(c+160,"io_xbar_bus_wstrb", false,-1, 7,0);
    tracep->declBit(c+157,"io_xbar_bus_wvalid", false,-1);
    tracep->declBit(c+161,"io_xbar_bus_bready", false,-1);
    tracep->declBus(c+140,"casez_tmp", false,-1, 1,0);
    tracep->declQuad(c+138,"casez_tmp_0", false,-1, 63,0);
    tracep->declBus(c+153,"casez_tmp_1", false,-1, 31,0);
    tracep->declBus(c+156,"casez_tmp_2", false,-1, 31,0);
    tracep->declQuad(c+158,"casez_tmp_3", false,-1, 63,0);
    tracep->declBus(c+160,"casez_tmp_4", false,-1, 7,0);
    tracep->declBit(c+162,"casez_tmp_5", false,-1);
    tracep->declBus(c+163,"state", false,-1, 1,0);
    tracep->declBit(c+142,"ifu_ac", false,-1);
    tracep->declBit(c+152,"lsu_ac", false,-1);
    tracep->pushNamePrefix("empty_axi4_ifu ");
    tracep->declQuad(c+441,"io_axi4_rdata", false,-1, 63,0);
    tracep->declBus(c+443,"io_axi4_rresp", false,-1, 1,0);
    tracep->declBus(c+443,"io_axi4_bresp", false,-1, 1,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("empty_axi4_lsu ");
    tracep->declQuad(c+441,"io_axi4_rdata", false,-1, 63,0);
    tracep->declBus(c+443,"io_axi4_rresp", false,-1, 1,0);
    tracep->declBus(c+443,"io_axi4_bresp", false,-1, 1,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("empty_xbar_bus ");
    tracep->declBus(c+444,"io_axi4_araddr", false,-1, 31,0);
    tracep->declBus(c+444,"io_axi4_awaddr", false,-1, 31,0);
    tracep->declQuad(c+441,"io_axi4_wdata", false,-1, 63,0);
    tracep->declBus(c+445,"io_axi4_wstrb", false,-1, 7,0);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("Decoder ");
    tracep->declBus(c+164,"io_inst", false,-1, 31,0);
    tracep->declBus(c+165,"io_rs1", false,-1, 4,0);
    tracep->declBus(c+166,"io_rs2", false,-1, 4,0);
    tracep->declBus(c+167,"io_rd", false,-1, 4,0);
    tracep->declBit(c+168,"io_rd_en", false,-1);
    tracep->declBit(c+169,"io_csr_en", false,-1);
    tracep->declQuad(c+170,"io_imm", false,-1, 63,0);
    tracep->declBus(c+172,"io_alu_op", false,-1, 4,0);
    tracep->declBus(c+173,"io_alu_sel_a", false,-1, 2,0);
    tracep->declBus(c+174,"io_alu_sel_b", false,-1, 2,0);
    tracep->declBit(c+175,"io_isEbreak", false,-1);
    tracep->declBit(c+176,"io_memvalid", false,-1);
    tracep->declBit(c+177,"io_memwen", false,-1);
    tracep->declBus(c+178,"io_memwmask", false,-1, 7,0);
    tracep->declBus(c+179,"io_memsext", false,-1, 2,0);
    tracep->declBit(c+180,"io_isword", false,-1);
    tracep->declBit(c+181,"io_rrs1", false,-1);
    tracep->declBit(c+182,"io_rrs2", false,-1);
    tracep->declQuad(c+170,"casez_tmp", false,-1, 63,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("Ebreak ");
    tracep->declBit(c+34,"isEbreak", false,-1);
    tracep->declBit(c+432,"clk", false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("InstFetcher ");
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declBit(c+439,"io_in_valid", false,-1);
    tracep->declBit(c+89,"io_in_bits_stall", false,-1);
    tracep->declBit(c+1,"io_in_bits_isdnpc", false,-1);
    tracep->declQuad(c+183,"io_in_bits_dnpc", false,-1, 63,0);
    tracep->declBit(c+440,"io_out_ready", false,-1);
    tracep->declBit(c+137,"io_axi4_to_arbiter_arready", false,-1);
    tracep->declQuad(c+138,"io_axi4_to_arbiter_rdata", false,-1, 63,0);
    tracep->declBus(c+140,"io_axi4_to_arbiter_rresp", false,-1, 1,0);
    tracep->declBit(c+141,"io_axi4_to_arbiter_rvalid", false,-1);
    tracep->declBit(c+142,"io_bus_ac", false,-1);
    tracep->declBit(c+185,"io_out_valid", false,-1);
    tracep->declQuad(c+186,"io_out_bits_pc", false,-1, 63,0);
    tracep->declBus(c+188,"io_out_bits_inst", false,-1, 31,0);
    tracep->declBus(c+113,"io_axi4_to_arbiter_araddr", false,-1, 31,0);
    tracep->declBit(c+114,"io_axi4_to_arbiter_arvalid", false,-1);
    tracep->declBit(c+115,"io_axi4_to_arbiter_rready", false,-1);
    tracep->declBit(c+116,"io_bus_reqr", false,-1);
    tracep->declBus(c+189,"state", false,-1, 1,0);
    tracep->declQuad(c+190,"PC", false,-1, 63,0);
    tracep->declBus(c+192,"readAddr", false,-1, 31,0);
    tracep->declBus(c+193,"outAddr", false,-1, 31,0);
    tracep->declBus(c+188,"outData", false,-1, 31,0);
    tracep->declQuad(c+194,"dnpc_reg", false,-1, 63,0);
    tracep->declBit(c+196,"dnpc_valid", false,-1);
    tracep->pushNamePrefix("icache ");
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declQuad(c+186,"io_io_raddr", false,-1, 63,0);
    tracep->declBit(c+197,"io_io_raddr_valid", false,-1);
    tracep->declBit(c+198,"io_io_rdata_ready", false,-1);
    tracep->declBit(c+137,"io_axi4_arready", false,-1);
    tracep->declQuad(c+138,"io_axi4_rdata", false,-1, 63,0);
    tracep->declBus(c+140,"io_axi4_rresp", false,-1, 1,0);
    tracep->declBit(c+141,"io_axi4_rvalid", false,-1);
    tracep->declBit(c+142,"io_bus_ac", false,-1);
    tracep->declBit(c+89,"io_stall", false,-1);
    tracep->declBit(c+199,"io_io_raddr_ready", false,-1);
    tracep->declBus(c+200,"io_io_rdata", false,-1, 31,0);
    tracep->declBit(c+201,"io_io_rdata_valid", false,-1);
    tracep->declBus(c+113,"io_axi4_araddr", false,-1, 31,0);
    tracep->declBit(c+114,"io_axi4_arvalid", false,-1);
    tracep->declBit(c+115,"io_axi4_rready", false,-1);
    tracep->declBit(c+116,"io_bus_reqr", false,-1);
    tracep->declQuad(c+202,"data_cacheline_reg", false,-1, 63,0);
    tracep->declBit(c+116,"reqr_reg", false,-1);
    tracep->declBus(c+204,"r_state", false,-1, 2,0);
    tracep->declQuad(c+205,"axi_reg_readAddr", false,-1, 63,0);
    tracep->declBit(c+207,"hit", false,-1);
    tracep->pushNamePrefix("cache_data_ext ");
    tracep->declBus(c+208,"R0_addr", false,-1, 8,0);
    tracep->declBit(c+446,"R0_en", false,-1);
    tracep->declBit(c+432,"R0_clk", false,-1);
    tracep->declBus(c+208,"W0_addr", false,-1, 8,0);
    tracep->declBit(c+209,"W0_en", false,-1);
    tracep->declBit(c+432,"W0_clk", false,-1);
    tracep->declQuad(c+138,"W0_data", false,-1, 63,0);
    tracep->declQuad(c+210,"R0_data", false,-1, 63,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("cache_tag_ext ");
    tracep->declBus(c+208,"R0_addr", false,-1, 8,0);
    tracep->declBit(c+446,"R0_en", false,-1);
    tracep->declBit(c+432,"R0_clk", false,-1);
    tracep->declBus(c+208,"W0_addr", false,-1, 8,0);
    tracep->declBit(c+209,"W0_en", false,-1);
    tracep->declBit(c+432,"W0_clk", false,-1);
    tracep->declQuad(c+212,"W0_data", false,-1, 60,0);
    tracep->declQuad(c+214,"R0_data", false,-1, 60,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("cache_valid_ext ");
    tracep->declBus(c+208,"R0_addr", false,-1, 8,0);
    tracep->declBit(c+446,"R0_en", false,-1);
    tracep->declBit(c+432,"R0_clk", false,-1);
    tracep->declBus(c+208,"W0_addr", false,-1, 8,0);
    tracep->declBit(c+209,"W0_en", false,-1);
    tracep->declBit(c+432,"W0_clk", false,-1);
    tracep->declBit(c+446,"W0_data", false,-1);
    tracep->declBit(c+216,"R0_data", false,-1);
    tracep->popNamePrefix(3);
    tracep->pushNamePrefix("MyClint ");
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declBus(c+217,"io_axi4_araddr", false,-1, 31,0);
    tracep->declBit(c+218,"io_axi4_arvalid", false,-1);
    tracep->declBit(c+219,"io_axi4_rready", false,-1);
    tracep->declBit(c+220,"io_axi4_arready", false,-1);
    tracep->declQuad(c+221,"io_axi4_rdata", false,-1, 63,0);
    tracep->declBit(c+223,"io_axi4_rvalid", false,-1);
    tracep->declBit(c+223,"r_state", false,-1);
    tracep->declQuad(c+224,"mtime_csr", false,-1, 63,0);
    tracep->declBus(c+226,"rdata", false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("MyUart ");
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declBit(c+227,"io_axi4_awvalid", false,-1);
    tracep->declQuad(c+228,"io_axi4_wdata", false,-1, 63,0);
    tracep->declBit(c+227,"io_axi4_wvalid", false,-1);
    tracep->declBit(c+230,"io_axi4_bready", false,-1);
    tracep->declBit(c+231,"io_axi4_awready", false,-1);
    tracep->declBit(c+232,"io_axi4_wready", false,-1);
    tracep->declBit(c+233,"io_axi4_bvalid", false,-1);
    tracep->declBus(c+234,"w_state", false,-1, 1,0);
    tracep->declQuad(c+235,"writeData", false,-1, 63,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("NPC_Mem ");
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declBit(c+38,"io_in_valid", false,-1);
    tracep->declBus(c+237,"io_in_bits_inst", false,-1, 31,0);
    tracep->declQuad(c+238,"io_in_bits_pc", false,-1, 63,0);
    tracep->declQuad(c+240,"io_in_bits_alures", false,-1, 63,0);
    tracep->declBit(c+242,"io_in_bits_memvalid", false,-1);
    tracep->declBit(c+243,"io_in_bits_wen", false,-1);
    tracep->declQuad(c+244,"io_in_bits_wmask", false,-1, 63,0);
    tracep->declBus(c+246,"io_in_bits_wsext", false,-1, 2,0);
    tracep->declBus(c+247,"io_in_bits_raddr", false,-1, 31,0);
    tracep->declBus(c+247,"io_in_bits_waddr", false,-1, 31,0);
    tracep->declQuad(c+248,"io_in_bits_wdata", false,-1, 63,0);
    tracep->declBit(c+250,"io_in_bits_rden", false,-1);
    tracep->declBus(c+251,"io_in_bits_rd", false,-1, 4,0);
    tracep->declBus(c+252,"io_in_bits_csridx", false,-1, 11,0);
    tracep->declQuad(c+253,"io_in_bits_csrwv", false,-1, 63,0);
    tracep->declBit(c+255,"io_in_bits_csr_en", false,-1);
    tracep->declBit(c+143,"io_axi4_to_arbiter_arready", false,-1);
    tracep->declQuad(c+144,"io_axi4_to_arbiter_rdata", false,-1, 63,0);
    tracep->declBus(c+146,"io_axi4_to_arbiter_rresp", false,-1, 1,0);
    tracep->declBit(c+147,"io_axi4_to_arbiter_rvalid", false,-1);
    tracep->declBit(c+148,"io_axi4_to_arbiter_awready", false,-1);
    tracep->declBit(c+149,"io_axi4_to_arbiter_wready", false,-1);
    tracep->declBus(c+150,"io_axi4_to_arbiter_bresp", false,-1, 1,0);
    tracep->declBit(c+151,"io_axi4_to_arbiter_bvalid", false,-1);
    tracep->declBit(c+152,"io_bus_ac", false,-1);
    tracep->declBit(c+256,"io_in_ready", false,-1);
    tracep->declBit(c+257,"io_out_valid", false,-1);
    tracep->declBus(c+258,"io_out_bits_inst", false,-1, 31,0);
    tracep->declQuad(c+259,"io_out_bits_pc", false,-1, 63,0);
    tracep->declQuad(c+261,"io_out_bits_alures", false,-1, 63,0);
    tracep->declBit(c+263,"io_out_bits_memvalid", false,-1);
    tracep->declBit(c+264,"io_out_bits_rden", false,-1);
    tracep->declBus(c+265,"io_out_bits_rd", false,-1, 4,0);
    tracep->declBus(c+266,"io_out_bits_csridx", false,-1, 11,0);
    tracep->declQuad(c+267,"io_out_bits_csrwv", false,-1, 63,0);
    tracep->declBit(c+269,"io_out_bits_csr_en", false,-1);
    tracep->declBus(c+270,"io_out_bits_memsext", false,-1, 2,0);
    tracep->declQuad(c+271,"io_out_bits_rdata", false,-1, 63,0);
    tracep->declBus(c+117,"io_axi4_to_arbiter_araddr", false,-1, 31,0);
    tracep->declBit(c+118,"io_axi4_to_arbiter_arvalid", false,-1);
    tracep->declBit(c+119,"io_axi4_to_arbiter_rready", false,-1);
    tracep->declBus(c+120,"io_axi4_to_arbiter_awaddr", false,-1, 31,0);
    tracep->declBit(c+121,"io_axi4_to_arbiter_awvalid", false,-1);
    tracep->declQuad(c+122,"io_axi4_to_arbiter_wdata", false,-1, 63,0);
    tracep->declBus(c+124,"io_axi4_to_arbiter_wstrb", false,-1, 7,0);
    tracep->declBit(c+121,"io_axi4_to_arbiter_wvalid", false,-1);
    tracep->declBit(c+125,"io_axi4_to_arbiter_bready", false,-1);
    tracep->declBit(c+126,"io_bus_reqr", false,-1);
    tracep->declBit(c+127,"io_bus_reqw", false,-1);
    tracep->declBus(c+273,"readAddr", false,-1, 31,0);
    tracep->declQuad(c+271,"readData", false,-1, 63,0);
    tracep->declBus(c+274,"writeAddr", false,-1, 31,0);
    tracep->declQuad(c+275,"writeData", false,-1, 63,0);
    tracep->declBus(c+277,"writeStrb", false,-1, 7,0);
    tracep->declBus(c+278,"r_state", false,-1, 1,0);
    tracep->declBus(c+279,"w_state", false,-1, 1,0);
    tracep->declBus(c+280,"r_offset_reg", false,-1, 2,0);
    tracep->declBus(c+258,"instreg", false,-1, 31,0);
    tracep->declQuad(c+259,"pcreg", false,-1, 63,0);
    tracep->declBit(c+263,"memvalidreg", false,-1);
    tracep->declQuad(c+261,"aluresreg", false,-1, 63,0);
    tracep->declBit(c+264,"rdenreg", false,-1);
    tracep->declBus(c+265,"rdreg", false,-1, 4,0);
    tracep->declBus(c+270,"memsextreg", false,-1, 2,0);
    tracep->declBus(c+266,"csridxreg", false,-1, 11,0);
    tracep->declQuad(c+267,"csrwvreg", false,-1, 63,0);
    tracep->declBit(c+269,"csrenreg", false,-1);
    tracep->declBit(c+281,"w_is_sram", false,-1);
    tracep->declBit(c+281,"r_is_sram", false,-1);
    tracep->pushNamePrefix("dcache ");
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declQuad(c+282,"io_io_raddr", false,-1, 63,0);
    tracep->declBit(c+284,"io_io_raddr_valid", false,-1);
    tracep->declBit(c+285,"io_io_rdata_ready", false,-1);
    tracep->declQuad(c+286,"io_io_waddr", false,-1, 63,0);
    tracep->declBit(c+288,"io_io_waddr_valid", false,-1);
    tracep->declQuad(c+275,"io_io_wdata", false,-1, 63,0);
    tracep->declBus(c+277,"io_io_wstrb", false,-1, 7,0);
    tracep->declBit(c+289,"io_io_bready", false,-1);
    tracep->declBit(c+143,"io_axi4_arready", false,-1);
    tracep->declQuad(c+144,"io_axi4_rdata", false,-1, 63,0);
    tracep->declBus(c+146,"io_axi4_rresp", false,-1, 1,0);
    tracep->declBit(c+147,"io_axi4_rvalid", false,-1);
    tracep->declBit(c+148,"io_axi4_awready", false,-1);
    tracep->declBit(c+149,"io_axi4_wready", false,-1);
    tracep->declBus(c+150,"io_axi4_bresp", false,-1, 1,0);
    tracep->declBit(c+151,"io_axi4_bvalid", false,-1);
    tracep->declBit(c+152,"io_bus_ac", false,-1);
    tracep->declBit(c+290,"io_io_raddr_ready", false,-1);
    tracep->declQuad(c+291,"io_io_rdata", false,-1, 63,0);
    tracep->declBit(c+293,"io_io_rdata_valid", false,-1);
    tracep->declBit(c+290,"io_io_waddr_ready", false,-1);
    tracep->declBit(c+290,"io_io_wdata_ready", false,-1);
    tracep->declBit(c+294,"io_io_bvalid", false,-1);
    tracep->declBus(c+117,"io_axi4_araddr", false,-1, 31,0);
    tracep->declBit(c+118,"io_axi4_arvalid", false,-1);
    tracep->declBit(c+119,"io_axi4_rready", false,-1);
    tracep->declBus(c+120,"io_axi4_awaddr", false,-1, 31,0);
    tracep->declBit(c+121,"io_axi4_awvalid", false,-1);
    tracep->declQuad(c+122,"io_axi4_wdata", false,-1, 63,0);
    tracep->declBus(c+124,"io_axi4_wstrb", false,-1, 7,0);
    tracep->declBit(c+121,"io_axi4_wvalid", false,-1);
    tracep->declBit(c+125,"io_axi4_bready", false,-1);
    tracep->declBit(c+126,"io_bus_reqr", false,-1);
    tracep->declBit(c+127,"io_bus_reqw", false,-1);
    tracep->declBus(c+295,"casez_tmp", false,-1, 2,0);
    tracep->declQuad(c+296,"data_cacheline_reg", false,-1, 63,0);
    tracep->declBit(c+126,"reqr_reg", false,-1);
    tracep->declBit(c+127,"reqw_reg", false,-1);
    tracep->declBus(c+298,"s_state", false,-1, 2,0);
    tracep->declQuad(c+299,"axi_reg_readAddr", false,-1, 63,0);
    tracep->declQuad(c+301,"axi_reg_writeAddr", false,-1, 63,0);
    tracep->declQuad(c+122,"axi_reg_writeData", false,-1, 63,0);
    tracep->declQuad(c+303,"axi_reg_writeMask", false,-1, 63,0);
    tracep->declBus(c+124,"axi_reg_wstrb", false,-1, 7,0);
    tracep->declBit(c+305,"uncached_r", false,-1);
    tracep->declQuad(c+306,"axi4_readData", false,-1, 63,0);
    tracep->pushNamePrefix("cache_data_ext ");
    tracep->declBus(c+308,"R0_addr", false,-1, 8,0);
    tracep->declBit(c+446,"R0_en", false,-1);
    tracep->declBit(c+432,"R0_clk", false,-1);
    tracep->declBus(c+309,"R1_addr", false,-1, 8,0);
    tracep->declBit(c+446,"R1_en", false,-1);
    tracep->declBit(c+432,"R1_clk", false,-1);
    tracep->declBus(c+308,"W0_addr", false,-1, 8,0);
    tracep->declBit(c+310,"W0_en", false,-1);
    tracep->declBit(c+432,"W0_clk", false,-1);
    tracep->declQuad(c+144,"W0_data", false,-1, 63,0);
    tracep->declBus(c+309,"W1_addr", false,-1, 8,0);
    tracep->declBit(c+311,"W1_en", false,-1);
    tracep->declBit(c+432,"W1_clk", false,-1);
    tracep->declQuad(c+312,"W1_data", false,-1, 63,0);
    tracep->declQuad(c+314,"R0_data", false,-1, 63,0);
    tracep->declQuad(c+316,"R1_data", false,-1, 63,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("cache_tag_ext ");
    tracep->declBus(c+308,"R0_addr", false,-1, 8,0);
    tracep->declBit(c+446,"R0_en", false,-1);
    tracep->declBit(c+432,"R0_clk", false,-1);
    tracep->declBus(c+308,"W0_addr", false,-1, 8,0);
    tracep->declBit(c+310,"W0_en", false,-1);
    tracep->declBit(c+432,"W0_clk", false,-1);
    tracep->declQuad(c+318,"W0_data", false,-1, 60,0);
    tracep->declBus(c+309,"W1_addr", false,-1, 8,0);
    tracep->declBit(c+311,"W1_en", false,-1);
    tracep->declBit(c+432,"W1_clk", false,-1);
    tracep->declQuad(c+320,"W1_data", false,-1, 60,0);
    tracep->declQuad(c+322,"R0_data", false,-1, 60,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("cache_valid_ext ");
    tracep->declBus(c+308,"R0_addr", false,-1, 8,0);
    tracep->declBit(c+446,"R0_en", false,-1);
    tracep->declBit(c+432,"R0_clk", false,-1);
    tracep->declBus(c+308,"W0_addr", false,-1, 8,0);
    tracep->declBit(c+310,"W0_en", false,-1);
    tracep->declBit(c+432,"W0_clk", false,-1);
    tracep->declBit(c+446,"W0_data", false,-1);
    tracep->declBus(c+309,"W1_addr", false,-1, 8,0);
    tracep->declBit(c+311,"W1_en", false,-1);
    tracep->declBit(c+432,"W1_clk", false,-1);
    tracep->declBit(c+446,"W1_data", false,-1);
    tracep->declBit(c+324,"R0_data", false,-1);
    tracep->popNamePrefix(3);
    tracep->pushNamePrefix("R_ext ");
    tracep->declBus(c+165,"R0_addr", false,-1, 4,0);
    tracep->declBit(c+446,"R0_en", false,-1);
    tracep->declBit(c+432,"R0_clk", false,-1);
    tracep->declBus(c+166,"R1_addr", false,-1, 4,0);
    tracep->declBit(c+446,"R1_en", false,-1);
    tracep->declBit(c+432,"R1_clk", false,-1);
    tracep->declBus(c+447,"W0_addr", false,-1, 4,0);
    tracep->declBit(c+446,"W0_en", false,-1);
    tracep->declBit(c+432,"W0_clk", false,-1);
    tracep->declQuad(c+441,"W0_data", false,-1, 63,0);
    tracep->declBus(c+67,"W1_addr", false,-1, 4,0);
    tracep->declBit(c+325,"W1_en", false,-1);
    tracep->declBit(c+432,"W1_clk", false,-1);
    tracep->declQuad(c+326,"W1_data", false,-1, 63,0);
    tracep->declQuad(c+328,"R0_data", false,-1, 63,0);
    tracep->declQuad(c+330,"R1_data", false,-1, 63,0);
    for (int i = 0; i < 32; ++i) {
        tracep->declQuad(c+332+i*2,"Memory", true,(i+0), 63,0);
    }
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("SRAM ");
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declBus(c+396,"io_axi4_araddr", false,-1, 31,0);
    tracep->declBit(c+397,"io_axi4_arvalid", false,-1);
    tracep->declBit(c+398,"io_axi4_rready", false,-1);
    tracep->declBus(c+399,"io_axi4_awaddr", false,-1, 31,0);
    tracep->declBit(c+400,"io_axi4_awvalid", false,-1);
    tracep->declQuad(c+401,"io_axi4_wdata", false,-1, 63,0);
    tracep->declBus(c+403,"io_axi4_wstrb", false,-1, 7,0);
    tracep->declBit(c+400,"io_axi4_wvalid", false,-1);
    tracep->declBit(c+404,"io_axi4_bready", false,-1);
    tracep->declBit(c+405,"io_axi4_arready", false,-1);
    tracep->declQuad(c+406,"io_axi4_rdata", false,-1, 63,0);
    tracep->declBit(c+408,"io_axi4_rvalid", false,-1);
    tracep->declBit(c+409,"io_axi4_awready", false,-1);
    tracep->declBit(c+410,"io_axi4_wready", false,-1);
    tracep->declBit(c+411,"io_axi4_bvalid", false,-1);
    tracep->declBus(c+412,"casez_tmp", false,-1, 1,0);
    tracep->declBus(c+413,"r_state", false,-1, 1,0);
    tracep->declBus(c+414,"delay", false,-1, 7,0);
    tracep->declBus(c+415,"delayCounter", false,-1, 7,0);
    tracep->declBit(c+416,"delayDone", false,-1);
    tracep->declQuad(c+406,"readData", false,-1, 63,0);
    tracep->declBus(c+417,"readAddr", false,-1, 31,0);
    tracep->declBit(c+408,"rvalidReg", false,-1);
    tracep->declBus(c+418,"w_state", false,-1, 1,0);
    tracep->declBus(c+419,"writeAddr", false,-1, 31,0);
    tracep->declQuad(c+420,"writeData", false,-1, 63,0);
    tracep->declBus(c+422,"writeStrb", false,-1, 7,0);
    tracep->pushNamePrefix("dpic_mem ");
    tracep->declBit(c+423,"valid", false,-1);
    tracep->declBit(c+424,"wen", false,-1);
    tracep->declBus(c+417,"raddr", false,-1, 31,0);
    tracep->declQuad(c+425,"rdata", false,-1, 63,0);
    tracep->declBus(c+419,"waddr", false,-1, 31,0);
    tracep->declQuad(c+420,"wdata", false,-1, 63,0);
    tracep->declBus(c+422,"wmask", false,-1, 7,0);
    tracep->declBit(c+432,"clk", false,-1);
    tracep->popNamePrefix(2);
    tracep->pushNamePrefix("XBar2 ");
    tracep->declBit(c+432,"clock", false,-1);
    tracep->declBit(c+433,"reset", false,-1);
    tracep->declBus(c+153,"io_axi4in_araddr", false,-1, 31,0);
    tracep->declBit(c+154,"io_axi4in_arvalid", false,-1);
    tracep->declBit(c+155,"io_axi4in_rready", false,-1);
    tracep->declBus(c+156,"io_axi4in_awaddr", false,-1, 31,0);
    tracep->declBit(c+157,"io_axi4in_awvalid", false,-1);
    tracep->declQuad(c+158,"io_axi4in_wdata", false,-1, 63,0);
    tracep->declBus(c+160,"io_axi4in_wstrb", false,-1, 7,0);
    tracep->declBit(c+157,"io_axi4in_wvalid", false,-1);
    tracep->declBit(c+161,"io_axi4in_bready", false,-1);
    tracep->declBit(c+231,"io_axi4out0_awready", false,-1);
    tracep->declBit(c+232,"io_axi4out0_wready", false,-1);
    tracep->declBus(c+443,"io_axi4out0_bresp", false,-1, 1,0);
    tracep->declBit(c+233,"io_axi4out0_bvalid", false,-1);
    tracep->declBit(c+405,"io_axi4out1_arready", false,-1);
    tracep->declQuad(c+406,"io_axi4out1_rdata", false,-1, 63,0);
    tracep->declBit(c+408,"io_axi4out1_rvalid", false,-1);
    tracep->declBit(c+409,"io_axi4out1_awready", false,-1);
    tracep->declBit(c+410,"io_axi4out1_wready", false,-1);
    tracep->declBus(c+443,"io_axi4out1_bresp", false,-1, 1,0);
    tracep->declBit(c+411,"io_axi4out1_bvalid", false,-1);
    tracep->declBit(c+220,"io_axi4out2_arready", false,-1);
    tracep->declQuad(c+221,"io_axi4out2_rdata", false,-1, 63,0);
    tracep->declBus(c+443,"io_axi4out2_rresp", false,-1, 1,0);
    tracep->declBit(c+223,"io_axi4out2_rvalid", false,-1);
    tracep->declBit(c+128,"io_axi4in_arready", false,-1);
    tracep->declQuad(c+129,"io_axi4in_rdata", false,-1, 63,0);
    tracep->declBus(c+131,"io_axi4in_rresp", false,-1, 1,0);
    tracep->declBit(c+132,"io_axi4in_rvalid", false,-1);
    tracep->declBit(c+133,"io_axi4in_awready", false,-1);
    tracep->declBit(c+134,"io_axi4in_wready", false,-1);
    tracep->declBus(c+135,"io_axi4in_bresp", false,-1, 1,0);
    tracep->declBit(c+136,"io_axi4in_bvalid", false,-1);
    tracep->declBit(c+227,"io_axi4out0_awvalid", false,-1);
    tracep->declQuad(c+228,"io_axi4out0_wdata", false,-1, 63,0);
    tracep->declBit(c+227,"io_axi4out0_wvalid", false,-1);
    tracep->declBit(c+230,"io_axi4out0_bready", false,-1);
    tracep->declBus(c+396,"io_axi4out1_araddr", false,-1, 31,0);
    tracep->declBit(c+397,"io_axi4out1_arvalid", false,-1);
    tracep->declBit(c+398,"io_axi4out1_rready", false,-1);
    tracep->declBus(c+399,"io_axi4out1_awaddr", false,-1, 31,0);
    tracep->declBit(c+400,"io_axi4out1_awvalid", false,-1);
    tracep->declQuad(c+401,"io_axi4out1_wdata", false,-1, 63,0);
    tracep->declBus(c+403,"io_axi4out1_wstrb", false,-1, 7,0);
    tracep->declBit(c+400,"io_axi4out1_wvalid", false,-1);
    tracep->declBit(c+404,"io_axi4out1_bready", false,-1);
    tracep->declBus(c+217,"io_axi4out2_araddr", false,-1, 31,0);
    tracep->declBit(c+218,"io_axi4out2_arvalid", false,-1);
    tracep->declBit(c+219,"io_axi4out2_rready", false,-1);
    tracep->declQuad(c+427,"casez_tmp", false,-1, 63,0);
    tracep->declBus(c+429,"casez_tmp_0", false,-1, 1,0);
    tracep->declBus(c+443,"casez_tmp_1", false,-1, 1,0);
    tracep->declQuad(c+129,"casez_tmp_2", false,-1, 63,0);
    tracep->declBus(c+131,"casez_tmp_3", false,-1, 1,0);
    tracep->declBit(c+133,"casez_tmp_4", false,-1);
    tracep->declBit(c+134,"casez_tmp_5", false,-1);
    tracep->declBus(c+135,"casez_tmp_6", false,-1, 1,0);
    tracep->declBit(c+136,"casez_tmp_7", false,-1);
    tracep->declBus(c+430,"state_r", false,-1, 1,0);
    tracep->declBus(c+431,"state_w", false,-1, 1,0);
    tracep->pushNamePrefix("empty_master_out ");
    tracep->declQuad(c+441,"io_axi4_rdata", false,-1, 63,0);
    tracep->declBus(c+443,"io_axi4_rresp", false,-1, 1,0);
    tracep->declBus(c+443,"io_axi4_bresp", false,-1, 1,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("empty_slave_in0 ");
    tracep->declBus(c+444,"io_axi4_araddr", false,-1, 31,0);
    tracep->declBus(c+444,"io_axi4_awaddr", false,-1, 31,0);
    tracep->declQuad(c+441,"io_axi4_wdata", false,-1, 63,0);
    tracep->declBus(c+445,"io_axi4_wstrb", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("empty_slave_in1 ");
    tracep->declBus(c+444,"io_axi4_araddr", false,-1, 31,0);
    tracep->declBus(c+444,"io_axi4_awaddr", false,-1, 31,0);
    tracep->declQuad(c+441,"io_axi4_wdata", false,-1, 63,0);
    tracep->declBus(c+445,"io_axi4_wstrb", false,-1, 7,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("empty_slave_in2 ");
    tracep->declBus(c+444,"io_axi4_araddr", false,-1, 31,0);
    tracep->declBus(c+444,"io_axi4_awaddr", false,-1, 31,0);
    tracep->declQuad(c+441,"io_axi4_wdata", false,-1, 63,0);
    tracep->declBus(c+445,"io_axi4_wstrb", false,-1, 7,0);
    tracep->popNamePrefix(3);
}

VL_ATTR_COLD void VTop___024root__trace_init_top(VTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_init_top\n"); );
    // Body
    VTop___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void VTop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VTop___024root__trace_chg_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void VTop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void VTop___024root__trace_register(VTop___024root* vlSelf, VerilatedVcd* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&VTop___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&VTop___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&VTop___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void VTop___024root__trace_full_sub_0(VTop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void VTop___024root__trace_full_top_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_full_top_0\n"); );
    // Init
    VTop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<VTop___024root*>(voidSelf);
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    VTop___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void VTop___024root__trace_full_sub_0(VTop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    VTop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    VTop___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullBit(oldp+1,(vlSelf->Top__DOT__pcsel));
    bufp->fullQData(oldp+2,(((IData)(vlSelf->Top__DOT__stall)
                              ? 0x114514ULL : ((0x67U 
                                                == (IData)(vlSelf->Top__DOT___GEN_1))
                                                ? (vlSelf->Top__DOT__rs1v 
                                                   + vlSelf->Top__DOT__Decoder__DOT__casez_tmp)
                                                : (
                                                   ((0x6fU 
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
    bufp->fullBit(oldp+4,(vlSelf->Top__DOT__IDRegen));
    bufp->fullQData(oldp+5,(((4U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
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
                                          << 8U) | (QData)((IData)(
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
    bufp->fullBit(oldp+7,(vlSelf->Top__DOT__IDReg_valid));
    bufp->fullIData(oldp+8,(vlSelf->Top__DOT__IDReg_inst),32);
    bufp->fullQData(oldp+9,(vlSelf->Top__DOT__IDReg_pc),64);
    bufp->fullBit(oldp+11,(vlSelf->Top__DOT__EXReg_valid));
    bufp->fullIData(oldp+12,(vlSelf->Top__DOT__EXReg_inst),32);
    bufp->fullQData(oldp+13,(vlSelf->Top__DOT__EXReg_pc),64);
    bufp->fullQData(oldp+15,(vlSelf->Top__DOT__EXReg_rs1v),64);
    bufp->fullQData(oldp+17,(vlSelf->Top__DOT__EXReg_rs2v),64);
    bufp->fullSData(oldp+19,(vlSelf->Top__DOT__EXReg_csridx),12);
    bufp->fullQData(oldp+20,(vlSelf->Top__DOT__EXReg_csrrv),64);
    bufp->fullQData(oldp+22,(vlSelf->Top__DOT__EXReg_csrwv),64);
    bufp->fullBit(oldp+24,(vlSelf->Top__DOT__EXReg_csr_en));
    bufp->fullQData(oldp+25,(vlSelf->Top__DOT__EXReg_imm),64);
    bufp->fullCData(oldp+27,(vlSelf->Top__DOT__EXReg_dataAsel),3);
    bufp->fullCData(oldp+28,(vlSelf->Top__DOT__EXReg_dataBsel),3);
    bufp->fullCData(oldp+29,(vlSelf->Top__DOT__EXReg_aluop),5);
    bufp->fullBit(oldp+30,(vlSelf->Top__DOT__EXReg_memvalid));
    bufp->fullBit(oldp+31,(vlSelf->Top__DOT__EXReg_memwen));
    bufp->fullCData(oldp+32,(vlSelf->Top__DOT__EXReg_memwmask),8);
    bufp->fullCData(oldp+33,(vlSelf->Top__DOT__EXReg_memsext),3);
    bufp->fullBit(oldp+34,(vlSelf->Top__DOT__EXReg_isEbreak));
    bufp->fullBit(oldp+35,(vlSelf->Top__DOT__EXReg_isword));
    bufp->fullBit(oldp+36,(vlSelf->Top__DOT__EXReg_rden));
    bufp->fullCData(oldp+37,(vlSelf->Top__DOT__EXReg_rd),5);
    bufp->fullBit(oldp+38,(vlSelf->Top__DOT__LSReg_valid));
    bufp->fullIData(oldp+39,(vlSelf->Top__DOT__LSReg_inst),32);
    bufp->fullQData(oldp+40,(vlSelf->Top__DOT__LSReg_pc),64);
    bufp->fullQData(oldp+42,(vlSelf->Top__DOT__LSReg_alures),64);
    bufp->fullQData(oldp+44,(vlSelf->Top__DOT__LSReg_rs2v),64);
    bufp->fullSData(oldp+46,(vlSelf->Top__DOT__LSReg_csridx),12);
    bufp->fullQData(oldp+47,(vlSelf->Top__DOT__LSReg_csrwv),64);
    bufp->fullBit(oldp+49,(vlSelf->Top__DOT__LSReg_csr_en));
    bufp->fullBit(oldp+50,(vlSelf->Top__DOT__LSReg_memvalid));
    bufp->fullBit(oldp+51,(vlSelf->Top__DOT__LSReg_memwen));
    bufp->fullCData(oldp+52,(vlSelf->Top__DOT__LSReg_memwmask),8);
    bufp->fullCData(oldp+53,(vlSelf->Top__DOT__LSReg_memsext),3);
    bufp->fullBit(oldp+54,(vlSelf->Top__DOT__LSReg_rden));
    bufp->fullCData(oldp+55,(vlSelf->Top__DOT__LSReg_rd),5);
    bufp->fullBit(oldp+56,(vlSelf->Top__DOT__WBReg_valid));
    bufp->fullIData(oldp+57,(vlSelf->Top__DOT__WBReg_inst),32);
    bufp->fullQData(oldp+58,(vlSelf->Top__DOT__WBReg_pc),64);
    bufp->fullQData(oldp+60,(vlSelf->Top__DOT__WBReg_alures),64);
    bufp->fullSData(oldp+62,(vlSelf->Top__DOT__WBReg_csridx),12);
    bufp->fullQData(oldp+63,(vlSelf->Top__DOT__WBReg_csrwv),64);
    bufp->fullBit(oldp+65,(vlSelf->Top__DOT__WBReg_csr_en));
    bufp->fullBit(oldp+66,(vlSelf->Top__DOT__WBReg_rden));
    bufp->fullCData(oldp+67,(vlSelf->Top__DOT__WBReg_rd),5);
    bufp->fullBit(oldp+68,(vlSelf->Top__DOT__WBReg_memvalid));
    bufp->fullCData(oldp+69,(vlSelf->Top__DOT__WBReg_memsext),3);
    bufp->fullQData(oldp+70,(vlSelf->Top__DOT__WBReg_rdata),64);
    bufp->fullBit(oldp+72,(vlSelf->Top__DOT__ISReg_valid));
    bufp->fullIData(oldp+73,(vlSelf->Top__DOT__ISReg_inst),32);
    bufp->fullQData(oldp+74,(vlSelf->Top__DOT__ISReg_pc),64);
    bufp->fullQData(oldp+76,(vlSelf->Top__DOT__mstatus),64);
    bufp->fullQData(oldp+78,(vlSelf->Top__DOT__mtvec),64);
    bufp->fullQData(oldp+80,(vlSelf->Top__DOT__mepc),64);
    bufp->fullQData(oldp+82,(vlSelf->Top__DOT__mcause),64);
    bufp->fullQData(oldp+84,(vlSelf->Top__DOT__rs2v),64);
    bufp->fullQData(oldp+86,(vlSelf->Top__DOT__rs1v),64);
    bufp->fullSData(oldp+88,(vlSelf->Top__DOT__csridx),12);
    bufp->fullBit(oldp+89,(vlSelf->Top__DOT__stall));
    bufp->fullIData(oldp+90,(((IData)(vlSelf->Top__DOT__EXReg_valid)
                               ? vlSelf->Top__DOT__EXReg_inst
                               : 0U)),32);
    bufp->fullQData(oldp+91,(vlSelf->Top__DOT____Vcellinp__ALU__io_rs1v),64);
    bufp->fullQData(oldp+93,(vlSelf->Top__DOT____Vcellinp__ALU__io_rs2v),64);
    bufp->fullQData(oldp+95,(vlSelf->Top__DOT____Vcellinp__ALU__io_csrrv),64);
    bufp->fullQData(oldp+97,(vlSelf->Top__DOT____Vcellinp__ALU__io_pc),64);
    bufp->fullCData(oldp+99,(vlSelf->Top__DOT____Vcellinp__ALU__io_asel),3);
    bufp->fullCData(oldp+100,(vlSelf->Top__DOT____Vcellinp__ALU__io_bsel),3);
    bufp->fullCData(oldp+101,(vlSelf->Top__DOT____Vcellinp__ALU__io_alu_op),5);
    bufp->fullQData(oldp+102,(vlSelf->Top__DOT____Vcellinp__ALU__io_imm),64);
    bufp->fullBit(oldp+104,(((IData)(vlSelf->Top__DOT__EXReg_isword) 
                             & (IData)(vlSelf->Top__DOT__EXReg_valid))));
    bufp->fullQData(oldp+105,((((IData)(vlSelf->Top__DOT__EXReg_isword) 
                                & (IData)(vlSelf->Top__DOT__EXReg_valid))
                                ? (((QData)((IData)(
                                                    (- (IData)(
                                                               (1U 
                                                                & (IData)(
                                                                          (vlSelf->Top__DOT__ALU__DOT__casez_tmp_1 
                                                                           >> 0x1fU))))))) 
                                    << 0x20U) | (QData)((IData)(vlSelf->Top__DOT__ALU__DOT__casez_tmp_1)))
                                : vlSelf->Top__DOT__ALU__DOT__casez_tmp_1)),64);
    bufp->fullQData(oldp+107,(vlSelf->Top__DOT__ALU__DOT__casez_tmp),64);
    bufp->fullQData(oldp+109,(vlSelf->Top__DOT__ALU__DOT__casez_tmp_0),64);
    bufp->fullQData(oldp+111,(vlSelf->Top__DOT__ALU__DOT__casez_tmp_1),64);
    bufp->fullIData(oldp+113,((IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__axi_reg_readAddr)),32);
    bufp->fullBit(oldp+114,((3U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state))));
    bufp->fullBit(oldp+115,((4U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state))));
    bufp->fullBit(oldp+116,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__reqr_reg));
    bufp->fullIData(oldp+117,((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_readAddr)),32);
    bufp->fullBit(oldp+118,((4U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
    bufp->fullBit(oldp+119,((5U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
    bufp->fullIData(oldp+120,((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeAddr)),32);
    bufp->fullBit(oldp+121,((6U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
    bufp->fullQData(oldp+122,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeData),64);
    bufp->fullCData(oldp+124,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_wstrb),8);
    bufp->fullBit(oldp+125,((7U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
    bufp->fullBit(oldp+126,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__reqr_reg));
    bufp->fullBit(oldp+127,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__reqw_reg));
    bufp->fullBit(oldp+128,(vlSelf->Top__DOT___XBar2_io_axi4in_arready));
    bufp->fullQData(oldp+129,(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_2),64);
    bufp->fullCData(oldp+131,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                ? (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0)
                                : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                    ? 0U : ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                             ? 0U : (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0))))),2);
    bufp->fullBit(oldp+132,(vlSelf->Top__DOT__XBar2__DOT___io_axi4in_rvalid_output));
    bufp->fullBit(oldp+133,((1U & ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
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
    bufp->fullBit(oldp+134,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                              ? (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_22)
                              : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                  ? (1U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))
                                  : ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                      ? (1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))
                                      : (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_22))))));
    bufp->fullCData(oldp+135,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                ? ((1U & ((~ (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid)) 
                                          | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_13)))
                                    ? 0U : 3U) : 0U)),2);
    bufp->fullBit(oldp+136,(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_7));
    bufp->fullBit(oldp+137,(((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h4ab110e3__0) 
                             & (IData)(vlSelf->Top__DOT___XBar2_io_axi4in_arready))));
    bufp->fullQData(oldp+138,(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_0),64);
    bufp->fullCData(oldp+140,(((0U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
                                ? 0U : ((1U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
                                         ? ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                             ? (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0)
                                             : ((1U 
                                                 == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                 ? 0U
                                                 : 
                                                ((2U 
                                                  == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                                  ? 0U
                                                  : (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0))))
                                         : 0U))),2);
    bufp->fullBit(oldp+141,(vlSelf->Top__DOT___AXI4Arbiter_io_ifu_bus_axi4_rvalid));
    bufp->fullBit(oldp+142,(vlSelf->Top__DOT__AXI4Arbiter__DOT__ifu_ac));
    bufp->fullBit(oldp+143,(((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0) 
                             & (IData)(vlSelf->Top__DOT___XBar2_io_axi4in_arready))));
    bufp->fullQData(oldp+144,(vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_rdata),64);
    bufp->fullCData(oldp+146,(((1U & ((~ (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2)) 
                                      | (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_3)))
                                ? 0U : ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                         ? (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0)
                                         : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                             ? 0U : 
                                            ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                              ? 0U : (IData)(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0)))))),2);
    bufp->fullBit(oldp+147,(vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_rvalid));
    bufp->fullBit(oldp+148,(((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0) 
                             & ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                 ? (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_21)
                                 : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                     ? (IData)(vlSelf->Top__DOT___SRAM_io_axi4_awready)
                                     : ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                         ? ((~ (IData)(
                                                       (0U 
                                                        != (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state)))) 
                                            | (1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state)))
                                         : (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_21)))))));
    bufp->fullBit(oldp+149,(((IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT____VdfgTmp_h56a4a0d3__0) 
                             & ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                 ? (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_22)
                                 : ((1U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                     ? (1U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))
                                     : ((2U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                         ? (1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))
                                         : (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_22)))))));
    bufp->fullCData(oldp+150,(((1U & ((~ (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_2)) 
                                      | (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT___GEN_3)))
                                ? 0U : ((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                         ? ((1U & (
                                                   (~ (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid)) 
                                                   | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_13)))
                                             ? 0U : 3U)
                                         : 0U))),2);
    bufp->fullBit(oldp+151,(vlSelf->Top__DOT___AXI4Arbiter_io_lsu_bus_axi4_bvalid));
    bufp->fullBit(oldp+152,(vlSelf->Top__DOT__AXI4Arbiter__DOT__lsu_ac));
    bufp->fullIData(oldp+153,(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1),32);
    bufp->fullBit(oldp+154,(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_arvalid));
    bufp->fullBit(oldp+155,(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready));
    bufp->fullIData(oldp+156,(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2),32);
    bufp->fullBit(oldp+157,(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_awvalid));
    bufp->fullQData(oldp+158,(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3),64);
    bufp->fullCData(oldp+160,(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_4),8);
    bufp->fullBit(oldp+161,(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready));
    bufp->fullBit(oldp+162,(((0U == (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__state))
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
    bufp->fullCData(oldp+163,(vlSelf->Top__DOT__AXI4Arbiter__DOT__state),2);
    bufp->fullIData(oldp+164,(vlSelf->Top__DOT___GEN_0),32);
    bufp->fullCData(oldp+165,(vlSelf->Top__DOT___Decoder_io_rs1),5);
    bufp->fullCData(oldp+166,(vlSelf->Top__DOT___Decoder_io_rs2),5);
    bufp->fullCData(oldp+167,(((IData)(vlSelf->Top__DOT__IDReg_valid)
                                ? (0x1fU & (vlSelf->Top__DOT__IDReg_inst 
                                            >> 7U))
                                : 0U)),5);
    bufp->fullBit(oldp+168,(((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_76) 
                             | ((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71)) 
                                & ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_67) 
                                   | ((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66)) 
                                      & (IData)(vlSelf->Top__DOT___Decoder_io_csr_en)))))));
    bufp->fullBit(oldp+169,(vlSelf->Top__DOT___Decoder_io_csr_en));
    bufp->fullQData(oldp+170,(vlSelf->Top__DOT__Decoder__DOT__casez_tmp),64);
    bufp->fullCData(oldp+172,(vlSelf->Top__DOT___Decoder_io_alu_op),5);
    bufp->fullCData(oldp+173,(((0x37U == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                ? 0U : ((0x17U == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                         ? 3U : ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_70)
                                                  ? 1U
                                                  : 
                                                 ((0x6fU 
                                                   == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0))
                                                   ? 3U
                                                   : 
                                                  (((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71) 
                                                    | (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_67))
                                                    ? 1U
                                                    : 
                                                   ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66)
                                                     ? 3U
                                                     : 
                                                    ((IData)(vlSelf->Top__DOT___Decoder_io_csr_en)
                                                      ? 6U
                                                      : 0U)))))))),3);
    bufp->fullCData(oldp+174,((((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74) 
                                | (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_73))
                                ? 4U : ((0x4293U == (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_14))
                                         ? 5U : ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_72)
                                                  ? 4U
                                                  : 
                                                 ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_69)
                                                   ? 5U
                                                   : 
                                                  (((0x6fU 
                                                     == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
                                                    | (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71))
                                                    ? 4U
                                                    : 
                                                   ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_67)
                                                     ? 2U
                                                     : 
                                                    ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_66) 
                                                     << 2U)))))))),3);
    bufp->fullBit(oldp+175,((0x100073U == vlSelf->Top__DOT___GEN_0)));
    bufp->fullBit(oldp+176,(((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)) 
                             & ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h8d1c1e58__0) 
                                | ((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_75)) 
                                   & (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71))))));
    bufp->fullBit(oldp+177,(((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_76)) 
                             & (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_71))));
    bufp->fullCData(oldp+178,(((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_76)
                                ? 0U : ((0x23U == (IData)(vlSelf->Top__DOT___GEN_1))
                                         ? 1U : ((0xa3U 
                                                  == (IData)(vlSelf->Top__DOT___GEN_1))
                                                  ? 3U
                                                  : 
                                                 ((0x123U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1))
                                                   ? 0xfU
                                                   : 
                                                  (0xffU 
                                                   & (- (IData)(
                                                                (0x1a3U 
                                                                 == (IData)(vlSelf->Top__DOT___GEN_1)))))))))),8);
    bufp->fullCData(oldp+179,(((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)
                                ? 6U : ((0x83U == (IData)(vlSelf->Top__DOT___GEN_1))
                                         ? 4U : ((0x283U 
                                                  == (IData)(vlSelf->Top__DOT___GEN_1))
                                                  ? 1U
                                                  : 
                                                 ((3U 
                                                   == (IData)(vlSelf->Top__DOT___GEN_1))
                                                   ? 3U
                                                   : 
                                                  ((0x203U 
                                                    == (IData)(vlSelf->Top__DOT___GEN_1))
                                                    ? 0U
                                                    : 
                                                   ((0x103U 
                                                     == (IData)(vlSelf->Top__DOT___GEN_1))
                                                     ? 5U
                                                     : 
                                                    (2U 
                                                     | ((0x303U 
                                                         != (IData)(vlSelf->Top__DOT___GEN_1)) 
                                                        << 2U))))))))),3);
    bufp->fullBit(oldp+180,(vlSelf->Top__DOT___Decoder_io_isword));
    bufp->fullBit(oldp+181,(((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_74)) 
                             & ((IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_70) 
                                | ((0x6fU != (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
                                   & ((IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h92124dc1__0) 
                                      | (IData)(vlSelf->Top__DOT___Decoder_io_csr_en)))))));
    bufp->fullBit(oldp+182,(((~ (IData)(vlSelf->Top__DOT__Decoder__DOT___GEN_76)) 
                             & (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h92124dc1__0))));
    bufp->fullQData(oldp+183,(((IData)(vlSelf->Top__DOT__pcsel)
                                ? ((IData)(vlSelf->Top__DOT__stall)
                                    ? 0x114514ULL : 
                                   ((0x67U == (IData)(vlSelf->Top__DOT___GEN_1))
                                     ? (vlSelf->Top__DOT__rs1v 
                                        + vlSelf->Top__DOT__Decoder__DOT__casez_tmp)
                                     : (((0x6fU == (IData)(vlSelf->Top__DOT__Decoder__DOT____VdfgTmp_h1fd6a75a__0)) 
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
                                             : ((0x73U 
                                                 == vlSelf->Top__DOT___GEN_0)
                                                 ? vlSelf->Top__DOT__mtvec
                                                 : 0ULL)))))
                                : 0ULL)),64);
    bufp->fullBit(oldp+185,(vlSelf->Top__DOT___InstFetcher_io_out_valid));
    bufp->fullQData(oldp+186,((QData)((IData)(vlSelf->Top__DOT__InstFetcher__DOT__readAddr))),64);
    bufp->fullIData(oldp+188,(vlSelf->Top__DOT__InstFetcher__DOT__outData),32);
    bufp->fullCData(oldp+189,(vlSelf->Top__DOT__InstFetcher__DOT__state),2);
    bufp->fullQData(oldp+190,(vlSelf->Top__DOT__InstFetcher__DOT__PC),64);
    bufp->fullIData(oldp+192,(vlSelf->Top__DOT__InstFetcher__DOT__readAddr),32);
    bufp->fullIData(oldp+193,(vlSelf->Top__DOT__InstFetcher__DOT__outAddr),32);
    bufp->fullQData(oldp+194,(vlSelf->Top__DOT__InstFetcher__DOT__dnpc_reg),64);
    bufp->fullBit(oldp+196,(vlSelf->Top__DOT__InstFetcher__DOT__dnpc_valid));
    bufp->fullBit(oldp+197,((1U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__state))));
    bufp->fullBit(oldp+198,((2U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__state))));
    bufp->fullBit(oldp+199,((1U & (~ (IData)((0U != (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state)))))));
    bufp->fullIData(oldp+200,(((4U & vlSelf->Top__DOT__InstFetcher__DOT__readAddr)
                                ? (IData)((vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__data_cacheline_reg 
                                           >> 0x20U))
                                : (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__data_cacheline_reg))),32);
    bufp->fullBit(oldp+201,((2U == (IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state))));
    bufp->fullQData(oldp+202,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__data_cacheline_reg),64);
    bufp->fullCData(oldp+204,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__r_state),3);
    bufp->fullQData(oldp+205,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__axi_reg_readAddr),64);
    bufp->fullBit(oldp+207,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__hit));
    bufp->fullSData(oldp+208,((0x1ffU & (vlSelf->Top__DOT__InstFetcher__DOT__readAddr 
                                         >> 3U))),9);
    bufp->fullBit(oldp+209,(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT___GEN_2));
    bufp->fullQData(oldp+210,(((IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_data_ext__DOT___GEN)
                                ? vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_data_ext__DOT__Memory
                               [vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_data_ext__DOT___GEN_0]
                                : 0ULL)),64);
    bufp->fullQData(oldp+212,((QData)((IData)((vlSelf->Top__DOT__InstFetcher__DOT__readAddr 
                                               >> 3U)))),61);
    bufp->fullQData(oldp+214,(((IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT___GEN)
                                ? vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT__Memory
                               [vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_tag_ext__DOT___GEN_0]
                                : 0ULL)),61);
    bufp->fullBit(oldp+216,(((IData)(vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT___GEN) 
                             & vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT__Memory
                             [vlSelf->Top__DOT__InstFetcher__DOT__icache__DOT__cache_valid_ext__DOT___GEN_0])));
    bufp->fullIData(oldp+217,((((2U != (IData)(vlSelf->Top__DOT__XBar2__DOT__state_r)) 
                                | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_7))
                                ? 0U : vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1)),32);
    bufp->fullBit(oldp+218,(vlSelf->Top__DOT___XBar2_io_axi4out2_arvalid));
    bufp->fullBit(oldp+219,(((IData)(vlSelf->Top__DOT__XBar2__DOT____VdfgTmp_hb75ae2a2__0) 
                             & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready))));
    bufp->fullBit(oldp+220,((1U & (~ (IData)(vlSelf->Top__DOT__MyClint__DOT__r_state)))));
    bufp->fullQData(oldp+221,((QData)((IData)(vlSelf->Top__DOT__MyClint__DOT__rdata))),64);
    bufp->fullBit(oldp+223,(vlSelf->Top__DOT__MyClint__DOT__r_state));
    bufp->fullQData(oldp+224,(vlSelf->Top__DOT__MyClint__DOT__mtime_csr),64);
    bufp->fullIData(oldp+226,(vlSelf->Top__DOT__MyClint__DOT__rdata),32);
    bufp->fullBit(oldp+227,(vlSelf->Top__DOT___XBar2_io_axi4out0_awvalid));
    bufp->fullQData(oldp+228,((((2U != (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w)) 
                                | (IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_20))
                                ? 0ULL : vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3)),64);
    bufp->fullBit(oldp+230,(((IData)(vlSelf->Top__DOT__XBar2__DOT____VdfgTmp_hd6eae8a8__0) 
                             & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready))));
    bufp->fullBit(oldp+231,((1U & ((~ (IData)((0U != (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state)))) 
                                   | (1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))))));
    bufp->fullBit(oldp+232,((1U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))));
    bufp->fullBit(oldp+233,((3U == (IData)(vlSelf->Top__DOT__MyUart__DOT__w_state))));
    bufp->fullCData(oldp+234,(vlSelf->Top__DOT__MyUart__DOT__w_state),2);
    bufp->fullQData(oldp+235,(vlSelf->Top__DOT__MyUart__DOT__writeData),64);
    bufp->fullIData(oldp+237,(((IData)(vlSelf->Top__DOT__LSReg_valid)
                                ? vlSelf->Top__DOT__LSReg_inst
                                : 0U)),32);
    bufp->fullQData(oldp+238,(((IData)(vlSelf->Top__DOT__LSReg_valid)
                                ? vlSelf->Top__DOT__LSReg_pc
                                : 0ULL)),64);
    bufp->fullQData(oldp+240,(((IData)(vlSelf->Top__DOT__LSReg_valid)
                                ? vlSelf->Top__DOT__LSReg_alures
                                : 0ULL)),64);
    bufp->fullBit(oldp+242,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_memvalid));
    bufp->fullBit(oldp+243,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wen));
    bufp->fullQData(oldp+244,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wmask),64);
    bufp->fullCData(oldp+246,(((IData)(vlSelf->Top__DOT__LSReg_valid)
                                ? (IData)(vlSelf->Top__DOT__LSReg_memsext)
                                : 6U)),3);
    bufp->fullIData(oldp+247,(vlSelf->Top__DOT___GEN_2),32);
    bufp->fullQData(oldp+248,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_wdata),64);
    bufp->fullBit(oldp+250,(((IData)(vlSelf->Top__DOT__LSReg_rden) 
                             & (IData)(vlSelf->Top__DOT__LSReg_valid))));
    bufp->fullCData(oldp+251,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_rd),5);
    bufp->fullSData(oldp+252,(vlSelf->Top__DOT____Vcellinp__NPC_Mem__io_in_bits_csridx),12);
    bufp->fullQData(oldp+253,(((IData)(vlSelf->Top__DOT__LSReg_valid)
                                ? vlSelf->Top__DOT__LSReg_csrwv
                                : 0ULL)),64);
    bufp->fullBit(oldp+255,(((IData)(vlSelf->Top__DOT__LSReg_csr_en) 
                             & (IData)(vlSelf->Top__DOT__LSReg_valid))));
    bufp->fullBit(oldp+256,(vlSelf->Top__DOT___NPC_Mem_io_in_ready));
    bufp->fullBit(oldp+257,(vlSelf->Top__DOT___NPC_Mem_io_out_valid));
    bufp->fullIData(oldp+258,(vlSelf->Top__DOT__NPC_Mem__DOT__instreg),32);
    bufp->fullQData(oldp+259,(vlSelf->Top__DOT__NPC_Mem__DOT__pcreg),64);
    bufp->fullQData(oldp+261,(vlSelf->Top__DOT__NPC_Mem__DOT__aluresreg),64);
    bufp->fullBit(oldp+263,(vlSelf->Top__DOT__NPC_Mem__DOT__memvalidreg));
    bufp->fullBit(oldp+264,(vlSelf->Top__DOT__NPC_Mem__DOT__rdenreg));
    bufp->fullCData(oldp+265,(vlSelf->Top__DOT__NPC_Mem__DOT__rdreg),5);
    bufp->fullSData(oldp+266,(vlSelf->Top__DOT__NPC_Mem__DOT__csridxreg),12);
    bufp->fullQData(oldp+267,(vlSelf->Top__DOT__NPC_Mem__DOT__csrwvreg),64);
    bufp->fullBit(oldp+269,(vlSelf->Top__DOT__NPC_Mem__DOT__csrenreg));
    bufp->fullCData(oldp+270,(vlSelf->Top__DOT__NPC_Mem__DOT__memsextreg),3);
    bufp->fullQData(oldp+271,(vlSelf->Top__DOT__NPC_Mem__DOT__readData),64);
    bufp->fullIData(oldp+273,(vlSelf->Top__DOT__NPC_Mem__DOT__readAddr),32);
    bufp->fullIData(oldp+274,(vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr),32);
    bufp->fullQData(oldp+275,(vlSelf->Top__DOT__NPC_Mem__DOT__writeData),64);
    bufp->fullCData(oldp+277,(vlSelf->Top__DOT__NPC_Mem__DOT__writeStrb),8);
    bufp->fullCData(oldp+278,(vlSelf->Top__DOT__NPC_Mem__DOT__r_state),2);
    bufp->fullCData(oldp+279,(vlSelf->Top__DOT__NPC_Mem__DOT__w_state),2);
    bufp->fullCData(oldp+280,(vlSelf->Top__DOT__NPC_Mem__DOT__r_offset_reg),3);
    bufp->fullBit(oldp+281,(vlSelf->Top__DOT__NPC_Mem__DOT__w_is_sram));
    bufp->fullQData(oldp+282,((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__readAddr))),64);
    bufp->fullBit(oldp+284,((1U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state))));
    bufp->fullBit(oldp+285,((2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__r_state))));
    bufp->fullQData(oldp+286,((QData)((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr))),64);
    bufp->fullBit(oldp+288,((1U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state))));
    bufp->fullBit(oldp+289,((2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__w_state))));
    bufp->fullBit(oldp+290,((1U & (~ (IData)((0U != (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state)))))));
    bufp->fullQData(oldp+291,(vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_rdata),64);
    bufp->fullBit(oldp+293,((2U == (IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state))));
    bufp->fullBit(oldp+294,(vlSelf->Top__DOT__NPC_Mem__DOT___dcache_io_io_bvalid));
    bufp->fullCData(oldp+295,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__casez_tmp),3);
    bufp->fullQData(oldp+296,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__data_cacheline_reg),64);
    bufp->fullCData(oldp+298,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__s_state),3);
    bufp->fullQData(oldp+299,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_readAddr),64);
    bufp->fullQData(oldp+301,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeAddr),64);
    bufp->fullQData(oldp+303,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeMask),64);
    bufp->fullBit(oldp+305,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__uncached_r));
    bufp->fullQData(oldp+306,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi4_readData),64);
    bufp->fullSData(oldp+308,((0x1ffU & (vlSelf->Top__DOT__NPC_Mem__DOT__readAddr 
                                         >> 3U))),9);
    bufp->fullSData(oldp+309,((0x1ffU & (vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr 
                                         >> 3U))),9);
    bufp->fullBit(oldp+310,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_5));
    bufp->fullBit(oldp+311,(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT___GEN_9));
    bufp->fullQData(oldp+312,((((~ vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeMask) 
                                & ((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_1)
                                    ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT__Memory
                                   [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_2]
                                    : 0ULL)) | (vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__axi_reg_writeMask 
                                                & vlSelf->Top__DOT__NPC_Mem__DOT__writeData))),64);
    bufp->fullQData(oldp+314,(((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN)
                                ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT__Memory
                               [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_0]
                                : 0ULL)),64);
    bufp->fullQData(oldp+316,(((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_1)
                                ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT__Memory
                               [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_data_ext__DOT___GEN_2]
                                : 0ULL)),64);
    bufp->fullQData(oldp+318,((QData)((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__readAddr 
                                               >> 3U)))),61);
    bufp->fullQData(oldp+320,((QData)((IData)((vlSelf->Top__DOT__NPC_Mem__DOT__writeAddr 
                                               >> 3U)))),61);
    bufp->fullQData(oldp+322,(((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT___GEN)
                                ? vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT__Memory
                               [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_tag_ext__DOT___GEN_0]
                                : 0ULL)),61);
    bufp->fullBit(oldp+324,(((IData)(vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT___GEN) 
                             & vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT__Memory
                             [vlSelf->Top__DOT__NPC_Mem__DOT__dcache__DOT__cache_valid_ext__DOT___GEN_0])));
    bufp->fullBit(oldp+325,(((IData)(vlSelf->Top__DOT__WBReg_valid) 
                             & ((IData)(vlSelf->Top__DOT__WBReg_rden) 
                                & (0U != (IData)(vlSelf->Top__DOT__WBReg_rd))))));
    bufp->fullQData(oldp+326,(((IData)(vlSelf->Top__DOT__WBReg_memvalid)
                                ? ((IData)(vlSelf->Top__DOT__WBReg_valid)
                                    ? ((4U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                        ? ((2U & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                            ? vlSelf->Top__DOT__WBReg_rdata
                                            : ((1U 
                                                & (IData)(vlSelf->Top__DOT__WBReg_memsext))
                                                ? (
                                                   ((QData)((IData)(
                                                                    (- (IData)(
                                                                               (1U 
                                                                                & (IData)(
                                                                                (vlSelf->Top__DOT__WBReg_rdata 
                                                                                >> 0x1fU))))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(vlSelf->Top__DOT__WBReg_rdata)))
                                                : (
                                                   ((- (QData)((IData)(
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
                                                ? (
                                                   ((- (QData)((IData)(
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
    bufp->fullQData(oldp+328,(vlSelf->Top__DOT___R_ext_R0_data),64);
    bufp->fullQData(oldp+330,(vlSelf->Top__DOT___R_ext_R1_data),64);
    bufp->fullQData(oldp+332,(vlSelf->Top__DOT__R_ext__DOT__Memory[0]),64);
    bufp->fullQData(oldp+334,(vlSelf->Top__DOT__R_ext__DOT__Memory[1]),64);
    bufp->fullQData(oldp+336,(vlSelf->Top__DOT__R_ext__DOT__Memory[2]),64);
    bufp->fullQData(oldp+338,(vlSelf->Top__DOT__R_ext__DOT__Memory[3]),64);
    bufp->fullQData(oldp+340,(vlSelf->Top__DOT__R_ext__DOT__Memory[4]),64);
    bufp->fullQData(oldp+342,(vlSelf->Top__DOT__R_ext__DOT__Memory[5]),64);
    bufp->fullQData(oldp+344,(vlSelf->Top__DOT__R_ext__DOT__Memory[6]),64);
    bufp->fullQData(oldp+346,(vlSelf->Top__DOT__R_ext__DOT__Memory[7]),64);
    bufp->fullQData(oldp+348,(vlSelf->Top__DOT__R_ext__DOT__Memory[8]),64);
    bufp->fullQData(oldp+350,(vlSelf->Top__DOT__R_ext__DOT__Memory[9]),64);
    bufp->fullQData(oldp+352,(vlSelf->Top__DOT__R_ext__DOT__Memory[10]),64);
    bufp->fullQData(oldp+354,(vlSelf->Top__DOT__R_ext__DOT__Memory[11]),64);
    bufp->fullQData(oldp+356,(vlSelf->Top__DOT__R_ext__DOT__Memory[12]),64);
    bufp->fullQData(oldp+358,(vlSelf->Top__DOT__R_ext__DOT__Memory[13]),64);
    bufp->fullQData(oldp+360,(vlSelf->Top__DOT__R_ext__DOT__Memory[14]),64);
    bufp->fullQData(oldp+362,(vlSelf->Top__DOT__R_ext__DOT__Memory[15]),64);
    bufp->fullQData(oldp+364,(vlSelf->Top__DOT__R_ext__DOT__Memory[16]),64);
    bufp->fullQData(oldp+366,(vlSelf->Top__DOT__R_ext__DOT__Memory[17]),64);
    bufp->fullQData(oldp+368,(vlSelf->Top__DOT__R_ext__DOT__Memory[18]),64);
    bufp->fullQData(oldp+370,(vlSelf->Top__DOT__R_ext__DOT__Memory[19]),64);
    bufp->fullQData(oldp+372,(vlSelf->Top__DOT__R_ext__DOT__Memory[20]),64);
    bufp->fullQData(oldp+374,(vlSelf->Top__DOT__R_ext__DOT__Memory[21]),64);
    bufp->fullQData(oldp+376,(vlSelf->Top__DOT__R_ext__DOT__Memory[22]),64);
    bufp->fullQData(oldp+378,(vlSelf->Top__DOT__R_ext__DOT__Memory[23]),64);
    bufp->fullQData(oldp+380,(vlSelf->Top__DOT__R_ext__DOT__Memory[24]),64);
    bufp->fullQData(oldp+382,(vlSelf->Top__DOT__R_ext__DOT__Memory[25]),64);
    bufp->fullQData(oldp+384,(vlSelf->Top__DOT__R_ext__DOT__Memory[26]),64);
    bufp->fullQData(oldp+386,(vlSelf->Top__DOT__R_ext__DOT__Memory[27]),64);
    bufp->fullQData(oldp+388,(vlSelf->Top__DOT__R_ext__DOT__Memory[28]),64);
    bufp->fullQData(oldp+390,(vlSelf->Top__DOT__R_ext__DOT__Memory[29]),64);
    bufp->fullQData(oldp+392,(vlSelf->Top__DOT__R_ext__DOT__Memory[30]),64);
    bufp->fullQData(oldp+394,(vlSelf->Top__DOT__R_ext__DOT__Memory[31]),64);
    bufp->fullIData(oldp+396,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_5)
                                    ? 0U : vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1)
                                : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_16)
                                    ? vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_1
                                    : 0U))),32);
    bufp->fullBit(oldp+397,(vlSelf->Top__DOT___XBar2_io_axi4out1_arvalid));
    bufp->fullBit(oldp+398,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                              ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
                                 & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready))
                              : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_18) 
                                 & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_rready)))));
    bufp->fullIData(oldp+399,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_5)
                                    ? 0U : vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2)
                                : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_16)
                                    ? vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_2
                                    : 0U))),32);
    bufp->fullBit(oldp+400,(vlSelf->Top__DOT___XBar2_io_axi4out1_awvalid));
    bufp->fullQData(oldp+401,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_5)
                                    ? 0ULL : vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3)
                                : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_16)
                                    ? vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_3
                                    : 0ULL))),64);
    bufp->fullCData(oldp+403,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                                ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_5)
                                    ? 0U : (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_4))
                                : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_16)
                                    ? (IData)(vlSelf->Top__DOT__AXI4Arbiter__DOT__casez_tmp_4)
                                    : 0U))),8);
    bufp->fullBit(oldp+404,(((0U == (IData)(vlSelf->Top__DOT__XBar2__DOT__state_w))
                              ? ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_17) 
                                 & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready))
                              : ((IData)(vlSelf->Top__DOT__XBar2__DOT___GEN_18) 
                                 & (IData)(vlSelf->Top__DOT___AXI4Arbiter_io_xbar_bus_bready)))));
    bufp->fullBit(oldp+405,((0U == (IData)(vlSelf->Top__DOT__SRAM__DOT__r_state))));
    bufp->fullQData(oldp+406,(vlSelf->Top__DOT__SRAM__DOT__readData),64);
    bufp->fullBit(oldp+408,(vlSelf->Top__DOT__SRAM__DOT__rvalidReg));
    bufp->fullBit(oldp+409,(vlSelf->Top__DOT___SRAM_io_axi4_awready));
    bufp->fullBit(oldp+410,((1U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))));
    bufp->fullBit(oldp+411,((3U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))));
    bufp->fullCData(oldp+412,(vlSelf->Top__DOT__SRAM__DOT__casez_tmp),2);
    bufp->fullCData(oldp+413,(vlSelf->Top__DOT__SRAM__DOT__r_state),2);
    bufp->fullCData(oldp+414,(vlSelf->Top__DOT__SRAM__DOT__delay),8);
    bufp->fullCData(oldp+415,(vlSelf->Top__DOT__SRAM__DOT__delayCounter),8);
    bufp->fullBit(oldp+416,(vlSelf->Top__DOT__SRAM__DOT__delayDone));
    bufp->fullIData(oldp+417,(vlSelf->Top__DOT__SRAM__DOT__readAddr),32);
    bufp->fullCData(oldp+418,(vlSelf->Top__DOT__SRAM__DOT__w_state),2);
    bufp->fullIData(oldp+419,(vlSelf->Top__DOT__SRAM__DOT__writeAddr),32);
    bufp->fullQData(oldp+420,(vlSelf->Top__DOT__SRAM__DOT__writeData),64);
    bufp->fullCData(oldp+422,(vlSelf->Top__DOT__SRAM__DOT__writeStrb),8);
    bufp->fullBit(oldp+423,((((IData)(vlSelf->Top__DOT__SRAM__DOT__delayDone) 
                              & (1U == (IData)(vlSelf->Top__DOT__SRAM__DOT__r_state))) 
                             | (2U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state)))));
    bufp->fullBit(oldp+424,((2U == (IData)(vlSelf->Top__DOT__SRAM__DOT__w_state))));
    bufp->fullQData(oldp+425,(vlSelf->Top__DOT__SRAM__DOT___dpic_mem_rdata),64);
    bufp->fullQData(oldp+427,(vlSelf->Top__DOT__XBar2__DOT__casez_tmp),64);
    bufp->fullCData(oldp+429,(vlSelf->Top__DOT__XBar2__DOT__casez_tmp_0),2);
    bufp->fullCData(oldp+430,(vlSelf->Top__DOT__XBar2__DOT__state_r),2);
    bufp->fullCData(oldp+431,(vlSelf->Top__DOT__XBar2__DOT__state_w),2);
    bufp->fullBit(oldp+432,(vlSelf->clock));
    bufp->fullBit(oldp+433,(vlSelf->reset));
    bufp->fullIData(oldp+434,(vlSelf->io_inst),32);
    bufp->fullQData(oldp+435,(vlSelf->io_pc),64);
    bufp->fullQData(oldp+437,(vlSelf->io_npc),64);
    bufp->fullBit(oldp+439,(vlSelf->Top__DOT____Vcellinp__InstFetcher__io_in_valid));
    bufp->fullBit(oldp+440,(((~ (IData)(vlSelf->reset)) 
                             & (IData)(vlSelf->Top__DOT__IDRegen))));
    bufp->fullQData(oldp+441,(0ULL),64);
    bufp->fullCData(oldp+443,(0U),2);
    bufp->fullIData(oldp+444,(0U),32);
    bufp->fullCData(oldp+445,(0U),8);
    bufp->fullBit(oldp+446,(1U));
    bufp->fullCData(oldp+447,(0U),5);
}
