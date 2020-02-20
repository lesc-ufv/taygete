module adder_tougaw_4bit ( 
    a0, a1, a2, a3, b0, b1, b2, b3,
    s0, s1, s2, s3, co0, co1, co2, co3  );
  input  a0, a1, a2, a3, b0, b1, b2, b3;
  output s0, s1, s2, s3, co0, co1, co2, co3;
  wire carry , new_n35_, new_n36_, new_n37_,
    new_n43_, new_n44_, new_n45_, new_n51_, new_n52_, new_n53_, new_n59_,
    new_n60_, new_n61_;
  assign carry  = 1'b0;
  assign new_n35_ = (~a0 & b0) | (~a0 & carry ) | (b0 & carry );
  assign new_n36_ = (a0 & b0) | (a0 & ~carry ) | (b0 & ~carry );
  assign new_n37_ = (a0 & ~b0) | (a0 & carry ) | (~b0 & carry );
  assign co0 = (b0 & carry ) | (a0 & b0) | (a0 & carry );
  assign s0 = (new_n36_ & new_n37_) | (new_n35_ & new_n36_) | (new_n35_ & new_n37_);
  assign new_n43_ = (~a1 & b1) | (~a1 & co0) | (b1 & co0);
  assign new_n44_ = (a1 & b1) | (a1 & ~co0) | (b1 & ~co0);
  assign new_n45_ = (a1 & ~b1) | (a1 & co0) | (~b1 & co0);
  assign co1 = (b1 & co0) | (a1 & b1) | (a1 & co0);
  assign s1 = (new_n44_ & new_n45_) | (new_n43_ & new_n44_) | (new_n43_ & new_n45_);
  assign new_n51_ = (~a2 & b2) | (~a2 & co1) | (b2 & co1);
  assign new_n52_ = (a2 & b2) | (a2 & ~co1) | (b2 & ~co1);
  assign new_n53_ = (a2 & ~b2) | (a2 & co1) | (~b2 & co1);
  assign co2 = (b2 & co1) | (a2 & b2) | (a2 & co1);
  assign s2 = (new_n52_ & new_n53_) | (new_n51_ & new_n52_) | (new_n51_ & new_n53_);
  assign new_n59_ = (~a3 & b3) | (~a3 & co2) | (b3 & co2);
  assign new_n60_ = (a3 & b3) | (a3 & ~co2) | (b3 & ~co2);
  assign new_n61_ = (a3 & ~b3) | (a3 & co2) | (~b3 & co2);
  assign co3 = (b3 & co2) | (a3 & b3) | (a3 & co2);
  assign s3 = (new_n60_ & new_n61_) | (new_n59_ & new_n60_) | (new_n59_ & new_n61_);
endmodule


