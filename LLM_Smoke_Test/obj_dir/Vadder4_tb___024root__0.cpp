// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadder4_tb.h for the primary calling header

#include "Vadder4_tb__pch.h"

VlCoroutine Vadder4_tb___024root___eval_initial__TOP__Vtiming__0(Vadder4_tb___024root* vlSelf);

void Vadder4_tb___024root___eval_initial(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___eval_initial\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vadder4_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
}

VlCoroutine Vadder4_tb___024root___eval_initial__TOP__Vtiming__0(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__0__ta;
    __Vtask_adder4_tb__DOT__check__0__ta = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__0__tb;
    __Vtask_adder4_tb__DOT__check__0__tb = 0;
    CData/*0:0*/ __Vtask_adder4_tb__DOT__check__0__tc;
    __Vtask_adder4_tb__DOT__check__0__tc = 0;
    CData/*4:0*/ __Vtask_adder4_tb__DOT__check__0__expected;
    __Vtask_adder4_tb__DOT__check__0__expected = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__1__ta;
    __Vtask_adder4_tb__DOT__check__1__ta = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__1__tb;
    __Vtask_adder4_tb__DOT__check__1__tb = 0;
    CData/*0:0*/ __Vtask_adder4_tb__DOT__check__1__tc;
    __Vtask_adder4_tb__DOT__check__1__tc = 0;
    CData/*4:0*/ __Vtask_adder4_tb__DOT__check__1__expected;
    __Vtask_adder4_tb__DOT__check__1__expected = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__2__ta;
    __Vtask_adder4_tb__DOT__check__2__ta = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__2__tb;
    __Vtask_adder4_tb__DOT__check__2__tb = 0;
    CData/*0:0*/ __Vtask_adder4_tb__DOT__check__2__tc;
    __Vtask_adder4_tb__DOT__check__2__tc = 0;
    CData/*4:0*/ __Vtask_adder4_tb__DOT__check__2__expected;
    __Vtask_adder4_tb__DOT__check__2__expected = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__3__ta;
    __Vtask_adder4_tb__DOT__check__3__ta = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__3__tb;
    __Vtask_adder4_tb__DOT__check__3__tb = 0;
    CData/*0:0*/ __Vtask_adder4_tb__DOT__check__3__tc;
    __Vtask_adder4_tb__DOT__check__3__tc = 0;
    CData/*4:0*/ __Vtask_adder4_tb__DOT__check__3__expected;
    __Vtask_adder4_tb__DOT__check__3__expected = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__4__ta;
    __Vtask_adder4_tb__DOT__check__4__ta = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__4__tb;
    __Vtask_adder4_tb__DOT__check__4__tb = 0;
    CData/*0:0*/ __Vtask_adder4_tb__DOT__check__4__tc;
    __Vtask_adder4_tb__DOT__check__4__tc = 0;
    CData/*4:0*/ __Vtask_adder4_tb__DOT__check__4__expected;
    __Vtask_adder4_tb__DOT__check__4__expected = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__5__ta;
    __Vtask_adder4_tb__DOT__check__5__ta = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__5__tb;
    __Vtask_adder4_tb__DOT__check__5__tb = 0;
    CData/*0:0*/ __Vtask_adder4_tb__DOT__check__5__tc;
    __Vtask_adder4_tb__DOT__check__5__tc = 0;
    CData/*4:0*/ __Vtask_adder4_tb__DOT__check__5__expected;
    __Vtask_adder4_tb__DOT__check__5__expected = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__6__ta;
    __Vtask_adder4_tb__DOT__check__6__ta = 0;
    CData/*3:0*/ __Vtask_adder4_tb__DOT__check__6__tb;
    __Vtask_adder4_tb__DOT__check__6__tb = 0;
    CData/*0:0*/ __Vtask_adder4_tb__DOT__check__6__tc;
    __Vtask_adder4_tb__DOT__check__6__tc = 0;
    CData/*4:0*/ __Vtask_adder4_tb__DOT__check__6__expected;
    __Vtask_adder4_tb__DOT__check__6__expected = 0;
    // Body
    vlSymsp->_vm_contextp__->dumpfile("adder4.vcd"s);
    VL_PRINTF_MT("-Info: adder4_tb.v:30: $dumpvar ignored, as Verilated without --trace\n");
    __Vtask_adder4_tb__DOT__check__0__expected = 0U;
    __Vtask_adder4_tb__DOT__check__0__tc = 0U;
    __Vtask_adder4_tb__DOT__check__0__tb = 0U;
    __Vtask_adder4_tb__DOT__check__0__ta = 0U;
    vlSelfRef.adder4_tb__DOT__a = 0U;
    vlSelfRef.adder4_tb__DOT__b = 0U;
    vlSelfRef.adder4_tb__DOT__cin = 0U;
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "adder4_tb.v", 
                                         18);
    if (((((IData)(vlSelfRef.adder4_tb__DOT__cout) 
           << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)) 
         != (IData)(__Vtask_adder4_tb__DOT__check__0__expected))) {
        VL_WRITEF_NX("FAIL: %0# + %0# + %0# = %0# (expected %0#)\n",0,
                     4,__Vtask_adder4_tb__DOT__check__0__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__0__tb),
                     1,__Vtask_adder4_tb__DOT__check__0__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)),
                     5,(IData)(__Vtask_adder4_tb__DOT__check__0__expected));
    } else {
        VL_WRITEF_NX("PASS: %0# + %0# + %0# = %0#\n",0,
                     4,__Vtask_adder4_tb__DOT__check__0__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__0__tb),
                     1,__Vtask_adder4_tb__DOT__check__0__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)));
    }
    __Vtask_adder4_tb__DOT__check__1__expected = 2U;
    __Vtask_adder4_tb__DOT__check__1__tc = 0U;
    __Vtask_adder4_tb__DOT__check__1__tb = 1U;
    __Vtask_adder4_tb__DOT__check__1__ta = 1U;
    vlSelfRef.adder4_tb__DOT__a = __Vtask_adder4_tb__DOT__check__1__ta;
    vlSelfRef.adder4_tb__DOT__b = __Vtask_adder4_tb__DOT__check__1__tb;
    vlSelfRef.adder4_tb__DOT__cin = __Vtask_adder4_tb__DOT__check__1__tc;
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "adder4_tb.v", 
                                         18);
    if (((((IData)(vlSelfRef.adder4_tb__DOT__cout) 
           << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)) 
         != (IData)(__Vtask_adder4_tb__DOT__check__1__expected))) {
        VL_WRITEF_NX("FAIL: %0# + %0# + %0# = %0# (expected %0#)\n",0,
                     4,__Vtask_adder4_tb__DOT__check__1__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__1__tb),
                     1,__Vtask_adder4_tb__DOT__check__1__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)),
                     5,(IData)(__Vtask_adder4_tb__DOT__check__1__expected));
    } else {
        VL_WRITEF_NX("PASS: %0# + %0# + %0# = %0#\n",0,
                     4,__Vtask_adder4_tb__DOT__check__1__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__1__tb),
                     1,__Vtask_adder4_tb__DOT__check__1__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)));
    }
    __Vtask_adder4_tb__DOT__check__2__expected = 0x0fU;
    __Vtask_adder4_tb__DOT__check__2__tc = 0U;
    __Vtask_adder4_tb__DOT__check__2__tb = 8U;
    __Vtask_adder4_tb__DOT__check__2__ta = 7U;
    vlSelfRef.adder4_tb__DOT__a = __Vtask_adder4_tb__DOT__check__2__ta;
    vlSelfRef.adder4_tb__DOT__b = __Vtask_adder4_tb__DOT__check__2__tb;
    vlSelfRef.adder4_tb__DOT__cin = __Vtask_adder4_tb__DOT__check__2__tc;
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "adder4_tb.v", 
                                         18);
    if (((((IData)(vlSelfRef.adder4_tb__DOT__cout) 
           << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)) 
         != (IData)(__Vtask_adder4_tb__DOT__check__2__expected))) {
        VL_WRITEF_NX("FAIL: %0# + %0# + %0# = %0# (expected %0#)\n",0,
                     4,__Vtask_adder4_tb__DOT__check__2__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__2__tb),
                     1,__Vtask_adder4_tb__DOT__check__2__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)),
                     5,(IData)(__Vtask_adder4_tb__DOT__check__2__expected));
    } else {
        VL_WRITEF_NX("PASS: %0# + %0# + %0# = %0#\n",0,
                     4,__Vtask_adder4_tb__DOT__check__2__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__2__tb),
                     1,__Vtask_adder4_tb__DOT__check__2__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)));
    }
    __Vtask_adder4_tb__DOT__check__3__expected = 0x10U;
    __Vtask_adder4_tb__DOT__check__3__tc = 0U;
    __Vtask_adder4_tb__DOT__check__3__tb = 8U;
    __Vtask_adder4_tb__DOT__check__3__ta = 8U;
    vlSelfRef.adder4_tb__DOT__a = __Vtask_adder4_tb__DOT__check__3__ta;
    vlSelfRef.adder4_tb__DOT__b = __Vtask_adder4_tb__DOT__check__3__tb;
    vlSelfRef.adder4_tb__DOT__cin = __Vtask_adder4_tb__DOT__check__3__tc;
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "adder4_tb.v", 
                                         18);
    if (((((IData)(vlSelfRef.adder4_tb__DOT__cout) 
           << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)) 
         != (IData)(__Vtask_adder4_tb__DOT__check__3__expected))) {
        VL_WRITEF_NX("FAIL: %0# + %0# + %0# = %0# (expected %0#)\n",0,
                     4,__Vtask_adder4_tb__DOT__check__3__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__3__tb),
                     1,__Vtask_adder4_tb__DOT__check__3__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)),
                     5,(IData)(__Vtask_adder4_tb__DOT__check__3__expected));
    } else {
        VL_WRITEF_NX("PASS: %0# + %0# + %0# = %0#\n",0,
                     4,__Vtask_adder4_tb__DOT__check__3__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__3__tb),
                     1,__Vtask_adder4_tb__DOT__check__3__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)));
    }
    __Vtask_adder4_tb__DOT__check__4__expected = 0x1fU;
    __Vtask_adder4_tb__DOT__check__4__tc = 1U;
    __Vtask_adder4_tb__DOT__check__4__tb = 0x0fU;
    __Vtask_adder4_tb__DOT__check__4__ta = 0x0fU;
    vlSelfRef.adder4_tb__DOT__a = __Vtask_adder4_tb__DOT__check__4__ta;
    vlSelfRef.adder4_tb__DOT__b = __Vtask_adder4_tb__DOT__check__4__tb;
    vlSelfRef.adder4_tb__DOT__cin = __Vtask_adder4_tb__DOT__check__4__tc;
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "adder4_tb.v", 
                                         18);
    if (((((IData)(vlSelfRef.adder4_tb__DOT__cout) 
           << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)) 
         != (IData)(__Vtask_adder4_tb__DOT__check__4__expected))) {
        VL_WRITEF_NX("FAIL: %0# + %0# + %0# = %0# (expected %0#)\n",0,
                     4,__Vtask_adder4_tb__DOT__check__4__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__4__tb),
                     1,__Vtask_adder4_tb__DOT__check__4__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)),
                     5,(IData)(__Vtask_adder4_tb__DOT__check__4__expected));
    } else {
        VL_WRITEF_NX("PASS: %0# + %0# + %0# = %0#\n",0,
                     4,__Vtask_adder4_tb__DOT__check__4__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__4__tb),
                     1,__Vtask_adder4_tb__DOT__check__4__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)));
    }
    __Vtask_adder4_tb__DOT__check__5__expected = 0x1eU;
    __Vtask_adder4_tb__DOT__check__5__tc = 0U;
    __Vtask_adder4_tb__DOT__check__5__tb = 0x0fU;
    __Vtask_adder4_tb__DOT__check__5__ta = 0x0fU;
    vlSelfRef.adder4_tb__DOT__a = __Vtask_adder4_tb__DOT__check__5__ta;
    vlSelfRef.adder4_tb__DOT__b = __Vtask_adder4_tb__DOT__check__5__tb;
    vlSelfRef.adder4_tb__DOT__cin = __Vtask_adder4_tb__DOT__check__5__tc;
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "adder4_tb.v", 
                                         18);
    if (((((IData)(vlSelfRef.adder4_tb__DOT__cout) 
           << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)) 
         != (IData)(__Vtask_adder4_tb__DOT__check__5__expected))) {
        VL_WRITEF_NX("FAIL: %0# + %0# + %0# = %0# (expected %0#)\n",0,
                     4,__Vtask_adder4_tb__DOT__check__5__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__5__tb),
                     1,__Vtask_adder4_tb__DOT__check__5__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)),
                     5,(IData)(__Vtask_adder4_tb__DOT__check__5__expected));
    } else {
        VL_WRITEF_NX("PASS: %0# + %0# + %0# = %0#\n",0,
                     4,__Vtask_adder4_tb__DOT__check__5__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__5__tb),
                     1,__Vtask_adder4_tb__DOT__check__5__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)));
    }
    __Vtask_adder4_tb__DOT__check__6__expected = 1U;
    __Vtask_adder4_tb__DOT__check__6__tc = 1U;
    __Vtask_adder4_tb__DOT__check__6__tb = 0U;
    __Vtask_adder4_tb__DOT__check__6__ta = 0U;
    vlSelfRef.adder4_tb__DOT__a = __Vtask_adder4_tb__DOT__check__6__ta;
    vlSelfRef.adder4_tb__DOT__b = __Vtask_adder4_tb__DOT__check__6__tb;
    vlSelfRef.adder4_tb__DOT__cin = __Vtask_adder4_tb__DOT__check__6__tc;
    co_await vlSelfRef.__VdlySched.delay(0x000000000000000aULL, 
                                         nullptr, "adder4_tb.v", 
                                         18);
    if (((((IData)(vlSelfRef.adder4_tb__DOT__cout) 
           << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)) 
         != (IData)(__Vtask_adder4_tb__DOT__check__6__expected))) {
        VL_WRITEF_NX("FAIL: %0# + %0# + %0# = %0# (expected %0#)\n",0,
                     4,__Vtask_adder4_tb__DOT__check__6__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__6__tb),
                     1,__Vtask_adder4_tb__DOT__check__6__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)),
                     5,(IData)(__Vtask_adder4_tb__DOT__check__6__expected));
    } else {
        VL_WRITEF_NX("PASS: %0# + %0# + %0# = %0#\n",0,
                     4,__Vtask_adder4_tb__DOT__check__6__ta,
                     4,(IData)(__Vtask_adder4_tb__DOT__check__6__tb),
                     1,__Vtask_adder4_tb__DOT__check__6__tc,
                     5,(((IData)(vlSelfRef.adder4_tb__DOT__cout) 
                         << 4U) | (IData)(vlSelfRef.adder4_tb__DOT__sum)));
    }
    VL_FINISH_MT("adder4_tb.v", 41, "");
    co_return;
}

void Vadder4_tb___024root___eval_triggers_vec__act(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___eval_triggers_vec__act\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(vlSelfRef.__VdlySched.awaitingCurrentTime()));
}

bool Vadder4_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___trigger_anySet__act\n"); );
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

void Vadder4_tb___024root___act_sequent__TOP__0(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___act_sequent__TOP__0\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.adder4_tb__DOT__sum = (0x0000000fU & 
                                     ((IData)(vlSelfRef.adder4_tb__DOT__a) 
                                      + ((IData)(vlSelfRef.adder4_tb__DOT__b) 
                                         + (IData)(vlSelfRef.adder4_tb__DOT__cin))));
    vlSelfRef.adder4_tb__DOT__cout = (1U & (((IData)(vlSelfRef.adder4_tb__DOT__a) 
                                             + ((IData)(vlSelfRef.adder4_tb__DOT__b) 
                                                + (IData)(vlSelfRef.adder4_tb__DOT__cin))) 
                                            >> 4U));
}

void Vadder4_tb___024root___eval_act(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___eval_act\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.adder4_tb__DOT__sum = (0x0000000fU 
                                         & ((IData)(vlSelfRef.adder4_tb__DOT__a) 
                                            + ((IData)(vlSelfRef.adder4_tb__DOT__b) 
                                               + (IData)(vlSelfRef.adder4_tb__DOT__cin))));
        vlSelfRef.adder4_tb__DOT__cout = (1U & (((IData)(vlSelfRef.adder4_tb__DOT__a) 
                                                 + 
                                                 ((IData)(vlSelfRef.adder4_tb__DOT__b) 
                                                  + (IData)(vlSelfRef.adder4_tb__DOT__cin))) 
                                                >> 4U));
    }
}

void Vadder4_tb___024root___eval_nba(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___eval_nba\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.adder4_tb__DOT__sum = (0x0000000fU 
                                         & ((IData)(vlSelfRef.adder4_tb__DOT__a) 
                                            + ((IData)(vlSelfRef.adder4_tb__DOT__b) 
                                               + (IData)(vlSelfRef.adder4_tb__DOT__cin))));
        vlSelfRef.adder4_tb__DOT__cout = (1U & (((IData)(vlSelfRef.adder4_tb__DOT__a) 
                                                 + 
                                                 ((IData)(vlSelfRef.adder4_tb__DOT__b) 
                                                  + (IData)(vlSelfRef.adder4_tb__DOT__cin))) 
                                                >> 4U));
    }
}

void Vadder4_tb___024root___timing_resume(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___timing_resume\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vadder4_tb___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vadder4_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vadder4_tb___024root___eval_phase__act(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___eval_phase__act\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vadder4_tb___024root___eval_triggers_vec__act(vlSelf);
    Vadder4_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vadder4_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vadder4_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vadder4_tb___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vadder4_tb___024root___timing_resume(vlSelf);
        Vadder4_tb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vadder4_tb___024root___eval_phase__inact(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___eval_phase__inact\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("adder4_tb.v", 1, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vadder4_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vadder4_tb___024root___eval_phase__nba(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___eval_phase__nba\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vadder4_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vadder4_tb___024root___eval_nba(vlSelf);
        Vadder4_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vadder4_tb___024root___eval(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___eval\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vadder4_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("adder4_tb.v", 1, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("adder4_tb.v", 1, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vadder4_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("adder4_tb.v", 1, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vadder4_tb___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vadder4_tb___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vadder4_tb___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vadder4_tb___024root___eval_debug_assertions(Vadder4_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vadder4_tb___024root___eval_debug_assertions\n"); );
    Vadder4_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
