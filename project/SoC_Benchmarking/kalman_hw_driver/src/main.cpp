/**
 * main.cpp — Kalman hardware accelerator profiling harness.
 *
 * Mirrors the structure of RVfpgaEL2_profiling/test/kalman-test.cpp, using
 * the same KalmanFilter class and identical model parameters, but replaces
 * the software measurement-correction step with kf.update_hw(), which
 * offloads the correct phase to the Kalman MMIO accelerator at 0x80010000.
 *
 * Algorithm split (KalmanFilter::update_hw):
 *   Predict (SW, Eigen): x̂⁻ = A·x̂,  P⁻ = A·P·Aᵀ + Q
 *   Correct (HW, MMIO): K, x̂, P via kalman_hw_update() — see kalman_hw.h
 *
 * Model matrices (identical to kalman-test.cpp):
 *   dt = 1/30,  A = [1,dt,0; 0,1,dt; 0,0,1],  Q = [.05,.05,0; .05,.05,0; 0,0,0]
 *   C = [1,0,0],  R = 5,  P0 = [.1,.1,.1; .1,10000,10; .1,10,100]
 *   x0 = [measurements[0], 0, -9.81]
 *
 * mcycle CSR snapshots and bump-allocator high-water marks bracket the loop
 * so GDB can compute elapsed_cycles, time_ms, throughput, heap_bytes.
 *
 * Profiling procedure (GDB JTAG, no UART):
 *   scripts/run_profiles.sh        — 5-run automated loop
 *   scripts/gdb_hw.gdb             — manual single run
 */

#include <vector>
#include <Eigen/Dense>
#include <stdint.h>

#include "kalman.hpp"
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
    int n = 3; // Number of states
    int m = 1; // Number of measurements

    double dt = 1.0 / 30; // Time step

    Eigen::MatrixXd A(n, n); // System dynamics matrix
    Eigen::MatrixXd C(m, n); // Output matrix
    Eigen::MatrixXd Q(n, n); // Process noise covariance
    Eigen::MatrixXd R(m, m); // Measurement noise covariance
    Eigen::MatrixXd P(n, n); // Estimate error covariance

    // Discrete LTI projectile motion, measuring position only
    A << 1, dt, 0, 0, 1, dt, 0, 0, 1;
    C << 1, 0, 0;

    // Reasonable covariance matrices
    Q << .05, .05, .0, .05, .05, .0, .0, .0, .0;
    R << 5;
    P << .1, .1, .1, .1, 10000, 10, .1, 10, 100;

    // Construct the filter
    KalmanFilter kf(dt, A, C, Q, R, P);

    // 45 noisy position measurements — identical to kalman-test.cpp baseline
    std::vector<double> measurements = {
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

    // Best guess of initial states (from kalman-test.cpp)
    Eigen::VectorXd x0(n);
    x0 << measurements[0], 0, -9.81;
    kf.init(0.0, x0);

    // Write R = 5.0 once before the loop (matches SW baseline R matrix)
    kalman_hw_set_r(5.0);

    /* ── Bracket the update loop ── */
    kf_heap_start = get_bump_top();
    { uint32_t c; __asm__ volatile("csrr %0, mcycle" : "=r"(c)); kf_cycles_start = c; }

    Eigen::VectorXd y(m);
    for (int i = 0; i < (int)measurements.size(); i++) {
        y << measurements[i];
        kf.update_hw(y);
    }

    { uint32_t c; __asm__ volatile("csrr %0, mcycle" : "=r"(c)); kf_cycles_end = c; }
    kf_heap_end = get_bump_top();

    /* GDB hardware breakpoint lands here — metrics are in kf_cycles_* and kf_heap_* */
    profile_done();

    return 0;
}
