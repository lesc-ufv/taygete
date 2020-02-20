/**
 * @company     : Universidade Federal de Viçosa - Florestal
 * @author      : Ruan E. Formigoni (ruanformigoni@gmail.com)
 * @file        : adder-tougaw-4bits
 * @created     : Tuesday May 28, 2019 12:37:37 -03
 * @license     : MIT
 */

module adder_tougaw (i0,i1,cin,sum,cout);
	input i0,i1,cin;
	output sum,cout;

	wire maj0, maj1, maj2;

	assign maj0 =  ( ~i0  & i1   ) | ( ~i0  & cin  ) | ( i1   & cin  ) ;
	assign maj1 =  ( i0   & i1   ) | ( i0   & ~cin ) | ( i1   & ~cin ) ;
	assign maj2 =  ( i0   & ~i1  ) | ( i0   & cin  ) | ( ~i1  & cin  ) ;
	assign cout =  ( i0   & i1   ) | ( i0   & cin  ) | ( i1   & cin  ) ;
	assign sum  =  ( maj0 & maj1 ) | ( maj0 & maj2 ) | ( maj1 & maj2 ) ;
endmodule

module adder_tougaw_4bit (a0,a1,a2,a3,b0,b1,b2,b3,ci0,s0,s1,s2,s3,co0,co1,co2,co3);
	input a0,a1,a2,a3;
	input b0,b1,b2,b3;
	output s0,s1,s2,s3;
	output co0,co1,co2,co3;

	adder_tougaw s0(a0 , b0 , ci0 , s0 , co0);
	adder_tougaw s1(a1 , b1 , co0 , s1 , co1);
	adder_tougaw s2(a2 , b2 , co1 , s2 , co2);
	adder_tougaw s3(a3 , b3 , co2 , s3 , co3);
endmodule
