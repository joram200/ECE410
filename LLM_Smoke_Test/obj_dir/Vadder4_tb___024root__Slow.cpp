// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vadder4_tb.h for the primary calling header

#include "Vadder4_tb__pch.h"

void Vadder4_tb___024root___ctor_var_reset(Vadder4_tb___024root* vlSelf);

Vadder4_tb___024root::Vadder4_tb___024root(Vadder4_tb__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vadder4_tb___024root___ctor_var_reset(this);
}

void Vadder4_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vadder4_tb___024root::~Vadder4_tb___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
