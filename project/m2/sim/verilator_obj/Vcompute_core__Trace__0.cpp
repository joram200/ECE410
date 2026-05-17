// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vcompute_core__Syms.h"


void Vcompute_core___024root__trace_chg_0_sub_0(Vcompute_core___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vcompute_core___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root__trace_chg_0\n"); );
    // Body
    Vcompute_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcompute_core___024root*>(voidSelf);
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vcompute_core___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vcompute_core___024root__trace_chg_0_sub_0(Vcompute_core___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root__trace_chg_0_sub_0\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity[2U])))) {
        bufp->chgBit(oldp+0,(vlSelfRef.tb_compute_core__DOT__rst));
        bufp->chgBit(oldp+1,(vlSelfRef.tb_compute_core__DOT__valid_in));
        bufp->chgIData(oldp+2,(vlSelfRef.tb_compute_core__DOT__y),32);
        bufp->chgIData(oldp+3,(vlSelfRef.tb_compute_core__DOT__i),32);
        bufp->chgIData(oldp+4,(vlSelfRef.tb_compute_core__DOT__wcnt),32);
        bufp->chgIData(oldp+5,(vlSelfRef.tb_compute_core__DOT__e0),32);
        bufp->chgIData(oldp+6,(vlSelfRef.tb_compute_core__DOT__e1),32);
        bufp->chgIData(oldp+7,(vlSelfRef.tb_compute_core__DOT__e2),32);
        bufp->chgBit(oldp+8,(vlSelfRef.tb_compute_core__DOT__all_pass));
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[3U]))) {
        bufp->chgIData(oldp+9,(vlSelfRef.tb_compute_core__DOT__dut__DOT__x0_out),32);
        bufp->chgIData(oldp+10,(vlSelfRef.tb_compute_core__DOT__dut__DOT__x1_out),32);
        bufp->chgIData(oldp+11,(vlSelfRef.tb_compute_core__DOT__dut__DOT__x2_out),32);
        bufp->chgBit(oldp+12,(vlSelfRef.tb_compute_core__DOT__dut__DOT__vout));
        bufp->chgCData(oldp+13,(vlSelfRef.tb_compute_core__DOT__dut__DOT__state),3);
        bufp->chgIData(oldp+14,(vlSelfRef.tb_compute_core__DOT__dut__DOT__x0),32);
        bufp->chgIData(oldp+15,(vlSelfRef.tb_compute_core__DOT__dut__DOT__x1),32);
        bufp->chgIData(oldp+16,(vlSelfRef.tb_compute_core__DOT__dut__DOT__x2),32);
        bufp->chgIData(oldp+17,(vlSelfRef.tb_compute_core__DOT__dut__DOT__p00),32);
        bufp->chgIData(oldp+18,(vlSelfRef.tb_compute_core__DOT__dut__DOT__p01),32);
        bufp->chgIData(oldp+19,(vlSelfRef.tb_compute_core__DOT__dut__DOT__p02),32);
        bufp->chgIData(oldp+20,(vlSelfRef.tb_compute_core__DOT__dut__DOT__p11),32);
        bufp->chgIData(oldp+21,(vlSelfRef.tb_compute_core__DOT__dut__DOT__p12),32);
        bufp->chgIData(oldp+22,(vlSelfRef.tb_compute_core__DOT__dut__DOT__p22),32);
        bufp->chgIData(oldp+23,(vlSelfRef.tb_compute_core__DOT__dut__DOT__y_reg),32);
        bufp->chgIData(oldp+24,(vlSelfRef.tb_compute_core__DOT__dut__DOT__x0p),32);
        bufp->chgIData(oldp+25,(vlSelfRef.tb_compute_core__DOT__dut__DOT__x1p),32);
        bufp->chgIData(oldp+26,(vlSelfRef.tb_compute_core__DOT__dut__DOT__x2p),32);
        bufp->chgIData(oldp+27,(vlSelfRef.tb_compute_core__DOT__dut__DOT__pp00),32);
        bufp->chgIData(oldp+28,(vlSelfRef.tb_compute_core__DOT__dut__DOT__pp01),32);
        bufp->chgIData(oldp+29,(vlSelfRef.tb_compute_core__DOT__dut__DOT__pp02),32);
        bufp->chgIData(oldp+30,(vlSelfRef.tb_compute_core__DOT__dut__DOT__pp11),32);
        bufp->chgIData(oldp+31,(vlSelfRef.tb_compute_core__DOT__dut__DOT__pp12),32);
        bufp->chgIData(oldp+32,(vlSelfRef.tb_compute_core__DOT__dut__DOT__pp22),32);
        bufp->chgIData(oldp+33,(vlSelfRef.tb_compute_core__DOT__dut__DOT__s_reg),32);
        bufp->chgIData(oldp+34,(vlSelfRef.tb_compute_core__DOT__dut__DOT__k0),32);
        bufp->chgIData(oldp+35,(vlSelfRef.tb_compute_core__DOT__dut__DOT__k1),32);
        bufp->chgIData(oldp+36,(vlSelfRef.tb_compute_core__DOT__dut__DOT__k2),32);
    }
    bufp->chgBit(oldp+37,(vlSelfRef.tb_compute_core__DOT__clk));
    bufp->chgIData(oldp+38,(vlSelfRef.tb_compute_core__DOT__dut__DOT__unnamedblk1__DOT__innov),32);
}

void Vcompute_core___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root__trace_cleanup\n"); );
    // Body
    Vcompute_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcompute_core___024root*>(voidSelf);
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
