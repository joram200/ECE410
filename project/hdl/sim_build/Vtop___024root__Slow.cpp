// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"

// Parameter definitions for Vtop___024root
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__DATA_WIDTH;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__FRAC_BITS;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__FP_ONE;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__FP_DT;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__FP_Q00;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__FP_R;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__P00_INIT;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__P01_INIT;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__P02_INIT;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__P11_INIT;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__P12_INIT;
constexpr IData/*31:0*/ Vtop___024root::kalman_filter__DOT__P22_INIT;


void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf);

Vtop___024root::Vtop___024root(Vtop__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vtop___024root___ctor_var_reset(this);
}

void Vtop___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vtop___024root::~Vtop___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
