module adder4_tb;
    reg  [3:0] a, b;
    reg        cin;
    wire [3:0] sum;
    wire       cout;

    adder4 uut (
        .a(a), .b(b), .cin(cin),
        .sum(sum), .cout(cout)
    );

    task check;
        input [3:0] ta, tb;
        input       tc;
        input [4:0] expected;
        begin
            a = ta; b = tb; cin = tc;
            #10;
            if ({cout, sum} !== expected) begin
                $display("FAIL: %0d + %0d + %0d = %0d (expected %0d)",
                         ta, tb, tc, {cout, sum}, expected);
            end else begin
                $display("PASS: %0d + %0d + %0d = %0d", ta, tb, tc, {cout, sum});
            end
        end
    endtask

    initial begin
        $dumpfile("adder4.vcd");
        $dumpvars(0, adder4_tb);

        // Basic cases
        check(4'd0,  4'd0,  1'b0, 5'd0);
        check(4'd1,  4'd1,  1'b0, 5'd2);
        check(4'd7,  4'd8,  1'b0, 5'd15);
        check(4'd8,  4'd8,  1'b0, 5'd16);   // carry-out
        check(4'd15, 4'd15, 1'b1, 5'd31);   // max with carry-in
        check(4'd15, 4'd15, 1'b0, 5'd30);
        check(4'd0,  4'd0,  1'b1, 5'd1);    // carry-in only

        $finish;
    end
endmodule
