// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmac_correct.h for the primary calling header

#include "Vmac_correct__pch.h"

void Vmac_correct___024root___ctor_var_reset(Vmac_correct___024root* vlSelf);

Vmac_correct___024root::Vmac_correct___024root(Vmac_correct__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vmac_correct___024root___ctor_var_reset(this);
}

void Vmac_correct___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vmac_correct___024root::~Vmac_correct___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
