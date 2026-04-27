module mac (
    input  logic             clk,
    input  logic             rst,
    input  logic signed [7:0] a,
    input  logic signed [7:0] b,
    output logic signed [31:0] out
);

    logic signed [31:0] acc_reg;

    always_ff @(posedge clk) begin
        if (rst)
            acc_reg <= 32'sd0;
        else
            acc_reg <= acc_reg + (a * b);
    end

    assign out = acc_reg;

endmodule
