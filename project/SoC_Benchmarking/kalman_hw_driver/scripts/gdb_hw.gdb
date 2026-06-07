# gdb_hw.gdb — TEMPLATE / REFERENCE ONLY
#
# run_profiles.sh generates a per-run script from this template by substituting:
#   __RUNDIR__          →  results/run_N
#   __PROFILE_DONE__    →  address of profile_done() from nm
#
# To run a single manual session (after loading addresses from nm):
#   ADDR=$(riscv64-unknown-elf-nm .pio/build/swervolf_nexys/firmware.elf \
#            | awk '$3 == "profile_done" && ($2=="T"||$2=="t") {print "0x"$1}')
#   sed -e "s|__RUNDIR__|results|" -e "s|__PROFILE_DONE__|$ADDR|" \
#       scripts/gdb_hw.gdb > /tmp/gdb_manual.gdb
#   riscv64-unknown-elf-gdb -batch -x /tmp/gdb_manual.gdb \
#       .pio/build/swervolf_nexys/firmware.elf

set pagination off
set confirm off
target remote localhost:3333
monitor reset halt
load

# Hardware breakpoints — do NOT use software breakpoints (break/b).
# Software BPs replace instructions with EBREAK, which on SweRV EL2 triggers a
# machine exception (mcause=3) that jumps to mtvec=0x0, restarting firmware.

# BP 1: profile_done() entry — fires after kf_cycles_end and kf_heap_end are written
hbreak *__PROFILE_DONE__

continue
printf "HIT profile_done — reading metrics\n"

# Read cycle and heap metrics by symbol name (DWARF from -g flag).
# Format: "METRIC <name> <value>" — grep-friendly for shell script parsing.
printf "METRIC kf_cycles_start %u\n", kf_cycles_start
printf "METRIC kf_cycles_end   %u\n", kf_cycles_end
printf "METRIC kf_heap_start   %u\n", kf_heap_start
printf "METRIC kf_heap_end     %u\n", kf_heap_end

printf "metrics captured — run __RUNDIR__\n"
quit
