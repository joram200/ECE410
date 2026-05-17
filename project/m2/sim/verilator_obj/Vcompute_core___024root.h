// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcompute_core.h for the primary calling header

#ifndef VERILATED_VCOMPUTE_CORE___024ROOT_H_
#define VERILATED_VCOMPUTE_CORE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vcompute_core__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcompute_core___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_compute_core__DOT__clk;
    CData/*0:0*/ tb_compute_core__DOT__rst;
    CData/*0:0*/ tb_compute_core__DOT__valid_in;
    CData/*0:0*/ tb_compute_core__DOT__all_pass;
    CData/*2:0*/ tb_compute_core__DOT__dut__DOT__state;
    CData/*0:0*/ tb_compute_core__DOT__dut__DOT__vout;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_compute_core__DOT__clk__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ tb_compute_core__DOT__y;
    IData/*31:0*/ tb_compute_core__DOT__i;
    IData/*31:0*/ tb_compute_core__DOT__wcnt;
    IData/*31:0*/ tb_compute_core__DOT__e0;
    IData/*31:0*/ tb_compute_core__DOT__e1;
    IData/*31:0*/ tb_compute_core__DOT__e2;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__x0;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__x1;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__x2;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__p00;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__p01;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__p02;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__p11;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__p12;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__p22;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__y_reg;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__x0p;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__x1p;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__x2p;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__pp00;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__pp01;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__pp02;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__pp11;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__pp12;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__pp22;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__s_reg;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__k0;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__k1;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__k2;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__x0_out;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__x1_out;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__x2_out;
    IData/*31:0*/ tb_compute_core__DOT__dut__DOT__unnamedblk1__DOT__innov;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<IData/*31:0*/, 45> tb_compute_core__DOT__meas;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_hf9cd8378__0;

    // INTERNAL VARIABLES
    Vcompute_core__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vcompute_core___024root(Vcompute_core__Syms* symsp, const char* namep);
    ~Vcompute_core___024root();
    VL_UNCOPYABLE(Vcompute_core___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
