// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vinterface__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vinterface::Vinterface(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vinterface__Syms(contextp(), _vcname__, this)}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vinterface::Vinterface(const char* _vcname__)
    : Vinterface(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vinterface::~Vinterface() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vinterface___024root___eval_debug_assertions(Vinterface___024root* vlSelf);
#endif  // VL_DEBUG
void Vinterface___024root___eval_static(Vinterface___024root* vlSelf);
void Vinterface___024root___eval_initial(Vinterface___024root* vlSelf);
void Vinterface___024root___eval_settle(Vinterface___024root* vlSelf);
void Vinterface___024root___eval(Vinterface___024root* vlSelf);

void Vinterface::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vinterface::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vinterface___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vinterface___024root___eval_static(&(vlSymsp->TOP));
        Vinterface___024root___eval_initial(&(vlSymsp->TOP));
        Vinterface___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vinterface___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

void Vinterface::eval_end_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+eval_end_step Vinterface::eval_end_step\n"); );
#ifdef VM_TRACE
    // Tracing
    if (VL_UNLIKELY(vlSymsp->__Vm_dumping)) vlSymsp->_traceDump();
#endif  // VM_TRACE
}

//============================================================
// Events and timing
bool Vinterface::eventsPending() { return !vlSymsp->TOP.__VdlySched.empty() && !contextp()->gotFinish(); }

uint64_t Vinterface::nextTimeSlot() { return vlSymsp->TOP.__VdlySched.nextTimeSlot(); }

//============================================================
// Utilities

const char* Vinterface::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vinterface___024root___eval_final(Vinterface___024root* vlSelf);

VL_ATTR_COLD void Vinterface::final() {
    Vinterface___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vinterface::hierName() const { return vlSymsp->name(); }
const char* Vinterface::modelName() const { return "Vinterface"; }
unsigned Vinterface::threads() const { return 1; }
void Vinterface::prepareClone() const { contextp()->prepareClone(); }
void Vinterface::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vinterface::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vinterface___024root__trace_decl_types(VerilatedVcd* tracep);

void Vinterface___024root__trace_init_top(Vinterface___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vinterface___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vinterface___024root*>(voidSelf);
    Vinterface__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(vlSymsp->name(), VerilatedTracePrefixType::SCOPE_MODULE);
    Vinterface___024root__trace_decl_types(tracep);
    Vinterface___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vinterface___024root__trace_register(Vinterface___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vinterface::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vinterface::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP), name(), false, 56);
    Vinterface___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
