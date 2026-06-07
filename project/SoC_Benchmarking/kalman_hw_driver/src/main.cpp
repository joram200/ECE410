/**
 * main.cpp — Kalman hardware accelerator profiling harness.
 *
 * Runs 45 measurement-correction updates via MMIO (matching the SW baseline
 * in project/RVfpgaEL2_profiling).  mcycle CSR snapshots and bump-allocator
 * high-water marks bracket the update loop so GDB can compute:
 *
 *   elapsed_cycles = kf_cycles_end - kf_cycles_start
 *   time_ms        = elapsed_cycles / 13000.0   (13 MHz core clock)
 *   throughput     = 45 / (elapsed_cycles / 13000000.0)  samples/sec
 *   heap_bytes     = kf_heap_end - kf_heap_start
 *
 * Profiling procedure (GDB JTAG, no UART):
 *   scripts/run_profiles.sh        — 5-run automated loop
 *   scripts/gdb_hw.gdb             — manual single run
 */

#include <stdint.h>
#include "kalman_hw.h"

/* Performance measurement globals.
 * Declared volatile so the compiler cannot elide the CSR stores.
 * Read by GDB at hbreak profile_done after all 45 updates complete. */
volatile uint32_t kf_cycles_start = 0;
volatile uint32_t kf_cycles_end   = 0;
volatile uint32_t kf_heap_start   = 0;
volatile uint32_t kf_heap_end     = 0;

/* Defined in syscalls.c — returns bump allocator high-water mark. */
extern "C" uint32_t get_bump_top(void);

/* Sentinel function — GDB sets hbreak here.
 * __attribute__((noinline)) prevents the compiler from inlining/tail-calling
 * so the symbol address is stable across debug/release builds. */
extern "C" __attribute__((noinline)) void profile_done(void) {
    __asm__ volatile("" ::: "memory");   /* prevent optimization across call */
}

int main(void) {
    /* 45 noisy position measurements — identical to kalman-test.cpp baseline */
    static const double measurements[45] = {
        1.04202710058,  1.10726790452,  1.2913511148,   1.48485250951,  1.72825901034,
        1.74216489744,  2.11672039768,  2.14529225112,  2.16029641405,  2.21269371128,
        2.57709350237,  2.6682215744,   2.51641839428,  2.76034056782,  2.88131780617,
        2.88373786518,  2.9448468727,   2.82866600131,  3.0006601946,   3.12920591669,
        2.858361783,    2.83808170354,  2.68975330958,  2.66533185589,  2.81613499531,
        2.81003612051,  2.88321849354,  2.69789264832,  2.4342229249,   2.23464791825,
        2.30278776224,  2.02069770395,  1.94393985809,  1.82498398739,  1.52526230354,
        1.86967808173,  1.18073207847,  1.10729605087,  0.916168349913, 0.678547664519,
        0.562381751596, 0.355468474885, -0.155607486619,-0.287198661013,-0.602973173813
    };

    /* Initial state: x0 = [measurements[0], 0, -9.81] (from kalman-test.cpp) */
    double x[3] = { measurements[0], 0.0, -9.81 };

    /* Initial P covariance (row-major, from kalman-test.cpp):
     *   P = [.1,  .1,   .1;
     *        .1, 10000, 10;
     *        .1,  10,  100] */
    double P[9] = { 0.1, 0.1, 0.1,  0.1, 10000.0, 10.0,  0.1, 10.0, 100.0 };

    double x_out[3] = {0.0, 0.0, 0.0};
    double P_out[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    /* Write R = 5.0 once before the loop (matches SW baseline R matrix) */
    kalman_hw_set_r(5.0);

    /* ── Bracket the update loop ── */
    kf_heap_start = get_bump_top();
    { uint32_t c; __asm__ volatile("csrr %0, mcycle" : "=r"(c)); kf_cycles_start = c; }

    for (int i = 0; i < 45; i++) {
        kalman_hw_update(measurements[i], x, P, x_out, P_out);
        /* Feed outputs back as inputs for the next step */
        x[0] = x_out[0];
        x[1] = x_out[1];
        x[2] = x_out[2];
        for (int j = 0; j < 9; j++) P[j] = P_out[j];
    }

    { uint32_t c; __asm__ volatile("csrr %0, mcycle" : "=r"(c)); kf_cycles_end = c; }
    kf_heap_end = get_bump_top();

    /* GDB hardware breakpoint lands here — metrics are in kf_cycles_* and kf_heap_* */
    profile_done();

    return 0;
}
