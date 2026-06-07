/**
 * kalman_hw.h — MMIO driver for the Kalman measurement-correction accelerator.
 *
 * Base address: 0x80010000 (AXI slave 2 in VeeRwolf SoC_impl)
 *
 * Register map (8-byte stride, 64-bit IEEE-754 doubles):
 *   0x00  CTRL  R/W  [0]=start one-shot, [1]=soft_rst
 *   0x08  STAT  RO   [0]=done (1-cycle pulse), [1]=busy
 *   0x10  z     WO   measurement scalar
 *   0x18  x_in[0] WO
 *   0x20  x_in[1] WO
 *   0x28  x_in[2] WO
 *   0x30  x_out[0] RO
 *   0x38  x_out[1] RO
 *   0x40  x_out[2] RO
 *   0x58  P_in[0,0] WO  (continues at +0x08 per element, row-major)
 *   ...
 *   0x98  P_in[2,2] WO
 *   0xA0  P_out[0,0] RO
 *   ...
 *   0xE0  P_out[2,2] RO
 *   0xE8  R_REG R/W  measurement noise covariance (default 5.0)
 *
 * All registers are 64-bit. On RV32 (no 64-bit integer stores), each write
 * is two 32-bit stores (lo word then hi word), relying on AXI WSTRB byte-
 * enables to update each half independently. Reads are likewise two LW ops.
 */

#ifndef KALMAN_HW_H
#define KALMAN_HW_H

#include <stdint.h>

/* Accelerator base address */
#define KALMAN_BASE_ADDR  0x80010000U

/* Convenience pointer for uint32_t-granular MMIO access */
#define KALMAN_BASE  ((volatile uint32_t *)(KALMAN_BASE_ADDR))

/* Register byte offsets */
#define KALMAN_CTRL   0x00U
#define KALMAN_STAT   0x08U
#define KALMAN_Z      0x10U
#define KALMAN_XIN0   0x18U
#define KALMAN_XIN1   0x20U
#define KALMAN_XIN2   0x28U
#define KALMAN_XOUT0  0x30U
#define KALMAN_XOUT1  0x38U
#define KALMAN_XOUT2  0x40U
#define KALMAN_PIN0   0x58U   /* P_in[0,0]  — stride 8 for elements [0..8] */
#define KALMAN_POUT0  0xA0U   /* P_out[0,0] — stride 8 for elements [0..8] */
#define KALMAN_RREG   0xE8U

/* STAT bit masks (applied to lo 32-bit word) */
#define KALMAN_STAT_DONE  (1U << 0)
#define KALMAN_STAT_BUSY  (1U << 1)

/* ── Low-level 64-bit MMIO helpers ─────────────────────────────────── */

/* Write one IEEE-754 double to a 64-bit MMIO register at byte offset.
 * Two 32-bit stores: lo word first, then hi word.
 * The AXI slave uses WSTRB byte-enables to update each 32-bit half. */
static inline void kw_write_f64(uint32_t offset_bytes, double val) {
    union { double d; uint32_t u[2]; } v;
    v.d = val;
    volatile uint32_t *p = KALMAN_BASE + (offset_bytes >> 2);
    p[0] = v.u[0];   /* low  word → WSTRB=0x0F, bytes [31:0]  */
    p[1] = v.u[1];   /* high word → WSTRB=0xF0, bytes [63:32] */
}

/* Read one IEEE-754 double from a 64-bit MMIO register at byte offset. */
static inline double kw_read_f64(uint32_t offset_bytes) {
    union { double d; uint32_t u[2]; } v;
    const volatile uint32_t *p = KALMAN_BASE + (offset_bytes >> 2);
    v.u[0] = p[0];
    v.u[1] = p[1];
    return v.d;
}

/* Write a raw uint32_t to the lo word of a 64-bit MMIO register.
 * Used for bit-field registers (CTRL) that are not IEEE-754 values. */
static inline void kw_write_ctrl(uint32_t lo_val) {
    KALMAN_BASE[KALMAN_CTRL >> 2]       = lo_val;  /* lo word */
    KALMAN_BASE[(KALMAN_CTRL >> 2) + 1] = 0U;      /* hi word = 0 */
}

/* ── Public API ─────────────────────────────────────────────────────── */

/**
 * kalman_hw_set_r — write measurement noise covariance R to R_REG (0xE8).
 *
 * Call once before the update loop. The hardware defaults to R = 5.0
 * (0x4014000000000000) on reset.
 */
static inline void kalman_hw_set_r(double r) {
    kw_write_f64(KALMAN_RREG, r);
}

/**
 * kalman_hw_update — one measurement-correction update via MMIO.
 *
 * Loads z, x_in[3], P_in[9] into the accelerator registers, fires the
 * one-shot start pulse, polls busy until clear, then reads back x_out[3]
 * and P_out[9].
 *
 * @param z       scalar measurement
 * @param x_in    prior state vector [3]
 * @param P_in    prior covariance matrix [9], row-major
 * @param x_out   corrected state vector [3] (output)
 * @param P_out   posterior covariance [9], row-major (output)
 * @return 0 on success, -1 on timeout (accelerator stuck busy)
 */
static inline int kalman_hw_update(double        z,
                                   const double  x_in[3],
                                   const double  P_in[9],
                                   double        x_out[3],
                                   double        P_out[9]) {
    int i;

    /* 1. Write measurement z */
    kw_write_f64(KALMAN_Z, z);

    /* 2. Write prior state x_in[0:2] */
    kw_write_f64(KALMAN_XIN0, x_in[0]);
    kw_write_f64(KALMAN_XIN1, x_in[1]);
    kw_write_f64(KALMAN_XIN2, x_in[2]);

    /* 3. Write prior covariance P_in[0:8] at 0x58..0x98, 8-byte stride */
    for (i = 0; i < 9; i++)
        kw_write_f64(KALMAN_PIN0 + (uint32_t)(i * 8), P_in[i]);

    /* 4. Fire: set CTRL[0]=1 (start bit) — raw uint32 write, not IEEE-754 */
    kw_write_ctrl(1U);

    /* 5. Poll STAT[1] (busy) until clear; bounded by timeout */
    {
        uint32_t timeout = 500000U;
        while ((KALMAN_BASE[KALMAN_STAT >> 2] & KALMAN_STAT_BUSY) && --timeout)
            ;
        if (!timeout) return -1;
    }

    /* 6. Read corrected state x_out[0:2] at 0x30..0x40 */
    x_out[0] = kw_read_f64(KALMAN_XOUT0);
    x_out[1] = kw_read_f64(KALMAN_XOUT1);
    x_out[2] = kw_read_f64(KALMAN_XOUT2);

    /* 7. Read posterior covariance P_out[0:8] at 0xA0..0xE0, 8-byte stride */
    for (i = 0; i < 9; i++)
        P_out[i] = kw_read_f64(KALMAN_POUT0 + (uint32_t)(i * 8));

    return 0;
}

#endif /* KALMAN_HW_H */
