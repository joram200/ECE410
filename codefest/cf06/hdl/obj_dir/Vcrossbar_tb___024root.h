// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vcrossbar_tb.h for the primary calling header

#ifndef VERILATED_VCROSSBAR_TB___024ROOT_H_
#define VERILATED_VCROSSBAR_TB___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vcrossbar_tb__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vcrossbar_tb___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ crossbar_tb__DOT__clk;
    CData/*0:0*/ crossbar_tb__DOT__rst;
    CData/*0:0*/ crossbar_tb__DOT__we;
    CData/*1:0*/ crossbar_tb__DOT__w_row;
    CData/*1:0*/ crossbar_tb__DOT__w_col;
    CData/*0:0*/ crossbar_tb__DOT__w_val;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ crossbar_tb__DOT__pass_count;
    IData/*31:0*/ crossbar_tb__DOT__fail_count;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<CData/*7:0*/, 4> crossbar_tb__DOT__in;
    VlUnpacked<CData/*7:0*/, 4> crossbar_tb__DOT__out;
    VlUnpacked<VlUnpacked<CData/*0:0*/, 4>, 4> crossbar_tb__DOT__dut__DOT__weight;
    VlUnpacked<VlUnpacked<CData/*7:0*/, 4>, 4> crossbar_tb__DOT__dut__DOT__xp_out;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    std::string __Vtask_crossbar_tb__DOT__log_msg__0__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__17__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__18__msg;
    std::string __Vtask_crossbar_tb__DOT__log_outputs__19__label;
    std::string __Vtask_crossbar_tb__DOT__log_msg__20__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__21__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__22__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__23__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__24__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__25__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__26__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__27__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__28__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__29__msg;
    std::string __Vtask_crossbar_tb__DOT__log_msg__30__msg;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_he9f331c2__0;
    VlTriggerScheduler __VtrigSched_he9f33e88__0;

    // INTERNAL VARIABLES
    Vcrossbar_tb__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vcrossbar_tb___024root(Vcrossbar_tb__Syms* symsp, const char* namep);
    ~Vcrossbar_tb___024root();
    VL_UNCOPYABLE(Vcrossbar_tb___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
