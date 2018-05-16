#include "element_1w_h0h7.h"
#include "clocks.h"
#include "str_bytes.h"
#include <stdio.h>

void bench_element_1w_h0h7()
{
	long int BENCH = 3000;
	Element_1w_H0H7 a,b,c,d;
	STR_BYTES A;

	printf("=====  1-way =====\n");

	random_Element_1w_h0h7(a);
	random_Element_1w_h0h7(b);
	random_Element_1w_h0h7(c);
	random_Element_1w_h0h7(d);
	CLOCKS(str_bytes_To_Element_1w_h0h7(a,A));
	CLOCKS(Element_1w_h0h7_To_str_bytes(A, a));
	CLOCKS(add_Element_1w_h0h7(c,a,b));
	CLOCKS(sub_Element_1w_h0h7(c,c,b));
	CLOCKS(addsub_Element_1w_h0h7(a,b));
	CLOCKS(naddsub_Element_1w_h0h7(c,d,a,b));
	CLOCKS(mul_schoolbook_Element_1w_h0h7(c,a,b));
	CLOCKS(mul_karatsuba_1w_h0h7(c,a,b));
	CLOCKS(mul_Element_1w_h0h7(c,a,b));
	CLOCKS(mul_Element_1w_h0h7(c,b,c));
	CLOCKS(mul_Element_1w_h0h7(c,c,b));
	CLOCKS(sqr_schoolbook_1w_h0h7(c));
	CLOCKS(sqr_karatsuba_1w_h0h7(c));
	CLOCKS(sqr_complex_Element_1w_h0h7(c));
	CLOCKS(sqr_Element_1w_h0h7(c));

	CLOCKS(compress_Element_1w_h0h7(c));
	CLOCKS(compressfast_Element_1w_h0h7(c));
	CLOCKS(new_compressfast_Element_1w_h0h7(c));

	BENCH = BENCH/10;
	CLOCKS(inv_Element_1w_h0h7(c,a));

	oper_second(
			random_Element_1w_h0h7(a),
			inv_Element_1w_h0h7(c,a)
	);

}
