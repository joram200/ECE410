// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcompute_core.h for the primary calling header

#include "Vcompute_core__pch.h"

VL_ATTR_COLD void Vcompute_core___024root___eval_initial__TOP(Vcompute_core___024root* vlSelf);
VlCoroutine Vcompute_core___024root___eval_initial__TOP__Vtiming__0(Vcompute_core___024root* vlSelf);
VlCoroutine Vcompute_core___024root___eval_initial__TOP__Vtiming__1(Vcompute_core___024root* vlSelf);

void Vcompute_core___024root___eval_initial(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_initial\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vcompute_core___024root___eval_initial__TOP(vlSelf);
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    Vcompute_core___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vcompute_core___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

void Vcompute_core___024root____VbeforeTrig_hf9cd8378__0(Vcompute_core___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vcompute_core___024root___eval_initial__TOP__Vtiming__0(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_compute_core__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_compute_core__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    // Body
    vlSymsp->_vm_contextp__->dumpfile("../sim/tb_compute_core.vcd"s);
    vlSymsp->_traceDumpOpen();
    vlSelfRef.tb_compute_core__DOT__valid_in = 0U;
    vlSelfRef.tb_compute_core__DOT__y = 0U;
    vlSelfRef.tb_compute_core__DOT__rst = 1U;
    tb_compute_core__DOT__unnamedblk1_1__DOT____Vrepeat0 = 3U;
    while (VL_LTS_III(32, 0U, tb_compute_core__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vcompute_core___024root____VbeforeTrig_hf9cd8378__0(vlSelf, 
                                                            "@(posedge tb_compute_core.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_hf9cd8378__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_compute_core.clk)", 
                                                             "/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 
                                                             165);
        tb_compute_core__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_compute_core__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 
                                         166);
    vlSelfRef.tb_compute_core__DOT__rst = 0U;
    Vcompute_core___024root____VbeforeTrig_hf9cd8378__0(vlSelf, 
                                                        "@(posedge tb_compute_core.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_hf9cd8378__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_compute_core.clk)", 
                                                         "/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 
                                                         168);
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 
                                         168);
    vlSelfRef.tb_compute_core__DOT__i = 0U;
    {
        while (VL_GTS_III(32, 0x0000002dU, vlSelfRef.tb_compute_core__DOT__i)) {
            vlSelfRef.tb_compute_core__DOT__valid_in = 1U;
            vlSelfRef.tb_compute_core__DOT__y = ((0x2cU 
                                                  >= 
                                                  (0x0000003fU 
                                                   & vlSelfRef.tb_compute_core__DOT__i))
                                                  ? vlSelfRef.tb_compute_core__DOT__meas
                                                 [(0x0000003fU 
                                                   & vlSelfRef.tb_compute_core__DOT__i)]
                                                  : 0U);
            Vcompute_core___024root____VbeforeTrig_hf9cd8378__0(vlSelf, 
                                                                "@(posedge tb_compute_core.clk)");
            vlSelfRef.__Vm_traceActivity[2U] = 1U;
            co_await vlSelfRef.__VtrigSched_hf9cd8378__0.trigger(0U, 
                                                                 nullptr, 
                                                                 "@(posedge tb_compute_core.clk)", 
                                                                 "/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 
                                                                 174);
            vlSelfRef.__Vm_traceActivity[2U] = 1U;
            co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                                 nullptr, 
                                                 "/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 
                                                 174);
            vlSelfRef.tb_compute_core__DOT__valid_in = 0U;
            vlSelfRef.tb_compute_core__DOT__y = 0U;
            vlSelfRef.tb_compute_core__DOT__wcnt = 0U;
            while (((~ (IData)(vlSelfRef.tb_compute_core__DOT__dut__DOT__vout)) 
                    & VL_GTS_III(32, 0x00000014U, vlSelfRef.tb_compute_core__DOT__wcnt))) {
                Vcompute_core___024root____VbeforeTrig_hf9cd8378__0(vlSelf, 
                                                                    "@(posedge tb_compute_core.clk)");
                vlSelfRef.__Vm_traceActivity[2U] = 1U;
                co_await vlSelfRef.__VtrigSched_hf9cd8378__0.trigger(0U, 
                                                                     nullptr, 
                                                                     "@(posedge tb_compute_core.clk)", 
                                                                     "/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 
                                                                     181);
                vlSelfRef.__Vm_traceActivity[2U] = 1U;
                co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                                     nullptr, 
                                                     "/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 
                                                     181);
                vlSelfRef.tb_compute_core__DOT__wcnt 
                    = ((IData)(1U) + vlSelfRef.tb_compute_core__DOT__wcnt);
            }
            if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.tb_compute_core__DOT__dut__DOT__vout)))))) {
                VL_WRITEF_NX("[TIMEOUT] valid_out not seen after measurement %0d\nFAIL\n",0,
                             32,vlSelfRef.tb_compute_core__DOT__i);
                VL_FINISH_MT("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 188, "");
                goto __Vlabel0;
            }
            vlSelfRef.tb_compute_core__DOT__i = ((IData)(1U) 
                                                 + vlSelfRef.tb_compute_core__DOT__i);
        }
        __Vlabel0: ;
    }
    vlSelfRef.tb_compute_core__DOT__e0 = (vlSelfRef.tb_compute_core__DOT__dut__DOT__x0_out 
                                          - (IData)(0xffff8650U));
    vlSelfRef.tb_compute_core__DOT__e1 = (vlSelfRef.tb_compute_core__DOT__dut__DOT__x1_out 
                                          - (IData)(0xfff7a804U));
    vlSelfRef.tb_compute_core__DOT__e2 = (vlSelfRef.tb_compute_core__DOT__dut__DOT__x2_out 
                                          - (IData)(0xfff5ab14U));
    if ((vlSelfRef.tb_compute_core__DOT__e0 >> 0x1fU)) {
        vlSelfRef.tb_compute_core__DOT__e0 = (- vlSelfRef.tb_compute_core__DOT__e0);
    }
    if ((vlSelfRef.tb_compute_core__DOT__e1 >> 0x1fU)) {
        vlSelfRef.tb_compute_core__DOT__e1 = (- vlSelfRef.tb_compute_core__DOT__e1);
    }
    if ((vlSelfRef.tb_compute_core__DOT__e2 >> 0x1fU)) {
        vlSelfRef.tb_compute_core__DOT__e2 = (- vlSelfRef.tb_compute_core__DOT__e2);
    }
    VL_WRITEF_NX("--- compute_core output (Q16.16) ---\n  x_hat_0 = %0d  ref = -31152  |err| = %0d\n  x_hat_1 = %0d  ref = -546812  |err| = %0d\n  x_hat_2 = %0d  ref = -677100  |err| = %0d\n  tolerance = 8192 LSBs\n",0,
                 32,vlSelfRef.tb_compute_core__DOT__dut__DOT__x0_out,
                 32,vlSelfRef.tb_compute_core__DOT__e0,
                 32,vlSelfRef.tb_compute_core__DOT__dut__DOT__x1_out,
                 32,vlSelfRef.tb_compute_core__DOT__e1,
                 32,vlSelfRef.tb_compute_core__DOT__dut__DOT__x2_out,
                 32,vlSelfRef.tb_compute_core__DOT__e2);
    vlSelfRef.tb_compute_core__DOT__all_pass = ((VL_GTES_III(32, 0x00002000U, vlSelfRef.tb_compute_core__DOT__e0) 
                                                 & VL_GTES_III(32, 0x00002000U, vlSelfRef.tb_compute_core__DOT__e1)) 
                                                & VL_GTES_III(32, 0x00002000U, vlSelfRef.tb_compute_core__DOT__e2));
    if (vlSelfRef.tb_compute_core__DOT__all_pass) {
        VL_WRITEF_NX("PASS\n",0);
    } else {
        VL_WRITEF_NX("FAIL  x0_err=%0d x1_err=%0d x2_err=%0d\n",0,
                     32,vlSelfRef.tb_compute_core__DOT__e0,
                     32,vlSelfRef.tb_compute_core__DOT__e1,
                     32,vlSelfRef.tb_compute_core__DOT__e2);
    }
    VL_FINISH_MT("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 215, "");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_return;
}

VlCoroutine Vcompute_core___024root___eval_initial__TOP__Vtiming__1(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 
                                             82);
        vlSelfRef.tb_compute_core__DOT__clk = (1U & 
                                               (~ (IData)(vlSelfRef.tb_compute_core__DOT__clk)));
    }
    co_return;
}

void Vcompute_core___024root___eval_triggers_vec__act(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_triggers_vec__act\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                      << 1U) 
                                                     | ((IData)(vlSelfRef.tb_compute_core__DOT__clk) 
                                                        & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_compute_core__DOT__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_compute_core__DOT__clk__0 
        = vlSelfRef.tb_compute_core__DOT__clk;
}

bool Vcompute_core___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___trigger_anySet__act\n"); );
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

void Vcompute_core___024root___nba_sequent__TOP__0(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___nba_sequent__TOP__0\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__a;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__a = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__a;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__a = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__a;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__a = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__a;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__a = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__a;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__a = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__a;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__a = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__a;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__a = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__a;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__a = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__a;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__a = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__prod = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__Vfuncout;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__b;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__b = 0;
    QData/*63:0*/ __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__prod;
    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__prod = 0;
    CData/*2:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__state;
    __Vdly__tb_compute_core__DOT__dut__DOT__state = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__x0;
    __Vdly__tb_compute_core__DOT__dut__DOT__x0 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__x1;
    __Vdly__tb_compute_core__DOT__dut__DOT__x1 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__x2;
    __Vdly__tb_compute_core__DOT__dut__DOT__x2 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__p00;
    __Vdly__tb_compute_core__DOT__dut__DOT__p00 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__p01;
    __Vdly__tb_compute_core__DOT__dut__DOT__p01 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__p02;
    __Vdly__tb_compute_core__DOT__dut__DOT__p02 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__p11;
    __Vdly__tb_compute_core__DOT__dut__DOT__p11 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__p12;
    __Vdly__tb_compute_core__DOT__dut__DOT__p12 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__p22;
    __Vdly__tb_compute_core__DOT__dut__DOT__p22 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__y_reg;
    __Vdly__tb_compute_core__DOT__dut__DOT__y_reg = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__x0p;
    __Vdly__tb_compute_core__DOT__dut__DOT__x0p = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__x1p;
    __Vdly__tb_compute_core__DOT__dut__DOT__x1p = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__x2p;
    __Vdly__tb_compute_core__DOT__dut__DOT__x2p = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__pp00;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp00 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__pp01;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp01 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__pp02;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp02 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__pp11;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp11 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__pp12;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp12 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__pp22;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp22 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__s_reg;
    __Vdly__tb_compute_core__DOT__dut__DOT__s_reg = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__k0;
    __Vdly__tb_compute_core__DOT__dut__DOT__k0 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__k1;
    __Vdly__tb_compute_core__DOT__dut__DOT__k1 = 0;
    IData/*31:0*/ __Vdly__tb_compute_core__DOT__dut__DOT__k2;
    __Vdly__tb_compute_core__DOT__dut__DOT__k2 = 0;
    // Body
    __Vdly__tb_compute_core__DOT__dut__DOT__state = vlSelfRef.tb_compute_core__DOT__dut__DOT__state;
    __Vdly__tb_compute_core__DOT__dut__DOT__x0 = vlSelfRef.tb_compute_core__DOT__dut__DOT__x0;
    __Vdly__tb_compute_core__DOT__dut__DOT__x1 = vlSelfRef.tb_compute_core__DOT__dut__DOT__x1;
    __Vdly__tb_compute_core__DOT__dut__DOT__x2 = vlSelfRef.tb_compute_core__DOT__dut__DOT__x2;
    __Vdly__tb_compute_core__DOT__dut__DOT__p00 = vlSelfRef.tb_compute_core__DOT__dut__DOT__p00;
    __Vdly__tb_compute_core__DOT__dut__DOT__p01 = vlSelfRef.tb_compute_core__DOT__dut__DOT__p01;
    __Vdly__tb_compute_core__DOT__dut__DOT__p02 = vlSelfRef.tb_compute_core__DOT__dut__DOT__p02;
    __Vdly__tb_compute_core__DOT__dut__DOT__p11 = vlSelfRef.tb_compute_core__DOT__dut__DOT__p11;
    __Vdly__tb_compute_core__DOT__dut__DOT__p12 = vlSelfRef.tb_compute_core__DOT__dut__DOT__p12;
    __Vdly__tb_compute_core__DOT__dut__DOT__p22 = vlSelfRef.tb_compute_core__DOT__dut__DOT__p22;
    __Vdly__tb_compute_core__DOT__dut__DOT__y_reg = vlSelfRef.tb_compute_core__DOT__dut__DOT__y_reg;
    __Vdly__tb_compute_core__DOT__dut__DOT__x0p = vlSelfRef.tb_compute_core__DOT__dut__DOT__x0p;
    __Vdly__tb_compute_core__DOT__dut__DOT__x1p = vlSelfRef.tb_compute_core__DOT__dut__DOT__x1p;
    __Vdly__tb_compute_core__DOT__dut__DOT__x2p = vlSelfRef.tb_compute_core__DOT__dut__DOT__x2p;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp00 = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp00;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp01 = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp01;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp02 = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp02;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp11 = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp11;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp12 = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp12;
    __Vdly__tb_compute_core__DOT__dut__DOT__pp22 = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp22;
    __Vdly__tb_compute_core__DOT__dut__DOT__s_reg = vlSelfRef.tb_compute_core__DOT__dut__DOT__s_reg;
    __Vdly__tb_compute_core__DOT__dut__DOT__k0 = vlSelfRef.tb_compute_core__DOT__dut__DOT__k0;
    __Vdly__tb_compute_core__DOT__dut__DOT__k1 = vlSelfRef.tb_compute_core__DOT__dut__DOT__k1;
    __Vdly__tb_compute_core__DOT__dut__DOT__k2 = vlSelfRef.tb_compute_core__DOT__dut__DOT__k2;
    if (vlSelfRef.tb_compute_core__DOT__rst) {
        __Vdly__tb_compute_core__DOT__dut__DOT__state = 0U;
        vlSelfRef.tb_compute_core__DOT__dut__DOT__vout = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__x0 = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__x1 = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__x2 = 0U;
        vlSelfRef.tb_compute_core__DOT__dut__DOT__x0_out = 0U;
        vlSelfRef.tb_compute_core__DOT__dut__DOT__x1_out = 0U;
        vlSelfRef.tb_compute_core__DOT__dut__DOT__x2_out = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__p00 = 0x0000199aU;
        __Vdly__tb_compute_core__DOT__dut__DOT__p01 = 0x0000199aU;
        __Vdly__tb_compute_core__DOT__dut__DOT__p02 = 0x0000199aU;
        __Vdly__tb_compute_core__DOT__dut__DOT__p11 = 0x27100000U;
        __Vdly__tb_compute_core__DOT__dut__DOT__p12 = 0x000a0000U;
        __Vdly__tb_compute_core__DOT__dut__DOT__p22 = 0x00640000U;
        __Vdly__tb_compute_core__DOT__dut__DOT__y_reg = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__x0p = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__x1p = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__x2p = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__pp00 = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__pp01 = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__pp02 = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__pp11 = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__pp12 = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__pp22 = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__s_reg = 0x00010000U;
        __Vdly__tb_compute_core__DOT__dut__DOT__k0 = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__k1 = 0U;
        __Vdly__tb_compute_core__DOT__dut__DOT__k2 = 0U;
    } else {
        vlSelfRef.tb_compute_core__DOT__dut__DOT__vout = 0U;
        if ((4U & (IData)(vlSelfRef.tb_compute_core__DOT__dut__DOT__state))) {
            if ((2U & (IData)(vlSelfRef.tb_compute_core__DOT__dut__DOT__state))) {
                if ((1U & (IData)(vlSelfRef.tb_compute_core__DOT__dut__DOT__state))) {
                    __Vdly__tb_compute_core__DOT__dut__DOT__state = 0U;
                } else {
                    vlSelfRef.tb_compute_core__DOT__dut__DOT__x0_out 
                        = vlSelfRef.tb_compute_core__DOT__dut__DOT__x0;
                    vlSelfRef.tb_compute_core__DOT__dut__DOT__x1_out 
                        = vlSelfRef.tb_compute_core__DOT__dut__DOT__x1;
                    vlSelfRef.tb_compute_core__DOT__dut__DOT__x2_out 
                        = vlSelfRef.tb_compute_core__DOT__dut__DOT__x2;
                    vlSelfRef.tb_compute_core__DOT__dut__DOT__vout = 1U;
                    __Vdly__tb_compute_core__DOT__dut__DOT__state = 0U;
                }
            } else if ((1U & (IData)(vlSelfRef.tb_compute_core__DOT__dut__DOT__state))) {
                vlSelfRef.tb_compute_core__DOT__dut__DOT__unnamedblk1__DOT__innov 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__y_reg 
                       - vlSelfRef.tb_compute_core__DOT__dut__DOT__x0p);
                __Vdly__tb_compute_core__DOT__dut__DOT__x0 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__x0p 
                       + ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__unnamedblk1__DOT__innov;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__a 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__k0;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__0__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__state = 6U;
                __Vdly__tb_compute_core__DOT__dut__DOT__x1 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__x1p 
                       + ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__unnamedblk1__DOT__innov;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__a 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__k1;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__1__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__x2 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__x2p 
                       + ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__unnamedblk1__DOT__innov;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__a 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__k2;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__2__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__p00 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__pp00 
                       - ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp00;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__a 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__k0;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__3__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__p01 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__pp01 
                       - ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp01;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__a 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__k0;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__4__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__p02 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__pp02 
                       - ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp02;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__a 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__k0;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__5__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__p11 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__pp11 
                       - ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp01;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__a 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__k1;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__6__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__p12 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__pp12 
                       - ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp02;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__a 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__k1;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__7__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__p22 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__pp22 
                       - ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__pp02;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__a 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__k2;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__prod 
                                = VL_MULS_QQQ(64, VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__a), 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__8__Vfuncout));
            } else {
                __Vdly__tb_compute_core__DOT__dut__DOT__k0 
                    = (IData)(VL_DIVS_QQQ(64, VL_SHIFTL_QQI(64,64,32, 
                                                            VL_EXTENDS_QI(64,32, vlSelfRef.tb_compute_core__DOT__dut__DOT__pp00), 0x00000010U), 
                                          VL_EXTENDS_QI(64,32, vlSelfRef.tb_compute_core__DOT__dut__DOT__s_reg)));
                __Vdly__tb_compute_core__DOT__dut__DOT__state = 5U;
                __Vdly__tb_compute_core__DOT__dut__DOT__k1 
                    = (IData)(VL_DIVS_QQQ(64, VL_SHIFTL_QQI(64,64,32, 
                                                            VL_EXTENDS_QI(64,32, vlSelfRef.tb_compute_core__DOT__dut__DOT__pp01), 0x00000010U), 
                                          VL_EXTENDS_QI(64,32, vlSelfRef.tb_compute_core__DOT__dut__DOT__s_reg)));
                __Vdly__tb_compute_core__DOT__dut__DOT__k2 
                    = (IData)(VL_DIVS_QQQ(64, VL_SHIFTL_QQI(64,64,32, 
                                                            VL_EXTENDS_QI(64,32, vlSelfRef.tb_compute_core__DOT__dut__DOT__pp02), 0x00000010U), 
                                          VL_EXTENDS_QI(64,32, vlSelfRef.tb_compute_core__DOT__dut__DOT__s_reg)));
            }
        } else if ((2U & (IData)(vlSelfRef.tb_compute_core__DOT__dut__DOT__state))) {
            if ((1U & (IData)(vlSelfRef.tb_compute_core__DOT__dut__DOT__state))) {
                __Vdly__tb_compute_core__DOT__dut__DOT__s_reg 
                    = ((IData)(0x00050000U) + vlSelfRef.tb_compute_core__DOT__dut__DOT__pp00);
                __Vdly__tb_compute_core__DOT__dut__DOT__state = 4U;
            } else {
                __Vdly__tb_compute_core__DOT__dut__DOT__pp00 
                    = ((IData)(0x00000ccdU) + (((vlSelfRef.tb_compute_core__DOT__dut__DOT__p00 
                                                 + 
                                                 ([&]() {
                                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__b 
                                            = vlSelfRef.tb_compute_core__DOT__dut__DOT__p01;
                                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__prod 
                                            = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                          VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__b));
                                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__Vfuncout 
                                            = (IData)(
                                                      (__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__prod 
                                                       >> 0x10U));
                                    }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__9__Vfuncout)) 
                                                + ([&]() {
                                    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__b 
                                        = vlSelfRef.tb_compute_core__DOT__dut__DOT__p01;
                                    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__prod 
                                        = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                      VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__b));
                                    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__Vfuncout 
                                        = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__prod 
                                                   >> 0x10U));
                                }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__10__Vfuncout)) 
                                               + ([&]() {
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__b 
                                    = vlSelfRef.tb_compute_core__DOT__dut__DOT__p11;
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__prod 
                                    = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                  VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__b));
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__Vfuncout 
                                    = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__prod 
                                               >> 0x10U));
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__b 
                                    = __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__12__Vfuncout;
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__prod 
                                    = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                  VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__b));
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__Vfuncout 
                                    = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__prod 
                                               >> 0x10U));
                            }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__11__Vfuncout)));
                __Vdly__tb_compute_core__DOT__dut__DOT__state = 3U;
                __Vdly__tb_compute_core__DOT__dut__DOT__pp01 
                    = (((vlSelfRef.tb_compute_core__DOT__dut__DOT__p01 
                         + ([&]() {
                                    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__b 
                                        = vlSelfRef.tb_compute_core__DOT__dut__DOT__p02;
                                    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__prod 
                                        = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                      VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__b));
                                    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__Vfuncout 
                                        = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__prod 
                                                   >> 0x10U));
                                }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__13__Vfuncout)) 
                        + ([&]() {
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__b 
                                    = vlSelfRef.tb_compute_core__DOT__dut__DOT__p11;
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__prod 
                                    = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                  VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__b));
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__Vfuncout 
                                    = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__prod 
                                               >> 0x10U));
                            }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__14__Vfuncout)) 
                       + ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__p12;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__prod 
                                = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__prod 
                                           >> 0x10U));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__b 
                                = __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__16__Vfuncout;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__prod 
                                = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__15__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__pp02 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__p02 
                       + ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__p12;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__prod 
                                = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__17__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__pp11 
                    = ((IData)(0x00000ccdU) + (((vlSelfRef.tb_compute_core__DOT__dut__DOT__p11 
                                                 + 
                                                 ([&]() {
                                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__b 
                                            = vlSelfRef.tb_compute_core__DOT__dut__DOT__p12;
                                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__prod 
                                            = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                          VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__b));
                                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__Vfuncout 
                                            = (IData)(
                                                      (__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__prod 
                                                       >> 0x10U));
                                    }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__18__Vfuncout)) 
                                                + ([&]() {
                                    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__b 
                                        = vlSelfRef.tb_compute_core__DOT__dut__DOT__p12;
                                    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__prod 
                                        = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                      VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__b));
                                    __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__Vfuncout 
                                        = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__prod 
                                                   >> 0x10U));
                                }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__19__Vfuncout)) 
                                               + ([&]() {
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__b 
                                    = vlSelfRef.tb_compute_core__DOT__dut__DOT__p22;
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__prod 
                                    = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                  VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__b));
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__Vfuncout 
                                    = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__prod 
                                               >> 0x10U));
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__b 
                                    = __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__21__Vfuncout;
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__prod 
                                    = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                                  VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__b));
                                __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__Vfuncout 
                                    = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__prod 
                                               >> 0x10U));
                            }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__20__Vfuncout)));
                __Vdly__tb_compute_core__DOT__dut__DOT__pp12 
                    = (vlSelfRef.tb_compute_core__DOT__dut__DOT__p12 
                       + ([&]() {
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__b 
                                = vlSelfRef.tb_compute_core__DOT__dut__DOT__p22;
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__prod 
                                = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                              VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__b));
                            __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__Vfuncout 
                                = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__prod 
                                           >> 0x10U));
                        }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__22__Vfuncout));
                __Vdly__tb_compute_core__DOT__dut__DOT__pp22 
                    = vlSelfRef.tb_compute_core__DOT__dut__DOT__p22;
            }
        } else if ((1U & (IData)(vlSelfRef.tb_compute_core__DOT__dut__DOT__state))) {
            __Vdly__tb_compute_core__DOT__dut__DOT__x0p 
                = (vlSelfRef.tb_compute_core__DOT__dut__DOT__x0 
                   + ([&]() {
                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__b 
                            = vlSelfRef.tb_compute_core__DOT__dut__DOT__x1;
                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__prod 
                            = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                          VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__b));
                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__Vfuncout 
                            = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__prod 
                                       >> 0x10U));
                    }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__23__Vfuncout));
            __Vdly__tb_compute_core__DOT__dut__DOT__state = 2U;
            __Vdly__tb_compute_core__DOT__dut__DOT__x1p 
                = (vlSelfRef.tb_compute_core__DOT__dut__DOT__x1 
                   + ([&]() {
                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__b 
                            = vlSelfRef.tb_compute_core__DOT__dut__DOT__x2;
                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__prod 
                            = VL_MULS_QQQ(64, 0x0000000000000889ULL, 
                                          VL_EXTENDS_QI(64,32, __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__b));
                        __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__Vfuncout 
                            = (IData)((__Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__prod 
                                       >> 0x10U));
                    }(), __Vfunc_tb_compute_core__DOT__dut__DOT__fp_mul__24__Vfuncout));
            __Vdly__tb_compute_core__DOT__dut__DOT__x2p 
                = vlSelfRef.tb_compute_core__DOT__dut__DOT__x2;
        } else if (vlSelfRef.tb_compute_core__DOT__valid_in) {
            __Vdly__tb_compute_core__DOT__dut__DOT__y_reg 
                = vlSelfRef.tb_compute_core__DOT__y;
            __Vdly__tb_compute_core__DOT__dut__DOT__state = 1U;
        }
    }
    vlSelfRef.tb_compute_core__DOT__dut__DOT__state 
        = __Vdly__tb_compute_core__DOT__dut__DOT__state;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__x0 = __Vdly__tb_compute_core__DOT__dut__DOT__x0;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__x1 = __Vdly__tb_compute_core__DOT__dut__DOT__x1;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__x2 = __Vdly__tb_compute_core__DOT__dut__DOT__x2;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__p00 = __Vdly__tb_compute_core__DOT__dut__DOT__p00;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__p01 = __Vdly__tb_compute_core__DOT__dut__DOT__p01;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__p02 = __Vdly__tb_compute_core__DOT__dut__DOT__p02;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__p11 = __Vdly__tb_compute_core__DOT__dut__DOT__p11;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__p12 = __Vdly__tb_compute_core__DOT__dut__DOT__p12;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__p22 = __Vdly__tb_compute_core__DOT__dut__DOT__p22;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__y_reg 
        = __Vdly__tb_compute_core__DOT__dut__DOT__y_reg;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__x0p = __Vdly__tb_compute_core__DOT__dut__DOT__x0p;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__x1p = __Vdly__tb_compute_core__DOT__dut__DOT__x1p;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__x2p = __Vdly__tb_compute_core__DOT__dut__DOT__x2p;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__pp00 
        = __Vdly__tb_compute_core__DOT__dut__DOT__pp00;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__pp01 
        = __Vdly__tb_compute_core__DOT__dut__DOT__pp01;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__pp02 
        = __Vdly__tb_compute_core__DOT__dut__DOT__pp02;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__pp11 
        = __Vdly__tb_compute_core__DOT__dut__DOT__pp11;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__pp12 
        = __Vdly__tb_compute_core__DOT__dut__DOT__pp12;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__pp22 
        = __Vdly__tb_compute_core__DOT__dut__DOT__pp22;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__s_reg 
        = __Vdly__tb_compute_core__DOT__dut__DOT__s_reg;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__k0 = __Vdly__tb_compute_core__DOT__dut__DOT__k0;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__k1 = __Vdly__tb_compute_core__DOT__dut__DOT__k1;
    vlSelfRef.tb_compute_core__DOT__dut__DOT__k2 = __Vdly__tb_compute_core__DOT__dut__DOT__k2;
}

void Vcompute_core___024root___eval_nba(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_nba\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vcompute_core___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
    }
}

void Vcompute_core___024root___timing_ready(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___timing_ready\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_hf9cd8378__0.ready("@(posedge tb_compute_core.clk)");
    }
}

void Vcompute_core___024root___timing_resume(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___timing_resume\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_hf9cd8378__0.moveToResumeQueue(
                                                          "@(posedge tb_compute_core.clk)");
    vlSelfRef.__VtrigSched_hf9cd8378__0.resume("@(posedge tb_compute_core.clk)");
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vcompute_core___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vcompute_core___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vcompute_core___024root___eval_phase__act(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_phase__act\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vcompute_core___024root___eval_triggers_vec__act(vlSelf);
    Vcompute_core___024root___timing_ready(vlSelf);
    Vcompute_core___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcompute_core___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vcompute_core___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vcompute_core___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vcompute_core___024root___timing_resume(vlSelf);
    }
    return (__VactExecute);
}

bool Vcompute_core___024root___eval_phase__inact(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_phase__inact\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 40, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vcompute_core___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vcompute_core___024root___eval_phase__nba(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_phase__nba\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vcompute_core___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vcompute_core___024root___eval_nba(vlSelf);
        Vcompute_core___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vcompute_core___024root___eval(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vcompute_core___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 40, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 40, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vcompute_core___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/project/m2/tb/tb_compute_core.sv", 40, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vcompute_core___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vcompute_core___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vcompute_core___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vcompute_core___024root____VbeforeTrig_hf9cd8378__0(Vcompute_core___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root____VbeforeTrig_hf9cd8378__0\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((IData)(vlSelfRef.tb_compute_core__DOT__clk) 
                                  & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_compute_core__DOT__clk__0)))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_compute_core__DOT__clk__0 
        = vlSelfRef.tb_compute_core__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_hf9cd8378__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hf9cd8378__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hf9cd8378__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_hf9cd8378__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vcompute_core___024root___eval_debug_assertions(Vcompute_core___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcompute_core___024root___eval_debug_assertions\n"); );
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
