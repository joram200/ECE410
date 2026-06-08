#!/usr/bin/env python3
"""
gen_waveform.py — Generate annotated waveform PNG from post_m3 VCD
Run from the repo root:
    source /home/sackb/.venv/bin/activate
    python3 project/m4/gen_waveform.py

Parses project/post_m3_Minor_Redesign/sim/cosim_waveform.vcd and produces
project/m4/sim/final_waveform.png showing one complete Kalman update cycle:
  HOST WRITE (z, x_in, P_in via AXI) → KALMAN COMPUTE → HOST READ (x_out, P_out)
"""

import os
import sys

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.ticker import MultipleLocator

# ── Paths ─────────────────────────────────────────────────────────────────────
REPO = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
VCD_FILE = os.path.join(REPO, "project", "post_m3_Minor_Redesign", "sim",
                        "cosim_waveform.vcd")
OUT_PNG  = os.path.join(REPO, "project", "m4", "sim", "final_waveform.png")

# ── VCD identifier → signal name map (from VCD $var declarations) ─────────────
ID_MAP = {
    '!': 'clk',
    '"': 'rst_n',
    '$': 'm_awvalid',
    '%': 'm_awready',
    '(': 'm_wvalid',
    ')': 'm_wready',
    '+': 'm_bvalid',
    ',': 'm_bready',
    '.': 'm_arvalid',
    '/': 'm_arready',
    '2': 'm_rvalid',
    '3': 'm_rready',
    '4': 'core_start',
    '5': 'core_busy',
    '6': 'core_done',
    '7': 'core_rst_n',
}

# ── VCD Parser ────────────────────────────────────────────────────────────────
def parse_vcd(filename):
    """Return dict: signal_name -> (list_of_times_ps, list_of_values_01)."""
    data = {name: ([], []) for name in ID_MAP.values()}
    t = 0
    in_header = True
    with open(filename) as f:
        for raw in f:
            line = raw.strip()
            if not line:
                continue
            if line.startswith('#'):
                t = int(line[1:])
            elif in_header and '$enddefinitions' in line:
                in_header = False
            elif not in_header:
                # Scalar value change: '0!' or '1$' etc.
                if len(line) >= 2 and line[0] in '01xzXZ' and line[1] not in ' ':
                    val_c, ident = line[0], line[1:].split()[0]
                    if ident in ID_MAP:
                        v = 1 if val_c == '1' else 0
                        name = ID_MAP[ident]
                        data[name][0].append(t)
                        data[name][1].append(v)
    return data


def to_step(times_ps, values, t_end_ps):
    """Convert sparse (time, value) pairs to a dense step-function pair.
    Returns (t_ns_array, v_array) suitable for plt.step(where='post')."""
    if not times_ps:
        return [0, t_end_ps / 1000], [0, 0]
    # Prepend t=0 with initial value 0 if not already there
    t_out = [0]
    v_out = [values[0] if times_ps[0] == 0 else 0]
    for t, v in zip(times_ps, values):
        t_out.append(t / 1000)   # ps → ns
        v_out.append(v)
    t_out.append(t_end_ps / 1000)
    v_out.append(v_out[-1])
    return t_out, v_out


# ── Main ──────────────────────────────────────────────────────────────────────
def main():
    print(f"Parsing {VCD_FILE} ...")
    data = parse_vcd(VCD_FILE)

    # Time window: just past reset to end of iteration 1 + small margin
    # Determined from signal inspection:
    #   writes:  85–845 ns   (19 AXI write transactions)
    #   compute: 875–1595 ns (kalman_update FSM + GEMM)
    #   reads:   1595–1975 ns (x_out[3] + P_out[9] + STAT)
    #   iter 2 starts: ~2755 ns
    T_START_NS =    0.0
    T_END_NS   = 2100.0
    T_END_PS   = int(T_END_NS * 1000)

    # Region boundaries (ns) — from VCD inspection
    R_WRITE_START  =   80.0   # first m_awvalid
    R_WRITE_END    =  868.0   # last write response done, just before core_start
    R_COMP_START   =  868.0   # core_start pulse / core_busy rise
    R_COMP_END     = 1598.0   # core_done fall
    R_READ_START   = 1598.0   # first result read begins
    R_READ_END     = 1980.0   # last m_rvalid falls

    # ── Build signal step functions ──────────────────────────────────────────
    sigs = {}
    for name in ('rst_n', 'm_awvalid', 'm_awready', 'm_wvalid', 'm_bvalid',
                 'core_start', 'core_busy', 'core_done',
                 'm_arvalid', 'm_arready', 'm_rvalid'):
        ts, vs = data[name]
        # Clip to window
        ts_c, vs_c = [], []
        prev_v = 0
        for t, v in zip(ts, vs):
            if t / 1000 > T_END_NS:
                break
            ts_c.append(t)
            vs_c.append(v)
            prev_v = v
        sigs[name] = to_step(ts_c, vs_c, T_END_PS)

    # ── Plot ──────────────────────────────────────────────────────────────────
    # Signals to display (top → bottom), with y-offset and label
    rows = [
        ('rst_n',       'rst_n',              0.0),
        ('m_awvalid',   'm_awvalid\n(AW)',     0.0),
        ('m_awready',   'm_awready',           0.0),
        ('m_wvalid',    'm_wvalid\n(W)',        0.0),
        ('m_bvalid',    'm_bvalid\n(B resp)',   0.0),
        ('core_start',  'core_start',          0.0),
        ('core_busy',   'core_busy',           0.0),
        ('core_done',   'core_done',           0.0),
        ('m_arvalid',   'm_arvalid\n(AR)',      0.0),
        ('m_arready',   'm_arready',           0.0),
        ('m_rvalid',    'm_rvalid\n(R)',        0.0),
    ]

    n_rows   = len(rows)
    row_h    = 1.4   # height units per signal
    fig_h    = n_rows * row_h + 1.2
    fig, ax  = plt.subplots(figsize=(16, fig_h))

    # ── Colored region backgrounds ────────────────────────────────────────────
    ax.axvspan(R_WRITE_START, R_WRITE_END, color='#cce5ff', alpha=0.45, zorder=0)
    ax.axvspan(R_COMP_START,  R_COMP_END,  color='#d4edda', alpha=0.45, zorder=0)
    ax.axvspan(R_READ_START,  R_READ_END,  color='#fff3cd', alpha=0.55, zorder=0)

    # ── Region labels at top ──────────────────────────────────────────────────
    y_label = n_rows * row_h + 0.10
    ax.text((R_WRITE_START + R_WRITE_END) / 2, y_label,
            "HOST WRITE\nz, x_in[3], P_in[9]\nR_REG, CTRL.start\n(19 AXI transactions)",
            ha='center', va='bottom', fontsize=8.5, color='#004085',
            fontweight='bold')
    ax.text((R_COMP_START + R_COMP_END) / 2, y_label,
            "KALMAN COMPUTE\nkalman_update FSM\n(51 states) + GEMM\n(21 states)",
            ha='center', va='bottom', fontsize=8.5, color='#155724',
            fontweight='bold')
    ax.text((R_READ_START + R_READ_END) / 2, y_label,
            "HOST READ\nx_out[3], P_out[9]\n(12 AXI transactions\n+ STAT polling)",
            ha='center', va='bottom', fontsize=8.5, color='#856404',
            fontweight='bold')

    # ── Draw each signal as a step waveform ───────────────────────────────────
    COLORS = {
        'rst_n':      '#555555',
        'm_awvalid':  '#0066cc',
        'm_awready':  '#0099cc',
        'm_wvalid':   '#0055aa',
        'm_bvalid':   '#003380',
        'core_start': '#009944',
        'core_busy':  '#00aa33',
        'core_done':  '#007722',
        'm_arvalid':  '#cc6600',
        'm_arready':  '#dd8800',
        'm_rvalid':   '#aa4400',
    }

    for row_idx, (sig_name, label, _) in enumerate(rows):
        y_base = (n_rows - 1 - row_idx) * row_h
        color  = COLORS.get(sig_name, '#333333')

        t_arr, v_arr = sigs[sig_name]

        # Scale 0/1 → y_base / y_base+0.8
        y_lo, y_hi = y_base + 0.05, y_base + 0.85
        v_scaled = [y_lo + (y_hi - y_lo) * v for v in v_arr]

        ax.step(t_arr, v_scaled, where='post', color=color, linewidth=1.4)
        # Fill under high segments
        ax.fill_between(t_arr, y_lo, v_scaled, step='post',
                        color=color, alpha=0.15)

        # Signal label on the left
        ax.text(-15, (y_lo + y_hi) / 2, label,
                ha='right', va='center', fontsize=8, color=color, fontweight='bold')

        # Baseline rule
        ax.axhline(y_lo, color='#cccccc', linewidth=0.4, zorder=0)

    # ── Annotation arrows for key events ─────────────────────────────────────
    # core_start pulse
    core_start_t = 865.0
    cs_row = next(i for i, (s,_,__) in enumerate(rows) if s == 'core_start')
    cs_y   = (n_rows - 1 - cs_row) * row_h + 0.85 + 0.15
    ax.annotate('core_start\npulse',
                xy=(core_start_t, cs_y),
                xytext=(core_start_t + 60, cs_y + 0.6),
                fontsize=7.5, color='#009944',
                arrowprops=dict(arrowstyle='->', color='#009944', lw=1.2))

    # core_done assertion
    core_done_t = 1595.0
    cd_row = next(i for i, (s,_,__) in enumerate(rows) if s == 'core_done')
    cd_y   = (n_rows - 1 - cd_row) * row_h + 0.85 + 0.15
    ax.annotate('core_done\n(72 cycles @ 100 MHz\n= 720 ns)',
                xy=(core_done_t, cd_y),
                xytext=(core_done_t + 50, cd_y + 0.7),
                fontsize=7.5, color='#007722',
                arrowprops=dict(arrowstyle='->', color='#007722', lw=1.2))

    # AXI write burst annotation
    ax.annotate('AXI write burst:\n19 transactions × 40 ns',
                xy=(450, (n_rows - 1 - 1) * row_h + 0.90),
                xytext=(350, (n_rows - 1 - 1) * row_h + 1.55),
                fontsize=7.5, color='#004085',
                arrowprops=dict(arrowstyle='->', color='#004085', lw=1.1))

    # STAT polling annotation (m_arvalid during compute)
    ax.annotate('STAT.busy\npolling',
                xy=(1100, (n_rows - 1 - 8) * row_h + 0.90),
                xytext=(950, (n_rows - 1 - 8) * row_h + 1.7),
                fontsize=7.5, color='#cc6600',
                arrowprops=dict(arrowstyle='->', color='#cc6600', lw=1.1))

    # Result reads annotation
    ax.annotate('Result reads:\nx_out[3] + P_out[9]',
                xy=(1780, (n_rows - 1 - 10) * row_h + 0.90),
                xytext=(1600, (n_rows - 1 - 10) * row_h + 1.7),
                fontsize=7.5, color='#aa4400',
                arrowprops=dict(arrowstyle='->', color='#aa4400', lw=1.1))

    # ── Vertical dividers ─────────────────────────────────────────────────────
    for xv in (R_WRITE_END, R_READ_START):
        ax.axvline(xv, color='#888888', linewidth=0.8, linestyle='--', zorder=1)

    # ── Axes formatting ───────────────────────────────────────────────────────
    ax.set_xlim(T_START_NS - 20, T_END_NS)
    ax.set_ylim(-0.2, n_rows * row_h + 1.8)
    ax.set_xlabel('Time (ns)', fontsize=10)
    ax.set_yticks([])
    ax.xaxis.set_major_locator(MultipleLocator(200))
    ax.xaxis.set_minor_locator(MultipleLocator(50))
    ax.tick_params(axis='x', which='major', labelsize=9)
    ax.grid(axis='x', which='major', color='#dddddd', linewidth=0.5)
    ax.grid(axis='x', which='minor', color='#eeeeee', linewidth=0.3)
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    ax.spines['left'].set_visible(False)

    # ── Title and legend ──────────────────────────────────────────────────────
    fig.suptitle(
        'M4 Final Waveform — Kalman Update Accelerator (post_m3_Minor_Redesign)\n'
        'AXI4-Lite 64-bit @ 100 MHz  |  One complete update: HOST WRITE → COMPUTE → HOST READ  |  '
        'Total ≈ 1.97 µs/update @ 100 MHz (87.8 µs @ 13 MHz SweRV EL2)',
        fontsize=9.5, y=0.995, va='top'
    )

    legend_patches = [
        mpatches.Patch(color='#cce5ff', label='HOST WRITE — 19 AXI write transactions'),
        mpatches.Patch(color='#d4edda', label='KALMAN COMPUTE — 72 FSM states'),
        mpatches.Patch(color='#fff3cd', label='HOST READ — result reads + STAT poll'),
    ]
    ax.legend(handles=legend_patches, loc='upper right', fontsize=8,
              framealpha=0.9, edgecolor='#aaaaaa')

    plt.tight_layout(rect=[0, 0, 1, 0.97])
    os.makedirs(os.path.dirname(OUT_PNG), exist_ok=True)
    fig.savefig(OUT_PNG, dpi=150, bbox_inches='tight')
    print(f"Saved: {OUT_PNG}")
    plt.close(fig)


if __name__ == '__main__':
    main()
