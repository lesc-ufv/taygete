module adder1bit (a, b, c, soma, carry);
    input a;
    input b;
    input c;
    output soma;
    output carry;

    assign a = c;
    assign carry = a & b;
    assign soma = a ^ b;

endmodule
