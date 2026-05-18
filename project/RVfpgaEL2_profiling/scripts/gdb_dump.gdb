set pagination off
set confirm off
target remote localhost:3333
monitor reset halt
load

# Hardware breakpoints — do NOT use software breakpoints (break/b).
# Software BPs replace instructions with EBREAK, which on SweRV EL2 triggers a
# machine exception (mcause=3) that jumps to mtvec=0x0 (_start), restarting the
# firmware in an infinite loop.  Hardware BPs use the PC-comparison registers and
# halt the CPU correctly.

# BP 1: main() entry (0x88) — halt before __monstartup / any _mcount recording
hbreak *0x88
# BP 2: main() ret  (0x416) — halt after all 45 KalmanFilter::update() calls
hbreak *0x416

# Run to main() entry
continue
printf "HIT main entry — firmware running\n"

# Run to main() return (fires after all 45 update steps complete)
continue
printf "HIT main ret — dumping arc_table\n"

# Dump 12288 bytes (1024 arcs * 12 bytes each) from arc_table start to end
# arc_table is at _end (0x375d4); arc_table end = 0x375d4 + 0x3000 = 0x3a5d4
dump binary memory gmon_runs/results/arc_table.bin 0x375d4 0x3a5d4

# Print arc_count (uint at 0x37518) as a sanity check
p/d *(unsigned int*)0x37518

printf "arc_table.bin written\n"
quit
