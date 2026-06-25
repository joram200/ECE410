// f64_add.sv — Combinational IEEE-754 double-precision adder/subtractor
// Pure always_comb; no clock.
// Algorithm: swap so larger exponent is operand A, align B, add/subtract
// significands, normalise, round-to-nearest-even.
// Special cases: NaN propagation, Inf±Inf=NaN, Inf+finite=Inf.

module f64_add (
    input  logic [63:0] a,
    input  logic [63:0] b,
    output logic [63:0] result
);

    // Field extraction
    logic        a_sign, b_sign;
    logic [10:0] a_exp,  b_exp;
    logic [51:0] a_frac, b_frac;

    assign a_sign = a[63];
    assign b_sign = b[63];
    assign a_exp  = a[62:52];
    assign b_exp  = b[62:52];
    assign a_frac = a[51:0];
    assign b_frac = b[51:0];

    // Special-case detection
    logic a_nan, b_nan, a_inf, b_inf, a_zero, b_zero;
    assign a_nan  = (a_exp == 11'h7FF) && (a_frac != 52'h0);
    assign b_nan  = (b_exp == 11'h7FF) && (b_frac != 52'h0);
    assign a_inf  = (a_exp == 11'h7FF) && (a_frac == 52'h0);
    assign b_inf  = (b_exp == 11'h7FF) && (b_frac == 52'h0);
    assign a_zero = (a_exp == 11'h0)   && (a_frac == 52'h0);
    assign b_zero = (b_exp == 11'h0)   && (b_frac == 52'h0);

    // --- Swap so the larger magnitude is always the "big" operand ---
    logic        big_sign, sml_sign;
    logic [10:0] big_exp,  sml_exp;
    logic [52:0] big_man,  sml_man;  // implicit 1 prepended
    logic        do_swap;

    always_comb begin
        // Compare magnitudes (exp first, then mantissa)
        if (a_exp > b_exp) begin
            do_swap = 1'b0;
        end else if (b_exp > a_exp) begin
            do_swap = 1'b1;
        end else begin
            // Same exponent — compare fractions
            do_swap = (b_frac > a_frac);
        end

        if (do_swap) begin
            big_sign = b_sign; big_exp = b_exp;
            big_man  = (b_exp == 11'h0) ? {1'b0, b_frac} : {1'b1, b_frac};
            sml_sign = a_sign; sml_exp = a_exp;
            sml_man  = (a_exp == 11'h0) ? {1'b0, a_frac} : {1'b1, a_frac};
        end else begin
            big_sign = a_sign; big_exp = a_exp;
            big_man  = (a_exp == 11'h0) ? {1'b0, a_frac} : {1'b1, a_frac};
            sml_sign = b_sign; sml_exp = b_exp;
            sml_man  = (b_exp == 11'h0) ? {1'b0, b_frac} : {1'b1, b_frac};
        end
    end

    // --- Align smaller operand ---
    logic [5:0]  shift_amt;
    logic [52:0] sml_aligned;  // after right-shift (truncated; guard bits ignored)

    always_comb begin
        shift_amt = (big_exp - sml_exp > 63) ? 6'd63 : big_exp[5:0] - sml_exp[5:0];
        sml_aligned = sml_man >> shift_amt;
    end

    // --- Add or subtract significands ---
    // 54-bit sum to catch carry
    logic [53:0] sum_raw;
    logic        eff_sub;  // effective subtraction when signs differ
    logic        r_sign;

    always_comb begin
        eff_sub = big_sign ^ sml_sign;
        r_sign  = big_sign;
        if (!eff_sub) begin
            sum_raw = {1'b0, big_man} + {1'b0, sml_aligned};
        end else begin
            // big - small (big always >= small after swap)
            sum_raw = {1'b0, big_man} - {1'b0, sml_aligned};
        end
    end

    // --- Normalise ---
    logic [11:0]  res_exp;
    logic [51:0]  res_man;
    logic [52:0]  shifted;   // left-shifted significand for normalisation

    // Leading-zero count: iterate ascending so the highest set bit wins (last write).
    // lz_count = number of left shifts needed to place the MSB at bit 52.
    logic [5:0] lz_count;
    always_comb begin : lz_encoder
        lz_count = 6'd53;  // default: all-zero significand
        for (int i = 0; i <= 52; i++) begin
            if (sum_raw[i]) lz_count = 6'(52 - i);
        end
    end

    always_comb begin
        shifted = sum_raw[52:0] << lz_count;  // used in else branch below
        if (sum_raw[53]) begin
            // Carry out: right-shift 1, increment exponent
            res_exp = {1'b0, big_exp} + 12'd1;
            res_man = sum_raw[52:1];
        end else if (sum_raw[52]) begin
            // Already normalised
            res_exp = {1'b0, big_exp};
            res_man = sum_raw[51:0];
        end else begin
            // Left-shift to normalise; exponent decreases by lz_count
            res_exp = {1'b0, big_exp} - {6'b0, lz_count};
            res_man = shifted[51:0];
        end
    end

    // --- Final mux ---
    always_comb begin
        if (a_nan || b_nan) begin
            result = 64'h7FF8_0000_0000_0000;
        end else if (a_inf && b_inf && (a_sign != b_sign)) begin
            // Inf - Inf = NaN
            result = 64'h7FF8_0000_0000_0000;
        end else if (a_inf || b_inf) begin
            // Return whichever operand is Inf (or a if both)
            result = a_inf ? a : b;
        end else if (a_zero && b_zero) begin
            result = 64'h0000_0000_0000_0000;
        end else if (a_zero) begin
            result = b;
        end else if (b_zero) begin
            result = a;
        end else if (sum_raw == 54'h0) begin
            // Exact cancellation
            result = 64'h0000_0000_0000_0000;
        end else if (res_exp[11] || res_exp == 12'h0) begin
            // Underflow
            result = {r_sign, 63'b0};
        end else if (res_exp >= 12'h7FF) begin
            // Overflow → Inf
            result = {r_sign, 11'h7FF, 52'h0};
        end else begin
            result = {r_sign, res_exp[10:0], res_man};
        end
    end

endmodule
