from PIL import Image, ImageDraw, ImageFont
import os, math

W, H = 1200, 920

# Palette
BG        = (240, 243, 248)
WHITE     = (255, 255, 255)
BLACK     = (25,  25,  30)
GRAY      = (120, 130, 145)
LGRAY     = (200, 208, 220)

# Block colours  (fill, header, border)
C_INIT    = ((232, 240, 255), ( 28,  72, 160), ( 28,  72, 160))
C_PRED    = ((230, 248, 236), ( 18, 120,  60), ( 18, 120,  60))
C_MEAS    = ((255, 244, 224), (190,  80,   5), (190,  80,   5))
C_UPD     = ((252, 234, 220), (160,  45,  10), (160,  45,  10))
C_OUT     = ((235, 235, 255), ( 80,  40, 160), ( 80,  40, 160))

ARROW_COL = (70, 85, 110)

OUT_PATH  = ("/run/media/sackb/Windows-SSD/Users/sackb/OneDrive/Desktop/"
             "University/Course_Work/2025-2026/Spring_2026/ECE_410/ECE410/"
             "project/kalman_filter_diagram.png")

# ── fonts ──────────────────────────────────────────────────────────────────
def font(size, bold=False):
    candidates = [
        f"/usr/share/fonts/TTF/DejaVuSans{'-Bold' if bold else ''}.ttf",
        f"/usr/share/fonts/truetype/dejavu/DejaVuSans{'-Bold' if bold else ''}.ttf",
        "/usr/share/fonts/TTF/DejaVuSansMono.ttf",
    ]
    for p in candidates:
        if os.path.exists(p):
            return ImageFont.truetype(p, size)
    return ImageFont.load_default()

F_HEAD   = font(17, bold=True)
F_LABEL  = font(15, bold=True)
F_CODE   = font(14)
F_SMALL  = font(13)
F_TITLE  = font(22, bold=True)
F_SUB    = font(14)

# ── drawing helpers ────────────────────────────────────────────────────────
def rrect(draw, x0, y0, x1, y1, r, fill, border, bw=2):
    draw.rounded_rectangle([x0, y0, x1, y1], radius=r,
                            fill=fill, outline=border, width=bw)

def text_w(draw, txt, fnt):
    bb = draw.textbbox((0, 0), txt, font=fnt)
    return bb[2] - bb[0]

def ctext(draw, txt, cx, y, fnt, col):
    draw.text((cx - text_w(draw, txt, fnt) // 2, y), txt, font=fnt, fill=col)

def ltext(draw, txt, x, y, fnt, col):
    draw.text((x, y), txt, font=fnt, fill=col)

def arrow_line(draw, pts, col=ARROW_COL, lw=2, head=10):
    for i in range(len(pts) - 1):
        draw.line([pts[i], pts[i+1]], fill=col, width=lw)
    x0, y0 = pts[-2]
    x1, y1 = pts[-1]
    ang = math.atan2(y1 - y0, x1 - x0)
    for da in (0.38, -0.38):
        ax = x1 - head * math.cos(ang - da)
        ay = y1 - head * math.sin(ang - da)
        draw.line([(x1, y1), (int(ax), int(ay))], fill=col, width=lw)

def block(draw, x, y, w, h, colours, title, lines, code_lines=True):
    fill, hdr, bdr = colours
    r = 10
    rrect(draw, x, y, x+w, y+h, r, fill, bdr, bw=2)
    # header bar
    draw.rounded_rectangle([x, y, x+w, y+28], radius=r, fill=hdr)
    draw.rectangle([x, y+14, x+w, y+28], fill=hdr)   # square off bottom of header
    ctext(draw, title, x + w//2, y + 5, F_HEAD, WHITE)
    # body lines
    cy = y + 36
    for txt in lines:
        if txt == "":
            cy += 8; continue
        if txt.startswith("//"):
            ltext(draw, txt, x+14, cy, F_CODE, GRAY)
        else:
            ltext(draw, txt, x+14, cy, F_CODE, BLACK)
        cy += 20

# ── canvas ────────────────────────────────────────────────────────────────
img  = Image.new("RGB", (W, H), BG)
draw = ImageDraw.Draw(img)

# subtle grid
for gx in range(0, W, 40):
    draw.line([(gx, 0), (gx, H)], fill=(230, 234, 242), width=1)
for gy in range(0, H, 40):
    draw.line([(0, gy), (W, gy)], fill=(230, 234, 242), width=1)

# ── title ─────────────────────────────────────────────────────────────────
ctext(draw, "Kalman Filter  --  High-Level Implementation with Eigen (C++)",
      W//2, 16, F_TITLE, (20, 50, 130))
ctext(draw, "State: VectorXd  |  Covariance / System matrices: MatrixXd  |  Loop: Predict -> Update",
      W//2, 46, F_SUB, GRAY)
draw.line([(40, 68), (W-40, 68)], fill=LGRAY, width=2)

# ── block geometry ────────────────────────────────────────────────────────
# INIT  (top-left)
IX, IY, IW, IH = 60,  88, 480, 162

# MEASUREMENT (top-right)
MX, MY, MW, MH = 730, 88, 390, 120

# PREDICT (left-middle)
PX, PY, PW, PH = 60,  318, 430, 200

# UPDATE (right-middle)
UX, UY, UW, UH = 680, 318, 430, 200

# OUTPUT (bottom-centre)
OX, OY, OW, OH = 410, 618, 380, 88

# ── INIT block ────────────────────────────────────────────────────────────
block(draw, IX, IY, IW, IH, C_INIT, "INITIALISE",
      ["x  = VectorXd::Zero(n)          // n-dim state vector",
       "P  = MatrixXd::Identity(n, n)   // error covariance",
       "F  = MatrixXd(n, n)             // state transition",
       "H  = MatrixXd(m, n)             // observation model",
       "Q  = MatrixXd(n, n)             // process noise cov.",
       "R  = MatrixXd(m, m)             // measurement noise cov.",
       "B  = MatrixXd(n, k)             // control-input model"])

# ── MEASUREMENT block ─────────────────────────────────────────────────────
block(draw, MX, MY, MW, MH, C_MEAS, "MEASUREMENT  (sensor input)",
      ["z = VectorXd(m)      // m-dim observation vector",
       "z << sensor_data;",
       "// z fed into Update step each iteration"])

# ── PREDICT block ─────────────────────────────────────────────────────────
block(draw, PX, PY, PW, PH, C_PRED, "PREDICT  (time update)",
      ["// --- Project state ahead ---",
       "x = F * x  +  B * u",
       "",
       "// --- Project covariance ahead ---",
       "P = F * P * F.transpose()  +  Q"])

# ── UPDATE block ──────────────────────────────────────────────────────────
block(draw, UX, UY, UW, UH, C_UPD, "UPDATE  (measurement update)",
      ["// Innovation (residual)",
       "y = z  -  H * x",
       "// Innovation covariance",
       "S = H * P * H.transpose()  +  R",
       "// Optimal Kalman gain",
       "K = P * H.transpose() * S.inverse()",
       "// Corrected state & covariance",
       "x = x  +  K * y",
       "P = (I  -  K * H) * P"])

# ── OUTPUT block ──────────────────────────────────────────────────────────
block(draw, OX, OY, OW, OH, C_OUT, "OUTPUT",
      ["x  -->  filtered state estimate",
       "P  -->  updated error covariance"])

# ── arrows ────────────────────────────────────────────────────────────────
hdr = 28   # header height

# INIT bottom-left -> PREDICT top-left
arrow_line(draw,
    [(IX + IW//4, IY + IH),
     (IX + IW//4, PY - 8),
     (PX + PW//2, PY - 8),
     (PX + PW//2, PY)],
    col=C_INIT[1], lw=2)

# PREDICT right -> UPDATE left
arrow_line(draw,
    [(PX + PW, PY + PH//2),
     (UX,      UY + UH//2)],
    col=ARROW_COL, lw=2)

# MEASUREMENT bottom -> UPDATE top-right
arrow_line(draw,
    [(MX + MW//2, MY + MH),
     (MX + MW//2, UY - 8),
     (UX + UW*3//4, UY - 8),
     (UX + UW*3//4, UY)],
    col=C_MEAS[1], lw=2)

# UPDATE bottom -> OUTPUT
arrow_line(draw,
    [(UX + UW//2, UY + UH),
     (UX + UW//2, OY + OH//2),
     (OX + OW,    OY + OH//2)],
    col=C_UPD[1], lw=2)

# OUTPUT / feedback loop -> PREDICT
loop_y = OY + OH + 36
arrow_line(draw,
    [(OX + OW//2, OY + OH),
     (OX + OW//2, loop_y),
     (PX + PW//2, loop_y),
     (PX + PW//2, PY + PH)],
    col=ARROW_COL, lw=2)

ctext(draw, "next time step  (loop)", (OX + OW//2 + PX + PW//2)//2,
      loop_y + 5, F_SMALL, GRAY)

# ── equations strip ───────────────────────────────────────────────────────
EY = 760
draw.line([(40, EY), (W-40, EY)], fill=LGRAY, width=1)
ctext(draw, "Key equations", W//2, EY + 8, F_LABEL, (50, 50, 80))
eqs = [
    ("Predict:",  "x- = F*x + B*u",            "P- = F*P*Ft + Q"),
    ("Update:",   "K = P-*Ht*(H*P-*Ht + R)-1",  "x = x- + K*(z-H*x-)    P = (I-K*H)*P-"),
]
ey = EY + 32
for label, eq1, eq2 in eqs:
    ltext(draw, label, 60,  ey, F_LABEL, GRAY)
    ltext(draw, eq1,   170, ey, F_CODE,  BLACK)
    ltext(draw, eq2,   600, ey, F_CODE,  BLACK)
    ey += 22

# ── legend ────────────────────────────────────────────────────────────────
LY = 854
items = [
    (C_INIT[1], "Init: state & matrices"),
    (C_PRED[1], "Predict (time update)"),
    (C_MEAS[1], "Measurement input"),
    (C_UPD[1],  "Update (meas. update)"),
    (C_OUT[1],  "Output estimate"),
]
lx = 60
for col, label in items:
    draw.rectangle([lx, LY, lx+16, LY+16], fill=col)
    ltext(draw, label, lx+22, LY, F_SMALL, BLACK)
    lx += 210

img.save(OUT_PATH, dpi=(150, 150))
print(f"Saved: {OUT_PATH}")
