// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vadder4_tb__pch.h"

//============================================================
// Constructors

Vadder4_tb::Vadder4_tb(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vadder4_tb__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vadder4_tb::Vadder4_tb(const char* _vcname__)
    : Vadder4_tb(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vadder4_tb::~Vadder4_tb() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vadder4_tb___024root___eval_debug_assertions(Vadder4_tb___024root* vlSelf);
#endif  // VL_DEBUG
void Vadder4_tb___024root___eval_static(Vadder4_tb___024root* vlSelf);
void Vadder4_tb___024root___eval_initial(Vadder4_tb___024root* vlSelf);
void Vadder4_tb___024root___eval_settle(Vadder4_tb___024root* vlSelf);
void Vadder4_tb___024root___eval(Vadder4_tb___024root* vlSelf);

void Vadder4_tb::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vadder4_tb::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vadder4_tb___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vadder4_tb___024root___eval_static(&(vlSymsp->TOP));
        Vadder4_tb___024root___eval_initial(&(vlSymsp->TOP));
        Vadder4_tb___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vadder4_tb___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vadder4_tb::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vadder4_tb::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vadder4_tb::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vadder4_tb___024root___eval_final(Vadder4_tb___024root* vlSelf);

VL_ATTR_COLD void Vadder4_tb::final() {
    Vadder4_tb___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vadder4_tb::hierName() const { return vlSymsp->name(); }
const char* Vadder4_tb::modelName() const { return "Vadder4_tb"; }
unsigned Vadder4_tb::threads() const { return 1; }
void Vadder4_tb::prepareClone() const { contextp()->prepareClone(); }
void Vadder4_tb::atClone() const {
    contextp()->threadPoolpOnClone();
}
