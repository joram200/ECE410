// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vinterface.h for the primary calling header

#include "Vinterface__pch.h"

VlCoroutine Vinterface___024root___eval_initial__TOP__Vtiming__0(Vinterface___024root* vlSelf);
VlCoroutine Vinterface___024root___eval_initial__TOP__Vtiming__1(Vinterface___024root* vlSelf);
VlCoroutine Vinterface___024root___eval_initial__TOP__Vtiming__2(Vinterface___024root* vlSelf);

void Vinterface___024root___eval_initial(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_initial\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vinterface___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
    Vinterface___024root___eval_initial__TOP__Vtiming__1(vlSelf);
    Vinterface___024root___eval_initial__TOP__Vtiming__2(vlSelf);
}

void Vinterface___024root____VbeforeTrig_h5647339b__0(Vinterface___024root* vlSelf, const char* __VeventDescription);
void Vinterface___024root____VbeforeTrig_h56473077__0(Vinterface___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vinterface___024root___eval_initial__TOP__Vtiming__0(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ tb_interface__DOT__unnamedblk1_1__DOT____Vrepeat0;
    tb_interface__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    IData/*31:0*/ tb_interface__DOT__unnamedblk1_2__DOT____Vrepeat1;
    tb_interface__DOT__unnamedblk1_2__DOT____Vrepeat1 = 0;
    IData/*31:0*/ tb_interface__DOT__unnamedblk1_3__DOT____Vrepeat2;
    tb_interface__DOT__unnamedblk1_3__DOT____Vrepeat2 = 0;
    IData/*31:0*/ tb_interface__DOT__unnamedblk1_4__DOT____Vrepeat3;
    tb_interface__DOT__unnamedblk1_4__DOT____Vrepeat3 = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_interface__DOT__send_tlp__0__tlp;
    VL_ZERO_W(128, __Vtask_tb_interface__DOT__send_tlp__0__tlp);
    VlWide<4>/*127:0*/ __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout);
    IData/*31:0*/ __Vfunc_tb_interface__DOT__mwr32__1__addr;
    __Vfunc_tb_interface__DOT__mwr32__1__addr = 0;
    SData/*15:0*/ __Vfunc_tb_interface__DOT__mwr32__1__req_id;
    __Vfunc_tb_interface__DOT__mwr32__1__req_id = 0;
    CData/*7:0*/ __Vfunc_tb_interface__DOT__mwr32__1__tag;
    __Vfunc_tb_interface__DOT__mwr32__1__tag = 0;
    IData/*31:0*/ __Vfunc_tb_interface__DOT__mwr32__1__wdata;
    __Vfunc_tb_interface__DOT__mwr32__1__wdata = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_interface__DOT__send_tlp__2__tlp;
    VL_ZERO_W(128, __Vtask_tb_interface__DOT__send_tlp__2__tlp);
    VlWide<4>/*127:0*/ __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout);
    IData/*31:0*/ __Vfunc_tb_interface__DOT__mrd32__3__addr;
    __Vfunc_tb_interface__DOT__mrd32__3__addr = 0;
    SData/*15:0*/ __Vfunc_tb_interface__DOT__mrd32__3__req_id;
    __Vfunc_tb_interface__DOT__mrd32__3__req_id = 0;
    CData/*7:0*/ __Vfunc_tb_interface__DOT__mrd32__3__tag;
    __Vfunc_tb_interface__DOT__mrd32__3__tag = 0;
    VlWide<4>/*127:0*/ __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout);
    SData/*15:0*/ __Vfunc_tb_interface__DOT__make_cpld__4__req_id;
    __Vfunc_tb_interface__DOT__make_cpld__4__req_id = 0;
    CData/*7:0*/ __Vfunc_tb_interface__DOT__make_cpld__4__tag;
    __Vfunc_tb_interface__DOT__make_cpld__4__tag = 0;
    IData/*31:0*/ __Vfunc_tb_interface__DOT__make_cpld__4__addr;
    __Vfunc_tb_interface__DOT__make_cpld__4__addr = 0;
    IData/*31:0*/ __Vfunc_tb_interface__DOT__make_cpld__4__rd_data;
    __Vfunc_tb_interface__DOT__make_cpld__4__rd_data = 0;
    VlWide<4>/*127:0*/ __Vtask_tb_interface__DOT__send_tlp__5__tlp;
    VL_ZERO_W(128, __Vtask_tb_interface__DOT__send_tlp__5__tlp);
    VlWide<4>/*127:0*/ __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout;
    VL_ZERO_W(128, __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout);
    IData/*31:0*/ __Vfunc_tb_interface__DOT__mwr32__6__addr;
    __Vfunc_tb_interface__DOT__mwr32__6__addr = 0;
    SData/*15:0*/ __Vfunc_tb_interface__DOT__mwr32__6__req_id;
    __Vfunc_tb_interface__DOT__mwr32__6__req_id = 0;
    CData/*7:0*/ __Vfunc_tb_interface__DOT__mwr32__6__tag;
    __Vfunc_tb_interface__DOT__mwr32__6__tag = 0;
    IData/*31:0*/ __Vfunc_tb_interface__DOT__mwr32__6__wdata;
    __Vfunc_tb_interface__DOT__mwr32__6__wdata = 0;
    // Body
    vlSymsp->_vm_contextp__->dumpfile("../sim/tb_interface.vcd"s);
    vlSymsp->_traceDumpOpen();
    vlSelfRef.tb_interface__DOT__rx_tdata[0U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[1U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[2U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[3U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tvalid = 0U;
    vlSelfRef.tb_interface__DOT__rx_tlast = 0U;
    vlSelfRef.tb_interface__DOT__tx_tready = 1U;
    vlSelfRef.tb_interface__DOT__core_valid_out = 0U;
    vlSelfRef.tb_interface__DOT__core_x_hat_0 = 0U;
    vlSelfRef.tb_interface__DOT__core_x_hat_1 = 0U;
    vlSelfRef.tb_interface__DOT__core_x_hat_2 = 0U;
    vlSelfRef.tb_interface__DOT__all_pass = 1U;
    vlSelfRef.tb_interface__DOT__rst_n = 0U;
    tb_interface__DOT__unnamedblk1_1__DOT____Vrepeat0 = 4U;
    while (VL_LTS_III(32, 0U, tb_interface__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                         "@(posedge tb_interface.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_interface.clk)", 
                                                             "tb_interface.sv", 
                                                             190);
        tb_interface__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (tb_interface__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         191);
    vlSelfRef.tb_interface__DOT__rst_n = 1U;
    Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                     "@(posedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         193);
    VL_WRITEF_NX("TEST 1: MWr32 to CTRL addr=0x00 data=0xdeadbeef\n",0);
    __Vfunc_tb_interface__DOT__mwr32__1__wdata = 0xdeadbeefU;
    __Vfunc_tb_interface__DOT__mwr32__1__tag = 1U;
    __Vfunc_tb_interface__DOT__mwr32__1__req_id = 0xabcdU;
    __Vfunc_tb_interface__DOT__mwr32__1__addr = 0U;
    VL_ZERO_W(128, __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout);
    __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout[0U] 
        = (IData)((((QData)((IData)((0xfffffffcU & __Vfunc_tb_interface__DOT__mwr32__1__addr))) 
                    << 0x00000020U) | (QData)((IData)(__Vfunc_tb_interface__DOT__mwr32__1__wdata))));
    __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout[1U] 
        = (IData)(((((QData)((IData)((0xfffffffcU & __Vfunc_tb_interface__DOT__mwr32__1__addr))) 
                     << 0x00000020U) | (QData)((IData)(__Vfunc_tb_interface__DOT__mwr32__1__wdata))) 
                   >> 0x00000020U));
    __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout[2U] 
        = (IData)((0x4000000100000000ULL | (QData)((IData)(
                                                           (0xffU 
                                                            | (((IData)(__Vfunc_tb_interface__DOT__mwr32__1__req_id) 
                                                                << 0x00000010U) 
                                                               | ((IData)(__Vfunc_tb_interface__DOT__mwr32__1__tag) 
                                                                  << 8U)))))));
    __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout[3U] 
        = (IData)(((0x4000000100000000ULL | (QData)((IData)(
                                                            (0xffU 
                                                             | (((IData)(__Vfunc_tb_interface__DOT__mwr32__1__req_id) 
                                                                 << 0x00000010U) 
                                                                | ((IData)(__Vfunc_tb_interface__DOT__mwr32__1__tag) 
                                                                   << 8U)))))) 
                   >> 0x00000020U));
    __Vtask_tb_interface__DOT__send_tlp__0__tlp[0U] 
        = __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout[0U];
    __Vtask_tb_interface__DOT__send_tlp__0__tlp[1U] 
        = __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout[1U];
    __Vtask_tb_interface__DOT__send_tlp__0__tlp[2U] 
        = __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout[2U];
    __Vtask_tb_interface__DOT__send_tlp__0__tlp[3U] 
        = __Vfunc_tb_interface__DOT__mwr32__1__Vfuncout[3U];
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         147);
    while ((0U != (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__state))) {
        Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                         "@(negedge tb_interface.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(negedge tb_interface.clk)", 
                                                             "tb_interface.sv", 
                                                             148);
    }
    vlSelfRef.tb_interface__DOT__rx_tdata[0U] = __Vtask_tb_interface__DOT__send_tlp__0__tlp[0U];
    vlSelfRef.tb_interface__DOT__rx_tdata[1U] = __Vtask_tb_interface__DOT__send_tlp__0__tlp[1U];
    vlSelfRef.tb_interface__DOT__rx_tdata[2U] = __Vtask_tb_interface__DOT__send_tlp__0__tlp[2U];
    vlSelfRef.tb_interface__DOT__rx_tdata[3U] = __Vtask_tb_interface__DOT__send_tlp__0__tlp[3U];
    vlSelfRef.tb_interface__DOT__rx_tvalid = 1U;
    vlSelfRef.tb_interface__DOT__rx_tlast = 1U;
    Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                     "@(posedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         152);
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         153);
    vlSelfRef.tb_interface__DOT__rx_tvalid = 0U;
    vlSelfRef.tb_interface__DOT__rx_tlast = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[0U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[1U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[2U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[3U] = 0U;
    tb_interface__DOT__unnamedblk1_2__DOT____Vrepeat1 = 2U;
    while (VL_LTS_III(32, 0U, tb_interface__DOT__unnamedblk1_2__DOT____Vrepeat1)) {
        Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                         "@(posedge tb_interface.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_interface.clk)", 
                                                             "tb_interface.sv", 
                                                             205);
        tb_interface__DOT__unnamedblk1_2__DOT____Vrepeat1 
            = (tb_interface__DOT__unnamedblk1_2__DOT____Vrepeat1 
               - (IData)(1U));
    }
    if ((0xdeadbeefU != vlSelfRef.tb_interface__DOT__dut__DOT__reg_ctrl)) {
        VL_WRITEF_NX("  FAIL: reg_ctrl=0x%08x expected=0xdeadbeef\n",0,
                     32,vlSelfRef.tb_interface__DOT__dut__DOT__reg_ctrl);
        vlSelfRef.tb_interface__DOT__all_pass = 0U;
    } else {
        VL_WRITEF_NX("  reg_ctrl=0x%08x  OK\n",0,32,
                     vlSelfRef.tb_interface__DOT__dut__DOT__reg_ctrl);
    }
    VL_WRITEF_NX("TEST 2: MRd32 from CTRL addr=0x00 expect CplD data=0xdeadbeef\n",0);
    vlSelfRef.tb_interface__DOT__tx_tready = 0U;
    __Vfunc_tb_interface__DOT__mrd32__3__tag = 2U;
    __Vfunc_tb_interface__DOT__mrd32__3__req_id = 0xabcdU;
    __Vfunc_tb_interface__DOT__mrd32__3__addr = 0U;
    VL_ZERO_W(128, __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout);
    __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout[0U] 
        = (IData)(((QData)((IData)((0xfffffffcU & __Vfunc_tb_interface__DOT__mrd32__3__addr))) 
                   << 0x00000020U));
    __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout[1U] 
        = (IData)((((QData)((IData)((0xfffffffcU & __Vfunc_tb_interface__DOT__mrd32__3__addr))) 
                    << 0x00000020U) >> 0x00000020U));
    __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout[2U] 
        = (IData)((0x0000000100000000ULL | (QData)((IData)(
                                                           (0xffU 
                                                            | (((IData)(__Vfunc_tb_interface__DOT__mrd32__3__req_id) 
                                                                << 0x00000010U) 
                                                               | ((IData)(__Vfunc_tb_interface__DOT__mrd32__3__tag) 
                                                                  << 8U)))))));
    __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout[3U] 
        = (IData)(((0x0000000100000000ULL | (QData)((IData)(
                                                            (0xffU 
                                                             | (((IData)(__Vfunc_tb_interface__DOT__mrd32__3__req_id) 
                                                                 << 0x00000010U) 
                                                                | ((IData)(__Vfunc_tb_interface__DOT__mrd32__3__tag) 
                                                                   << 8U)))))) 
                   >> 0x00000020U));
    __Vtask_tb_interface__DOT__send_tlp__2__tlp[0U] 
        = __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout[0U];
    __Vtask_tb_interface__DOT__send_tlp__2__tlp[1U] 
        = __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout[1U];
    __Vtask_tb_interface__DOT__send_tlp__2__tlp[2U] 
        = __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout[2U];
    __Vtask_tb_interface__DOT__send_tlp__2__tlp[3U] 
        = __Vfunc_tb_interface__DOT__mrd32__3__Vfuncout[3U];
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         147);
    while ((0U != (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__state))) {
        Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                         "@(negedge tb_interface.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(negedge tb_interface.clk)", 
                                                             "tb_interface.sv", 
                                                             148);
    }
    vlSelfRef.tb_interface__DOT__rx_tdata[0U] = __Vtask_tb_interface__DOT__send_tlp__2__tlp[0U];
    vlSelfRef.tb_interface__DOT__rx_tdata[1U] = __Vtask_tb_interface__DOT__send_tlp__2__tlp[1U];
    vlSelfRef.tb_interface__DOT__rx_tdata[2U] = __Vtask_tb_interface__DOT__send_tlp__2__tlp[2U];
    vlSelfRef.tb_interface__DOT__rx_tdata[3U] = __Vtask_tb_interface__DOT__send_tlp__2__tlp[3U];
    vlSelfRef.tb_interface__DOT__rx_tvalid = 1U;
    vlSelfRef.tb_interface__DOT__rx_tlast = 1U;
    Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                     "@(posedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         152);
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         153);
    vlSelfRef.tb_interface__DOT__rx_tvalid = 0U;
    vlSelfRef.tb_interface__DOT__rx_tlast = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[0U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[1U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[2U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[3U] = 0U;
    Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                     "@(posedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         230);
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         231);
    vlSelfRef.tb_interface__DOT__got_cpld[0U] = vlSelfRef.tb_interface__DOT__tx_tdata[0U];
    vlSelfRef.tb_interface__DOT__got_cpld[1U] = vlSelfRef.tb_interface__DOT__tx_tdata[1U];
    vlSelfRef.tb_interface__DOT__got_cpld[2U] = vlSelfRef.tb_interface__DOT__tx_tdata[2U];
    vlSelfRef.tb_interface__DOT__got_cpld[3U] = vlSelfRef.tb_interface__DOT__tx_tdata[3U];
    __Vfunc_tb_interface__DOT__make_cpld__4__rd_data = 0xdeadbeefU;
    __Vfunc_tb_interface__DOT__make_cpld__4__addr = 0U;
    __Vfunc_tb_interface__DOT__make_cpld__4__tag = 2U;
    __Vfunc_tb_interface__DOT__make_cpld__4__req_id = 0xabcdU;
    VL_ZERO_W(128, __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout);
    __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout[0U] 
        = __Vfunc_tb_interface__DOT__make_cpld__4__rd_data;
    __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout[1U] 
        = (((IData)(__Vfunc_tb_interface__DOT__make_cpld__4__req_id) 
            << 0x00000010U) | (((IData)(__Vfunc_tb_interface__DOT__make_cpld__4__tag) 
                                << 8U) | (0x0000007fU 
                                          & __Vfunc_tb_interface__DOT__make_cpld__4__addr)));
    __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout[2U] = 0x00080004U;
    __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout[3U] = 0x4a000001U;
    vlSelfRef.tb_interface__DOT__exp_cpld[0U] = __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout[0U];
    vlSelfRef.tb_interface__DOT__exp_cpld[1U] = __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout[1U];
    vlSelfRef.tb_interface__DOT__exp_cpld[2U] = __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout[2U];
    vlSelfRef.tb_interface__DOT__exp_cpld[3U] = __Vfunc_tb_interface__DOT__make_cpld__4__Vfuncout[3U];
    if (VL_LIKELY((vlSelfRef.tb_interface__DOT__tx_tvalid))) {
        if (VL_LIKELY((vlSelfRef.tb_interface__DOT__tx_tlast))) {
            if ((0U != ((((vlSelfRef.tb_interface__DOT__got_cpld[0U] 
                           ^ vlSelfRef.tb_interface__DOT__exp_cpld[0U]) 
                          | (vlSelfRef.tb_interface__DOT__got_cpld[1U] 
                             ^ vlSelfRef.tb_interface__DOT__exp_cpld[1U])) 
                         | (vlSelfRef.tb_interface__DOT__got_cpld[2U] 
                            ^ vlSelfRef.tb_interface__DOT__exp_cpld[2U])) 
                        | (vlSelfRef.tb_interface__DOT__got_cpld[3U] 
                           ^ vlSelfRef.tb_interface__DOT__exp_cpld[3U])))) {
                VL_WRITEF_NX("  FAIL: CplD mismatch\n    got=0x%032x\n    exp=0x%032x\n",0,
                             128,vlSelfRef.tb_interface__DOT__got_cpld.data(),
                             128,vlSelfRef.tb_interface__DOT__exp_cpld.data());
                vlSelfRef.tb_interface__DOT__all_pass = 0U;
            } else {
                VL_WRITEF_NX("  CplD=0x%032x  OK\n",0,
                             128,vlSelfRef.tb_interface__DOT__got_cpld.data());
            }
        } else {
            VL_WRITEF_NX("  FAIL: tx_tlast not asserted during TX_CPL\n",0);
            vlSelfRef.tb_interface__DOT__all_pass = 0U;
        }
    } else {
        VL_WRITEF_NX("  FAIL: tx_tvalid not asserted during TX_CPL\n",0);
        vlSelfRef.tb_interface__DOT__all_pass = 0U;
    }
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         252);
    vlSelfRef.tb_interface__DOT__tx_tready = 1U;
    tb_interface__DOT__unnamedblk1_3__DOT____Vrepeat2 = 2U;
    while (VL_LTS_III(32, 0U, tb_interface__DOT__unnamedblk1_3__DOT____Vrepeat2)) {
        Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                         "@(posedge tb_interface.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_interface.clk)", 
                                                             "tb_interface.sv", 
                                                             254);
        tb_interface__DOT__unnamedblk1_3__DOT____Vrepeat2 
            = (tb_interface__DOT__unnamedblk1_3__DOT____Vrepeat2 
               - (IData)(1U));
    }
    VL_WRITEF_NX("TEST 3: MWr32 to MEAS addr=0x08 data=0xcafebabe\n",0);
    __Vfunc_tb_interface__DOT__mwr32__6__wdata = 0xcafebabeU;
    __Vfunc_tb_interface__DOT__mwr32__6__tag = 3U;
    __Vfunc_tb_interface__DOT__mwr32__6__req_id = 0xabcdU;
    __Vfunc_tb_interface__DOT__mwr32__6__addr = 8U;
    VL_ZERO_W(128, __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout);
    __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout[0U] 
        = (IData)((((QData)((IData)((0xfffffffcU & __Vfunc_tb_interface__DOT__mwr32__6__addr))) 
                    << 0x00000020U) | (QData)((IData)(__Vfunc_tb_interface__DOT__mwr32__6__wdata))));
    __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout[1U] 
        = (IData)(((((QData)((IData)((0xfffffffcU & __Vfunc_tb_interface__DOT__mwr32__6__addr))) 
                     << 0x00000020U) | (QData)((IData)(__Vfunc_tb_interface__DOT__mwr32__6__wdata))) 
                   >> 0x00000020U));
    __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout[2U] 
        = (IData)((0x4000000100000000ULL | (QData)((IData)(
                                                           (0xffU 
                                                            | (((IData)(__Vfunc_tb_interface__DOT__mwr32__6__req_id) 
                                                                << 0x00000010U) 
                                                               | ((IData)(__Vfunc_tb_interface__DOT__mwr32__6__tag) 
                                                                  << 8U)))))));
    __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout[3U] 
        = (IData)(((0x4000000100000000ULL | (QData)((IData)(
                                                            (0xffU 
                                                             | (((IData)(__Vfunc_tb_interface__DOT__mwr32__6__req_id) 
                                                                 << 0x00000010U) 
                                                                | ((IData)(__Vfunc_tb_interface__DOT__mwr32__6__tag) 
                                                                   << 8U)))))) 
                   >> 0x00000020U));
    __Vtask_tb_interface__DOT__send_tlp__5__tlp[0U] 
        = __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout[0U];
    __Vtask_tb_interface__DOT__send_tlp__5__tlp[1U] 
        = __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout[1U];
    __Vtask_tb_interface__DOT__send_tlp__5__tlp[2U] 
        = __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout[2U];
    __Vtask_tb_interface__DOT__send_tlp__5__tlp[3U] 
        = __Vfunc_tb_interface__DOT__mwr32__6__Vfuncout[3U];
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         147);
    while ((0U != (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__state))) {
        Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                         "@(negedge tb_interface.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(negedge tb_interface.clk)", 
                                                             "tb_interface.sv", 
                                                             148);
    }
    vlSelfRef.tb_interface__DOT__rx_tdata[0U] = __Vtask_tb_interface__DOT__send_tlp__5__tlp[0U];
    vlSelfRef.tb_interface__DOT__rx_tdata[1U] = __Vtask_tb_interface__DOT__send_tlp__5__tlp[1U];
    vlSelfRef.tb_interface__DOT__rx_tdata[2U] = __Vtask_tb_interface__DOT__send_tlp__5__tlp[2U];
    vlSelfRef.tb_interface__DOT__rx_tdata[3U] = __Vtask_tb_interface__DOT__send_tlp__5__tlp[3U];
    vlSelfRef.tb_interface__DOT__rx_tvalid = 1U;
    vlSelfRef.tb_interface__DOT__rx_tlast = 1U;
    Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                     "@(posedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         152);
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         153);
    vlSelfRef.tb_interface__DOT__rx_tvalid = 0U;
    vlSelfRef.tb_interface__DOT__rx_tlast = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[0U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[1U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[2U] = 0U;
    vlSelfRef.tb_interface__DOT__rx_tdata[3U] = 0U;
    Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                     "@(posedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         267);
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         268);
    if (vlSelfRef.tb_interface__DOT__dut__DOT__meas_pulse) {
        VL_WRITEF_NX("  core_valid_in=1  OK (WR_EXEC cycle)\n",0);
    } else {
        VL_WRITEF_NX("  FAIL: core_valid_in not pulsed after MEAS write\n",0);
        vlSelfRef.tb_interface__DOT__all_pass = 0U;
    }
    if ((0xcafebabeU != vlSelfRef.tb_interface__DOT__dut__DOT__c_wdata)) {
        VL_WRITEF_NX("  FAIL: core_y=0x%08x expected=0xcafebabe\n",0,
                     32,vlSelfRef.tb_interface__DOT__dut__DOT__c_wdata);
        vlSelfRef.tb_interface__DOT__all_pass = 0U;
    } else {
        VL_WRITEF_NX("  core_y=0x%08x  OK\n",0,32,vlSelfRef.tb_interface__DOT__dut__DOT__c_wdata);
    }
    Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                     "@(posedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         284);
    Vinterface___024root____VbeforeTrig_h56473077__0(vlSelf, 
                                                     "@(negedge tb_interface.clk)");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_await vlSelfRef.__VtrigSched_h56473077__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge tb_interface.clk)", 
                                                         "tb_interface.sv", 
                                                         285);
    if (vlSelfRef.tb_interface__DOT__dut__DOT__meas_pulse) {
        VL_WRITEF_NX("  FAIL: core_valid_in still high in IDLE (not a 1-cycle pulse)\n",0);
        vlSelfRef.tb_interface__DOT__all_pass = 0U;
    } else {
        VL_WRITEF_NX("  core_valid_in=0  OK (IDLE cycle)\n",0);
    }
    tb_interface__DOT__unnamedblk1_4__DOT____Vrepeat3 = 2U;
    while (VL_LTS_III(32, 0U, tb_interface__DOT__unnamedblk1_4__DOT____Vrepeat3)) {
        Vinterface___024root____VbeforeTrig_h5647339b__0(vlSelf, 
                                                         "@(posedge tb_interface.clk)");
        vlSelfRef.__Vm_traceActivity[2U] = 1U;
        co_await vlSelfRef.__VtrigSched_h5647339b__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge tb_interface.clk)", 
                                                             "tb_interface.sv", 
                                                             295);
        tb_interface__DOT__unnamedblk1_4__DOT____Vrepeat3 
            = (tb_interface__DOT__unnamedblk1_4__DOT____Vrepeat3 
               - (IData)(1U));
    }
    if (vlSelfRef.tb_interface__DOT__all_pass) {
        VL_WRITEF_NX("PASS\n",0);
    } else {
        VL_WRITEF_NX("FAIL\n",0);
    }
    VL_FINISH_MT("tb_interface.sv", 300, "");
    vlSelfRef.__Vm_traceActivity[2U] = 1U;
    co_return;
}

VlCoroutine Vinterface___024root___eval_initial__TOP__Vtiming__1(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    co_await vlSelfRef.__VdlySched.delay(0x0000000002faf080ULL, 
                                         nullptr, "tb_interface.sv", 
                                         305);
    VL_WRITEF_NX("FAIL: simulation timeout\n",0);
    VL_FINISH_MT("tb_interface.sv", 307, "");
    co_return;
}

VlCoroutine Vinterface___024root___eval_initial__TOP__Vtiming__2(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_initial__TOP__Vtiming__2\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "tb_interface.sv", 
                                             28);
        vlSelfRef.tb_interface__DOT__clk = (1U & (~ (IData)(vlSelfRef.tb_interface__DOT__clk)));
    }
    co_return;
}

void Vinterface___024root___eval_triggers_vec__act(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_triggers_vec__act\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    (((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                       << 3U) 
                                                      | (((~ (IData)(vlSelfRef.tb_interface__DOT__clk)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0)) 
                                                         << 2U)) 
                                                     | ((((~ (IData)(vlSelfRef.tb_interface__DOT__rst_n)) 
                                                          & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__rst_n__0)) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.tb_interface__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0 
        = vlSelfRef.tb_interface__DOT__clk;
    vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__rst_n__0 
        = vlSelfRef.tb_interface__DOT__rst_n;
}

bool Vinterface___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___trigger_anySet__act\n"); );
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

void Vinterface___024root___act_comb__TOP__0(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___act_comb__TOP__0\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.tb_interface__DOT__dut__DOT__rd_data 
        = ((4U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
            ? ((2U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                ? 0U : ((1U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                         ? vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat2
                         : vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat1))
            : ((2U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                ? ((1U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                    ? vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat0
                    : 0U) : ((1U & (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))
                              ? (((IData)(vlSelfRef.tb_interface__DOT__dut__DOT__busy_r) 
                                  << 1U) | (IData)(vlSelfRef.tb_interface__DOT__core_valid_out))
                              : vlSelfRef.tb_interface__DOT__dut__DOT__reg_ctrl)));
}

void Vinterface___024root___eval_act(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_act\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((5ULL & vlSelfRef.__VactTriggered[0U])) {
        Vinterface___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vinterface___024root___nba_sequent__TOP__0(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___nba_sequent__TOP__0\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    SData/*15:0*/ __Vdly__tb_interface__DOT__dut__DOT__c_req_id;
    __Vdly__tb_interface__DOT__dut__DOT__c_req_id = 0;
    CData/*7:0*/ __Vdly__tb_interface__DOT__dut__DOT__c_tag;
    __Vdly__tb_interface__DOT__dut__DOT__c_tag = 0;
    IData/*31:0*/ __Vdly__tb_interface__DOT__dut__DOT__c_addr;
    __Vdly__tb_interface__DOT__dut__DOT__c_addr = 0;
    CData/*2:0*/ __Vdly__tb_interface__DOT__dut__DOT__c_dw_off;
    __Vdly__tb_interface__DOT__dut__DOT__c_dw_off = 0;
    IData/*31:0*/ __Vdly__tb_interface__DOT__dut__DOT__c_wdata;
    __Vdly__tb_interface__DOT__dut__DOT__c_wdata = 0;
    CData/*1:0*/ __Vdly__tb_interface__DOT__dut__DOT__state;
    __Vdly__tb_interface__DOT__dut__DOT__state = 0;
    // Body
    __Vdly__tb_interface__DOT__dut__DOT__c_req_id = vlSelfRef.tb_interface__DOT__dut__DOT__c_req_id;
    __Vdly__tb_interface__DOT__dut__DOT__c_tag = vlSelfRef.tb_interface__DOT__dut__DOT__c_tag;
    __Vdly__tb_interface__DOT__dut__DOT__c_addr = vlSelfRef.tb_interface__DOT__dut__DOT__c_addr;
    __Vdly__tb_interface__DOT__dut__DOT__c_wdata = vlSelfRef.tb_interface__DOT__dut__DOT__c_wdata;
    __Vdly__tb_interface__DOT__dut__DOT__state = vlSelfRef.tb_interface__DOT__dut__DOT__state;
    __Vdly__tb_interface__DOT__dut__DOT__c_dw_off = vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off;
    if (vlSelfRef.tb_interface__DOT__rst_n) {
        vlSelfRef.tb_interface__DOT__dut__DOT__meas_pulse = 0U;
        if (vlSelfRef.tb_interface__DOT__core_valid_out) {
            vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat0 
                = vlSelfRef.tb_interface__DOT__core_x_hat_0;
            vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat1 
                = vlSelfRef.tb_interface__DOT__core_x_hat_1;
            vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat2 
                = vlSelfRef.tb_interface__DOT__core_x_hat_2;
            vlSelfRef.tb_interface__DOT__dut__DOT__busy_r = 0U;
        }
        if ((0U == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__state))) {
            vlSelfRef.tb_interface__DOT__tx_tvalid = 0U;
            if (vlSelfRef.tb_interface__DOT__rx_tvalid) {
                vlSelfRef.tb_interface__DOT__dut__DOT__c_fmt 
                    = (vlSelfRef.tb_interface__DOT__rx_tdata[3U] 
                       >> 0x0000001dU);
                vlSelfRef.tb_interface__DOT__dut__DOT__c_type 
                    = (0x0000001fU & (vlSelfRef.tb_interface__DOT__rx_tdata[3U] 
                                      >> 0x00000018U));
                __Vdly__tb_interface__DOT__dut__DOT__c_req_id 
                    = (vlSelfRef.tb_interface__DOT__rx_tdata[2U] 
                       >> 0x00000010U);
                __Vdly__tb_interface__DOT__dut__DOT__c_tag 
                    = (0x000000ffU & (vlSelfRef.tb_interface__DOT__rx_tdata[2U] 
                                      >> 8U));
                __Vdly__tb_interface__DOT__dut__DOT__c_addr 
                    = (0xfffffffcU & vlSelfRef.tb_interface__DOT__rx_tdata[1U]);
                __Vdly__tb_interface__DOT__dut__DOT__c_dw_off 
                    = (7U & (vlSelfRef.tb_interface__DOT__rx_tdata[1U] 
                             >> 2U));
                __Vdly__tb_interface__DOT__dut__DOT__c_wdata 
                    = vlSelfRef.tb_interface__DOT__rx_tdata[0U];
                if ((IData)((0x40000000U == (0xff000000U 
                                             & vlSelfRef.tb_interface__DOT__rx_tdata[3U])))) {
                    __Vdly__tb_interface__DOT__dut__DOT__state = 1U;
                } else if ((IData)((0U == (0xff000000U 
                                           & vlSelfRef.tb_interface__DOT__rx_tdata[3U])))) {
                    __Vdly__tb_interface__DOT__dut__DOT__state = 2U;
                }
            }
        } else if ((1U == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__state))) {
            if ((0U == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))) {
                vlSelfRef.tb_interface__DOT__dut__DOT__reg_ctrl 
                    = vlSelfRef.tb_interface__DOT__dut__DOT__c_wdata;
            } else if ((2U == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))) {
                vlSelfRef.tb_interface__DOT__dut__DOT__meas_pulse = 1U;
                vlSelfRef.tb_interface__DOT__dut__DOT__busy_r = 1U;
            }
            __Vdly__tb_interface__DOT__dut__DOT__state = 0U;
            if ((1U & (~ VL_ONEHOT_I((((2U == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off)) 
                                       << 1U) | (0U 
                                                 == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))))))) {
                if ((0U != (((2U == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off)) 
                             << 1U) | (0U == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off))))) {
                    if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                        VL_WRITEF_NX("[%0t] %%Error: interface.sv:237: Assertion failed in %Ntb_interface.dut: unique case, but multiple matches found for '3'h%x'\n",0,
                                     64,VL_TIME_UNITED_Q(1000),
                                     -9,vlSymsp->name(),
                                     3,(IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off));
                        VL_STOP_MT("../rtl/interface.sv", 237, "");
                    }
                }
            }
        } else if ((2U == (IData)(vlSelfRef.tb_interface__DOT__dut__DOT__state))) {
            vlSelfRef.tb_interface__DOT__tx_tdata[0U] 
                = vlSelfRef.tb_interface__DOT__dut__DOT__rd_data;
            vlSelfRef.tb_interface__DOT__tx_tdata[1U] 
                = (((IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_req_id) 
                    << 0x00000010U) | (((IData)(vlSelfRef.tb_interface__DOT__dut__DOT__c_tag) 
                                        << 8U) | (0x0000007fU 
                                                  & vlSelfRef.tb_interface__DOT__dut__DOT__c_addr)));
            vlSelfRef.tb_interface__DOT__tx_tdata[2U] = 0x00080004U;
            vlSelfRef.tb_interface__DOT__tx_tdata[3U] = 0x4a000001U;
            vlSelfRef.tb_interface__DOT__tx_tvalid = 1U;
            vlSelfRef.tb_interface__DOT__tx_tlast = 1U;
            if (vlSelfRef.tb_interface__DOT__tx_tready) {
                vlSelfRef.tb_interface__DOT__tx_tvalid = 0U;
                __Vdly__tb_interface__DOT__dut__DOT__state = 0U;
            }
        } else {
            __Vdly__tb_interface__DOT__dut__DOT__state = 0U;
        }
    } else {
        __Vdly__tb_interface__DOT__dut__DOT__state = 0U;
        vlSelfRef.tb_interface__DOT__dut__DOT__reg_ctrl = 0U;
        vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat0 = 0U;
        vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat1 = 0U;
        vlSelfRef.tb_interface__DOT__dut__DOT__reg_xhat2 = 0U;
        vlSelfRef.tb_interface__DOT__dut__DOT__busy_r = 0U;
        vlSelfRef.tb_interface__DOT__dut__DOT__c_fmt = 0U;
        vlSelfRef.tb_interface__DOT__dut__DOT__c_type = 0U;
        __Vdly__tb_interface__DOT__dut__DOT__c_req_id = 0U;
        __Vdly__tb_interface__DOT__dut__DOT__c_tag = 0U;
        __Vdly__tb_interface__DOT__dut__DOT__c_addr = 0U;
        __Vdly__tb_interface__DOT__dut__DOT__c_dw_off = 0U;
        __Vdly__tb_interface__DOT__dut__DOT__c_wdata = 0U;
        vlSelfRef.tb_interface__DOT__dut__DOT__meas_pulse = 0U;
        vlSelfRef.tb_interface__DOT__tx_tdata[0U] = 0U;
        vlSelfRef.tb_interface__DOT__tx_tdata[1U] = 0U;
        vlSelfRef.tb_interface__DOT__tx_tdata[2U] = 0U;
        vlSelfRef.tb_interface__DOT__tx_tdata[3U] = 0U;
        vlSelfRef.tb_interface__DOT__tx_tvalid = 0U;
        vlSelfRef.tb_interface__DOT__tx_tlast = 0U;
    }
    vlSelfRef.tb_interface__DOT__dut__DOT__c_req_id 
        = __Vdly__tb_interface__DOT__dut__DOT__c_req_id;
    vlSelfRef.tb_interface__DOT__dut__DOT__c_tag = __Vdly__tb_interface__DOT__dut__DOT__c_tag;
    vlSelfRef.tb_interface__DOT__dut__DOT__c_addr = __Vdly__tb_interface__DOT__dut__DOT__c_addr;
    vlSelfRef.tb_interface__DOT__dut__DOT__c_wdata 
        = __Vdly__tb_interface__DOT__dut__DOT__c_wdata;
    vlSelfRef.tb_interface__DOT__dut__DOT__state = __Vdly__tb_interface__DOT__dut__DOT__state;
    vlSelfRef.tb_interface__DOT__dut__DOT__c_dw_off 
        = __Vdly__tb_interface__DOT__dut__DOT__c_dw_off;
}

void Vinterface___024root___eval_nba(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_nba\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vinterface___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[3U] = 1U;
    }
    if ((7ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vinterface___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vinterface___024root___timing_ready(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___timing_ready\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h5647339b__0.ready("@(posedge tb_interface.clk)");
    }
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_h56473077__0.ready("@(negedge tb_interface.clk)");
    }
}

void Vinterface___024root___timing_resume(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___timing_resume\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_h5647339b__0.moveToResumeQueue(
                                                          "@(posedge tb_interface.clk)");
    vlSelfRef.__VtrigSched_h56473077__0.moveToResumeQueue(
                                                          "@(negedge tb_interface.clk)");
    vlSelfRef.__VtrigSched_h5647339b__0.resume("@(posedge tb_interface.clk)");
    vlSelfRef.__VtrigSched_h56473077__0.resume("@(negedge tb_interface.clk)");
    if ((8ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vinterface___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vinterface___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vinterface___024root___eval_phase__act(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_phase__act\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vinterface___024root___eval_triggers_vec__act(vlSelf);
    Vinterface___024root___timing_ready(vlSelf);
    Vinterface___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vinterface___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vinterface___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vinterface___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vinterface___024root___timing_resume(vlSelf);
        Vinterface___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vinterface___024root___eval_phase__inact(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_phase__inact\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("tb_interface.sv", 24, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vinterface___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vinterface___024root___eval_phase__nba(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_phase__nba\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vinterface___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vinterface___024root___eval_nba(vlSelf);
        Vinterface___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vinterface___024root___eval(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vinterface___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("tb_interface.sv", 24, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("tb_interface.sv", 24, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vinterface___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("tb_interface.sv", 24, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vinterface___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vinterface___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vinterface___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vinterface___024root____VbeforeTrig_h5647339b__0(Vinterface___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root____VbeforeTrig_h5647339b__0\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((((~ (IData)(vlSelfRef.tb_interface__DOT__clk)) 
                                    & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0)) 
                                   << 2U) | ((IData)(vlSelfRef.tb_interface__DOT__clk) 
                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0 
        = vlSelfRef.tb_interface__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
    }
    if ((4ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vinterface___024root____VbeforeTrig_h56473077__0(Vinterface___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root____VbeforeTrig_h56473077__0\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((((~ (IData)(vlSelfRef.tb_interface__DOT__clk)) 
                                    & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0)) 
                                   << 2U) | ((IData)(vlSelfRef.tb_interface__DOT__clk) 
                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__tb_interface__DOT__clk__0 
        = vlSelfRef.tb_interface__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h5647339b__0.ready(__VeventDescription);
    }
    if ((4ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_h56473077__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vinterface___024root___eval_debug_assertions(Vinterface___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vinterface___024root___eval_debug_assertions\n"); );
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
