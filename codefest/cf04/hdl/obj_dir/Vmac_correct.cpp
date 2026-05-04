// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vmac_correct__pch.h"

//============================================================
// Constructors

Vmac_correct::Vmac_correct(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vmac_correct__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vmac_correct::Vmac_correct(const char* _vcname__)
    : Vmac_correct(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vmac_correct::~Vmac_correct() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vmac_correct___024root___eval_debug_assertions(Vmac_correct___024root* vlSelf);
#endif  // VL_DEBUG
void Vmac_correct___024root___eval_static(Vmac_correct___024root* vlSelf);
void Vmac_correct___024root___eval_initial(Vmac_correct___024root* vlSelf);
void Vmac_correct___024root___eval_settle(Vmac_correct___024root* vlSelf);
void Vmac_correct___024root___eval(Vmac_correct___024root* vlSelf);

void Vmac_correct::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmac_correct::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vmac_correct___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vmac_correct___024root___eval_static(&(vlSymsp->TOP));
        Vmac_correct___024root___eval_initial(&(vlSymsp->TOP));
        Vmac_correct___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vmac_correct___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vmac_correct::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vmac_correct::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vmac_correct::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vmac_correct___024root___eval_final(Vmac_correct___024root* vlSelf);

VL_ATTR_COLD void Vmac_correct::final() {
    Vmac_correct___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vmac_correct::hierName() const { return vlSymsp->name(); }
const char* Vmac_correct::modelName() const { return "Vmac_correct"; }
unsigned Vmac_correct::threads() const { return 1; }
void Vmac_correct::prepareClone() const { contextp()->prepareClone(); }
void Vmac_correct::atClone() const {
    contextp()->threadPoolpOnClone();
}
