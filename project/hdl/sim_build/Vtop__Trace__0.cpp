// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    bufp->chgBit(oldp+0,(vlSelfRef.clk));
    bufp->chgBit(oldp+1,(vlSelfRef.rst));
    bufp->chgBit(oldp+2,(vlSelfRef.valid_in));
    bufp->chgIData(oldp+3,(vlSelfRef.y),32);
    bufp->chgIData(oldp+4,(vlSelfRef.x_hat_0),32);
    bufp->chgIData(oldp+5,(vlSelfRef.x_hat_1),32);
    bufp->chgIData(oldp+6,(vlSelfRef.x_hat_2),32);
    bufp->chgBit(oldp+7,(vlSelfRef.valid_out));
    bufp->chgBit(oldp+8,(vlSelfRef.kalman_filter__DOT__clk));
    bufp->chgBit(oldp+9,(vlSelfRef.kalman_filter__DOT__rst));
    bufp->chgBit(oldp+10,(vlSelfRef.kalman_filter__DOT__valid_in));
    bufp->chgIData(oldp+11,(vlSelfRef.kalman_filter__DOT__y),32);
    bufp->chgIData(oldp+12,(vlSelfRef.kalman_filter__DOT__x_hat_0),32);
    bufp->chgIData(oldp+13,(vlSelfRef.kalman_filter__DOT__x_hat_1),32);
    bufp->chgIData(oldp+14,(vlSelfRef.kalman_filter__DOT__x_hat_2),32);
    bufp->chgBit(oldp+15,(vlSelfRef.kalman_filter__DOT__valid_out));
    bufp->chgCData(oldp+16,(vlSelfRef.kalman_filter__DOT__state),3);
    bufp->chgIData(oldp+17,(vlSelfRef.kalman_filter__DOT__x0),32);
    bufp->chgIData(oldp+18,(vlSelfRef.kalman_filter__DOT__x1),32);
    bufp->chgIData(oldp+19,(vlSelfRef.kalman_filter__DOT__x2),32);
    bufp->chgIData(oldp+20,(vlSelfRef.kalman_filter__DOT__p00),32);
    bufp->chgIData(oldp+21,(vlSelfRef.kalman_filter__DOT__p01),32);
    bufp->chgIData(oldp+22,(vlSelfRef.kalman_filter__DOT__p02),32);
    bufp->chgIData(oldp+23,(vlSelfRef.kalman_filter__DOT__p11),32);
    bufp->chgIData(oldp+24,(vlSelfRef.kalman_filter__DOT__p12),32);
    bufp->chgIData(oldp+25,(vlSelfRef.kalman_filter__DOT__p22),32);
    bufp->chgIData(oldp+26,(vlSelfRef.kalman_filter__DOT__y_reg),32);
    bufp->chgIData(oldp+27,(vlSelfRef.kalman_filter__DOT__x0p),32);
    bufp->chgIData(oldp+28,(vlSelfRef.kalman_filter__DOT__x1p),32);
    bufp->chgIData(oldp+29,(vlSelfRef.kalman_filter__DOT__x2p),32);
    bufp->chgIData(oldp+30,(vlSelfRef.kalman_filter__DOT__pp00),32);
    bufp->chgIData(oldp+31,(vlSelfRef.kalman_filter__DOT__pp01),32);
    bufp->chgIData(oldp+32,(vlSelfRef.kalman_filter__DOT__pp02),32);
    bufp->chgIData(oldp+33,(vlSelfRef.kalman_filter__DOT__pp11),32);
    bufp->chgIData(oldp+34,(vlSelfRef.kalman_filter__DOT__pp12),32);
    bufp->chgIData(oldp+35,(vlSelfRef.kalman_filter__DOT__pp22),32);
    bufp->chgIData(oldp+36,(vlSelfRef.kalman_filter__DOT__s_reg),32);
    bufp->chgIData(oldp+37,(vlSelfRef.kalman_filter__DOT__k0),32);
    bufp->chgIData(oldp+38,(vlSelfRef.kalman_filter__DOT__k1),32);
    bufp->chgIData(oldp+39,(vlSelfRef.kalman_filter__DOT__k2),32);
    bufp->chgIData(oldp+40,(vlSelfRef.kalman_filter__DOT__x0_out),32);
    bufp->chgIData(oldp+41,(vlSelfRef.kalman_filter__DOT__x1_out),32);
    bufp->chgIData(oldp+42,(vlSelfRef.kalman_filter__DOT__x2_out),32);
    bufp->chgBit(oldp+43,(vlSelfRef.kalman_filter__DOT__vout));
    bufp->chgIData(oldp+44,(vlSelfRef.kalman_filter__DOT__unnamedblk1__DOT__innov),32);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Locals
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
