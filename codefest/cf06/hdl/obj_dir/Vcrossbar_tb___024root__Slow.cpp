// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcrossbar_tb.h for the primary calling header

#include "Vcrossbar_tb__pch.h"

void Vcrossbar_tb___024root___ctor_var_reset(Vcrossbar_tb___024root* vlSelf);

Vcrossbar_tb___024root::Vcrossbar_tb___024root(Vcrossbar_tb__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vcrossbar_tb___024root___ctor_var_reset(this);
}

void Vcrossbar_tb___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vcrossbar_tb___024root::~Vcrossbar_tb___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
