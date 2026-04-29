// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__pch.h"

Vtop__Syms::Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(1308);
    // Setup sub module instances
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscopep_TOP = new VerilatedScope{this, "TOP", "TOP", "<null>", 0, VerilatedScope::SCOPE_OTHER};
    __Vscopep_kalman_filter = new VerilatedScope{this, "kalman_filter", "kalman_filter", "kalman_filter", -9, VerilatedScope::SCOPE_MODULE};
    __Vscopep_kalman_filter__unnamedblk1 = new VerilatedScope{this, "kalman_filter.unnamedblk1", "unnamedblk1", "<null>", -9, VerilatedScope::SCOPE_OTHER};
    // Set up scope hierarchy
    __Vhier.add(0, __Vscopep_kalman_filter);
    __Vhier.add(__Vscopep_kalman_filter, __Vscopep_kalman_filter__unnamedblk1);
    // Setup export functions - final: 0
    // Setup export functions - final: 1
    // Setup public variables
    __Vscopep_TOP->varInsert("clk", &(TOP.clk), false, VLVT_UINT8, VLVD_IN|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("rst", &(TOP.rst), false, VLVT_UINT8, VLVD_IN|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("valid_in", &(TOP.valid_in), false, VLVT_UINT8, VLVD_IN|VLVF_PUB_RW, 0, 0);
    __Vscopep_TOP->varInsert("valid_out", &(TOP.valid_out), false, VLVT_UINT8, VLVD_OUT|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_TOP->varInsert("x_hat_0", &(TOP.x_hat_0), false, VLVT_UINT32, VLVD_OUT|VLVF_PUB_RW|VLVF_CONTINUOUSLY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_TOP->varInsert("x_hat_1", &(TOP.x_hat_1), false, VLVT_UINT32, VLVD_OUT|VLVF_PUB_RW|VLVF_CONTINUOUSLY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_TOP->varInsert("x_hat_2", &(TOP.x_hat_2), false, VLVT_UINT32, VLVD_OUT|VLVF_PUB_RW|VLVF_CONTINUOUSLY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_TOP->varInsert("y", &(TOP.y), false, VLVT_UINT32, VLVD_IN|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("DATA_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__DATA_WIDTH))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("FP_DT", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__FP_DT))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("FP_ONE", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__FP_ONE))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("FP_Q00", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__FP_Q00))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("FP_R", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__FP_R))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("FRAC_BITS", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__FRAC_BITS))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_DPI_CLAY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("P00_INIT", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__P00_INIT))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("P01_INIT", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__P01_INIT))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("P02_INIT", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__P02_INIT))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("P11_INIT", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__P11_INIT))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("P12_INIT", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__P12_INIT))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("P22_INIT", const_cast<void*>(static_cast<const void*>(&(TOP.kalman_filter__DOT__P22_INIT))), true, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("clk", &(TOP.kalman_filter__DOT__clk), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_kalman_filter->varInsert("k0", &(TOP.kalman_filter__DOT__k0), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("k1", &(TOP.kalman_filter__DOT__k1), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("k2", &(TOP.kalman_filter__DOT__k2), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("p00", &(TOP.kalman_filter__DOT__p00), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("p01", &(TOP.kalman_filter__DOT__p01), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("p02", &(TOP.kalman_filter__DOT__p02), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("p11", &(TOP.kalman_filter__DOT__p11), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("p12", &(TOP.kalman_filter__DOT__p12), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("p22", &(TOP.kalman_filter__DOT__p22), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("pp00", &(TOP.kalman_filter__DOT__pp00), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("pp01", &(TOP.kalman_filter__DOT__pp01), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("pp02", &(TOP.kalman_filter__DOT__pp02), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("pp11", &(TOP.kalman_filter__DOT__pp11), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("pp12", &(TOP.kalman_filter__DOT__pp12), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("pp22", &(TOP.kalman_filter__DOT__pp22), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("rst", &(TOP.kalman_filter__DOT__rst), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_kalman_filter->varInsert("s_reg", &(TOP.kalman_filter__DOT__s_reg), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("state", &(TOP.kalman_filter__DOT__state), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 1 ,2,0);
    __Vscopep_kalman_filter->varInsert("valid_in", &(TOP.kalman_filter__DOT__valid_in), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_kalman_filter->varInsert("valid_out", &(TOP.kalman_filter__DOT__valid_out), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY, 0, 0);
    __Vscopep_kalman_filter->varInsert("vout", &(TOP.kalman_filter__DOT__vout), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 0, 0);
    __Vscopep_kalman_filter->varInsert("x0", &(TOP.kalman_filter__DOT__x0), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x0_out", &(TOP.kalman_filter__DOT__x0_out), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x0p", &(TOP.kalman_filter__DOT__x0p), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x1", &(TOP.kalman_filter__DOT__x1), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x1_out", &(TOP.kalman_filter__DOT__x1_out), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x1p", &(TOP.kalman_filter__DOT__x1p), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x2", &(TOP.kalman_filter__DOT__x2), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x2_out", &(TOP.kalman_filter__DOT__x2_out), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x2p", &(TOP.kalman_filter__DOT__x2p), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x_hat_0", &(TOP.kalman_filter__DOT__x_hat_0), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x_hat_1", &(TOP.kalman_filter__DOT__x_hat_1), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("x_hat_2", &(TOP.kalman_filter__DOT__x_hat_2), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_CONTINUOUSLY|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("y", &(TOP.kalman_filter__DOT__y), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter->varInsert("y_reg", &(TOP.kalman_filter__DOT__y_reg), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
    __Vscopep_kalman_filter__unnamedblk1->varInsert("innov", &(TOP.kalman_filter__DOT__unnamedblk1__DOT__innov), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW|VLVF_SIGNED, 0, 1 ,31,0);
}

Vtop__Syms::~Vtop__Syms() {
    // Tear down scope hierarchy
    __Vhier.remove(0, __Vscopep_kalman_filter);
    __Vhier.remove(__Vscopep_kalman_filter, __Vscopep_kalman_filter__unnamedblk1);
    // Clear keys from hierarchy map after values have been removed
    __Vhier.clear();
    // Tear down scopes
    VL_DO_CLEAR(delete __Vscopep_TOP, __Vscopep_TOP = nullptr);
    VL_DO_CLEAR(delete __Vscopep_kalman_filter, __Vscopep_kalman_filter = nullptr);
    VL_DO_CLEAR(delete __Vscopep_kalman_filter__unnamedblk1, __Vscopep_kalman_filter__unnamedblk1 = nullptr);
    // Tear down sub module instances
}
