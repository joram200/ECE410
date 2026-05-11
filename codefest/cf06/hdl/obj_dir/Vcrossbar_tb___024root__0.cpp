// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcrossbar_tb.h for the primary calling header

#include "Vcrossbar_tb__pch.h"

VlCoroutine Vcrossbar_tb___024root___eval_initial__TOP__Vtiming__0(Vcrossbar_tb___024root* vlSelf);
VlCoroutine Vcrossbar_tb___024root___eval_initial__TOP__Vtiming__1(Vcrossbar_tb___024root* vlSelf);

void Vcrossbar_tb___024root___eval_initial(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_initial\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.crossbar_tb__DOT__clk = 0U;
    Vcrossbar_tb___024root___eval_initial__TOP__Vtiming__0(vlSelf);
    Vcrossbar_tb___024root___eval_initial__TOP__Vtiming__1(vlSelf);
}

void Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(Vcrossbar_tb___024root* vlSelf, const char* __VeventDescription);
void Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(Vcrossbar_tb___024root* vlSelf, const char* __VeventDescription);

VlCoroutine Vcrossbar_tb___024root___eval_initial__TOP__Vtiming__0(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_initial__TOP__Vtiming__0\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ crossbar_tb__DOT__log_fd;
    crossbar_tb__DOT__log_fd = 0;
    IData/*31:0*/ crossbar_tb__DOT__unnamedblk1_1__DOT____Vrepeat0;
    crossbar_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__1__row;
    __Vtask_crossbar_tb__DOT__write_weight__1__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__1__col;
    __Vtask_crossbar_tb__DOT__write_weight__1__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__1__val;
    __Vtask_crossbar_tb__DOT__write_weight__1__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__2__row;
    __Vtask_crossbar_tb__DOT__write_weight__2__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__2__col;
    __Vtask_crossbar_tb__DOT__write_weight__2__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__2__val;
    __Vtask_crossbar_tb__DOT__write_weight__2__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__3__row;
    __Vtask_crossbar_tb__DOT__write_weight__3__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__3__col;
    __Vtask_crossbar_tb__DOT__write_weight__3__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__3__val;
    __Vtask_crossbar_tb__DOT__write_weight__3__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__4__row;
    __Vtask_crossbar_tb__DOT__write_weight__4__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__4__col;
    __Vtask_crossbar_tb__DOT__write_weight__4__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__4__val;
    __Vtask_crossbar_tb__DOT__write_weight__4__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__5__row;
    __Vtask_crossbar_tb__DOT__write_weight__5__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__5__col;
    __Vtask_crossbar_tb__DOT__write_weight__5__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__5__val;
    __Vtask_crossbar_tb__DOT__write_weight__5__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__6__row;
    __Vtask_crossbar_tb__DOT__write_weight__6__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__6__col;
    __Vtask_crossbar_tb__DOT__write_weight__6__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__6__val;
    __Vtask_crossbar_tb__DOT__write_weight__6__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__7__row;
    __Vtask_crossbar_tb__DOT__write_weight__7__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__7__col;
    __Vtask_crossbar_tb__DOT__write_weight__7__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__7__val;
    __Vtask_crossbar_tb__DOT__write_weight__7__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__8__row;
    __Vtask_crossbar_tb__DOT__write_weight__8__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__8__col;
    __Vtask_crossbar_tb__DOT__write_weight__8__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__8__val;
    __Vtask_crossbar_tb__DOT__write_weight__8__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__9__row;
    __Vtask_crossbar_tb__DOT__write_weight__9__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__9__col;
    __Vtask_crossbar_tb__DOT__write_weight__9__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__9__val;
    __Vtask_crossbar_tb__DOT__write_weight__9__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__10__row;
    __Vtask_crossbar_tb__DOT__write_weight__10__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__10__col;
    __Vtask_crossbar_tb__DOT__write_weight__10__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__10__val;
    __Vtask_crossbar_tb__DOT__write_weight__10__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__11__row;
    __Vtask_crossbar_tb__DOT__write_weight__11__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__11__col;
    __Vtask_crossbar_tb__DOT__write_weight__11__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__11__val;
    __Vtask_crossbar_tb__DOT__write_weight__11__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__12__row;
    __Vtask_crossbar_tb__DOT__write_weight__12__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__12__col;
    __Vtask_crossbar_tb__DOT__write_weight__12__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__12__val;
    __Vtask_crossbar_tb__DOT__write_weight__12__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__13__row;
    __Vtask_crossbar_tb__DOT__write_weight__13__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__13__col;
    __Vtask_crossbar_tb__DOT__write_weight__13__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__13__val;
    __Vtask_crossbar_tb__DOT__write_weight__13__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__14__row;
    __Vtask_crossbar_tb__DOT__write_weight__14__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__14__col;
    __Vtask_crossbar_tb__DOT__write_weight__14__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__14__val;
    __Vtask_crossbar_tb__DOT__write_weight__14__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__15__row;
    __Vtask_crossbar_tb__DOT__write_weight__15__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__15__col;
    __Vtask_crossbar_tb__DOT__write_weight__15__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__15__val;
    __Vtask_crossbar_tb__DOT__write_weight__15__val = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__16__row;
    __Vtask_crossbar_tb__DOT__write_weight__16__row = 0;
    CData/*1:0*/ __Vtask_crossbar_tb__DOT__write_weight__16__col;
    __Vtask_crossbar_tb__DOT__write_weight__16__col = 0;
    CData/*0:0*/ __Vtask_crossbar_tb__DOT__write_weight__16__val;
    __Vtask_crossbar_tb__DOT__write_weight__16__val = 0;
    // Body
    crossbar_tb__DOT__log_fd = VL_FOPEN_NN("sim.log"s
                                           , "w"s);
    ;
    if (VL_UNLIKELY(((0U == crossbar_tb__DOT__log_fd)))) {
        VL_WRITEF_NX("[%0t] %%Fatal: crossbar_tb.sv:101: Assertion failed in %Ncrossbar_tb: ERROR: could not open sim.log\n",0,
                     64,VL_TIME_UNITED_Q(1000),-9,vlSymsp->name());
        VL_STOP_MT("crossbar_tb.sv", 101, "", false);
    }
    vlSelfRef.crossbar_tb__DOT__rst = 1U;
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    vlSelfRef.crossbar_tb__DOT__w_row = 0U;
    vlSelfRef.crossbar_tb__DOT__w_col = 0U;
    vlSelfRef.crossbar_tb__DOT__w_val = 0U;
    vlSelfRef.crossbar_tb__DOT__in[0U] = 0U;
    vlSelfRef.crossbar_tb__DOT__in[1U] = 0U;
    vlSelfRef.crossbar_tb__DOT__in[2U] = 0U;
    vlSelfRef.crossbar_tb__DOT__in[3U] = 0U;
    crossbar_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 = 2U;
    while (VL_LTS_III(32, 0U, crossbar_tb__DOT__unnamedblk1_1__DOT____Vrepeat0)) {
        Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                           "@(posedge crossbar_tb.clk)");
        co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                             nullptr, 
                                                             "@(posedge crossbar_tb.clk)", 
                                                             "crossbar_tb.sv", 
                                                             115);
        crossbar_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
            = (crossbar_tb__DOT__unnamedblk1_1__DOT____Vrepeat0 
               - (IData)(1U));
    }
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         116);
    vlSelfRef.crossbar_tb__DOT__rst = 0U;
    vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__0__msg 
        = VL_SFORMATF_N_NX("[%0t ns] Reset released.",0,
                           64,VL_TIME_UNITED_Q(1000),
                           -9) ;
    VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__0__msg));
    VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                  -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__0__msg));
    __Vtask_crossbar_tb__DOT__write_weight__1__val = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__1__col = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__1__row = 0U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__1__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__1__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__1__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__2__val = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__2__col = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__2__row = 0U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__2__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__2__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__2__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__3__val = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__3__col = 2U;
    __Vtask_crossbar_tb__DOT__write_weight__3__row = 0U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__3__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__3__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__3__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__4__val = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__4__col = 3U;
    __Vtask_crossbar_tb__DOT__write_weight__4__row = 0U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__4__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__4__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__4__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__5__val = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__5__col = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__5__row = 1U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__5__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__5__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__5__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__6__val = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__6__col = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__6__row = 1U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__6__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__6__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__6__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__7__val = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__7__col = 2U;
    __Vtask_crossbar_tb__DOT__write_weight__7__row = 1U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__7__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__7__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__7__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__8__val = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__8__col = 3U;
    __Vtask_crossbar_tb__DOT__write_weight__8__row = 1U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__8__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__8__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__8__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__9__val = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__9__col = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__9__row = 2U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__9__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__9__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__9__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__10__val = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__10__col = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__10__row = 2U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__10__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__10__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__10__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__11__val = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__11__col = 2U;
    __Vtask_crossbar_tb__DOT__write_weight__11__row = 2U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__11__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__11__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__11__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__12__val = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__12__col = 3U;
    __Vtask_crossbar_tb__DOT__write_weight__12__row = 2U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__12__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__12__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__12__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__13__val = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__13__col = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__13__row = 3U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__13__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__13__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__13__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__14__val = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__14__col = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__14__row = 3U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__14__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__14__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__14__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__15__val = 1U;
    __Vtask_crossbar_tb__DOT__write_weight__15__col = 2U;
    __Vtask_crossbar_tb__DOT__write_weight__15__row = 3U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__15__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__15__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__15__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__16__val = 0U;
    __Vtask_crossbar_tb__DOT__write_weight__16__col = 3U;
    __Vtask_crossbar_tb__DOT__write_weight__16__row = 3U;
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         81);
    vlSelfRef.crossbar_tb__DOT__we = 1U;
    vlSelfRef.crossbar_tb__DOT__w_row = __Vtask_crossbar_tb__DOT__write_weight__16__row;
    vlSelfRef.crossbar_tb__DOT__w_col = __Vtask_crossbar_tb__DOT__write_weight__16__col;
    vlSelfRef.crossbar_tb__DOT__w_val = __Vtask_crossbar_tb__DOT__write_weight__16__val;
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         86);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         87);
    vlSelfRef.crossbar_tb__DOT__we = 0U;
    vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__17__msg 
        = VL_SFORMATF_N_NX("[%0t ns] Weights loaded.",0,
                           64,VL_TIME_UNITED_Q(1000),
                           -9) ;
    VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__17__msg));
    VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                  -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__17__msg));
    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(vlSelf, 
                                                       "@(negedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f33e88__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(negedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         146);
    vlSelfRef.crossbar_tb__DOT__in[0U] = 0x0aU;
    vlSelfRef.crossbar_tb__DOT__in[1U] = 0x14U;
    vlSelfRef.crossbar_tb__DOT__in[2U] = 0x1eU;
    vlSelfRef.crossbar_tb__DOT__in[3U] = 0x28U;
    vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__18__msg 
        = VL_SFORMATF_N_NX("[%0t ns] Inputs applied: in = [%0d, %0d, %0d, %0d]",0,
                           64,VL_TIME_UNITED_Q(1000),
                           -9,8,vlSelfRef.crossbar_tb__DOT__in[0U],
                           8,vlSelfRef.crossbar_tb__DOT__in[1U],
                           8,vlSelfRef.crossbar_tb__DOT__in[2U],
                           8,vlSelfRef.crossbar_tb__DOT__in[3U]) ;
    VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__18__msg));
    VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                  -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__18__msg));
    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(vlSelf, 
                                                       "@(posedge crossbar_tb.clk)");
    co_await vlSelfRef.__VtrigSched_he9f331c2__0.trigger(0U, 
                                                         nullptr, 
                                                         "@(posedge crossbar_tb.clk)", 
                                                         "crossbar_tb.sv", 
                                                         155);
    co_await vlSelfRef.__VdlySched.delay(0x00000000000003e8ULL, 
                                         nullptr, "crossbar_tb.sv", 
                                         156);
    vlSelfRef.__Vtask_crossbar_tb__DOT__log_outputs__19__label = "MAC result"s;
    vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__20__msg 
        = VL_SFORMATF_N_NX("[%0t ns] %@: out = [%0d, %0d, %0d, %0d]",0,
                           64,VL_TIME_UNITED_Q(1000),
                           -9,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_outputs__19__label),
                           8,vlSelfRef.crossbar_tb__DOT__out[0U],
                           8,vlSelfRef.crossbar_tb__DOT__out[1U],
                           8,vlSelfRef.crossbar_tb__DOT__out[2U],
                           8,vlSelfRef.crossbar_tb__DOT__out[3U]) ;
    VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__20__msg));
    VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                  -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__20__msg));
    vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__21__msg 
        = VL_SFORMATF_N_NX("[%0t ns] --- Checking outputs ---",0,
                           64,VL_TIME_UNITED_Q(1000),
                           -9) ;
    VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__21__msg));
    VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                  -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__21__msg));
    if ((0xd8U == vlSelfRef.crossbar_tb__DOT__out[0U])) {
        vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__22__msg 
            = VL_SFORMATF_N_NX("  PASS  out[0] = %0d (expected -40)",0,
                               8,vlSelfRef.crossbar_tb__DOT__out[0U]) ;
        VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__22__msg));
        VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                      -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__22__msg));
        vlSelfRef.crossbar_tb__DOT__pass_count = ((IData)(1U) 
                                                  + vlSelfRef.crossbar_tb__DOT__pass_count);
    } else {
        vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__23__msg 
            = VL_SFORMATF_N_NX("  FAIL  out[0] = %0d (expected -40)",0,
                               8,vlSelfRef.crossbar_tb__DOT__out[0U]) ;
        VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__23__msg));
        VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                      -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__23__msg));
        vlSelfRef.crossbar_tb__DOT__fail_count = ((IData)(1U) 
                                                  + vlSelfRef.crossbar_tb__DOT__fail_count);
    }
    if ((0U == vlSelfRef.crossbar_tb__DOT__out[1U])) {
        vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__24__msg 
            = VL_SFORMATF_N_NX("  PASS  out[1] = %0d (expected  0)",0,
                               8,vlSelfRef.crossbar_tb__DOT__out[1U]) ;
        VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__24__msg));
        VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                      -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__24__msg));
        vlSelfRef.crossbar_tb__DOT__pass_count = ((IData)(1U) 
                                                  + vlSelfRef.crossbar_tb__DOT__pass_count);
    } else {
        vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__25__msg 
            = VL_SFORMATF_N_NX("  FAIL  out[1] = %0d (expected  0)",0,
                               8,vlSelfRef.crossbar_tb__DOT__out[1U]) ;
        VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__25__msg));
        VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                      -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__25__msg));
        vlSelfRef.crossbar_tb__DOT__fail_count = ((IData)(1U) 
                                                  + vlSelfRef.crossbar_tb__DOT__fail_count);
    }
    if ((0xecU == vlSelfRef.crossbar_tb__DOT__out[2U])) {
        vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__26__msg 
            = VL_SFORMATF_N_NX("  PASS  out[2] = %0d (expected -20)",0,
                               8,vlSelfRef.crossbar_tb__DOT__out[2U]) ;
        VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__26__msg));
        VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                      -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__26__msg));
        vlSelfRef.crossbar_tb__DOT__pass_count = ((IData)(1U) 
                                                  + vlSelfRef.crossbar_tb__DOT__pass_count);
    } else {
        vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__27__msg 
            = VL_SFORMATF_N_NX("  FAIL  out[2] = %0d (expected -20)",0,
                               8,vlSelfRef.crossbar_tb__DOT__out[2U]) ;
        VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__27__msg));
        VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                      -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__27__msg));
        vlSelfRef.crossbar_tb__DOT__fail_count = ((IData)(1U) 
                                                  + vlSelfRef.crossbar_tb__DOT__fail_count);
    }
    if ((0xecU == vlSelfRef.crossbar_tb__DOT__out[3U])) {
        vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__28__msg 
            = VL_SFORMATF_N_NX("  PASS  out[3] = %0d (expected -20)",0,
                               8,vlSelfRef.crossbar_tb__DOT__out[3U]) ;
        VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__28__msg));
        VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                      -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__28__msg));
        vlSelfRef.crossbar_tb__DOT__pass_count = ((IData)(1U) 
                                                  + vlSelfRef.crossbar_tb__DOT__pass_count);
    } else {
        vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__29__msg 
            = VL_SFORMATF_N_NX("  FAIL  out[3] = %0d (expected -20)",0,
                               8,vlSelfRef.crossbar_tb__DOT__out[3U]) ;
        VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__29__msg));
        VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                      -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__29__msg));
        vlSelfRef.crossbar_tb__DOT__fail_count = ((IData)(1U) 
                                                  + vlSelfRef.crossbar_tb__DOT__fail_count);
    }
    vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__30__msg 
        = VL_SFORMATF_N_NX("[%0t ns] --- Results: %0d passed, %0d failed ---",0,
                           64,VL_TIME_UNITED_Q(1000),
                           -9,32,vlSelfRef.crossbar_tb__DOT__pass_count,
                           32,vlSelfRef.crossbar_tb__DOT__fail_count) ;
    VL_WRITEF_NX("%@\n",0,-1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__30__msg));
    VL_FWRITEF_NX(crossbar_tb__DOT__log_fd,"%@\n",0,
                  -1,&(vlSelfRef.__Vtask_crossbar_tb__DOT__log_msg__30__msg));
    VL_FCLOSE_I(crossbar_tb__DOT__log_fd); VL_FINISH_MT("crossbar_tb.sv", 198, "");
    co_return;
}

VlCoroutine Vcrossbar_tb___024root___eval_initial__TOP__Vtiming__1(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_initial__TOP__Vtiming__1\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    while (VL_LIKELY(!vlSymsp->_vm_contextp__->gotFinish())) {
        co_await vlSelfRef.__VdlySched.delay(0x0000000000001388ULL, 
                                             nullptr, 
                                             "crossbar_tb.sv", 
                                             54);
        vlSelfRef.crossbar_tb__DOT__clk = (1U & (~ (IData)(vlSelfRef.crossbar_tb__DOT__clk)));
    }
    co_return;
}

void Vcrossbar_tb___024root___eval_triggers_vec__act(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_triggers_vec__act\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((~ (IData)(vlSelfRef.crossbar_tb__DOT__clk)) 
                                                       & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0)) 
                                                      << 2U) 
                                                     | ((vlSelfRef.__VdlySched.awaitingCurrentTime() 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.crossbar_tb__DOT__clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0 
        = vlSelfRef.crossbar_tb__DOT__clk;
}

bool Vcrossbar_tb___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___trigger_anySet__act\n"); );
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

void Vcrossbar_tb___024root___act_comb__TOP__0(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___act_comb__TOP__0\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[0U][0U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[0U][0U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[0U])
                           : vlSelfRef.crossbar_tb__DOT__in[0U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[0U][1U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[0U][1U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[0U])
                           : vlSelfRef.crossbar_tb__DOT__in[0U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[0U][2U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[0U][2U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[0U])
                           : vlSelfRef.crossbar_tb__DOT__in[0U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[0U][3U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[0U][3U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[0U])
                           : vlSelfRef.crossbar_tb__DOT__in[0U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[1U][0U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[1U][0U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[1U])
                           : vlSelfRef.crossbar_tb__DOT__in[1U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[1U][1U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[1U][1U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[1U])
                           : vlSelfRef.crossbar_tb__DOT__in[1U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[1U][2U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[1U][2U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[1U])
                           : vlSelfRef.crossbar_tb__DOT__in[1U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[1U][3U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[1U][3U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[1U])
                           : vlSelfRef.crossbar_tb__DOT__in[1U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[2U][0U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[2U][0U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[2U])
                           : vlSelfRef.crossbar_tb__DOT__in[2U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[2U][1U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[2U][1U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[2U])
                           : vlSelfRef.crossbar_tb__DOT__in[2U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[2U][2U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[2U][2U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[2U])
                           : vlSelfRef.crossbar_tb__DOT__in[2U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[2U][3U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[2U][3U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[2U])
                           : vlSelfRef.crossbar_tb__DOT__in[2U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[3U][0U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[3U][0U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[3U])
                           : vlSelfRef.crossbar_tb__DOT__in[3U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[3U][1U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[3U][1U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[3U])
                           : vlSelfRef.crossbar_tb__DOT__in[3U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[3U][2U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[3U][2U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[3U])
                           : vlSelfRef.crossbar_tb__DOT__in[3U]));
    vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[3U][3U] 
        = (0x000000ffU & (vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[3U][3U]
                           ? (- vlSelfRef.crossbar_tb__DOT__in[3U])
                           : vlSelfRef.crossbar_tb__DOT__in[3U]));
}

void Vcrossbar_tb___024root___eval_act(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_act\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((7ULL & vlSelfRef.__VactTriggered[0U])) {
        Vcrossbar_tb___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vcrossbar_tb___024root___nba_sequent__TOP__0(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___nba_sequent__TOP__0\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VdlySet__crossbar_tb__DOT__dut__DOT__weight__v0;
    __VdlySet__crossbar_tb__DOT__dut__DOT__weight__v0 = 0;
    CData/*0:0*/ __VdlyVal__crossbar_tb__DOT__dut__DOT__weight__v16;
    __VdlyVal__crossbar_tb__DOT__dut__DOT__weight__v16 = 0;
    CData/*1:0*/ __VdlyDim0__crossbar_tb__DOT__dut__DOT__weight__v16;
    __VdlyDim0__crossbar_tb__DOT__dut__DOT__weight__v16 = 0;
    CData/*1:0*/ __VdlyDim1__crossbar_tb__DOT__dut__DOT__weight__v16;
    __VdlyDim1__crossbar_tb__DOT__dut__DOT__weight__v16 = 0;
    CData/*0:0*/ __VdlySet__crossbar_tb__DOT__dut__DOT__weight__v16;
    __VdlySet__crossbar_tb__DOT__dut__DOT__weight__v16 = 0;
    CData/*0:0*/ __VdlySet__crossbar_tb__DOT__out__v0;
    __VdlySet__crossbar_tb__DOT__out__v0 = 0;
    CData/*7:0*/ __VdlyVal__crossbar_tb__DOT__out__v4;
    __VdlyVal__crossbar_tb__DOT__out__v4 = 0;
    CData/*0:0*/ __VdlySet__crossbar_tb__DOT__out__v4;
    __VdlySet__crossbar_tb__DOT__out__v4 = 0;
    CData/*7:0*/ __VdlyVal__crossbar_tb__DOT__out__v5;
    __VdlyVal__crossbar_tb__DOT__out__v5 = 0;
    CData/*7:0*/ __VdlyVal__crossbar_tb__DOT__out__v6;
    __VdlyVal__crossbar_tb__DOT__out__v6 = 0;
    CData/*7:0*/ __VdlyVal__crossbar_tb__DOT__out__v7;
    __VdlyVal__crossbar_tb__DOT__out__v7 = 0;
    // Body
    __VdlySet__crossbar_tb__DOT__out__v0 = 0U;
    __VdlySet__crossbar_tb__DOT__out__v4 = 0U;
    __VdlySet__crossbar_tb__DOT__dut__DOT__weight__v0 = 0U;
    __VdlySet__crossbar_tb__DOT__dut__DOT__weight__v16 = 0U;
    if (vlSelfRef.crossbar_tb__DOT__rst) {
        __VdlySet__crossbar_tb__DOT__out__v0 = 1U;
        __VdlySet__crossbar_tb__DOT__dut__DOT__weight__v0 = 1U;
    } else {
        __VdlyVal__crossbar_tb__DOT__out__v4 = (0x000000ffU 
                                                & (((vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[0U][0U] 
                                                     + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[1U][0U]) 
                                                    + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[2U][0U]) 
                                                   + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[3U][0U]));
        __VdlySet__crossbar_tb__DOT__out__v4 = 1U;
        __VdlyVal__crossbar_tb__DOT__out__v5 = (0x000000ffU 
                                                & (((vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[0U][1U] 
                                                     + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[1U][1U]) 
                                                    + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[2U][1U]) 
                                                   + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[3U][1U]));
        __VdlyVal__crossbar_tb__DOT__out__v6 = (0x000000ffU 
                                                & (((vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[0U][2U] 
                                                     + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[1U][2U]) 
                                                    + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[2U][2U]) 
                                                   + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[3U][2U]));
        __VdlyVal__crossbar_tb__DOT__out__v7 = (0x000000ffU 
                                                & (((vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[0U][3U] 
                                                     + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[1U][3U]) 
                                                    + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[2U][3U]) 
                                                   + vlSelfRef.crossbar_tb__DOT__dut__DOT__xp_out[3U][3U]));
        if (vlSelfRef.crossbar_tb__DOT__we) {
            __VdlyVal__crossbar_tb__DOT__dut__DOT__weight__v16 
                = vlSelfRef.crossbar_tb__DOT__w_val;
            __VdlyDim0__crossbar_tb__DOT__dut__DOT__weight__v16 
                = vlSelfRef.crossbar_tb__DOT__w_col;
            __VdlyDim1__crossbar_tb__DOT__dut__DOT__weight__v16 
                = vlSelfRef.crossbar_tb__DOT__w_row;
            __VdlySet__crossbar_tb__DOT__dut__DOT__weight__v16 = 1U;
        }
    }
    if (__VdlySet__crossbar_tb__DOT__out__v0) {
        vlSelfRef.crossbar_tb__DOT__out[0U] = 0U;
        vlSelfRef.crossbar_tb__DOT__out[1U] = 0U;
        vlSelfRef.crossbar_tb__DOT__out[2U] = 0U;
        vlSelfRef.crossbar_tb__DOT__out[3U] = 0U;
    }
    if (__VdlySet__crossbar_tb__DOT__out__v4) {
        vlSelfRef.crossbar_tb__DOT__out[0U] = __VdlyVal__crossbar_tb__DOT__out__v4;
        vlSelfRef.crossbar_tb__DOT__out[1U] = __VdlyVal__crossbar_tb__DOT__out__v5;
        vlSelfRef.crossbar_tb__DOT__out[2U] = __VdlyVal__crossbar_tb__DOT__out__v6;
        vlSelfRef.crossbar_tb__DOT__out[3U] = __VdlyVal__crossbar_tb__DOT__out__v7;
    }
    if (__VdlySet__crossbar_tb__DOT__dut__DOT__weight__v0) {
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[0U][0U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[0U][1U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[0U][2U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[0U][3U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[1U][0U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[1U][1U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[1U][2U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[1U][3U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[2U][0U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[2U][1U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[2U][2U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[2U][3U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[3U][0U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[3U][1U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[3U][2U] = 0U;
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[3U][3U] = 0U;
    }
    if (__VdlySet__crossbar_tb__DOT__dut__DOT__weight__v16) {
        vlSelfRef.crossbar_tb__DOT__dut__DOT__weight[__VdlyDim1__crossbar_tb__DOT__dut__DOT__weight__v16][__VdlyDim0__crossbar_tb__DOT__dut__DOT__weight__v16] 
            = __VdlyVal__crossbar_tb__DOT__dut__DOT__weight__v16;
    }
}

void Vcrossbar_tb___024root___eval_nba(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_nba\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vcrossbar_tb___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((7ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vcrossbar_tb___024root___act_comb__TOP__0(vlSelf);
    }
}

void Vcrossbar_tb___024root___timing_ready(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___timing_ready\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_he9f331c2__0.ready("@(posedge crossbar_tb.clk)");
    }
    if ((4ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VtrigSched_he9f33e88__0.ready("@(negedge crossbar_tb.clk)");
    }
}

void Vcrossbar_tb___024root___timing_resume(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___timing_resume\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VtrigSched_he9f331c2__0.moveToResumeQueue(
                                                          "@(posedge crossbar_tb.clk)");
    vlSelfRef.__VtrigSched_he9f33e88__0.moveToResumeQueue(
                                                          "@(negedge crossbar_tb.clk)");
    vlSelfRef.__VtrigSched_he9f331c2__0.resume("@(posedge crossbar_tb.clk)");
    vlSelfRef.__VtrigSched_he9f33e88__0.resume("@(negedge crossbar_tb.clk)");
    if ((2ULL & vlSelfRef.__VactTriggered[0U])) {
        vlSelfRef.__VdlySched.resume();
    }
}

void Vcrossbar_tb___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___trigger_orInto__act_vec_vec\n"); );
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
VL_ATTR_COLD void Vcrossbar_tb___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vcrossbar_tb___024root___eval_phase__act(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_phase__act\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VactExecute;
    // Body
    Vcrossbar_tb___024root___eval_triggers_vec__act(vlSelf);
    Vcrossbar_tb___024root___timing_ready(vlSelf);
    Vcrossbar_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VactTriggered, vlSelfRef.__VactTriggeredAcc);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vcrossbar_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vcrossbar_tb___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    __VactExecute = Vcrossbar_tb___024root___trigger_anySet__act(vlSelfRef.__VactTriggered);
    if (__VactExecute) {
        vlSelfRef.__VactTriggeredAcc.fill(0ULL);
        Vcrossbar_tb___024root___timing_resume(vlSelf);
        Vcrossbar_tb___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vcrossbar_tb___024root___eval_phase__inact(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_phase__inact\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VinactExecute;
    // Body
    __VinactExecute = vlSelfRef.__VdlySched.awaitingZeroDelay();
    if (__VinactExecute) {
        VL_FATAL_MT("crossbar_tb.sv", 22, "", "ZERODLY: Design Verilated with '--no-sched-zero-delay', but #0 delay executed at runtime");
    }
    return (__VinactExecute);
}

void Vcrossbar_tb___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vcrossbar_tb___024root___eval_phase__nba(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_phase__nba\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vcrossbar_tb___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vcrossbar_tb___024root___eval_nba(vlSelf);
        Vcrossbar_tb___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vcrossbar_tb___024root___eval(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00000064U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vcrossbar_tb___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("crossbar_tb.sv", 22, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 100 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VinactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VinactIterCount)))) {
                VL_FATAL_MT("crossbar_tb.sv", 22, "", "DIDNOTCONVERGE: Inactive region did not converge after '--converge-limit' of 100 tries");
            }
            vlSelfRef.__VinactIterCount = ((IData)(1U) 
                                           + vlSelfRef.__VinactIterCount);
            vlSelfRef.__VactIterCount = 0U;
            do {
                if (VL_UNLIKELY(((0x00000064U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                    Vcrossbar_tb___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                    VL_FATAL_MT("crossbar_tb.sv", 22, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 100 tries");
                }
                vlSelfRef.__VactIterCount = ((IData)(1U) 
                                             + vlSelfRef.__VactIterCount);
                vlSelfRef.__VactPhaseResult = Vcrossbar_tb___024root___eval_phase__act(vlSelf);
            } while (vlSelfRef.__VactPhaseResult);
            vlSelfRef.__VinactPhaseResult = Vcrossbar_tb___024root___eval_phase__inact(vlSelf);
        } while (vlSelfRef.__VinactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vcrossbar_tb___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

void Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0(Vcrossbar_tb___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root____VbeforeTrig_he9f331c2__0\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((((~ (IData)(vlSelfRef.crossbar_tb__DOT__clk)) 
                                    & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0)) 
                                   << 2U) | ((IData)(vlSelfRef.crossbar_tb__DOT__clk) 
                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0 
        = vlSelfRef.crossbar_tb__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
    }
    if ((4ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

void Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0(Vcrossbar_tb___024root* vlSelf, const char* __VeventDescription) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root____VbeforeTrig_he9f33e88__0\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    VlUnpacked<QData/*63:0*/, 1> __VTmp;
    // Body
    __VTmp[0U] = (QData)((IData)(((((~ (IData)(vlSelfRef.crossbar_tb__DOT__clk)) 
                                    & (IData)(vlSelfRef.__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0)) 
                                   << 2U) | ((IData)(vlSelfRef.crossbar_tb__DOT__clk) 
                                             & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0))))));
    vlSelfRef.__Vtrigprevexpr___TOP__crossbar_tb__DOT__clk__0 
        = vlSelfRef.crossbar_tb__DOT__clk;
    if ((1ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f331c2__0.ready(__VeventDescription);
    }
    if ((4ULL & __VTmp[0U])) {
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
        vlSelfRef.__VtrigSched_he9f33e88__0.ready(__VeventDescription);
    }
    vlSelfRef.__VactTriggeredAcc[0U] = (vlSelfRef.__VactTriggeredAcc[0U] 
                                        | __VTmp[0U]);
}

#ifdef VL_DEBUG
void Vcrossbar_tb___024root___eval_debug_assertions(Vcrossbar_tb___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcrossbar_tb___024root___eval_debug_assertions\n"); );
    Vcrossbar_tb__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
