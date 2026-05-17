// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vinterface__Syms.h"


VL_ATTR_COLD void Vinterface___024root__trace_init_sub__TOP__0(Vinterface___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root__trace_init_sub__TOP__0\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    tracep->pushPrefix("tb_interface", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+42,0,"clk",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+0,0,"rst_n",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+1,0,"rx_tdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBit(c+5,0,"rx_tvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+21,0,"rx_tready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"rx_tlast",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+22,0,"tx_tdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBit(c+26,0,"tx_tvalid",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+7,0,"tx_tready",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+27,0,"tx_tlast",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"core_valid_in",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+29,0,"core_y",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+8,0,"core_valid_out",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+9,0,"core_x_hat_0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"core_x_hat_1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+11,0,"core_x_hat_2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+12,0,"all_pass",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+13,0,"got_cpld",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declArray(c+17,0,"exp_cpld",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBus(c+45,0,"CTRL_WDATA",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+46,0,"MEAS_WDATA",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+47,0,"REQ_ID",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+48,0,"TAG_WR_CTRL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+49,0,"TAG_RD_CTRL",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+50,0,"TAG_WR_MEAS",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->pushPrefix("dut", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+51,0,"COMPLETER_ID",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+42,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+0,0,"rst_n",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+1,0,"rx_tdata",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBit(c+5,0,"rx_tvalid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+21,0,"rx_tready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+6,0,"rx_tlast",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declArray(c+22,0,"tx_tdata",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 127,0);
    tracep->declBit(c+26,0,"tx_tvalid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+7,0,"tx_tready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+27,0,"tx_tlast",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+28,0,"core_valid_in",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+29,0,"core_y",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+8,0,"core_valid_out",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+9,0,"core_x_hat_0",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+10,0,"core_x_hat_1",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+11,0,"core_x_hat_2",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+52,0,"FMT_3DW_NODATA",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+53,0,"FMT_3DW_DATA",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+54,0,"TYPE_MEM",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+55,0,"TYPE_CPLD",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+30,0,"reg_ctrl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+31,0,"reg_xhat0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+32,0,"reg_xhat1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+33,0,"reg_xhat2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBit(c+34,0,"busy_r",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+43,0,"reg_stat",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+35,0,"c_fmt",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+36,0,"c_type",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 4,0);
    tracep->declBus(c+37,0,"c_req_id",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+38,0,"c_tag",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 7,0);
    tracep->declBus(c+39,0,"c_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+40,0,"c_dw_off",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 2,0);
    tracep->declBus(c+29,0,"c_wdata",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+44,0,"rd_data",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+41,0,"state",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+28,0,"meas_pulse",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
    tracep->popPrefix();
}

VL_ATTR_COLD void Vinterface___024root__trace_init_top(Vinterface___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root__trace_init_top\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vinterface___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vinterface___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vinterface___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vinterface___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vinterface___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vinterface___024root__trace_register(Vinterface___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root__trace_register\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vinterface___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vinterface___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vinterface___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vinterface___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vinterface___024root__trace_const_0_sub_0(Vinterface___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vinterface___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root__trace_const_0\n"); );
    // Body
    Vinterface___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vinterface___024root*>(voidSelf);
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vinterface___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vinterface___024root__trace_const_0_sub_0(Vinterface___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root__trace_const_0_sub_0\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullIData(oldp+45,(0xdeadbeefU),32);
    bufp->fullIData(oldp+46,(0xcafebabeU),32);
    bufp->fullSData(oldp+47,(0xabcdU),16);
    bufp->fullCData(oldp+48,(1U),8);
    bufp->fullCData(oldp+49,(2U),8);
    bufp->fullCData(oldp+50,(3U),8);
    bufp->fullSData(oldp+51,(8U),16);
    bufp->fullCData(oldp+52,(0U),3);
    bufp->fullCData(oldp+53,(2U),3);
    bufp->fullCData(oldp+54,(0U),5);
    bufp->fullCData(oldp+55,(0x0aU),5);
}

VL_ATTR_COLD void Vinterface___024root__trace_full_0_sub_0(Vinterface___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vinterface___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root__trace_full_0\n"); );
    // Body
    Vinterface___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vinterface___024root*>(voidSelf);
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vinterface___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vinterface___024root__trace_full_0_sub_0(Vinterface___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root__trace_full_0_sub_0\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullBit(oldp+0,(vlSelfRef.tb_interface__DOT__rst_n));
    bufp->fullWData(oldp+1,(vlSelfRef.tb_interface__DOT__rx_tdata),128);
    bufp->fullBit(oldp+5,(vlSelfRef.tb_interface__DOT__rx_tvalid));
    bufp->fullBit(oldp+6,(vlSelfRef.tb_interface__DOT__rx_tlast));
    bufp->fullBit(oldp+7,(vlSelfRef.tb_interface__DOT__tx_tready));
    bufp->fullBit(oldp+8,(vlSelfRef.tb_interface__DOT__core_valid_out));
    bufp->fullIData(oldp+9,(vlSelfRef.tb_interface__DOT__core_x_hat_0),32);
    bufp->fullIData(oldp+10,(vlSelfRef.tb_interface__DOT__core_x_hat_1),32);
    bufp->fullIData(oldp+11,(vlSelfRef.tb_interface__DOT__core_x_hat_2),32);
    bufp->fullBit(oldp+12,(vlSelfRef.tb_interface__DOT__all_pass));
    bufp->fullWData(oldp+13,(vlSelfRef.tb_interface__DOT__got_cpld),128);
    bufp->fullWData(oldp+17,(vlSelfRef.tb_interface__DOT__exp_cpld),128);
    bufp->fullBit(oldp+21,((0U == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__state))));
    bufp->fullWData(oldp+22,(vlSelfRef.tb_interface__DOT__tx_tdata),128);
    bufp->fullBit(oldp+26,(vlSelfRef.tb_interface__DOT__tx_tvalid));
    bufp->fullBit(oldp+27,(vlSelfRef.tb_interface__DOT__tx_tlast));
    bufp->fullBit(oldp+28,(vlSelfRef.tb_interface__DOT__dut__DOT__meas_pulse));
    bufp->fullIData(oldp+29,(vlSelfRef.tb_interface__DOT__dut__DOT__c_wdata),32);
    bufp->fullIData(oldp+30,(vlSelfRef.tb_interface__DOT__dut__DOT__reg_ctrl),32);
    bufp->fullIData(oldp+31,(vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat0),32);
    bufp->fullIData(oldp+32,(vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat1),32);
    bufp->fullIData(oldp+33,(vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat2),32);
    bufp->fullBit(oldp+34,(vlSelfRef.tb_interface__DOT__dut__DOT__busy_r));
    bufp->fullCData(oldp+35,(vlSelfRef.tb_interface__DOT__dut__DOT__c_fmt),3);
    bufp->fullCData(oldp+36,(vlSelfRef.tb_interface__DOT__dut__DOT__c_type),5);
    bufp->fullSData(oldp+37,(vlSelfRef.tb_interface__DOT__dut__DOT__c_req_id),16);
    bufp->fullCData(oldp+38,(vlSelfRef.tb_interface__DOT__dut__DOT__c_tag),8);
    bufp->fullIData(oldp+39,(vlSelfRef.tb_interface__DOT__dut__DOT__c_addr),32);
    bufp->fullCData(oldp+40,(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off),3);
    bufp->fullCData(oldp+41,(vlSelfRef.tb_interface__DOT__dut__DOT__state),2);
    bufp->fullBit(oldp+42,(vlSelfRef.tb_interface__DOT__clk));
    bufp->fullIData(oldp+43,((((IData)(vlSelfRef.tb_interface__DOT__dut__DOT__busy_r) 
                               << 1U) | (IData)(vlSelfRef.tb_interface__DOT__core_valid_out))),32);
    bufp->fullIData(oldp+44,(((4U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                               ? ((2U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                                   ? 0U : ((1U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                                            ? vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat2
                                            : vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat1))
                               : ((2U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                                   ? ((1U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                                       ? vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat0
                                       : 0U) : ((1U 
                                                 & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                                                 ? 
                                                (((IData)(vlSelfRef.tb_interface__DOT__dut__DOT__busy_r) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.tb_interface__DOT__core_valid_out))
                                                 : vlSelfRef.tb_interface__DOT__dut__DOT__reg_ctrl)))),32);
}
