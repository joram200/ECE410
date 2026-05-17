// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vinterface.h for the primary calling header

#include "Vinterface__pch.h"

void Vinterface___024root___ctor_var_reset(Vinterface___024root* vlSelf);

Vinterface___024root::Vinterface___024root(Vinterface__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vinterface___024root___ctor_var_reset(this);
}

void Vinterface___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vinterface___024root::~Vinterface___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
