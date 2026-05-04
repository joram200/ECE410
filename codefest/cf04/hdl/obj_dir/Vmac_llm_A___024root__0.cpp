// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmac_llm_A.h for the primary calling header

#include "Vmac_llm_A__pch.h"

VlCoroutine Vmac_llm_A___024root___eval_initial__TOP__Vtiming__0(Vmac_llm_A___024root* vlSelf);
VlCoroutine Vmac_llm_A___024root___eval_initial__TOP__Vtiming__1(Vmac_llm_A___024root* vlSelf);

void Vmac_llm_A___024root___eval_initial(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___eval_initial\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.mac_tb__DOT__clk = 0U;
    Vmac_llm_A___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vmac_llm_A___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

void Vmac_llm_A___024root____VbeforeTrig_h27d3174b__0(Vmac_llm_A___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vmac_llm_A___024root___eval_initial__TOP__Vtiming__0(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ mac_tb__DOT__cycle;
    mac_tb__DOT__cycle = 0;
    IData/*31:0*/ mac_tb__DOT__unnamedblk1_1__DOT____Vrepeat0;
    mac_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ mac_tb__DOT__unnamedblk1_2__DOT____Vrepeat1;
    mac_tb__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    // Body
    mac_tb__DOT__cycle = 0U;
    vlSelfRef.mac_tb__DOT__rst = 1U;
    vlSelfRef.mac_tb__DOT__a = 0U;
    vlSelfRef.mac_tb__DOT__b = 0U;
    Vmac_llm_A___024root____VbeforeTrig_h27d3174b__0(vlSelf, 
                                                     "@(posedge mac_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h27d3174b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge mac_tb.clk)", 
                                                         "mac_tb.v", 
                                                         27);
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "mac_tb.v", 
                                         27);
    mac_tb__DOT__cycle = ((IData)(1U) + mac_tb__DOT__cycle);
    VL_WRITEF_NX("Cycle %0d | rst=%0b a=%0d b=%0d | out=%0d\n",0,
                 32,mac_tb__DOT__cycle,1,(IData)(vlSelfRef.mac_tb__DOT__rst),
                 8,vlSelfRef.mac_tb__DOT__a,8,(IData)(vlSelfRef.mac_tb__DOT__b),
                 32,vlSelfRef.mac_tb__DOT__out);
    vlSelfRef.mac_tb__DOT__rst = 0U;
    vlSelfRef.mac_tb__DOT__a = 3U;
    vlSelfRef.mac_tb__DOT__b = 4U;
    mac_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 3U;
    while (VL_LTS_III(32, 0U, mac_tb__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vmac_llm_A___024root____VbeforeTrig_h27d3174b__0(vlSelf, 
                                                         "@(posedge mac_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h27d3174b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge mac_tb.clk)", 
                                                             "mac_tb.v", 
                                                             34);
        co_await vlSelfRef.__VdlySched.delay(1ULL, 
                                             nullptr, 
                                             "mac_tb.v", 
                                             34);
        mac_tb__DOT__cycle = ((IData)(1U) + mac_tb__DOT__cycle);
        VL_WRITEF_NX("Cycle %0d | rst=%0b a=%0d b=%0d | out=%0d\n",0,
                     32,mac_tb__DOT__cycle,1,(IData)(vlSelfRef.mac_tb__DOT__rst),
                     8,vlSelfRef.mac_tb__DOT__a,8,(IData)(vlSelfRef.mac_tb__DOT__b),
                     32,vlSelfRef.mac_tb__DOT__out);
        mac_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (mac_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.mac_tb__DOT__rst = 1U;
    Vmac_llm_A___024root____VbeforeTrig_h27d3174b__0(vlSelf, 
                                                     "@(posedge mac_tb.clk)");
    co_await vlSelfRef.__VtrigSched_h27d3174b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge mac_tb.clk)", 
                                                         "mac_tb.v", 
                                                         41);
    co_await vlSelfRef.__VdlySched.delay(1ULL, nullptr, 
                                         "mac_tb.v", 
                                         41);
    mac_tb__DOT__cycle = ((IData)(1U) + mac_tb__DOT__cycle);
    VL_WRITEF_NX("Cycle %0d | rst=%0b a=%0d b=%0d | out=%0d\n",0,
                 32,mac_tb__DOT__cycle,1,(IData)(vlSelfRef.mac_tb__DOT__rst),
                 8,vlSelfRef.mac_tb__DOT__a,8,(IData)(vlSelfRef.mac_tb__DOT__b),
                 32,vlSelfRef.mac_tb__DOT__out);
    vlSelfRef.mac_tb__DOT__rst = 0U;
    vlSelfRef.mac_tb__DOT__a = 0xfbU;
    vlSelfRef.mac_tb__DOT__b = 2U;
    mac_tb__DOT__unnamedblk1_2__DOT____Vrepeat1 = 2U;
    while (VL_LTS_III(32, 0U, mac_tb__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        Vmac_llm_A___024root____VbeforeTrig_h27d3174b__0(vlSelf, 
                                                         "@(posedge mac_tb.clk)");
        co_await vlSelfRef.__VtrigSched_h27d3174b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge mac_tb.clk)", 
                                                             "mac_tb.v", 
                                                             48);
        co_await vlSelfRef.__VdlySched.delay(1ULL, 
                                             nullptr, 
                                             "mac_tb.v", 
                                             48);
        mac_tb__DOT__cycle = ((IData)(1U) + mac_tb__DOT__cycle);
        VL_WRITEF_NX("Cycle %0d | rst=%0b a=%0d b=%0d | out=%0d\n",0,
                     32,mac_tb__DOT__cycle,1,(IData)(vlSelfRef.mac_tb__DOT__rst),
                     8,vlSelfRef.mac_tb__DOT__a,8,(IData)(vlSelfRef.mac_tb__DOT__b),
                     32,vlSelfRef.mac_tb__DOT__out);
        mac_tb__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (mac_tb__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
    }
    VL_FINISH_MT("mac_tb.v", 53, "");
    co_return;
}

VlCoroutine Vmac_llm_A___024root___eval_initial__TOP__Vtiming__1(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(5ULL, 
                                             nullptr, 
                                             "mac_tb.v", 
                                             19);
        vlSelfRef.mac_tb__DOT__clk = (1U & (~ (IData)(vlSelfRef.mac_tb__DOT__clk)));
    }
    co_return;
}

void Vmac_llm_A___024root___eval_triggers_vec__act(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___eval_triggers_vec__act\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.mac_tb__DOT__clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__mac_tb__DOT__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__mac_tb__DOT__clk__0 
        = vlSelfRef.mac_tb__DOT__clk;
}

bool Vmac_llm_A___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___trigger_anySet__act\n"); );
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

void Vmac_llm_A___024root___nba_sequent__TOP__0(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___nba_sequent__TOP__0\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.mac_tb__DOT__out = ((IData)(vlSelfRef.mac_tb__DOT__rst)
                                   ? 0U : (vlSelfRef.mac_tb__DOT__out 
                                           + VL_MULS_III(32, 
                                                         VL_EXTENDS_II(32,8, (IData)(vlSelfRef.mac_tb__DOT__a)), 
                                                         VL_EXTENDS_II(32,8, (IData)(vlSelfRef.mac_tb__DOT__b)))));
}

void Vmac_llm_A___024root___eval_nba(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___eval_nba\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.mac_tb__DOT__out = ((IData)(vlSelfRef.mac_tb__DOT__rst)
                                       ? 0U : (vlSelfRef.mac_tb__DOT__out 
                                               + VL_MULS_III(32, 
                                                             VL_EXTENDS_II(32,8, (IData)(vlSelfRef.mac_tb__DOT__a)), 
                                                             VL_EXTENDS_II(32,8, (IData)(vlSelfRef.mac_tb__DOT__b)))));
    }
}

void Vmac_llm_A___024root___timing_ready(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___timing_ready\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h27d3174b__0.ready("@(posedge mac_tb.clk)");
    }
}

void Vmac_llm_A___024root___timing_resume(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___timing_resume\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h27d3174b__0.moveToResumeQueue(
                                                          "@(posedge mac_tb.clk)");
    vlSelfRef.__VtrigSched_h27d3174b__0.resume("@(posedge mac_tb.clk)");
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vmac_llm_A___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vmac_llm_A___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vmac_llm_A___024root___eval_phase__act(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___eval_phase__act\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vmac_llm_A___024root___eval_triggers_vec__act(vlSelf);
    Vmac_llm_A___024root___timing_ready(vlSelf);
    Vmac_llm_A___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vmac_llm_A___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vmac_llm_A___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vmac_llm_A___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vmac_llm_A___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vmac_llm_A___024root___eval_phase__inact(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___eval_phase__inact\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("mac_tb.v", 1, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vmac_llm_A___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vmac_llm_A___024root___eval_phase__nba(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___eval_phase__nba\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vmac_llm_A___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vmac_llm_A___024root___eval_nba(vlSelf);
        Vmac_llm_A___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vmac_llm_A___024root___eval(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___eval\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vmac_llm_A___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("mac_tb.v", 1, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("mac_tb.v", 1, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vmac_llm_A___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("mac_tb.v", 1, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vmac_llm_A___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vmac_llm_A___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vmac_llm_A___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vmac_llm_A___024root____VbeforeTrig_h27d3174b__0(Vmac_llm_A___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root____VbeforeTrig_h27d3174b__0\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.mac_tb__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__mac_tb__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__mac_tb__DOT__clk__0 
        = vlSelfRef.mac_tb__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h27d3174b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h27d3174b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h27d3174b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h27d3174b__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vmac_llm_A___024root___eval_debug_assertions(Vmac_llm_A___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmac_llm_A___024root___eval_debug_assertions\n"); );
    Vmac_llm_A__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
