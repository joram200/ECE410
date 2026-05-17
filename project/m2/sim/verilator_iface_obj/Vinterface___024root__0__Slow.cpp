// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vinterface.h for the primary calling header

#include "Vinterface__pch.h"

VL_ATTR_COLD void Vinterface___024root___eval_static__TOP(Vinterface___024root* vlSelf);
void Vinterface___024root___timing_ready(Vinterface___024root* vlSelf);

VL_ATTR_COLD void Vinterface___024root___eval_static(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_static\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vinterface___024root___eval_static__TOP(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0 = 0U;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__rst_n__0 
        = vlSelfRef.tb_interface__DOT__rst_n;
    Vinterface___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vinterface___024root___eval_static__TOP(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_static__TOP\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_interface__DOT__clk = 0U;
}

VL_ATTR_COLD void Vinterface___024root___eval_final(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_final\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vinterface___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vinterface___024root___eval_phase__stl(Vinterface___024root* vlSelf);

VL_ATTR_COLD void Vinterface___024root___eval_settle(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_settle\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VstlIterCount;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vinterface___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
#endif
            VL_FATAL_MT("tb_interface.sv", 24, "", "DIDNOTCONVERGE: Settle region did not converge after '--converge-limit' of 100 tries");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        vlSelfRef.__VstlPhaseResult = Vinterface___024root___eval_phase__stl(vlSelf);
        vlSelfRef.__VstlFirstIteration = 0U;
    } while (vlSelfRef.__VstlPhaseResult);
}

VL_ATTR_COLD void Vinterface___024root___eval_triggers_vec__stl(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_triggers_vec__stl\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VstlTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VstlFirstIteration)));
}

VL_ATTR_COLD bool Vinterface___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vinterface___024root___dump_triggers__stl(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(Vinterface___024root___trigger_anySet__stl(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD bool Vinterface___024root___trigger_anySet__stl(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___trigger_anySet__stl\n"); );
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

void Vinterface___024root___act_comb__TOP__0(Vinterface___024root* vlSelf);

VL_ATTR_COLD void Vinterface___024root___eval_stl(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_stl\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered[0U])) {
        Vinterface___024root___act_comb__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD bool Vinterface___024root___eval_phase__stl(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_phase__stl\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VstlExecute;
    // Body
    Vinterface___024root___eval_triggers_vec__stl(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vinterface___024root___dump_triggers__stl(vlSelfRef.__VstlTriggered, "stl"s);
    }
#endif
    __VstlExecute = Vinterface___024root___trigger_anySet__stl(vlSelfRef.__VstlTriggered);
    if (__VstlExecute) {
        Vinterface___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

bool Vinterface___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vinterface___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vinterface___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_interface.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @(negedge tb_interface.rst_n)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 2U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 2 is active: @(negedge tb_interface.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 3U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 3 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vinterface___024root___ctor_var_reset(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___ctor_var_reset\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_interface__DOT__rst_n = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 13940582816938783124ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_interface__DOT__rx_tdata, __VscopeHash, 2928629433551419833ull);
    vlSelf->tb_interface__DOT__rx_tvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4441824315910314728ull);
    vlSelf->tb_interface__DOT__rx_tlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7517535488352618724ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_interface__DOT__tx_tdata, __VscopeHash, 15226347986683217572ull);
    vlSelf->tb_interface__DOT__tx_tvalid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16052131039185569989ull);
    vlSelf->tb_interface__DOT__tx_tready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12357567379466376222ull);
    vlSelf->tb_interface__DOT__tx_tlast = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8328280450740152863ull);
    vlSelf->tb_interface__DOT__core_valid_out = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 248987736393865402ull);
    vlSelf->tb_interface__DOT__core_x_hat_0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9278563807012145265ull);
    vlSelf->tb_interface__DOT__core_x_hat_1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5287672085218457841ull);
    vlSelf->tb_interface__DOT__core_x_hat_2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14887624382096082556ull);
    vlSelf->tb_interface__DOT__all_pass = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 544666657023968910ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_interface__DOT__got_cpld, __VscopeHash, 13858479113444413002ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->tb_interface__DOT__exp_cpld, __VscopeHash, 11131981374137399870ull);
    vlSelf->tb_interface__DOT__dut__DOT__reg_ctrl = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13396092345695401886ull);
    vlSelf->tb_interface__DOT__dut__DOT__reg_xhat0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9991212091623226392ull);
    vlSelf->tb_interface__DOT__dut__DOT__reg_xhat1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4551160211889349091ull);
    vlSelf->tb_interface__DOT__dut__DOT__reg_xhat2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9003167827909341742ull);
    vlSelf->tb_interface__DOT__dut__DOT__busy_r = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11019583399378376575ull);
    vlSelf->tb_interface__DOT__dut__DOT__c_fmt = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 2532829082966120842ull);
    vlSelf->tb_interface__DOT__dut__DOT__c_type = VL_SCOPED_RAND_RESET_I(5, __VscopeHash, 9012893545676360727ull);
    vlSelf->tb_interface__DOT__dut__DOT__c_req_id = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 16012094922166957550ull);
    vlSelf->tb_interface__DOT__dut__DOT__c_tag = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 13434574417543165521ull);
    vlSelf->tb_interface__DOT__dut__DOT__c_addr = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4076858766255398705ull);
    vlSelf->tb_interface__DOT__dut__DOT__c_dw_off = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 14049475846562147380ull);
    vlSelf->tb_interface__DOT__dut__DOT__c_wdata = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17636880396338755879ull);
    vlSelf->tb_interface__DOT__dut__DOT__rd_data = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14487528888130601916ull);
    vlSelf->tb_interface__DOT__dut__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5115748425176622791ull);
    vlSelf->tb_interface__DOT__dut__DOT__meas_pulse = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12924954197617442232ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VstlTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0 = 0;
    vlSelf->__Vtrigprevexpr___TOP__tb_interface__DOT__rst_n__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
