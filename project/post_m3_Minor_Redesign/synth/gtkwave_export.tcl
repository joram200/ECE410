# gtkwave_export.tcl — GTKWave Tcl script: export annotated waveform PNG
# Loads AXI write, compute, and AXI read signal groups and marks the three
# transaction regions with comments.
#
# Usage (called from run_m3.sh):
#   gtkwave sim/cosim_waveform.vcd --script synth/gtkwave_export.tcl \
#           -o sim/cosim_waveform.png
#
# Requires GTKWave >= 3.3.100 with Tcl batch mode support.

set dumpfile [lindex $argv 0]
set outfile  [lindex $argv 1]

# Load VCD
gtkwave::loadFile $dumpfile

# Set reasonable zoom: fit first iteration into view
gtkwave::setZoomFactor -10
gtkwave::setLeftJustify 1

# ── Region 1: HOST WRITE (AXI write transactions to A_REG/B_REG) ─────────────
gtkwave::addComment "──── HOST WRITE: z, x_in, P_in via AXI ────"
foreach sig {
    tb_top.m_awvalid
    tb_top.m_awready
    tb_top.m_awaddr
    tb_top.m_wvalid
    tb_top.m_wready
    tb_top.m_wdata
    tb_top.m_bvalid
    tb_top.m_bready
} {
    catch { gtkwave::addSignalsFromList [list $sig] }
}

# ── Region 2: KALMAN COMPUTE ──────────────────────────────────────────────────
gtkwave::addComment "──── KALMAN COMPUTE: core_start → busy → done ────"
foreach sig {
    tb_top.core_start
    tb_top.core_busy
    tb_top.core_done
    tb_top.core_rst_n
} {
    catch { gtkwave::addSignalsFromList [list $sig] }
}

# ── Region 3: HOST READ (AXI read of C_REG / x_out / P_out) ─────────────────
gtkwave::addComment "──── HOST READ: x_out, P_out via AXI ────"
foreach sig {
    tb_top.m_arvalid
    tb_top.m_arready
    tb_top.m_araddr
    tb_top.m_rvalid
    tb_top.m_rready
    tb_top.m_rdata
} {
    catch { gtkwave::addSignalsFromList [list $sig] }
}

# Export PNG
gtkwave::hardcopy $outfile
puts "INFO: Waveform exported to $outfile"
