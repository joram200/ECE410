// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vinterface.h for the primary calling header

#ifndef VERILATED_VINTERFACE___024ROOT_H_
#define VERILATED_VINTERFACE___024ROOT_H_  // guard

#include "verilated.h"
#include "verilated_timing.h"


class Vinterface__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vinterface___024root final {
  public:

    // DESIGN SPECIFIC STATE
    CData/*0:0*/ tb_interface__DOT__clk;
    CData/*0:0*/ tb_interface__DOT__rst_n;
    CData/*0:0*/ tb_interface__DOT__rx_tvalid;
    CData/*0:0*/ tb_interface__DOT__rx_tlast;
    CData/*0:0*/ tb_interface__DOT__tx_tvalid;
    CData/*0:0*/ tb_interface__DOT__tx_tready;
    CData/*0:0*/ tb_interface__DOT__tx_tlast;
    CData/*0:0*/ tb_interface__DOT__core_valid_out;
    CData/*0:0*/ tb_interface__DOT__all_pass;
    CData/*0:0*/ tb_interface__DOT__dut__DOT__busy_r;
    CData/*2:0*/ tb_interface__DOT__dut__DOT__c_fmt;
    CData/*4:0*/ tb_interface__DOT__dut__DOT__c_type;
    CData/*7:0*/ tb_interface__DOT__dut__DOT__c_tag;
    CData/*2:0*/ tb_interface__DOT__dut__DOT__c_dw_off;
    CData/*1:0*/ tb_interface__DOT__dut__DOT__state;
    CData/*0:0*/ tb_interface__DOT__dut__DOT__meas_pulse;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_interface__DOT__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__tb_interface__DOT__rst_n__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VinactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    SData/*15:0*/ tb_interface__DOT__dut__DOT__c_req_id;
    VlWide<4>/*127:0*/ tb_interface__DOT__rx_tdata;
    VlWide<4>/*127:0*/ tb_interface__DOT__tx_tdata;
    IData/*31:0*/ tb_interface__DOT__core_x_hat_0;
    IData/*31:0*/ tb_interface__DOT__core_x_hat_1;
    IData/*31:0*/ tb_interface__DOT__core_x_hat_2;
    VlWide<4>/*127:0*/ tb_interface__DOT__got_cpld;
    VlWide<4>/*127:0*/ tb_interface__DOT__exp_cpld;
    IData/*31:0*/ tb_interface__DOT__dut__DOT__reg_ctrl;
    IData/*31:0*/ tb_interface__DOT__dut__DOT__reg_xhat0;
    IData/*31:0*/ tb_interface__DOT__dut__DOT__reg_xhat1;
    IData/*31:0*/ tb_interface__DOT__dut__DOT__reg_xhat2;
    IData/*31:0*/ tb_interface__DOT__dut__DOT__c_addr;
    IData/*31:0*/ tb_interface__DOT__dut__DOT__c_wdata;
    IData/*31:0*/ tb_interface__DOT__dut__DOT__rd_data;
    IData/*31:0*/ __VactIterCount;
    IData/*31:0*/ __VinactIterCount;
    IData/*31:0*/ __Vi;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggeredAcc;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
    VlDelayScheduler __VdlySched;
    VlTriggerScheduler __VtrigSched_h5647339b__0;
    VlTriggerScheduler __VtrigSched_h56473077__0;

    // INTERNAL VARIABLES
    Vinterface__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vinterface___024root(Vinterface__Syms* symsp, const char* namep);
    ~Vinterface___024root();
    VL_UNCOPYABLE(Vinterface___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
