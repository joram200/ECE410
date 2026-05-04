// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VMAC_LLM_A__SYMS_H_
#define VERILATED_VMAC_LLM_A__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vmac_llm_A.h"

// INCLUDE MODULE CLASSES
#include "Vmac_llm_A___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vmac_llm_A__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vmac_llm_A* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vmac_llm_A___024root           TOP;

    // CONSTRUCTORS
    Vmac_llm_A__Syms(VerilatedContext* contextp, const char* namep, Vmac_llm_A* modelp);
    ~Vmac_llm_A__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
