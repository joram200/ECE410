# gdb_dump.gdb — TEMPLATE / REFERENCE ONLY
#
# This file is NOT executed directly.  run_profiles.sh generates a per-run
# GDB script from this template by substituting three tokens:
#
#   __RUNDIR__    →  results/run_N   (output directory for this run)
#   __ARC_START__ →  0x375d4         (arc_table start = _end symbol)
#   __ARC_END__   →  0x3a5d4         (arc_table end = _end + 12288)
#
# GDB's `dump` command does not accept string convenience variables as
# filenames in batch mode; literal substitution is the only robust approach.
#
# To run a single manual test without the shell script:
#   sed -e 's|__RUNDIR__|results|' \
#       -e 's|__ARC_START__|0x375d4|' \
#       -e 's|__ARC_END__|0x3a5d4|' \
#       scripts/gdb_dump.gdb > /tmp/gdb_manual.gdb
#   $GDB -batch -x /tmp/gdb_manual.gdb .pio/build/swervolf_nexys/firmware.elf

set pagination off
set confirm off
target remote localhost:3333
monitor reset halt
load

# Hardware breakpoints — do NOT use software breakpoints (break/b).
# Software BPs replace instructions with EBREAK, which on SweRV EL2 triggers a
# machine exception (mcause=3) that jumps to mtvec=0x0 (_start), restarting the
# firmware in an infinite loop.  Hardware BPs use PC-comparison registers.

# BP 1: main() entry (0x5b6) — halt before __monstartup / any _mcount recording
hbreak *0x5b6
# BP 2: main() ret  (0xb00) — halt after all 45 KalmanFilter::update() calls and
#                              after kf_cycles_end / kf_heap_end have been written
hbreak *0xb00

continue
printf "HIT main entry — firmware running\n"

continue
printf "HIT main ret — reading metrics\n"

# Read cycle and heap metrics by symbol name (DWARF debug info from -g flag).
# Format: "METRIC <name> <value>" — grep-friendly for shell script parsing.
printf "METRIC kf_cycles_start %u\n", kf_cycles_start
printf "METRIC kf_cycles_end   %u\n", kf_cycles_end
printf "METRIC kf_heap_start   %u\n", kf_heap_start
printf "METRIC kf_heap_end     %u\n", kf_heap_end
printf "METRIC arc_count       %u\n", arc_count

# Dump 12288 bytes (1024 arcs × 12 bytes) of arc_table from SRAM to disk.
dump binary memory __RUNDIR__/arc_table.bin __ARC_START__ __ARC_END__

printf "arc_table.bin written to __RUNDIR__\n"
quit
