// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vmac_llm_B__pch.h"

//============================================================
// Constructors

Vmac_llm_B::Vmac_llm_B(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vmac_llm_B__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vmac_llm_B::Vmac_llm_B(const char* _vcname__)
    : Vmac_llm_B(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vmac_llm_B::~Vmac_llm_B() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vmac_llm_B___024root___eval_debug_assertions(Vmac_llm_B___024root* vlSelf);
#endif  // VL_DEBUG
void Vmac_llm_B___024root___eval_static(Vmac_llm_B___024root* vlSelf);
void Vmac_llm_B___024root___eval_initial(Vmac_llm_B___024root* vlSelf);
void Vmac_llm_B___024root___eval_settle(Vmac_llm_B___024root* vlSelf);
void Vmac_llm_B___024root___eval(Vmac_llm_B___024root* vlSelf);

void Vmac_llm_B::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmac_llm_B::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vmac_llm_B___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vmac_llm_B___024root___eval_static(&(vlSymsp->TOP));
        Vmac_llm_B___024root___eval_initial(&(vlSymsp->TOP));
        Vmac_llm_B___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vmac_llm_B___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vmac_llm_B::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vmac_llm_B::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vmac_llm_B::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vmac_llm_B___024root___eval_final(Vmac_llm_B___024root* vlSelf);

VL_ATTR_COLD void Vmac_llm_B::final() {
    Vmac_llm_B___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vmac_llm_B::hierName() const { return vlSymsp->name(); }
const char* Vmac_llm_B::modelName() const { return "Vmac_llm_B"; }
unsigned Vmac_llm_B::threads() const { return 1; }
void Vmac_llm_B::prepareClone() const { contextp()->prepareClone(); }
void Vmac_llm_B::atClone() const {
    contextp()->threadPoolpOnClone();
}
