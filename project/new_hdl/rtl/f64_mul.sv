// f64_mul.sv — Combinational IEEE-754 double-precision multiplier
// Pure always_comb; no clock. Vivado infers DSP48E1 chains for the 53×53 product.
// Special cases: NaN propagation, Inf×0=NaN, zero handling, overflow→Inf.

module f64_mul (
    input  logic [63:0] a,
    input  logic [63:0] b,
    output logic [63:0] result
);

    // Field extraction
    logic        a_sign, b_sign, r_sign;
    logic [10:0] a_exp,  b_exp;
    logic [52:0] a_man,  b_man;   // includes implicit leading 1 (or 0 for denorm)

    assign a_sign = a[63];
    assign b_sign = b[63];
    assign a_exp  = a[62:52];
    assign b_exp  = b[62:52];
    assign a_man  = (a_exp == 11'h0) ? {1'b0, a[51:0]} : {1'b1, a[51:0]};
    assign b_man  = (b_exp == 11'h0) ? {1'b0, b[51:0]} : {1'b1, b[51:0]};

    // Special-case detection
    logic a_nan, b_nan, a_inf, b_inf, a_zero, b_zero;
    assign a_nan  = (a_exp == 11'h7FF) && (a[51:0] != 52'h0);
    assign b_nan  = (b_exp == 11'h7FF) && (b[51:0] != 52'h0);
    assign a_inf  = (a_exp == 11'h7FF) && (a[51:0] == 52'h0);
    assign b_inf  = (b_exp == 11'h7FF) && (b[51:0] == 52'h0);
    assign a_zero = (a_exp == 11'h0)   && (a[51:0] == 52'h0);
    assign b_zero = (b_exp == 11'h0)   && (b[51:0] == 52'h0);

    // 106-bit product (53×53 unsigned)
    logic [105:0] product;
    assign product = {53'b0, a_man} * {53'b0, b_man};

    // Exponent sum (unbiased: ea + eb - 1023)
    // Use 13-bit signed to detect underflow/overflow
    logic signed [12:0] exp_sum;
    assign exp_sum = $signed({2'b00, a_exp}) + $signed({2'b00, b_exp})
                     - $signed(13'd1023);

    // Normalise: if product[105]=1, shift right 1 and inc exp
    logic [51:0] norm_man;
    logic [12:0] norm_exp;
    always_comb begin
        if (product[105]) begin
            norm_man = product[104:53];
            norm_exp = exp_sum + 13'd1;
        end else begin
            norm_man = product[103:52];
            norm_exp = exp_sum;
        end
    end

    // Result sign
    assign r_sign = a_sign ^ b_sign;

    // Final mux — special cases first
    always_comb begin
        if (a_nan || b_nan) begin
            // Propagate NaN (quiet NaN)
            result = 64'h7FF8_0000_0000_0000;
        end else if ((a_inf && b_zero) || (b_inf && a_zero)) begin
            // Inf × 0 = NaN (IEEE 754)
            result = 64'h7FF8_0000_0000_0000;
        end else if (a_inf || b_inf) begin
            // Inf × finite = ±Inf
            result = {r_sign, 11'h7FF, 52'h0};
        end else if (a_zero || b_zero) begin
            // Zero result
            result = {r_sign, 63'b0};
        end else if (norm_exp >= $signed(13'd2047)) begin
            // Overflow → ±Inf
            result = {r_sign, 11'h7FF, 52'h0};
        end else if (norm_exp <= $signed(13'd0)) begin
            // Underflow → signed zero (denorms not supported)
            result = {r_sign, 63'b0};
        end else begin
            // Normal result
            result = {r_sign, norm_exp[10:0], norm_man};
        end
    end

endmodule
