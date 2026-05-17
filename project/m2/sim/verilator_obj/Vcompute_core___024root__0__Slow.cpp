// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcompute_core.h for the primary calling header

#include "Vcompute_core__pch.h"

VL_ATTR_COLD void Vcompute_core___024root___eval_static__TOP(Vcompute_core___024root* vlSelf);
void Vcompute_core___024root___timing_ready(Vcompute_core___024root* vlSelf);

VL_ATTR_COLD void Vcompute_core___024root___eval_static(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_static\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vcompute_core___024root___eval_static__TOP(vlSelf);
    vlSelfRef.__Vtrigprevexpr___TOP__tb_compute_core__DOT__clk__0 
        = vlSelfRef.tb_compute_core__DOT__clk;
    Vcompute_core___024root___timing_ready(vlSelf);
    do {
        vlSelfRef.__VactTriggeredAcc[vlSelfRef.__Vi] 
            = vlSelfRef.__VactTriggered[vlSelfRef.__Vi];
        vlSelfRef.__Vi = ((IData)(1U) + vlSelfRef.__Vi);
    } while ((0U >= vlSelfRef.__Vi));
}

VL_ATTR_COLD void Vcompute_core___024root___eval_static__TOP(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_static__TOP\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_compute_core__DOT__dut__DOT__unnamedblk1__DOT__innov = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2911607863116973205ull);
}

VL_ATTR_COLD void Vcompute_core___024root___eval_initial__TOP(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_initial__TOP\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_compute_core__DOT__clk = 0U;
    vlSelfRef.tb_compute_core__DOT__meas[0U] = 0x00010ac2U;
    vlSelfRef.tb_compute_core__DOT__meas[1U] = 0x00011b76U;
    vlSelfRef.tb_compute_core__DOT__meas[2U] = 0x00014a96U;
    vlSelfRef.tb_compute_core__DOT__meas[3U] = 0x00017c1fU;
    vlSelfRef.tb_compute_core__DOT__meas[4U] = 0x0001ba6fU;
    vlSelfRef.tb_compute_core__DOT__meas[5U] = 0x0001bdffU;
    vlSelfRef.tb_compute_core__DOT__meas[6U] = 0x00021de1U;
    vlSelfRef.tb_compute_core__DOT__meas[7U] = 0x00022532U;
    vlSelfRef.tb_compute_core__DOT__meas[8U] = 0x00022909U;
    vlSelfRef.tb_compute_core__DOT__meas[9U] = 0x00023673U;
    vlSelfRef.tb_compute_core__DOT__meas[10U] = 0x000293bcU;
    vlSelfRef.tb_compute_core__DOT__meas[11U] = 0x0002ab11U;
    vlSelfRef.tb_compute_core__DOT__meas[12U] = 0x00028434U;
    vlSelfRef.tb_compute_core__DOT__meas[13U] = 0x0002c2a6U;
    vlSelfRef.tb_compute_core__DOT__meas[14U] = 0x0002e19eU;
    vlSelfRef.tb_compute_core__DOT__meas[15U] = 0x0002e23dU;
    vlSelfRef.tb_compute_core__DOT__meas[16U] = 0x0002f1e1U;
    vlSelfRef.tb_compute_core__DOT__meas[17U] = 0x0002d423U;
    vlSelfRef.tb_compute_core__DOT__meas[18U] = 0x0003002bU;
    vlSelfRef.tb_compute_core__DOT__meas[19U] = 0x00032114U;
    vlSelfRef.tb_compute_core__DOT__meas[20U] = 0x0002dbbeU;
    vlSelfRef.tb_compute_core__DOT__meas[21U] = 0x0002d68dU;
    vlSelfRef.tb_compute_core__DOT__meas[22U] = 0x0002b094U;
    vlSelfRef.tb_compute_core__DOT__meas[23U] = 0x0002aa53U;
    vlSelfRef.tb_compute_core__DOT__meas[24U] = 0x0002d0eeU;
    vlSelfRef.tb_compute_core__DOT__meas[25U] = 0x0002cf5fU;
    vlSelfRef.tb_compute_core__DOT__meas[26U] = 0x0002e21bU;
    vlSelfRef.tb_compute_core__DOT__meas[27U] = 0x0002b2a9U;
    vlSelfRef.tb_compute_core__DOT__meas[28U] = 0x00026f29U;
    vlSelfRef.tb_compute_core__DOT__meas[29U] = 0x00023c12U;
    vlSelfRef.tb_compute_core__DOT__meas[30U] = 0x00024d83U;
    vlSelfRef.tb_compute_core__DOT__meas[31U] = 0x0002054cU;
    vlSelfRef.tb_compute_core__DOT__meas[32U] = 0x0001f1a6U;
    vlSelfRef.tb_compute_core__DOT__meas[33U] = 0x0001d332U;
    vlSelfRef.tb_compute_core__DOT__meas[34U] = 0x00018678U;
    vlSelfRef.tb_compute_core__DOT__meas[35U] = 0x0001dea3U;
    vlSelfRef.tb_compute_core__DOT__meas[36U] = 0x00012e44U;
    vlSelfRef.tb_compute_core__DOT__meas[37U] = 0x00011b78U;
    vlSelfRef.tb_compute_core__DOT__meas[38U] = 0x0000ea8aU;
    vlSelfRef.tb_compute_core__DOT__meas[39U] = 0x0000adb5U;
    vlSelfRef.tb_compute_core__DOT__meas[40U] = 0x00008ff8U;
    vlSelfRef.tb_compute_core__DOT__meas[41U] = 0x00005b00U;
    vlSelfRef.tb_compute_core__DOT__meas[42U] = 0xffffd82aU;
    vlSelfRef.tb_compute_core__DOT__meas[43U] = 0xffffb67aU;
    vlSelfRef.tb_compute_core__DOT__meas[44U] = 0xffff65a4U;
}

VL_ATTR_COLD void Vcompute_core___024root___eval_final(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_final\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vcompute_core___024root___eval_settle(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_settle\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

bool Vcompute_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in);

#ifdef VL_DEBUG
VL_ATTR_COLD void Vcompute_core___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(Vcompute_core___024root___trigger_anySet__act(triggers))))) {
        VL_DBG_MSGS("         No '" + tag + "' region triggers active\n");
    }
    if ((1U & (IData)(triggers[0U]))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 0 is active: @(posedge tb_compute_core.clk)\n");
    }
    if ((1U & (IData)((triggers[0U] >> 1U)))) {
        VL_DBG_MSGS("         '" + tag + "' region trigger index 1 is active: @([true] __VdlySched.awaitingCurrentTime())\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vcompute_core___024root___ctor_var_reset(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___ctor_var_reset\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->vlNamep);
    vlSelf->tb_compute_core__DOT__clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3008233840291440629ull);
    vlSelf->tb_compute_core__DOT__rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14356966467475152209ull);
    vlSelf->tb_compute_core__DOT__valid_in = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10008681970562147942ull);
    vlSelf->tb_compute_core__DOT__y = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13791456908308339984ull);
    for (int __Vi0 = 0; __Vi0 < 45; ++__Vi0) {
        vlSelf->tb_compute_core__DOT__meas[__Vi0] = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 6826391708891533788ull);
    }
    vlSelf->tb_compute_core__DOT__i = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 14050565756845609994ull);
    vlSelf->tb_compute_core__DOT__wcnt = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8704652139531639012ull);
    vlSelf->tb_compute_core__DOT__e0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9775532625277279260ull);
    vlSelf->tb_compute_core__DOT__e1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17785687695206185996ull);
    vlSelf->tb_compute_core__DOT__e2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13343009677028133134ull);
    vlSelf->tb_compute_core__DOT__all_pass = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8406619950999474319ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__state = VL_SCOPED_RAND_RESET_I(3, __VscopeHash, 12650788600417885169ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__x0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 15498163156482035347ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__x1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1617270589443025437ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__x2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13418606305807773068ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__p00 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10388987789817051929ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__p01 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 11256834025286354849ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__p02 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16702864594929370559ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__p11 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13242369179600329516ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__p12 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 7955640714509222438ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__p22 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1520714574296102593ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__y_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 1822245142676685679ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__x0p = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16436735709673154831ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__x1p = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 18338374804718259445ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__x2p = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 5088748737063946918ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__pp00 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17488073941474966923ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__pp01 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 4328617751815772611ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__pp02 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 12988288531366238785ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__pp11 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 2870298606605553149ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__pp12 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17770374126294789196ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__pp22 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 9952634678233024471ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__s_reg = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 16434375423859907601ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__k0 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 3445951710758335933ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__k1 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 8011803217428860418ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__k2 = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 13441490843119588936ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__x0_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10430073743265899626ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__x1_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 10254386279533991782ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__x2_out = VL_SCOPED_RAND_RESET_I(32, __VscopeHash, 17509457789219931530ull);
    vlSelf->tb_compute_core__DOT__dut__DOT__vout = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15629707525899702625ull);
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggered[__Vi0] = 0;
    }
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VactTriggeredAcc[__Vi0] = 0;
    }
    vlSelf->__Vtrigprevexpr___TOP__tb_compute_core__DOT__clk__0 = 0;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        vlSelf->__VnbaTriggered[__Vi0] = 0;
    }
    vlSelf->__Vi = 0;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
