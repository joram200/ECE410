// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VMAC_CORRECT__SYMS_H_
#define VERILATED_VMAC_CORRECT__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vmac_correct.h"

// INCLUDE MODULE CLASSES
#include "Vmac_correct___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vmac_correct__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vmac_correct* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vmac_correct___024root         TOP;

    // CONSTRUCTORS
    Vmac_correct__Syms(VerilatedContext* contextp, const char* namep, Vmac_correct* modelp);
    ~Vmac_correct__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
