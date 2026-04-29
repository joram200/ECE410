// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

VL_ATTR_COLD void Vtop___024root___eval_static__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_static__TOP(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__kalman_filter__DOT__clk__0 
        = vlSelfRef.kalman_filter__DOT__clk;
}

VL_ATTR_COLD void Vtop___024root___eval_static__TOP(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static__TOP\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->kalman_filter__DOT__unnamedblk1__DOT__innov = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1665441613458983703ull);
}

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/hdl/kalman_filter.sv", 11, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vtop___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vtop___024root___eval_triggers_vec__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers_vec__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vtop___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___trigger_anySet__stl\n"); );
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

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vtop___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vtop___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__ico(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

bool Vtop___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vtop___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge kalman_filter.clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->valid_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16540271516330450727ull);
    vlSelf->y = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11123243248953317070ull);
    vlSelf->x_hat_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9674590582767991292ull);
    vlSelf->x_hat_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6388601144683247561ull);
    vlSelf->x_hat_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6129019061363985819ull);
    vlSelf->valid_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8744939437868816662ull);
    vlSelf->kalman_filter__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2636817665758052783ull);
    vlSelf->kalman_filter__DOT__rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12934287665583269699ull);
    vlSelf->kalman_filter__DOT__valid_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14098184157556068723ull);
    vlSelf->kalman_filter__DOT__y = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6174889961818801442ull);
    vlSelf->kalman_filter__DOT__x_hat_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14883308066170402435ull);
    vlSelf->kalman_filter__DOT__x_hat_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7489608608049891975ull);
    vlSelf->kalman_filter__DOT__x_hat_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3284405874843572089ull);
    vlSelf->kalman_filter__DOT__valid_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4720894997879011803ull);
    vlSelf->kalman_filter__DOT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 2021095768269034871ull);
    vlSelf->kalman_filter__DOT__x0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10146175016498443197ull);
    vlSelf->kalman_filter__DOT__x1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12979719705125083521ull);
    vlSelf->kalman_filter__DOT__x2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12739148830230849225ull);
    vlSelf->kalman_filter__DOT__p00 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11091095442206443124ull);
    vlSelf->kalman_filter__DOT__p01 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16913388204024331742ull);
    vlSelf->kalman_filter__DOT__p02 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13691868953162249080ull);
    vlSelf->kalman_filter__DOT__p11 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18037776574149329099ull);
    vlSelf->kalman_filter__DOT__p12 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16291895063484005947ull);
    vlSelf->kalman_filter__DOT__p22 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16298639918972129621ull);
    vlSelf->kalman_filter__DOT__y_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5268280226909753675ull);
    vlSelf->kalman_filter__DOT__x0p = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2440474450203933265ull);
    vlSelf->kalman_filter__DOT__x1p = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17865347869319721548ull);
    vlSelf->kalman_filter__DOT__x2p = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8617237296252468301ull);
    vlSelf->kalman_filter__DOT__pp00 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13057858721323052722ull);
    vlSelf->kalman_filter__DOT__pp01 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17821250278048768377ull);
    vlSelf->kalman_filter__DOT__pp02 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8649512737132223731ull);
    vlSelf->kalman_filter__DOT__pp11 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9353934552580161601ull);
    vlSelf->kalman_filter__DOT__pp12 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11954715946346935768ull);
    vlSelf->kalman_filter__DOT__pp22 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17338661441598781575ull);
    vlSelf->kalman_filter__DOT__s_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9033712491931609327ull);
    vlSelf->kalman_filter__DOT__k0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4809835259392974367ull);
    vlSelf->kalman_filter__DOT__k1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14996280889407977435ull);
    vlSelf->kalman_filter__DOT__k2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17699073577605454961ull);
    vlSelf->kalman_filter__DOT__x0_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2555042902056632003ull);
    vlSelf->kalman_filter__DOT__x1_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13981039135406362642ull);
    vlSelf->kalman_filter__DOT__x2_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1877615251109473988ull);
    vlSelf->kalman_filter__DOT__vout = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 17774476673985118531ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VicoTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__kalman_filter__DOT__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
}
