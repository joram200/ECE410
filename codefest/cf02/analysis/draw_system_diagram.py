"""
System diagram for the tiled GEMM Kalman filter optimized kernel.
Drawn entirely with Pillow (PIL) — no matplotlib required.
Output: project/m1/system_diagram.png
"""

from PIL import Image, ImageDraw, ImageFont
import os

# ---------------------------------------------------------------------------
# Canvas
# ---------------------------------------------------------------------------
W, H = 1200, 960
img = Image.new("RGB", (W, H), "#F8F9FA")
d   = ImageDraw.Draw(img)

# ---------------------------------------------------------------------------
# Fonts  (fall back gracefully if DejaVu not present)
# ---------------------------------------------------------------------------
def load_font(size, bold=False):
    candidates = [
        f"/usr/share/fonts/TTF/DejaVuSans{'-Bold' if bold else ''}.ttf",
        f"/usr/share/fonts/truetype/dejavu/DejaVuSans{'-Bold' if bold else ''}.ttf",
        f"/usr/share/fonts/dejavu/DejaVuSans{'-Bold' if bold else ''}.ttf",
        "/usr/share/fonts/TTF/LiberationSans-Bold.ttf" if bold else
        "/usr/share/fonts/TTF/LiberationSans-Regular.ttf",
    ]
    for p in candidates:
        if os.path.exists(p):
            return ImageFont.truetype(p, size)
    return ImageFont.load_default()

fnt_title  = load_font(22, bold=True)
fnt_label  = load_font(18, bold=True)
fnt_sub    = load_font(14)
fnt_small  = load_font(12)
fnt_tiny   = load_font(11)

# ---------------------------------------------------------------------------
# Colour palette
# ---------------------------------------------------------------------------
C = {
    "bg"        : "#F8F9FA",
    "chiplet_bg": "#EAF2FB",
    "chiplet_bd": "#2471A3",
    "host_bg"   : "#EBF5EB",
    "host_bd"   : "#1E8449",
    "compute_bg": "#D6EAF8",
    "compute_bd": "#1A5276",
    "mem_bg"    : "#D5F5E3",
    "mem_bd"    : "#1A7A4A",
    "iface_bg"  : "#FEF9E7",
    "iface_bd"  : "#B7950B",
    "arrow"     : "#2C3E50",
    "bw_arrow"  : "#1A5276",
    "red_arrow" : "#C0392B",
    "text_dark" : "#1C2833",
    "text_mid"  : "#2E4053",
    "grid"      : "#D5D8DC",
}

# ---------------------------------------------------------------------------
# Helper: rounded rectangle
# ---------------------------------------------------------------------------
def rrect(draw, box, radius, fill, outline, width=2):
    x0, y0, x1, y1 = box
    draw.rounded_rectangle([x0, y0, x1, y1], radius=radius,
                           fill=fill, outline=outline, width=width)

# ---------------------------------------------------------------------------
# Helper: centred text (multi-line)
# ---------------------------------------------------------------------------
def ctext(draw, cx, cy, lines, fonts, color="#1C2833", spacing=6):
    """lines = list of (text, font) tuples; stacked centred at (cx,cy)."""
    total_h = sum(f.getbbox(t)[3] - f.getbbox(t)[1] for t, f in lines) \
              + spacing * (len(lines) - 1)
    y = cy - total_h // 2
    for text, font in lines:
        bb   = font.getbbox(text)
        tw   = bb[2] - bb[0]
        draw.text((cx - tw // 2, y), text, font=font, fill=color)
        y += (bb[3] - bb[1]) + spacing

# ---------------------------------------------------------------------------
# Helper: horizontal/vertical arrow with label
# ---------------------------------------------------------------------------
def arrow(draw, p1, p2, color, label="", font=None, label_side="top",
          width=3, head=14):
    """Draw a line with an arrowhead at p2."""
    x1, y1 = p1
    x2, y2 = p2
    draw.line([x1, y1, x2, y2], fill=color, width=width)
    # Arrowhead (simple triangle)
    import math
    dx, dy = x2 - x1, y2 - y1
    length = math.hypot(dx, dy)
    if length == 0:
        return
    ux, uy = dx / length, dy / length
    px, py = -uy, ux
    ax1 = (x2 - head * ux + head * 0.4 * px,
           y2 - head * uy + head * 0.4 * py)
    ax2 = (x2 - head * ux - head * 0.4 * px,
           y2 - head * uy - head * 0.4 * py)
    draw.polygon([(x2, y2), ax1, ax2], fill=color)
    if label and font:
        mx, my = (x1 + x2) // 2, (y1 + y2) // 2
        bb  = font.getbbox(label)
        tw  = bb[2] - bb[0]
        th  = bb[3] - bb[1]
        off = 10
        if label_side == "top":
            draw.text((mx - tw // 2, my - th - off), label, font=font, fill=color)
        elif label_side == "bottom":
            draw.text((mx - tw // 2, my + off), label, font=font, fill=color)
        elif label_side == "left":
            draw.text((mx - tw - off, my - th // 2), label, font=font, fill=color)
        elif label_side == "right":
            draw.text((mx + off, my - th // 2), label, font=font, fill=color)

def double_arrow(draw, p1, p2, color, label="", font=None,
                 label_side="top", width=3, head=14):
    arrow(draw, p1, p2, color, label, font, label_side, width, head)
    arrow(draw, p2, p1, color, width=width, head=head)

# ============================================================
# LAYOUT
# ============================================================

# ---- TITLE ----
title = "Optimised Kalman Filter Update Kernel - System Architecture"
bb = fnt_title.getbbox(title)
d.text(((W - (bb[2]-bb[0])) // 2, 18), title, font=fnt_title, fill=C["text_dark"])

# ---- CHIPLET BOUNDARY  (large outer box) ----
CB = (60, 70, W - 60, H - 200)   # (x0,y0,x1,y1)
rrect(d, CB, 16, C["chiplet_bg"], C["chiplet_bd"], width=3)

# "CHIPLET BOUNDARY" label — top-left corner tab
tab_w, tab_h = 230, 32
rrect(d, (CB[0], CB[1] - tab_h + 4, CB[0] + tab_w, CB[1] + 14),
      8, C["chiplet_bd"], C["chiplet_bd"])
d.text((CB[0] + 12, CB[1] - tab_h + 10), "CHIPLET BOUNDARY",
       font=fnt_small, fill="white")

# ---- COMPUTE ENGINE  (left block inside chiplet) ----
CE = (110, 120, 520, 490)
rrect(d, CE, 12, C["compute_bg"], C["compute_bd"], width=2)
ctext(d, (CE[0]+CE[2])//2, (CE[1]+CE[3])//2,
      [("COMPUTE ENGINE",  fnt_label),
       ("Tiled GEMM Kernel",  fnt_sub),
       ("n=3, m=1  |  float64", fnt_tiny),
       ("230 FLOPs / update()", fnt_tiny),
       ("109 GFLOP/s attainable", fnt_tiny)],
      [], color=C["text_dark"])

# Sub-label: pipeline stages inside CE
stages = ["Predict state", "Predict covariance", "Kalman gain",
          "Correct state", "Correct covariance"]
stage_x = CE[0] + 18
stage_y = CE[3] - 120
for i, s in enumerate(stages):
    d.ellipse([stage_x, stage_y + i*20, stage_x+8, stage_y + i*20+8],
              fill=C["compute_bd"])
    d.text((stage_x + 14, stage_y + i*20 - 1), s, font=fnt_tiny,
           fill=C["text_mid"])

# ---- ON-CHIP MEMORY  (right block inside chiplet) ----
OM = (600, 120, 1080, 490)
rrect(d, OM, 12, C["mem_bg"], C["mem_bd"], width=2)

# Memory title
ctext(d, (OM[0]+OM[2])//2, 162,
      [("ON-CHIP MEMORY", fnt_label), ("(SRAM / L1 cache)", fnt_sub)],
      [], color=C["text_dark"])

# Memory contents table
rows = [
    ("Weights",  "A (3x3), C (1x3), Q (3x3), R, I, dt",  "496 B total"),
    ("Inputs",   "x_hat (3x1), P (3x3), y, t",            "112 B"),
    ("Outputs",  "x_hat' (3x1), P' (3x3), K (3x1), t'",   "128 B"),
    ("Capacity", "All tensors fit in L1 (48 KB/core)",     "< 1 KiB used"),
]
row_x0 = OM[0] + 22
row_y  = 215
for cat, contents, size in rows:
    rrect(d, [row_x0, row_y, OM[2]-22, row_y+52], 6,
          "#FDFEFE", C["mem_bd"], width=1)
    d.text((row_x0+10, row_y+6),  cat,      font=fnt_small, fill=C["mem_bd"])
    d.text((row_x0+10, row_y+24), contents, font=fnt_tiny,  fill=C["text_mid"])
    d.text((OM[2]-22-d.textlength(size, font=fnt_tiny)-8, row_y+6),
           size, font=fnt_tiny, fill=C["text_dark"])
    row_y += 62

# ---- BIDIRECTIONAL ARROW: Compute Engine <-> On-chip Memory ----
ay = (CE[1] + CE[3]) // 2
double_arrow(d, (CE[2], ay), (OM[0], ay),
             C["bw_arrow"],
             label="235 GB/s  (L1 BW)",
             font=fnt_sub, label_side="top", width=4, head=16)
# secondary annotation below
bw_label2 = "496 B / 2.11 ns"
bw_x = (CE[2] + OM[0]) // 2
bb2 = fnt_tiny.getbbox(bw_label2)
d.text((bw_x - (bb2[2]-bb2[0])//2, ay + 14), bw_label2,
       font=fnt_tiny, fill=C["bw_arrow"])

# ---- INTERFACE BOX  (below chiplet, above host) ----
IB_cx = W // 2
IB = (IB_cx - 200, CB[3] + 10, IB_cx + 200, CB[3] + 68)
rrect(d, IB, 10, C["iface_bg"], C["iface_bd"], width=2)
ctext(d, IB_cx, (IB[1]+IB[3])//2,
      [("INTERFACE", fnt_label), ("PCIe 4.0 x16  |  ~21.8 GB/s practical", fnt_tiny)],
      [], color=C["text_dark"])

# ---- HOST BOX ----
HB_cx = W // 2
HB = (HB_cx - 240, IB[3] + 10, HB_cx + 240, IB[3] + 110)
rrect(d, HB, 12, C["host_bg"], C["host_bd"], width=2)
ctext(d, HB_cx, (HB[1]+HB[3])//2,
      [("HOST", fnt_label),
       ("Intel Core i7-11800H  |  8c x 4.6 GHz  |  15.4 GiB DDR4", fnt_sub),
       ("Sends: y (measurement, 8 B)    Receives: x_hat', K (32 B)", fnt_tiny)],
      [], color=C["text_dark"])

# ---- ARROW: Chiplet boundary bottom -> Interface ----
cb_bot_cx = W // 2
arrow(d, (cb_bot_cx, CB[3]), (cb_bot_cx, IB[1]),
      C["arrow"], width=3, head=12)

# ---- ARROW: Interface -> Host ----
arrow(d, (cb_bot_cx, IB[3]), (cb_bot_cx, HB[1]),
      C["arrow"], width=3, head=12)

# ---- Vertical annotation on the right of interface arrows ----
ann_x = cb_bot_cx + 230
ann_y1 = CB[3] + 4
ann_y2 = HB[1] - 4
d.line([(ann_x, ann_y1), (ann_x, ann_y2)], fill=C["iface_bd"], width=1)
d.line([(ann_x-4, ann_y1), (ann_x+4, ann_y1)], fill=C["iface_bd"], width=1)
d.line([(ann_x-4, ann_y2), (ann_x+4, ann_y2)], fill=C["iface_bd"], width=1)
ann_mid = (ann_y1 + ann_y2) // 2
ann_txt = "~21.8 GB/s"
bb3 = fnt_tiny.getbbox(ann_txt)
d.text((ann_x + 6, ann_mid - (bb3[3]-bb3[1])//2), ann_txt,
       font=fnt_tiny, fill=C["iface_bd"])

# ---- Arrow: Compute Engine to Interface (down the left side) ----
#  vertical connector on left side
lx = 150
arrow(d, (lx, CE[3]), (lx, CB[3]),
      C["arrow"], width=2, head=10)

# ---- Legend box ----
leg_x, leg_y = CB[0] + 16, CB[3] - 92
legend = [
    (C["compute_bg"], C["compute_bd"], "Compute Engine"),
    (C["mem_bg"],     C["mem_bd"],     "On-chip Memory"),
    (C["iface_bg"],   C["iface_bd"],   "Interface"),
    (C["host_bg"],    C["host_bd"],    "Host"),
]
for i, (bg, bd, lbl) in enumerate(legend):
    lx2 = leg_x + (i % 2) * 195
    ly2 = leg_y + (i // 2) * 26
    rrect(d, [lx2, ly2, lx2+18, ly2+16], 3, bg, bd, width=1)
    d.text((lx2+24, ly2), lbl, font=fnt_tiny, fill=C["text_dark"])

# ---- Data-flow labels on the left connector ----
d.text((CB[0] + 6, (CE[3] + CB[3])//2 - 10), "y, state", font=fnt_tiny, fill=C["arrow"])

# ---- Bandwidth requirement callout ----
bwr_box = (CE[0]+4, CE[3]+8, CE[0]+260, CE[3]+52)
rrect(d, bwr_box, 6, "#FDEDEC", "#C0392B", width=1)
d.text((bwr_box[0]+8, bwr_box[1]+4),
       "Required BW:", font=fnt_tiny, fill="#922B21")
d.text((bwr_box[0]+8, bwr_box[1]+20),
       "473.9 Mupdates/s x 496 B = 235 GB/s", font=fnt_tiny, fill="#922B21")

# ---- Save ----
out_path = ("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/"
            "University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/"
            "project/m1/system_diagram.png")
img.save(out_path, dpi=(150, 150))
print(f"Saved {W}×{H} diagram to:\n  {out_path}")
