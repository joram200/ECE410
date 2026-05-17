// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vcompute_core__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vcompute_core::Vcompute_core(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vcompute_core__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vcompute_core::Vcompute_core(const char* _vcname__)
    : Vcompute_core(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vcompute_core::~Vcompute_core() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vcompute_core___024root___eval_debug_assertions(Vcompute_core___024root* vlSelf);
#endif  // VL_DEBUG
void Vcompute_core___024root___eval_static(Vcompute_core___024root* vlSelf);
void Vcompute_core___024root___eval_initial(Vcompute_core___024root* vlSelf);
void Vcompute_core___024root___eval_settle(Vcompute_core___024root* vlSelf);
void Vcompute_core___024root___eval(Vcompute_core___024root* vlSelf);

void Vcompute_core::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vcompute_core::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vcompute_core___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vcompute_core___024root___eval_static(&(vlSymsp->TOP));
        Vcompute_core___024root___eval_initial(&(vlSymsp->TOP));
        Vcompute_core___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vcompute_core___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

void Vcompute_core::eval_end_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+eval_end_step Vcompute_core::eval_end_step\n"); );
#ifdef VM_TRACE
    // Tracing
    if (VL_UNLIKELY(vlSymsp->__Vm_dumping)) vlSymsp->_traceDump();
#endif  // VM_TRACE
}

//============================================================
// Events and timing
bool Vcompute_core::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vcompute_core::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vcompute_core::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vcompute_core___024root___eval_final(Vcompute_core___024root* vlSelf);

VL_ATTR_COLD void Vcompute_core::final() {
    Vcompute_core___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vcompute_core::hierName() const { return vlSymsp->name(); }
const char* Vcompute_core::modelName() const { return "Vcompute_core"; }
unsigned Vcompute_core::threads() const { return 1; }
void Vcompute_core::prepareClone() const { contextp()->prepareClone(); }
void Vcompute_core::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vcompute_core::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vcompute_core___024root__trace_decl_types(VerilatedVcd* tracep);

void Vcompute_core___024root__trace_init_top(Vcompute_core___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vcompute_core___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcompute_core___024root*>(voidSelf);
    Vcompute_core__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vcompute_core___024root__trace_decl_types(tracep);
    Vcompute_core___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vcompute_core___024root__trace_register(Vcompute_core___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vcompute_core::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vcompute_core::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 56);
    Vcompute_core___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
