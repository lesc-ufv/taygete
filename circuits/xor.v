module xorgate (a, b, y);
    input a, b;
    output y;

	wire w0, w1;

    assign w0 = a & ~b;
	assign w1 = ~a & b;
	assign y = w0 | w1;
endmodule
