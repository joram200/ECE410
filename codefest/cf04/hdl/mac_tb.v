module mac_tb;

    logic        clk;
    logic        rst;
    logic signed [7:0]  a;
    logic signed [7:0]  b;
    logic signed [31:0] out;

    mac dut (
        .clk(clk),
        .rst(rst),
        .a(a),
        .b(b),
        .out(out)
    );

    // 10 ns clock period
    initial clk = 0;
    always #5 clk = ~clk;

    int cycle;
    initial begin
        cycle = 0;
        rst = 1; a = 0; b = 0;

        // Cycle 0: reset
        @(posedge clk); #1;
        cycle++;
        $display("Cycle %0d | rst=%0b a=%0d b=%0d | out=%0d", cycle, rst, a, b, out);

        // Cycles 1-3: a=3, b=4
        rst = 0; a = 3; b = 4;
        repeat (3) begin
            @(posedge clk); #1;
            cycle++;
            $display("Cycle %0d | rst=%0b a=%0d b=%0d | out=%0d", cycle, rst, a, b, out);
        end

        // Assert reset for 1 cycle
        rst = 1;
        @(posedge clk); #1;
        cycle++;
        $display("Cycle %0d | rst=%0b a=%0d b=%0d | out=%0d", cycle, rst, a, b, out);

        // Cycles 5-6: a=-5, b=2
        rst = 0; a = -5; b = 2;
        repeat (2) begin
            @(posedge clk); #1;
            cycle++;
            $display("Cycle %0d | rst=%0b a=%0d b=%0d | out=%0d", cycle, rst, a, b, out);
        end

        $finish;
    end

endmodule
