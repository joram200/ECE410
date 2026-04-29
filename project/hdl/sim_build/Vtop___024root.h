// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(valid_in,0,0);
    VL_OUT8(valid_out,0,0);
    CData/*0:0*/ kalman_filter__DOT__clk;
    CData/*0:0*/ kalman_filter__DOT__rst;
    CData/*0:0*/ kalman_filter__DOT__valid_in;
    CData/*0:0*/ kalman_filter__DOT__valid_out;
    CData/*2:0*/ kalman_filter__DOT__state;
    CData/*0:0*/ kalman_filter__DOT__vout;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VicoPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__kalman_filter__DOT__clk__0;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    VL_IN(y,31,0);
    VL_OUT(x_hat_0,31,0);
    VL_OUT(x_hat_1,31,0);
    VL_OUT(x_hat_2,31,0);
    IData/*31:0*/ kalman_filter__DOT__y;
    IData/*31:0*/ kalman_filter__DOT__x_hat_0;
    IData/*31:0*/ kalman_filter__DOT__x_hat_1;
    IData/*31:0*/ kalman_filter__DOT__x_hat_2;
    IData/*31:0*/ kalman_filter__DOT__x0;
    IData/*31:0*/ kalman_filter__DOT__x1;
    IData/*31:0*/ kalman_filter__DOT__x2;
    IData/*31:0*/ kalman_filter__DOT__p00;
    IData/*31:0*/ kalman_filter__DOT__p01;
    IData/*31:0*/ kalman_filter__DOT__p02;
    IData/*31:0*/ kalman_filter__DOT__p11;
    IData/*31:0*/ kalman_filter__DOT__p12;
    IData/*31:0*/ kalman_filter__DOT__p22;
    IData/*31:0*/ kalman_filter__DOT__y_reg;
    IData/*31:0*/ kalman_filter__DOT__x0p;
    IData/*31:0*/ kalman_filter__DOT__x1p;
    IData/*31:0*/ kalman_filter__DOT__x2p;
    IData/*31:0*/ kalman_filter__DOT__pp00;
    IData/*31:0*/ kalman_filter__DOT__pp01;
    IData/*31:0*/ kalman_filter__DOT__pp02;
    IData/*31:0*/ kalman_filter__DOT__pp11;
    IData/*31:0*/ kalman_filter__DOT__pp12;
    IData/*31:0*/ kalman_filter__DOT__pp22;
    IData/*31:0*/ kalman_filter__DOT__s_reg;
    IData/*31:0*/ kalman_filter__DOT__k0;
    IData/*31:0*/ kalman_filter__DOT__k1;
    IData/*31:0*/ kalman_filter__DOT__k2;
    IData/*31:0*/ kalman_filter__DOT__x0_out;
    IData/*31:0*/ kalman_filter__DOT__x1_out;
    IData/*31:0*/ kalman_filter__DOT__x2_out;
    IData/*31:0*/ kalman_filter__DOT__unnamedblk1__DOT__innov;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* vlSymsp;
    const char* vlNamep;

    // PARAMETERS
    static constexpr IData/*31:0*/ kalman_filter__DOT__DATA_WIDTH = 0x00000020U;
    static constexpr IData/*31:0*/ kalman_filter__DOT__FRAC_BITS = 0x00000010U;
    static constexpr IData/*31:0*/ kalman_filter__DOT__FP_ONE = 0x00010000U;
    static constexpr IData/*31:0*/ kalman_filter__DOT__FP_DT = 0x00000889U;
    static constexpr IData/*31:0*/ kalman_filter__DOT__FP_Q00 = 0x00000ccdU;
    static constexpr IData/*31:0*/ kalman_filter__DOT__FP_R = 0x00050000U;
    static constexpr IData/*31:0*/ kalman_filter__DOT__P00_INIT = 0x0000199aU;
    static constexpr IData/*31:0*/ kalman_filter__DOT__P01_INIT = 0x0000199aU;
    static constexpr IData/*31:0*/ kalman_filter__DOT__P02_INIT = 0x0000199aU;
    static constexpr IData/*31:0*/ kalman_filter__DOT__P11_INIT = 0x27100000U;
    static constexpr IData/*31:0*/ kalman_filter__DOT__P12_INIT = 0x000a0000U;
    static constexpr IData/*31:0*/ kalman_filter__DOT__P22_INIT = 0x00640000U;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* namep);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
