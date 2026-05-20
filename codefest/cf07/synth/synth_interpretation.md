# Synthesis Analysis  

## Design and Tool Selection

I have decided to change the platform for my project which requires changes to my compute core design. I've instead used the fallback option of the crossbar MAC from cf06 to synthesis. I also used the Vivado tool platform since I have it installed on my system for another class this term and with is disk space being massive I couldn't have openland & docker installed on this same system. Vivado was ran in Out-of-Context (OOC) synthesis mode to emulate ASIC synthesis.

## Synthesis Results

The clock period was set to 10.0 ns with the worst case slack time being t<sub>WNS</sub> = +3.713 ns, t<sub>WHS</sub> = +0.193 ns, and Pulse Width being +4.500 ns all of which were acceptable times.  

The critial path is the following: in\[2\]\[0\] \(input port, 2.000 ns input delay\) → out\[1\]\[3\]_i_13\(LUT3\) → out\[1\]\[3\]_i_9\(LUT5\) → out\[1\]\[3\]_i_2\(LUT6\) → out\[1\]\[3\]_i_5\(LUT6\) → out_reg\[1\]\[3\]_i_1\(CARRY4 \(S\[3\]→CO\[3\]\)\) → out_reg\[1\]\[7\]_i_1\(CARRY4 \(CI→O\[1\]\)\) → out_reg\[1\]\[5\]/D. The Dominant cell types LUT3, LUT5, LUT6, and CARRY4 create a wide mux tree feeding a 2-stage ripple-carry accumulator.  

Due to synthesis in Vivado the total area is measured as 155 Physical LUT sites and 44 Slices. The top 3 contributers by instance count are LUT6 \(76 instances, per-port output mux/accumulate logic\), LUT5, \(66 instances, intermediate weight-select and MAC tree mapped\), and FDRE \(46 instances, all the synchronous-reset CE registers: 16 weight regs + 30 output regs\). If I assume at 28nm a NAND2 cell ≈ 0.18 µm² and a LUT6 maps to roughly 14 NAND2-equivalent gates in area, I can calculate that the ASIC area would be around 155 LUTs × 14 × 0.18 µm²  +  46 FFs × 0.25 µm² = 390 µm² + 12 µm² ≈ **__400 µm²__**


There was only one DRC violation which has to do with unset bank voltage \(CFGBVS/CONFIG_VOLTAGE\) due to there being no physical pads. There 71 warnings called XDCH-2 — "Same min and max delay on IO port." This is due to the input delay being set for the max setup time and min hold time and can be fixed by setting a minimum delay splits the delay between them.
