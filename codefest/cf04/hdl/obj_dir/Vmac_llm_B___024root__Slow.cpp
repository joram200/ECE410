// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmac_llm_B.h for the primary calling header

#include "Vmac_llm_B__pch.h"

void Vmac_llm_B___024root___ctor_var_reset(Vmac_llm_B___024root* vlSelf);

Vmac_llm_B___024root::Vmac_llm_B___024root(Vmac_llm_B__Syms* symsp, const char* namep)
    : __VdlySched{*symsp->_vm_contextp__}
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vmac_llm_B___024root___ctor_var_reset(this);
}

void Vmac_llm_B___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vmac_llm_B___024root::~Vmac_llm_B___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
