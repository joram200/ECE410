#!/usr/bin/env python3
"""
parse_arc_table.py — parse a raw arc_table SRAM binary dump and produce gmon.out.

The arc_table is populated by _mcount (in gprof_support.c) during firmware
execution.  It holds 1024 entries of the form:
    { uint32_t from_pc; uint32_t self_pc; uint32_t count; }  (little-endian)
totalling 12288 bytes.

This replaces the original UART hex-extraction approach (extract_gmon.py).
The arc_table is dumped directly from SRAM over JTAG via the GDB script
gdb_dump.gdb, bypassing the broken BSP UART entirely.

Usage:
    python3 parse_arc_table.py <arc_table.bin> [output_gmon.out]

Exits with code 1 on any error.
"""

import struct
import sys
import os

ARC_TABLE_SIZE = 1024
ENTRY_SIZE = 12        # 3 x uint32_t, little-endian


def parse_arc_table(bin_path, output_path):
    try:
        with open(bin_path, "rb") as f:
            data = f.read()
    except OSError as exc:
        print(f"Error reading '{bin_path}': {exc}", file=sys.stderr)
        sys.exit(1)

    expected = ARC_TABLE_SIZE * ENTRY_SIZE
    if len(data) < expected:
        print(f"Warning: binary is {len(data)} bytes, expected {expected}; "
              f"truncated dump?", file=sys.stderr)

    arcs = []
    for i in range(min(ARC_TABLE_SIZE, len(data) // ENTRY_SIZE)):
        offset = i * ENTRY_SIZE
        from_pc, self_pc, count = struct.unpack_from('<III', data, offset)
        if count > 0:
            arcs.append((from_pc, self_pc, count))

    print(f"Binary size       : {len(data)} bytes (expected {expected})")
    print(f"Non-empty arcs    : {len(arcs)}")
    print()
    print(f"{'from_pc':>12}  {'self_pc':>12}  {'count':>8}")
    print("-" * 38)
    for from_pc, self_pc, count in sorted(arcs, key=lambda x: -x[2]):
        print(f"  0x{from_pc:08x}  0x{self_pc:08x}  {count:8d}")

    # Write gmon.out (GMON_TAG_CG_ARC records)
    try:
        with open(output_path, "wb") as f:
            # gmon.out header: magic + version 1 + 12 bytes padding
            f.write(b"gmon")
            f.write(struct.pack("<I", 1))
            f.write(b"\x00" * 12)
            # One GMON_TAG_CG_ARC (tag=0x01) record per non-empty arc
            for from_pc, self_pc, count in arcs:
                f.write(b"\x01")
                f.write(struct.pack("<III", from_pc, self_pc, count))
    except OSError as exc:
        print(f"Error writing '{output_path}': {exc}", file=sys.stderr)
        sys.exit(1)

    print()
    print(f"gmon.out written  : {output_path} ({os.path.getsize(output_path)} bytes)")
    return arcs


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <arc_table.bin> [output.gmon.out]",
              file=sys.stderr)
        sys.exit(1)

    bin_path    = sys.argv[1]
    output_path = sys.argv[2] if len(sys.argv) > 2 else "gmon.out"
    parse_arc_table(bin_path, output_path)
