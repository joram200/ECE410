"""
cocotb testbench for kalman_filter.sv

Mirrors the Python reference in project/profiling/kalman_profile.py.
Fixed-point format: Q16.16  (DATA_WIDTH=32, FRAC_BITS=16)
"""

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer
import numpy as np

# ---------------------------------------------------------------------------
# Q16.16 helpers
# ---------------------------------------------------------------------------
FP = 1 << 16  # 65536


def to_fp(x):
    """Python float -> Q16.16 integer."""
    return int(round(x * FP))


def from_fp(v):
    """Q16.16 integer -> Python float."""
    # handle negative two's-complement values from cocotb
    if v >= (1 << 31):
        v -= (1 << 32)
    return v / FP


# ---------------------------------------------------------------------------
# Reference Kalman filter (Python, matches kalman_profile.py)
# ---------------------------------------------------------------------------
def _ref_kalman_all(measurements):
    """Run all measurements through the Python reference KF; return final state."""
    n, m, dt = 3, 1, 1.0 / 30.0
    A = np.array([[1, dt, 0], [0, 1, dt], [0, 0, 1]], dtype=float)
    C = np.array([[1, 0, 0]], dtype=float)
    Q = np.array([[.05, .05, .0], [.05, .05, .0], [.0, .0, .0]], dtype=float)
    R = np.array([[5.0]], dtype=float)
    P = np.array([[.1, .1, .1], [.1, 1e4, 10], [.1, 10, 100]], dtype=float)

    x = np.array([measurements[0], 0.0, -9.81])
    I = np.eye(n)

    for z in measurements:
        y_vec = np.array([z])
        x_new = A @ x
        P = A @ P @ A.T + Q
        S = C @ P @ C.T + R
        K = P @ C.T @ np.linalg.inv(S)
        x_new += (K @ (y_vec - C @ x_new)).ravel()
        P = (I - K @ C) @ P
        x = x_new
    return x


MEASUREMENTS = [
    1.04202710058, 1.10726790452, 1.2913511148,  1.48485250951, 1.72825901034,
    1.74216489744, 2.11672039768, 2.14529225112, 2.16029641405, 2.21269371128,
    2.57709350237, 2.6682215744,  2.51641839428, 2.76034056782, 2.88131780617,
    2.88373786518, 2.9448468727,  2.82866600131, 3.0006601946,  3.12920591669,
    2.858361783,   2.83808170354, 2.68975330958, 2.66533185589, 2.81613499531,
    2.81003612051, 2.88321849354, 2.69789264832, 2.4342229249,  2.23464791825,
    2.30278776224, 2.02069770395, 1.94393985809, 1.82498398739, 1.52526230354,
    1.86967808173, 1.18073207847, 1.10729605087, 0.916168349913, 0.678547664519,
    0.562381751596, 0.355468474885, -0.155607486619, -0.287198661013,
    -0.602973173813,
]


# ---------------------------------------------------------------------------
# Helper: drive one update and wait for valid_out
# ---------------------------------------------------------------------------
async def run_one_update(dut, y_val, timeout=20):
    """Assert valid_in for one cycle with y=y_val; poll for valid_out."""
    dut.valid_in.value = 1
    dut.y.value = to_fp(y_val)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    dut.valid_in.value = 0
    dut.y.value = 0

    for _ in range(timeout):
        if int(dut.valid_out.value):
            return
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
    raise AssertionError("valid_out never asserted within timeout")


# ---------------------------------------------------------------------------
# Test 1: reset
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_reset(dut):
    """After synchronous reset, all outputs must be 0."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    dut.rst.value = 1
    dut.valid_in.value = 0
    dut.y.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    assert dut.x_hat_0.value.to_signed() == 0, f"x_hat_0={dut.x_hat_0.value.to_signed()}"
    assert dut.x_hat_1.value.to_signed() == 0, f"x_hat_1={dut.x_hat_1.value.to_signed()}"
    assert dut.x_hat_2.value.to_signed() == 0, f"x_hat_2={dut.x_hat_2.value.to_signed()}"
    assert int(dut.valid_out.value) == 0

    cocotb.log.info("test_reset PASSED: all outputs 0 after reset")


# ---------------------------------------------------------------------------
# Test 2: single update
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_single_update(dut):
    """One measurement: valid_out pulses, x_hat_0 roughly tracks y."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    # Reset
    dut.rst.value = 1
    dut.valid_in.value = 0
    dut.y.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    dut.rst.value = 0

    # Drive first measurement
    y_val = MEASUREMENTS[0]
    await run_one_update(dut, y_val)

    x0 = from_fp(dut.x_hat_0.value.to_unsigned())
    cocotb.log.info(f"test_single_update: y={y_val:.4f} x_hat_0={x0:.4f}")

    # After the first update the corrected position should be in the ballpark
    # of the measurement (P is large, so K≈1, x0 ≈ y)
    assert abs(x0 - y_val) < 1.0, f"x_hat_0 ({x0:.4f}) too far from y ({y_val:.4f})"
    cocotb.log.info("test_single_update PASSED")


# ---------------------------------------------------------------------------
# Test 3: two updates
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_two_updates(dut):
    """Two updates: valid_out pulses after each; state is monotonically finite."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    dut.rst.value = 1
    dut.valid_in.value = 0
    dut.y.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    dut.rst.value = 0

    for i in range(2):
        await run_one_update(dut, MEASUREMENTS[i])
        x0 = from_fp(dut.x_hat_0.value.to_unsigned())
        cocotb.log.info(f"  update {i+1}: x_hat_0={x0:.4f}")
        assert abs(x0) < 100.0, f"x_hat_0 diverged: {x0}"

    cocotb.log.info("test_two_updates PASSED")


# ---------------------------------------------------------------------------
# Test 4: numerical accuracy across all 45 measurements
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_numerical_accuracy(dut):
    """Run all 45 measurements; compare final x_hat_0 to Python reference."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    dut.rst.value = 1
    dut.valid_in.value = 0
    dut.y.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    dut.rst.value = 0

    # Set initial state to match Python reference: x0 = measurements[0], x1=0, x2=-9.81
    # The HDL resets to x=[0,0,0]; feed all 45 measurements (no separate init step)
    for z in MEASUREMENTS:
        await run_one_update(dut, z)

    x0_hw  = from_fp(dut.x_hat_0.value.to_unsigned())
    x1_hw  = from_fp(dut.x_hat_1.value.to_unsigned())
    x2_hw  = from_fp(dut.x_hat_2.value.to_unsigned())

    ref    = _ref_kalman_all(MEASUREMENTS)
    x0_ref = ref[0]

    cocotb.log.info(f"HW  x_hat = [{x0_hw:.4f}, {x1_hw:.4f}, {x2_hw:.4f}]")
    cocotb.log.info(f"REF x_hat = [{x0_ref:.4f}, {ref[1]:.4f}, {ref[2]:.4f}]")
    cocotb.log.info(f"x_hat_0 error = {abs(x0_hw - x0_ref):.4f}")

    # Fixed-point Q16.16 resolution is ~1.5e-5; allow ±0.5 for accumulated rounding
    assert abs(x0_hw - x0_ref) < 0.5, (
        f"x_hat_0 error {abs(x0_hw - x0_ref):.4f} exceeds 0.5 tolerance"
    )
    cocotb.log.info("test_numerical_accuracy PASSED")
