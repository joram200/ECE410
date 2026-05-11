// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcrossbar_tb.h for the primary calling header

#include "Vcrossbar_tb__pch.h"

void Vcrossbar_tb___024root___timing_ready(Vcrossbar_tb___024root* vlSelf);

VL_ATTR_COLD void Vcrossbar_tb___024root___eval_static(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_static\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.crossbar_tb__DOT__pass_count = 0U;
    vlSelfRef.crossbar_tb__DOT__fail_count = 0U;
    vlSelfRef.__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0 
        = vlSelfRef.crossbar_tb__DOT__clk;
    Vcrossbar_tb___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vcrossbar_tb___024root___eval_static__TOP(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_static__TOP\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.crossbar_tb__DOT__pass_count = 0U;
    vlSelfRef.crossbar_tb__DOT__fail_count = 0U;
}

VL_ATTR_COLD void Vcrossbar_tb___024root___eval_initial__TOP(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_initial__TOP\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.crossbar_tb__DOT__clk = 0U;
}

VL_ATTR_COLD void Vcrossbar_tb___024root___eval_final(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_final\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcrossbar_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vcrossbar_tb___024root___eval_phase__stl(Vcrossbar_tb___024root* vlSelf);

VL_ATTR_COLD void Vcrossbar_tb___024root___eval_settle(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_settle\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vcrossbar_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("crossbar_tb.sv", 22, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vcrossbar_tb___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vcrossbar_tb___024root___eval_triggers_vec__stl(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_triggers_vec__stl\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vcrossbar_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcrossbar_tb___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vcrossbar_tb___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vcrossbar_tb___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___trigger_anySet__stl\n"); );
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

void Vcrossbar_tb___024root___act_comb__TOP__0(Vcrossbar_tb___024root* vlSelf);

VL_ATTR_COLD void Vcrossbar_tb___024root___eval_stl(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_stl\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vcrossbar_tb___024root___act_comb__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vcrossbar_tb___024root___eval_phase__stl(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_phase__stl\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vcrossbar_tb___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcrossbar_tb___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vcrossbar_tb___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vcrossbar_tb___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vcrossbar_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcrossbar_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vcrossbar_tb___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge crossbar_tb.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @(negedge crossbar_tb.clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcrossbar_tb___024root___ctor_var_reset(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___ctor_var_reset\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->crossbar_tb__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10180193221538717711ull);
    vlSelf->crossbar_tb__DOT__rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16086515779862690407ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->crossbar_tb__DOT__in[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 16580481028305929230ull);
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->crossbar_tb__DOT__out[__Vi0] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5762467087645792306ull);
    }
    vlSelf->crossbar_tb__DOT__we = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6068658451738654270ull);
    vlSelf->crossbar_tb__DOT__w_row = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 765646892133890255ull);
    vlSelf->crossbar_tb__DOT__w_col = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11221972849712543377ull);
    vlSelf->crossbar_tb__DOT__w_val = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1031143165136791525ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->crossbar_tb__DOT__dut__DOT__weight[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9565390540206126499ull);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        for (int __Vi1 = 0; __Vi1 < 4; ++__Vi1) {
            vlSelf->crossbar_tb__DOT__dut__DOT__xp_out[__Vi0][__Vi1] = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5697178292106991891ull);
        }
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
}
