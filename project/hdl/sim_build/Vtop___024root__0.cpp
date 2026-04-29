// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

void Vtop___024root___eval_triggers_vec__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers_vec__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vtop___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.kalman_filter__DOT__clk = vlSelfRef.clk;
    vlSelfRef.kalman_filter__DOT__rst = vlSelfRef.rst;
    vlSelfRef.kalman_filter__DOT__valid_in = vlSelfRef.valid_in;
    vlSelfRef.kalman_filter__DOT__y = vlSelfRef.y;
    vlSelfRef.kalman_filter__DOT__x_hat_0 = vlSelfRef.kalman_filter__DOT__x0_out;
    vlSelfRef.kalman_filter__DOT__x_hat_1 = vlSelfRef.kalman_filter__DOT__x1_out;
    vlSelfRef.kalman_filter__DOT__x_hat_2 = vlSelfRef.kalman_filter__DOT__x2_out;
    vlSelfRef.kalman_filter__DOT__valid_out = vlSelfRef.kalman_filter__DOT__vout;
    vlSelfRef.x_hat_0 = vlSelfRef.kalman_filter__DOT__x_hat_0;
    vlSelfRef.x_hat_1 = vlSelfRef.kalman_filter__DOT__x_hat_1;
    vlSelfRef.x_hat_2 = vlSelfRef.kalman_filter__DOT__x_hat_2;
    vlSelfRef.valid_out = vlSelfRef.kalman_filter__DOT__valid_out;
}

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vtop___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_triggers_vec__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers_vec__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((IData)(vlSelfRef.kalman_filter__DOT__clk) 
                                                     & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__kalman_filter__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__kalman_filter__DOT__clk__0 
        = vlSelfRef.kalman_filter__DOT__clk;
}

bool Vtop___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__0__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__0__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__0__a;
    __Vfunc_kalman_filter__DOT__fp_mul__0__a = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__0__b;
    __Vfunc_kalman_filter__DOT__fp_mul__0__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__0__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__0__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__1__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__1__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__1__a;
    __Vfunc_kalman_filter__DOT__fp_mul__1__a = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__1__b;
    __Vfunc_kalman_filter__DOT__fp_mul__1__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__1__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__1__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__2__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__2__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__2__a;
    __Vfunc_kalman_filter__DOT__fp_mul__2__a = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__2__b;
    __Vfunc_kalman_filter__DOT__fp_mul__2__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__2__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__2__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__3__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__3__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__3__a;
    __Vfunc_kalman_filter__DOT__fp_mul__3__a = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__3__b;
    __Vfunc_kalman_filter__DOT__fp_mul__3__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__3__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__3__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__4__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__4__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__4__a;
    __Vfunc_kalman_filter__DOT__fp_mul__4__a = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__4__b;
    __Vfunc_kalman_filter__DOT__fp_mul__4__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__4__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__4__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__5__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__5__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__5__a;
    __Vfunc_kalman_filter__DOT__fp_mul__5__a = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__5__b;
    __Vfunc_kalman_filter__DOT__fp_mul__5__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__5__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__5__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__6__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__6__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__6__a;
    __Vfunc_kalman_filter__DOT__fp_mul__6__a = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__6__b;
    __Vfunc_kalman_filter__DOT__fp_mul__6__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__6__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__6__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__7__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__7__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__7__a;
    __Vfunc_kalman_filter__DOT__fp_mul__7__a = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__7__b;
    __Vfunc_kalman_filter__DOT__fp_mul__7__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__7__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__7__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__8__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__8__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__8__a;
    __Vfunc_kalman_filter__DOT__fp_mul__8__a = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__8__b;
    __Vfunc_kalman_filter__DOT__fp_mul__8__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__8__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__8__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__9__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__9__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__9__b;
    __Vfunc_kalman_filter__DOT__fp_mul__9__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__9__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__9__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__10__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__10__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__10__b;
    __Vfunc_kalman_filter__DOT__fp_mul__10__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__10__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__10__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__11__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__11__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__11__b;
    __Vfunc_kalman_filter__DOT__fp_mul__11__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__11__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__11__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__12__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__12__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__12__b;
    __Vfunc_kalman_filter__DOT__fp_mul__12__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__12__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__12__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__13__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__13__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__13__b;
    __Vfunc_kalman_filter__DOT__fp_mul__13__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__13__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__13__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__14__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__14__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__14__b;
    __Vfunc_kalman_filter__DOT__fp_mul__14__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__14__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__14__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__15__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__15__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__15__b;
    __Vfunc_kalman_filter__DOT__fp_mul__15__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__15__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__15__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__16__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__16__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__16__b;
    __Vfunc_kalman_filter__DOT__fp_mul__16__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__16__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__16__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__17__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__17__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__17__b;
    __Vfunc_kalman_filter__DOT__fp_mul__17__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__17__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__17__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__18__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__18__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__18__b;
    __Vfunc_kalman_filter__DOT__fp_mul__18__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__18__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__18__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__19__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__19__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__19__b;
    __Vfunc_kalman_filter__DOT__fp_mul__19__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__19__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__19__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__20__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__20__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__20__b;
    __Vfunc_kalman_filter__DOT__fp_mul__20__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__20__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__20__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__21__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__21__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__21__b;
    __Vfunc_kalman_filter__DOT__fp_mul__21__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__21__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__21__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__22__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__22__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__22__b;
    __Vfunc_kalman_filter__DOT__fp_mul__22__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__22__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__22__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__23__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__23__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__23__b;
    __Vfunc_kalman_filter__DOT__fp_mul__23__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__23__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__23__prod = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__24__Vfuncout;
    __Vfunc_kalman_filter__DOT__fp_mul__24__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_kalman_filter__DOT__fp_mul__24__b;
    __Vfunc_kalman_filter__DOT__fp_mul__24__b = 0;
    QData/*63:0*/ __Vfunc_kalman_filter__DOT__fp_mul__24__prod;
    __Vfunc_kalman_filter__DOT__fp_mul__24__prod = 0;
    CData/*2:0*/ __Vdly__kalman_filter__DOT__state;
    __Vdly__kalman_filter__DOT__state = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__x0;
    __Vdly__kalman_filter__DOT__x0 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__x1;
    __Vdly__kalman_filter__DOT__x1 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__x2;
    __Vdly__kalman_filter__DOT__x2 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__p00;
    __Vdly__kalman_filter__DOT__p00 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__p01;
    __Vdly__kalman_filter__DOT__p01 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__p02;
    __Vdly__kalman_filter__DOT__p02 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__p11;
    __Vdly__kalman_filter__DOT__p11 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__p12;
    __Vdly__kalman_filter__DOT__p12 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__p22;
    __Vdly__kalman_filter__DOT__p22 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__y_reg;
    __Vdly__kalman_filter__DOT__y_reg = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__x0p;
    __Vdly__kalman_filter__DOT__x0p = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__x1p;
    __Vdly__kalman_filter__DOT__x1p = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__x2p;
    __Vdly__kalman_filter__DOT__x2p = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__pp00;
    __Vdly__kalman_filter__DOT__pp00 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__pp01;
    __Vdly__kalman_filter__DOT__pp01 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__pp02;
    __Vdly__kalman_filter__DOT__pp02 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__pp11;
    __Vdly__kalman_filter__DOT__pp11 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__pp12;
    __Vdly__kalman_filter__DOT__pp12 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__pp22;
    __Vdly__kalman_filter__DOT__pp22 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__s_reg;
    __Vdly__kalman_filter__DOT__s_reg = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__k0;
    __Vdly__kalman_filter__DOT__k0 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__k1;
    __Vdly__kalman_filter__DOT__k1 = 0;
    IData/*31:0*/ __Vdly__kalman_filter__DOT__k2;
    __Vdly__kalman_filter__DOT__k2 = 0;
    // Body
    __Vdly__kalman_filter__DOT__state = vlSelfRef.kalman_filter__DOT__state;
    __Vdly__kalman_filter__DOT__x0 = vlSelfRef.kalman_filter__DOT__x0;
    __Vdly__kalman_filter__DOT__x1 = vlSelfRef.kalman_filter__DOT__x1;
    __Vdly__kalman_filter__DOT__x2 = vlSelfRef.kalman_filter__DOT__x2;
    __Vdly__kalman_filter__DOT__p00 = vlSelfRef.kalman_filter__DOT__p00;
    __Vdly__kalman_filter__DOT__p01 = vlSelfRef.kalman_filter__DOT__p01;
    __Vdly__kalman_filter__DOT__p02 = vlSelfRef.kalman_filter__DOT__p02;
    __Vdly__kalman_filter__DOT__p11 = vlSelfRef.kalman_filter__DOT__p11;
    __Vdly__kalman_filter__DOT__p12 = vlSelfRef.kalman_filter__DOT__p12;
    __Vdly__kalman_filter__DOT__p22 = vlSelfRef.kalman_filter__DOT__p22;
    __Vdly__kalman_filter__DOT__y_reg = vlSelfRef.kalman_filter__DOT__y_reg;
    __Vdly__kalman_filter__DOT__x0p = vlSelfRef.kalman_filter__DOT__x0p;
    __Vdly__kalman_filter__DOT__x1p = vlSelfRef.kalman_filter__DOT__x1p;
    __Vdly__kalman_filter__DOT__x2p = vlSelfRef.kalman_filter__DOT__x2p;
    __Vdly__kalman_filter__DOT__pp00 = vlSelfRef.kalman_filter__DOT__pp00;
    __Vdly__kalman_filter__DOT__pp01 = vlSelfRef.kalman_filter__DOT__pp01;
    __Vdly__kalman_filter__DOT__pp02 = vlSelfRef.kalman_filter__DOT__pp02;
    __Vdly__kalman_filter__DOT__pp11 = vlSelfRef.kalman_filter__DOT__pp11;
    __Vdly__kalman_filter__DOT__pp12 = vlSelfRef.kalman_filter__DOT__pp12;
    __Vdly__kalman_filter__DOT__pp22 = vlSelfRef.kalman_filter__DOT__pp22;
    __Vdly__kalman_filter__DOT__s_reg = vlSelfRef.kalman_filter__DOT__s_reg;
    __Vdly__kalman_filter__DOT__k0 = vlSelfRef.kalman_filter__DOT__k0;
    __Vdly__kalman_filter__DOT__k1 = vlSelfRef.kalman_filter__DOT__k1;
    __Vdly__kalman_filter__DOT__k2 = vlSelfRef.kalman_filter__DOT__k2;
    if (vlSelfRef.kalman_filter__DOT__rst) {
        __Vdly__kalman_filter__DOT__state = 0U;
        vlSelfRef.kalman_filter__DOT__vout = 0U;
        __Vdly__kalman_filter__DOT__x0 = 0U;
        __Vdly__kalman_filter__DOT__x1 = 0U;
        __Vdly__kalman_filter__DOT__x2 = 0U;
        vlSelfRef.kalman_filter__DOT__x0_out = 0U;
        vlSelfRef.kalman_filter__DOT__x1_out = 0U;
        vlSelfRef.kalman_filter__DOT__x2_out = 0U;
        __Vdly__kalman_filter__DOT__p00 = 0x0000199aU;
        __Vdly__kalman_filter__DOT__p01 = 0x0000199aU;
        __Vdly__kalman_filter__DOT__p02 = 0x0000199aU;
        __Vdly__kalman_filter__DOT__p11 = 0x27100000U;
        __Vdly__kalman_filter__DOT__p12 = 0x000a0000U;
        __Vdly__kalman_filter__DOT__p22 = 0x00640000U;
        __Vdly__kalman_filter__DOT__y_reg = 0U;
        __Vdly__kalman_filter__DOT__x0p = 0U;
        __Vdly__kalman_filter__DOT__x1p = 0U;
        __Vdly__kalman_filter__DOT__x2p = 0U;
        __Vdly__kalman_filter__DOT__pp00 = 0U;
        __Vdly__kalman_filter__DOT__pp01 = 0U;
        __Vdly__kalman_filter__DOT__pp02 = 0U;
        __Vdly__kalman_filter__DOT__pp11 = 0U;
        __Vdly__kalman_filter__DOT__pp12 = 0U;
        __Vdly__kalman_filter__DOT__pp22 = 0U;
        __Vdly__kalman_filter__DOT__s_reg = 0x00010000U;
        __Vdly__kalman_filter__DOT__k0 = 0U;
        __Vdly__kalman_filter__DOT__k1 = 0U;
        __Vdly__kalman_filter__DOT__k2 = 0U;
    } else {
        vlSelfRef.kalman_filter__DOT__vout = 0U;
        if ((4U & (IData)(vlSelfRef.kalman_filter__DOT__state))) {
            if ((2U & (IData)(vlSelfRef.kalman_filter__DOT__state))) {
                if ((1U & (IData)(vlSelfRef.kalman_filter__DOT__state))) {
                    __Vdly__kalman_filter__DOT__state = 0U;
                } else {
                    vlSelfRef.kalman_filter__DOT__x0_out 
                        = vlSelfRef.kalman_filter__DOT__x0;
                    vlSelfRef.kalman_filter__DOT__x1_out 
                        = vlSelfRef.kalman_filter__DOT__x1;
                    vlSelfRef.kalman_filter__DOT__x2_out 
                        = vlSelfRef.kalman_filter__DOT__x2;
                    vlSelfRef.kalman_filter__DOT__vout = 1U;
                    __Vdly__kalman_filter__DOT__state = 0U;
                }
            } else if ((1U & (IData)(vlSelfRef.kalman_filter__DOT__state))) {
                vlSelfRef.kalman_filter__DOT__unnamedblk1__DOT__innov 
                    = (vlSelfRef.kalman_filter__DOT__y_reg 
                       - vlSelfRef.kalman_filter__DOT__x0p);
                __Vdly__kalman_filter__DOT__x0 = (vlSelfRef.kalman_filter__DOT__x0p 
                                                  + 
                                                  ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__0__b 
                                = vlSelfRef.kalman_filter__DOT__unnamedblk1__DOT__innov;
                            __Vfunc_kalman_filter__DOT__fp_mul__0__a 
                                = vlSelfRef.kalman_filter__DOT__k0;
                            __Vfunc_kalman_filter__DOT__fp_mul__0__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__0__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__0__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__0__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__0__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__0__Vfuncout));
                __Vdly__kalman_filter__DOT__state = 6U;
                __Vdly__kalman_filter__DOT__x1 = (vlSelfRef.kalman_filter__DOT__x1p 
                                                  + 
                                                  ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__1__b 
                                = vlSelfRef.kalman_filter__DOT__unnamedblk1__DOT__innov;
                            __Vfunc_kalman_filter__DOT__fp_mul__1__a 
                                = vlSelfRef.kalman_filter__DOT__k1;
                            __Vfunc_kalman_filter__DOT__fp_mul__1__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__1__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__1__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__1__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__1__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__1__Vfuncout));
                __Vdly__kalman_filter__DOT__x2 = (vlSelfRef.kalman_filter__DOT__x2p 
                                                  + 
                                                  ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__2__b 
                                = vlSelfRef.kalman_filter__DOT__unnamedblk1__DOT__innov;
                            __Vfunc_kalman_filter__DOT__fp_mul__2__a 
                                = vlSelfRef.kalman_filter__DOT__k2;
                            __Vfunc_kalman_filter__DOT__fp_mul__2__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__2__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__2__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__2__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__2__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__2__Vfuncout));
                __Vdly__kalman_filter__DOT__p00 = (vlSelfRef.kalman_filter__DOT__pp00 
                                                   - 
                                                   ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__3__b 
                                = vlSelfRef.kalman_filter__DOT__pp00;
                            __Vfunc_kalman_filter__DOT__fp_mul__3__a 
                                = vlSelfRef.kalman_filter__DOT__k0;
                            __Vfunc_kalman_filter__DOT__fp_mul__3__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__3__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__3__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__3__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__3__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__3__Vfuncout));
                __Vdly__kalman_filter__DOT__p01 = (vlSelfRef.kalman_filter__DOT__pp01 
                                                   - 
                                                   ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__4__b 
                                = vlSelfRef.kalman_filter__DOT__pp01;
                            __Vfunc_kalman_filter__DOT__fp_mul__4__a 
                                = vlSelfRef.kalman_filter__DOT__k0;
                            __Vfunc_kalman_filter__DOT__fp_mul__4__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__4__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__4__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__4__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__4__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__4__Vfuncout));
                __Vdly__kalman_filter__DOT__p02 = (vlSelfRef.kalman_filter__DOT__pp02 
                                                   - 
                                                   ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__5__b 
                                = vlSelfRef.kalman_filter__DOT__pp02;
                            __Vfunc_kalman_filter__DOT__fp_mul__5__a 
                                = vlSelfRef.kalman_filter__DOT__k0;
                            __Vfunc_kalman_filter__DOT__fp_mul__5__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__5__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__5__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__5__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__5__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__5__Vfuncout));
                __Vdly__kalman_filter__DOT__p11 = (vlSelfRef.kalman_filter__DOT__pp11 
                                                   - 
                                                   ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__6__b 
                                = vlSelfRef.kalman_filter__DOT__pp01;
                            __Vfunc_kalman_filter__DOT__fp_mul__6__a 
                                = vlSelfRef.kalman_filter__DOT__k1;
                            __Vfunc_kalman_filter__DOT__fp_mul__6__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__6__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__6__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__6__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__6__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__6__Vfuncout));
                __Vdly__kalman_filter__DOT__p12 = (vlSelfRef.kalman_filter__DOT__pp12 
                                                   - 
                                                   ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__7__b 
                                = vlSelfRef.kalman_filter__DOT__pp02;
                            __Vfunc_kalman_filter__DOT__fp_mul__7__a 
                                = vlSelfRef.kalman_filter__DOT__k1;
                            __Vfunc_kalman_filter__DOT__fp_mul__7__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__7__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__7__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__7__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__7__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__7__Vfuncout));
                __Vdly__kalman_filter__DOT__p22 = (vlSelfRef.kalman_filter__DOT__pp22 
                                                   - 
                                                   ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__8__b 
                                = vlSelfRef.kalman_filter__DOT__pp02;
                            __Vfunc_kalman_filter__DOT__fp_mul__8__a 
                                = vlSelfRef.kalman_filter__DOT__k2;
                            __Vfunc_kalman_filter__DOT__fp_mul__8__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__8__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__8__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__8__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__8__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__8__Vfuncout));
            } else {
                __Vdly__kalman_filter__DOT__k0 = (IData)(
                                                         VL_DIVS_QQQ(64, 
                                                                     VL_SHIFTL_QQI(64,64,32, 
                                                                                VL_EXTENDS_QI(64,32, vlSelfRef.kalman_filter__DOT__pp00), 0x00000010U), 
                                                                     VL_EXTENDS_QI(64,32, vlSelfRef.kalman_filter__DOT__s_reg)));
                __Vdly__kalman_filter__DOT__state = 5U;
                __Vdly__kalman_filter__DOT__k1 = (IData)(
                                                         VL_DIVS_QQQ(64, 
                                                                     VL_SHIFTL_QQI(64,64,32, 
                                                                                VL_EXTENDS_QI(64,32, vlSelfRef.kalman_filter__DOT__pp01), 0x00000010U), 
                                                                     VL_EXTENDS_QI(64,32, vlSelfRef.kalman_filter__DOT__s_reg)));
                __Vdly__kalman_filter__DOT__k2 = (IData)(
                                                         VL_DIVS_QQQ(64, 
                                                                     VL_SHIFTL_QQI(64,64,32, 
                                                                                VL_EXTENDS_QI(64,32, vlSelfRef.kalman_filter__DOT__pp02), 0x00000010U), 
                                                                     VL_EXTENDS_QI(64,32, vlSelfRef.kalman_filter__DOT__s_reg)));
            }
        } else if ((2U & (IData)(vlSelfRef.kalman_filter__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.kalman_filter__DOT__state))) {
                __Vdly__kalman_filter__DOT__s_reg = 
                    ((IData)(0x00050000U) + vlSelfRef.kalman_filter__DOT__pp00);
                __Vdly__kalman_filter__DOT__state = 4U;
            } else {
                __Vdly__kalman_filter__DOT__pp00 = 
                    ((IData)(0x00000ccdU) + (((vlSelfRef.kalman_filter__DOT__p00 
                                               + ([&]() {
                                        __Vfunc_kalman_filter__DOT__fp_mul__9__b 
                                            = vlSelfRef.kalman_filter__DOT__p01;
                                        __Vfunc_kalman_filter__DOT__fp_mul__9__prod 
                                            = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                          VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__9__b));
                                        __Vfunc_kalman_filter__DOT__fp_mul__9__Vfuncout 
                                            = (IData)(
                                                      (__Vfunc_kalman_filter__DOT__fp_mul__9__prod 
                                                       >> 0x10U));
                                    }(), __Vfunc_kalman_filter__DOT__fp_mul__9__Vfuncout)) 
                                              + ([&]() {
                                    __Vfunc_kalman_filter__DOT__fp_mul__10__b 
                                        = vlSelfRef.kalman_filter__DOT__p01;
                                    __Vfunc_kalman_filter__DOT__fp_mul__10__prod 
                                        = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                      VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__10__b));
                                    __Vfunc_kalman_filter__DOT__fp_mul__10__Vfuncout 
                                        = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__10__prod 
                                                   >> 0x10U));
                                }(), __Vfunc_kalman_filter__DOT__fp_mul__10__Vfuncout)) 
                                             + ([&]() {
                                __Vfunc_kalman_filter__DOT__fp_mul__12__b 
                                    = vlSelfRef.kalman_filter__DOT__p11;
                                __Vfunc_kalman_filter__DOT__fp_mul__12__prod 
                                    = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                  VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__12__b));
                                __Vfunc_kalman_filter__DOT__fp_mul__12__Vfuncout 
                                    = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__12__prod 
                                               >> 0x10U));
                                __Vfunc_kalman_filter__DOT__fp_mul__11__b 
                                    = __Vfunc_kalman_filter__DOT__fp_mul__12__Vfuncout;
                                __Vfunc_kalman_filter__DOT__fp_mul__11__prod 
                                    = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                  VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__11__b));
                                __Vfunc_kalman_filter__DOT__fp_mul__11__Vfuncout 
                                    = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__11__prod 
                                               >> 0x10U));
                            }(), __Vfunc_kalman_filter__DOT__fp_mul__11__Vfuncout)));
                __Vdly__kalman_filter__DOT__state = 3U;
                __Vdly__kalman_filter__DOT__pp01 = 
                    (((vlSelfRef.kalman_filter__DOT__p01 
                       + ([&]() {
                                    __Vfunc_kalman_filter__DOT__fp_mul__13__b 
                                        = vlSelfRef.kalman_filter__DOT__p02;
                                    __Vfunc_kalman_filter__DOT__fp_mul__13__prod 
                                        = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                      VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__13__b));
                                    __Vfunc_kalman_filter__DOT__fp_mul__13__Vfuncout 
                                        = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__13__prod 
                                                   >> 0x10U));
                                }(), __Vfunc_kalman_filter__DOT__fp_mul__13__Vfuncout)) 
                      + ([&]() {
                                __Vfunc_kalman_filter__DOT__fp_mul__14__b 
                                    = vlSelfRef.kalman_filter__DOT__p11;
                                __Vfunc_kalman_filter__DOT__fp_mul__14__prod 
                                    = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                  VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__14__b));
                                __Vfunc_kalman_filter__DOT__fp_mul__14__Vfuncout 
                                    = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__14__prod 
                                               >> 0x10U));
                            }(), __Vfunc_kalman_filter__DOT__fp_mul__14__Vfuncout)) 
                     + ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__16__b 
                                = vlSelfRef.kalman_filter__DOT__p12;
                            __Vfunc_kalman_filter__DOT__fp_mul__16__prod 
                                = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__16__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__16__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__16__prod 
                                           >> 0x10U));
                            __Vfunc_kalman_filter__DOT__fp_mul__15__b 
                                = __Vfunc_kalman_filter__DOT__fp_mul__16__Vfuncout;
                            __Vfunc_kalman_filter__DOT__fp_mul__15__prod 
                                = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__15__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__15__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__15__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__15__Vfuncout));
                __Vdly__kalman_filter__DOT__pp02 = 
                    (vlSelfRef.kalman_filter__DOT__p02 
                     + ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__17__b 
                                = vlSelfRef.kalman_filter__DOT__p12;
                            __Vfunc_kalman_filter__DOT__fp_mul__17__prod 
                                = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__17__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__17__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__17__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__17__Vfuncout));
                __Vdly__kalman_filter__DOT__pp11 = 
                    ((IData)(0x00000ccdU) + (((vlSelfRef.kalman_filter__DOT__p11 
                                               + ([&]() {
                                        __Vfunc_kalman_filter__DOT__fp_mul__18__b 
                                            = vlSelfRef.kalman_filter__DOT__p12;
                                        __Vfunc_kalman_filter__DOT__fp_mul__18__prod 
                                            = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                          VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__18__b));
                                        __Vfunc_kalman_filter__DOT__fp_mul__18__Vfuncout 
                                            = (IData)(
                                                      (__Vfunc_kalman_filter__DOT__fp_mul__18__prod 
                                                       >> 0x10U));
                                    }(), __Vfunc_kalman_filter__DOT__fp_mul__18__Vfuncout)) 
                                              + ([&]() {
                                    __Vfunc_kalman_filter__DOT__fp_mul__19__b 
                                        = vlSelfRef.kalman_filter__DOT__p12;
                                    __Vfunc_kalman_filter__DOT__fp_mul__19__prod 
                                        = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                      VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__19__b));
                                    __Vfunc_kalman_filter__DOT__fp_mul__19__Vfuncout 
                                        = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__19__prod 
                                                   >> 0x10U));
                                }(), __Vfunc_kalman_filter__DOT__fp_mul__19__Vfuncout)) 
                                             + ([&]() {
                                __Vfunc_kalman_filter__DOT__fp_mul__21__b 
                                    = vlSelfRef.kalman_filter__DOT__p22;
                                __Vfunc_kalman_filter__DOT__fp_mul__21__prod 
                                    = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                  VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__21__b));
                                __Vfunc_kalman_filter__DOT__fp_mul__21__Vfuncout 
                                    = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__21__prod 
                                               >> 0x10U));
                                __Vfunc_kalman_filter__DOT__fp_mul__20__b 
                                    = __Vfunc_kalman_filter__DOT__fp_mul__21__Vfuncout;
                                __Vfunc_kalman_filter__DOT__fp_mul__20__prod 
                                    = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                  VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__20__b));
                                __Vfunc_kalman_filter__DOT__fp_mul__20__Vfuncout 
                                    = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__20__prod 
                                               >> 0x10U));
                            }(), __Vfunc_kalman_filter__DOT__fp_mul__20__Vfuncout)));
                __Vdly__kalman_filter__DOT__pp12 = 
                    (vlSelfRef.kalman_filter__DOT__p12 
                     + ([&]() {
                            __Vfunc_kalman_filter__DOT__fp_mul__22__b 
                                = vlSelfRef.kalman_filter__DOT__p22;
                            __Vfunc_kalman_filter__DOT__fp_mul__22__prod 
                                = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                              VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__22__b));
                            __Vfunc_kalman_filter__DOT__fp_mul__22__Vfuncout 
                                = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__22__prod 
                                           >> 0x10U));
                        }(), __Vfunc_kalman_filter__DOT__fp_mul__22__Vfuncout));
                __Vdly__kalman_filter__DOT__pp22 = vlSelfRef.kalman_filter__DOT__p22;
            }
        } else if ((1U & (IData)(vlSelfRef.kalman_filter__DOT__state))) {
            __Vdly__kalman_filter__DOT__x0p = (vlSelfRef.kalman_filter__DOT__x0 
                                               + ([&]() {
                        __Vfunc_kalman_filter__DOT__fp_mul__23__b 
                            = vlSelfRef.kalman_filter__DOT__x1;
                        __Vfunc_kalman_filter__DOT__fp_mul__23__prod 
                            = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                          VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__23__b));
                        __Vfunc_kalman_filter__DOT__fp_mul__23__Vfuncout 
                            = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__23__prod 
                                       >> 0x10U));
                    }(), __Vfunc_kalman_filter__DOT__fp_mul__23__Vfuncout));
            __Vdly__kalman_filter__DOT__state = 2U;
            __Vdly__kalman_filter__DOT__x1p = (vlSelfRef.kalman_filter__DOT__x1 
                                               + ([&]() {
                        __Vfunc_kalman_filter__DOT__fp_mul__24__b 
                            = vlSelfRef.kalman_filter__DOT__x2;
                        __Vfunc_kalman_filter__DOT__fp_mul__24__prod 
                            = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                          VL_EXTENDS_QI(64,32, __Vfunc_kalman_filter__DOT__fp_mul__24__b));
                        __Vfunc_kalman_filter__DOT__fp_mul__24__Vfuncout 
                            = (IData)((__Vfunc_kalman_filter__DOT__fp_mul__24__prod 
                                       >> 0x10U));
                    }(), __Vfunc_kalman_filter__DOT__fp_mul__24__Vfuncout));
            __Vdly__kalman_filter__DOT__x2p = vlSelfRef.kalman_filter__DOT__x2;
        } else if (vlSelfRef.kalman_filter__DOT__valid_in) {
            __Vdly__kalman_filter__DOT__y_reg = vlSelfRef.kalman_filter__DOT__y;
            __Vdly__kalman_filter__DOT__state = 1U;
        }
    }
    vlSelfRef.kalman_filter__DOT__state = __Vdly__kalman_filter__DOT__state;
    vlSelfRef.kalman_filter__DOT__x0 = __Vdly__kalman_filter__DOT__x0;
    vlSelfRef.kalman_filter__DOT__x1 = __Vdly__kalman_filter__DOT__x1;
    vlSelfRef.kalman_filter__DOT__x2 = __Vdly__kalman_filter__DOT__x2;
    vlSelfRef.kalman_filter__DOT__p00 = __Vdly__kalman_filter__DOT__p00;
    vlSelfRef.kalman_filter__DOT__p01 = __Vdly__kalman_filter__DOT__p01;
    vlSelfRef.kalman_filter__DOT__p02 = __Vdly__kalman_filter__DOT__p02;
    vlSelfRef.kalman_filter__DOT__p11 = __Vdly__kalman_filter__DOT__p11;
    vlSelfRef.kalman_filter__DOT__p12 = __Vdly__kalman_filter__DOT__p12;
    vlSelfRef.kalman_filter__DOT__p22 = __Vdly__kalman_filter__DOT__p22;
    vlSelfRef.kalman_filter__DOT__y_reg = __Vdly__kalman_filter__DOT__y_reg;
    vlSelfRef.kalman_filter__DOT__x0p = __Vdly__kalman_filter__DOT__x0p;
    vlSelfRef.kalman_filter__DOT__x1p = __Vdly__kalman_filter__DOT__x1p;
    vlSelfRef.kalman_filter__DOT__x2p = __Vdly__kalman_filter__DOT__x2p;
    vlSelfRef.kalman_filter__DOT__pp00 = __Vdly__kalman_filter__DOT__pp00;
    vlSelfRef.kalman_filter__DOT__pp01 = __Vdly__kalman_filter__DOT__pp01;
    vlSelfRef.kalman_filter__DOT__pp02 = __Vdly__kalman_filter__DOT__pp02;
    vlSelfRef.kalman_filter__DOT__pp11 = __Vdly__kalman_filter__DOT__pp11;
    vlSelfRef.kalman_filter__DOT__pp12 = __Vdly__kalman_filter__DOT__pp12;
    vlSelfRef.kalman_filter__DOT__pp22 = __Vdly__kalman_filter__DOT__pp22;
    vlSelfRef.kalman_filter__DOT__s_reg = __Vdly__kalman_filter__DOT__s_reg;
    vlSelfRef.kalman_filter__DOT__k0 = __Vdly__kalman_filter__DOT__k0;
    vlSelfRef.kalman_filter__DOT__k1 = __Vdly__kalman_filter__DOT__k1;
    vlSelfRef.kalman_filter__DOT__k2 = __Vdly__kalman_filter__DOT__k2;
    vlSelfRef.kalman_filter__DOT__valid_out = vlSelfRef.kalman_filter__DOT__vout;
    vlSelfRef.kalman_filter__DOT__x_hat_0 = vlSelfRef.kalman_filter__DOT__x0_out;
    vlSelfRef.kalman_filter__DOT__x_hat_1 = vlSelfRef.kalman_filter__DOT__x1_out;
    vlSelfRef.kalman_filter__DOT__x_hat_2 = vlSelfRef.kalman_filter__DOT__x2_out;
    vlSelfRef.valid_out = vlSelfRef.kalman_filter__DOT__valid_out;
    vlSelfRef.x_hat_0 = vlSelfRef.kalman_filter__DOT__x_hat_0;
    vlSelfRef.x_hat_1 = vlSelfRef.kalman_filter__DOT__x_hat_1;
    vlSelfRef.x_hat_2 = vlSelfRef.kalman_filter__DOT__x_hat_2;
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vtop___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vtop___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vtop___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        Vtop___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/hdl/kalman_filter.sv", 11, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 100 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vtop___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/hdl/kalman_filter.sv", 11, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/hdl/kalman_filter.sv", 11, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vtop___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vtop___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");
    }
    if (VL_UNLIKELY(((vlSelfRef.valid_in & 0xfeU)))) {
        Verilated::overWidthError("valid_in");
    }
}
#endif  // VL_DEBUG
