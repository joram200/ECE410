// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VADDER4_TB__SYMS_H_
#define VERILATED_VADDER4_TB__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vadder4_tb.h"

// INCLUDE MODULE CLASSES
#include "Vadder4_tb___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vadder4_tb__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vadder4_tb* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vadder4_tb___024root           TOP;

    // CONSTRUCTORS
    Vadder4_tb__Syms(VerilatedContext* contextp, const char* namep, Vadder4_tb* modelp);
    ~Vadder4_tb__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
