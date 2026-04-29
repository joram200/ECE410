import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer, ClockCycles


@cocotb.test()
async def test_mac_basic(dut):
    """Replicate mac_tb.v: reset, a=3/b=4 x3 cycles, reset, a=-5/b=2 x2 cycles."""

    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    # Cycle 1: assert reset
    dut.rst.value = 1
    dut.a.value   = 0
    dut.b.value   = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")   # let flip-flop NBA region settle
    cocotb.log.info(f"Cycle 1 | rst=1 a=0 b=0 | out={dut.out.value.to_signed()}")
    assert dut.out.value.to_signed() == 0

    # Cycles 2-4: a=3, b=4
    dut.rst.value = 0
    dut.a.value   = 3
    dut.b.value   = 4
    for cycle, expected in enumerate([12, 24, 36], start=2):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        actual = dut.out.value.to_signed()
        cocotb.log.info(f"Cycle {cycle} | rst=0 a=3 b=4 | out={actual}")
        assert actual == expected, f"Cycle {cycle}: expected {expected}, got {actual}"

    # Cycle 5: reset again
    dut.rst.value = 1
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    cocotb.log.info(f"Cycle 5 | rst=1 a=3 b=4 | out={dut.out.value.to_signed()}")
    assert dut.out.value.to_signed() == 0

    # Cycles 6-7: a=-5, b=2
    dut.rst.value = 0
    dut.a.value   = -5
    dut.b.value   = 2
    for cycle, expected in enumerate([-10, -20], start=6):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        actual = dut.out.value.to_signed()
        cocotb.log.info(f"Cycle {cycle} | rst=0 a=-5 b=2 | out={actual}")
        assert actual == expected, f"Cycle {cycle}: expected {expected}, got {actual}"


@cocotb.test()
async def test_mac_overflow(dut):
    """Verify signed 2's-complement overflow as accumulator approaches and crosses 2^31 - 1.

    a = -128, b = -128  =>  product = 16384 = 2^14 per cycle (maximum accumulation rate).

    After 2^17 - 1 = 131071 cycles: acc = 2^31 - 2^14 = 2147467264  (16383 below INT32_MAX)
    After 2^17     = 131072 cycles: acc wraps to         -2147483648  (INT32_MIN, exact)
    After 2^17 + 1 = 131073 cycles: acc =               -2147467264  (accumulation resumes)
    """
    INT32_MAX = 2**31 - 1     #  2147483647
    INT32_MIN = -(2**31)      # -2147483648
    product   = 16384         # (-128) * (-128)

    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    # Synchronous reset
    dut.rst.value = 1
    dut.a.value   = 0
    dut.b.value   = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert dut.out.value.to_signed() == 0

    # Drive maximum-product inputs: a = -128 (0x80), b = -128 (0x80)
    dut.rst.value = 0
    dut.a.value   = -128
    dut.b.value   = -128

    # --- Phase 1: bulk accumulation to just below INT32_MAX ---
    # After n_bulk cycles: acc = (2^17 - 1) * 2^14 = 2^31 - 2^14 = 2147467264
    # Gap to INT32_MAX = 2^14 - 1 = 16383  (less than one product, so next step overflows)
    n_bulk   = 2**17 - 1        # 131071
    near_max = n_bulk * product  # 2147467264

    await ClockCycles(dut.clk, n_bulk)
    await Timer(1, unit="ns")
    actual = dut.out.value.to_signed()
    cocotb.log.info(
        f"After {n_bulk} cycles | acc={actual} "
        f"(gap to INT32_MAX = {INT32_MAX - actual})"
    )
    assert actual == near_max, f"Expected {near_max}, got {actual}"
    assert INT32_MAX - actual < product, "Must be within one product of INT32_MAX"

    # --- Phase 2: one more cycle triggers overflow ---
    # 2147467264 + 16384 = 2^31 = -2^31 in signed 32-bit
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    actual = dut.out.value.to_signed()
    cocotb.log.info(f"After {n_bulk + 1} cycles | acc={actual} (overflow wraps to INT32_MIN)")
    assert actual == INT32_MIN, f"Expected INT32_MIN={INT32_MIN} after overflow, got {actual}"

    # --- Phase 3: accumulation continues correctly after wrap ---
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    actual       = dut.out.value.to_signed()
    post_wrap    = INT32_MIN + product  # -2147467264
    cocotb.log.info(f"After {n_bulk + 2} cycles | acc={actual} (post-overflow accumulation)")
    assert actual == post_wrap, f"Expected {post_wrap}, got {actual}"
