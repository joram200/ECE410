// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vinterface__Syms.h"


void Vinterface___024root__trace_chg_0_sub_0(Vinterface___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vinterface___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root__trace_chg_0\n"); );
    // Body
    Vinterface___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vinterface___024root*>(voidSelf);
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vinterface___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vinterface___024root__trace_chg_0_sub_0(Vinterface___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root__trace_chg_0_sub_0\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity[2U])))) {
        bufp->chgBit(oldp+0,(vlSelfRef.tb_interface__DOT__rst_n));
        bufp->chgWData(oldp+1,(vlSelfRef.tb_interface__DOT__rx_tdata),128);
        bufp->chgBit(oldp+5,(vlSelfRef.tb_interface__DOT__rx_tvalid));
        bufp->chgBit(oldp+6,(vlSelfRef.tb_interface__DOT__rx_tlast));
        bufp->chgBit(oldp+7,(vlSelfRef.tb_interface__DOT__tx_tready));
        bufp->chgBit(oldp+8,(vlSelfRef.tb_interface__DOT__core_valid_out));
        bufp->chgIData(oldp+9,(vlSelfRef.tb_interface__DOT__core_x_hat_0),32);
        bufp->chgIData(oldp+10,(vlSelfRef.tb_interface__DOT__core_x_hat_1),32);
        bufp->chgIData(oldp+11,(vlSelfRef.tb_interface__DOT__core_x_hat_2),32);
        bufp->chgBit(oldp+12,(vlSelfRef.tb_interface__DOT__all_pass));
        bufp->chgWData(oldp+13,(vlSelfRef.tb_interface__DOT__got_cpld),128);
        bufp->chgWData(oldp+17,(vlSelfRef.tb_interface__DOT__exp_cpld),128);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[3U]))) {
        bufp->chgBit(oldp+21,((0U == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__state))));
        bufp->chgWData(oldp+22,(vlSelfRef.tb_interface__DOT__tx_tdata),128);
        bufp->chgBit(oldp+26,(vlSelfRef.tb_interface__DOT__tx_tvalid));
        bufp->chgBit(oldp+27,(vlSelfRef.tb_interface__DOT__tx_tlast));
        bufp->chgBit(oldp+28,(vlSelfRef.tb_interface__DOT__dut__DOT__meas_pulse));
        bufp->chgIData(oldp+29,(vlSelfRef.tb_interface__DOT__dut__DOT__c_wdata),32);
        bufp->chgIData(oldp+30,(vlSelfRef.tb_interface__DOT__dut__DOT__reg_ctrl),32);
        bufp->chgIData(oldp+31,(vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat0),32);
        bufp->chgIData(oldp+32,(vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat1),32);
        bufp->chgIData(oldp+33,(vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat2),32);
        bufp->chgBit(oldp+34,(vlSelfRef.tb_interface__DOT__dut__DOT__busy_r));
        bufp->chgCData(oldp+35,(vlSelfRef.tb_interface__DOT__dut__DOT__c_fmt),3);
        bufp->chgCData(oldp+36,(vlSelfRef.tb_interface__DOT__dut__DOT__c_type),5);
        bufp->chgSData(oldp+37,(vlSelfRef.tb_interface__DOT__dut__DOT__c_req_id),16);
        bufp->chgCData(oldp+38,(vlSelfRef.tb_interface__DOT__dut__DOT__c_tag),8);
        bufp->chgIData(oldp+39,(vlSelfRef.tb_interface__DOT__dut__DOT__c_addr),32);
        bufp->chgCData(oldp+40,(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off),3);
        bufp->chgCData(oldp+41,(vlSelfRef.tb_interface__DOT__dut__DOT__state),2);
    }
    bufp->chgBit(oldp+42,(vlSelfRef.tb_interface__DOT__clk));
    bufp->chgIData(oldp+43,((((IData)(vlSelfRef.tb_interface__DOT__dut__DOT__busy_r) 
                              << 1U) | (IData)(vlSelfRef.tb_interface__DOT__core_valid_out))),32);
    bufp->chgIData(oldp+44,(((4U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                              ? ((2U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                                  ? 0U : ((1U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                                           ? vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat2
                                           : vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat1))
                              : ((2U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                                  ? ((1U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                                      ? vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat0
                                      : 0U) : ((1U 
                                                & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                                                ? (
                                                   ((IData)(vlSelfRef.tb_interface__DOT__dut__DOT__busy_r) 
                                                    << 1U) 
                                                   | (IData)(vlSelfRef.tb_interface__DOT__core_valid_out))
                                                : vlSelfRef.tb_interface__DOT__dut__DOT__reg_ctrl)))),32);
}

void Vinterface___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root__trace_cleanup\n"); );
    // Body
    Vinterface___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vinterface___024root*>(voidSelf);
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
