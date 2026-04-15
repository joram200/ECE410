According to profiling results in project_profile.txt, the function kf.update is the computationally dominant kernal, accounting for 2.22% of total runtime.

---

## Arithmetic Intensity: Kalman Filter `update()`

**Source:** <https://github.com/hmartiro/kalman-cpp>  
**State dim:** n = 3 | **Measurement dim:** m = 1 | **dtype:** float64 (8 B/element)

---

### FLOPs per `update()` Call

**Matmul formula:** `(p×q)·(q×r)` → `p·r·(2q−1)` FLOPs  
**Add/sub formula:** `(p×q)` element-wise → `p·q` FLOPs

| Step | Expression | Shape | General Formula | Substituted (n=3, m=1) | FLOPs |
|------|-----------|-------|----------------|------------------------|-------|
| 1 | `A @ x_hat` | (n,n)·(n,1) | n(2n−1) | 3(5) | **15** |
| 2a | `A @ P` | (n,n)·(n,n) | n²(2n−1) | 9(5) | **45** |
| 2b | `AP @ Aᵀ` | (n,n)·(n,n) | n²(2n−1) | 9(5) | **45** |
| 2c | `APAT + Q` | (n,n) add | n² | 9 | **9** |
| 3a | `C @ P` | (m,n)·(n,n) | mn(2n−1) | 1·3·5 | **15** |
| 3b | `CP @ Cᵀ` | (m,n)·(n,m) | m²(2n−1) | 1(5) | **5** |
| 3c | `CPCT + R` | (m,m) add | m² | 1 | **1** |
| 3d | `P @ Cᵀ` | (n,n)·(n,m) | nm(2n−1) | 3·1·5 | **15** |
| 3e | `inv(S)` | (1,1) | 1 div | 1 | **1** |
| 3f | `PCT @ S⁻¹` | (n,m)·(m,m) | nm(2m−1) | 3·1·1 | **3** |
| 4a | `C @ x̂_new` | (m,n)·(n,1) | m(2n−1) | 1(5) | **5** |
| 4b | `y − Cx̂` | (m,1) sub | m | 1 | **1** |
| 4c | `K @ innov` | (n,m)·(m,1) | n(2m−1) | 3(1) | **3** |
| 4d | `x̂_new +=` | (n,1) add | n | 3 | **3** |
| 5a | `K @ C` | (n,m)·(m,n) | n²(2m−1) | 9(1) | **9** |
| 5b | `I − KC` | (n,n) sub | n² | 9 | **9** |
| 5c | `IKC @ P` | (n,n)·(n,n) | n²(2n−1) | 9(5) | **45** |
| 7 | `t += dt` | scalar | 1 | 1 | **1** |
| | **Total** | | | | **230** |

---

### Memory Traffic — DRAM No-Reuse (Worst Case)

Every read comes from DRAM; every write goes to DRAM — no register or cache reuse between operations.  
Element size = 8 B (float64); tensor size (B) = elements × 8.

#### Weights (read-only model parameters)

| Operand | Shape | Elements | Accesses | Bytes/access | Total reads |
|---------|-------|----------|----------|--------------|-------------|
| A | n×n = 3×3 | 9 → 72 B | ×3 (steps 1, 2a, 2b) | 72 B | 216 B |
| C | m×n = 1×3 | 3 → 24 B | ×5 (steps 3a, 3b, 3d, 4a, 5a) | 24 B | 120 B |
| Q | n×n = 3×3 | 9 → 72 B | ×1 (step 2c) | 72 B | 72 B |
| R | m×m = 1×1 | 1 → 8 B | ×1 (step 3c) | 8 B | 8 B |
| I | n×n = 3×3 | 9 → 72 B | ×1 (step 5b) | 72 B | 72 B |
| dt | scalar | 1 → 8 B | ×1 (step 7) | 8 B | 8 B |
| **Subtotal** | | | | | **496 B** |

#### Inputs (per-call dynamic reads, first access only)

| Operand | Shape | Elements | Read at step | Bytes |
|---------|-------|----------|-------------|-------|
| x_hat (prior state) | n×1 = 3×1 | 3 → 24 B | 1 | 24 B |
| P (prior covariance) | n×n = 3×3 | 9 → 72 B | 2a (initial read) | 72 B |
| y (measurement) | m×1 = 1×1 | 1 → 8 B | 4b | 8 B |
| t (time) | scalar | 1 → 8 B | 7 | 8 B |
| **Subtotal** | | | | **112 B** |

#### Outputs (final writes to DRAM)

| Operand | Shape | Elements | Written at step | Bytes |
|---------|-------|----------|----------------|-------|
| x_hat (updated state) | n×1 = 3×1 | 3 → 24 B | 6 | 24 B |
| P (updated covariance) | n×n = 3×3 | 9 → 72 B | 5c (final write) | 72 B |
| K (Kalman gain) | n×m = 3×1 | 3 → 24 B | 3f | 24 B |
| t (updated time) | scalar | 1 → 8 B | 7 | 8 B |
| **Subtotal** | | | | **128 B** |

#### Intermediates (temporary buffers + mid-kernel state re-accesses)

| Operand | Shape | Traffic | Bytes/elem | Total |
|---------|-------|---------|------------|-------|
| x_hat_new | n×1 | 2W (steps 1, 4d) + 3R (steps 4a, 4d, 6) | 24 B | 120 B |
| AP | n×n | 1W + 1R | 72 B | 144 B |
| APAT | n×n | 1W + 1R | 72 B | 144 B |
| P re-accesses | n×n | 1W (step 2c) + 3R (steps 3a, 3d, 5c) after initial read | 72 B | 288 B |
| CP | m×n | 1W + 1R | 24 B | 48 B |
| CPCT | m×m | 1W + 1R | 8 B | 16 B |
| S | m×m | 1W + 1R | 8 B | 16 B |
| PCT | n×m | 1W + 1R | 24 B | 48 B |
| S_inv | m×m | 1W + 1R | 8 B | 16 B |
| Cx | m×1 | 1W + 1R | 8 B | 16 B |
| innov | m×1 | 1W + 1R | 8 B | 16 B |
| K re-reads | n×m | 2R (steps 4c, 5a) after output write | 24 B | 48 B |
| Kinnov | n×1 | 1W + 1R | 24 B | 48 B |
| KC | n×n | 1W + 1R | 72 B | 144 B |
| IKC | n×n | 1W + 1R | 72 B | 144 B |
| **Subtotal** | | | | **1256 B** |

#### Traffic Summary

| Category | Bytes |
|----------|-------|
| Weights (reads) | 496 B |
| Inputs (reads) | 112 B |
| Outputs (writes) | 128 B |
| Intermediates (reads + writes) | 1256 B |
| **Total** | **1992 B** |

---

### Arithmetic Intensity

**AI (DRAM no-reuse) = 230 FLOPs / 1992 B = 0.1155 FLOPs/byte**

| Model | Bytes | AI (FLOPs/byte) |
|-------|-------|-----------------|
| DRAM no-reuse (this analysis) | 1992 B | **0.1155** |
| Naive (numpy, all temps to DRAM) | 1168 B | 0.1969 |
| Ideal (temps in registers/cache) | 496 B | 0.4637 |

---

### Interpretation

All models yield AI ≪ 1 FLOPs/byte, placing the kernel firmly in the **memory-bound** region of the Roofline model. The two dominant sources of DRAM traffic under no-reuse are:

- **A** re-loaded 3×: 3 × 72 B = 216 B
- **P** accessed 6× (4R + 2W): 6 × 72 B = 432 B (including intermediate write)

Together these two tensors account for **648 B — 32.5%** of total traffic.

---

Using Claude to calculate the arthimetic intensity, as shown above, gives 0.1155 FLOPs/byte.
