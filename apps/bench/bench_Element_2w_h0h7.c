#include "element_2w_h0h7.h"
#include "element_1w_h0h7.h"
#include "clocks.h"
#include <stdio.h>

void bench_element_2w_h0h7()
{
	long int BENCH = 3000;
	Element_2w_H0H7 a,b,c;
	Element_1w_H0H7 a0,a1;
	printf("===== 2-way =====\n");

	random_Element_2w_h0h7(a);
	random_Element_2w_h0h7(b);
	random_Element_2w_h0h7(c);

	CLOCKS(interleave(a,a0,a1));
	CLOCKS(deinterleave(a0,a1,a));

	CLOCKS(add_Element_2w_h0h7(c,a,b));
	CLOCKS(sub_Element_2w_h0h7(c,c,b));
//	CLOCKS(addsub_Element_2w_h0h7(c,a,b,0,0));
//	CLOCKS(addsub_Element_2w_h0h7(c,a,b,1,0));
//	CLOCKS(addsub_Element_2w_h0h7(c,a,b,0,1));
//	CLOCKS(addsub_Element_2w_h0h7(c,a,b,1,1));
	/*CLOCKS(subadd_Element_2w_h0h7(c,b,0));
	CLOCKS(subadd_Element_2w_h0h7(c,b,1));
	CLOCKS(addsub_Element_2w_h0h7(c,b));
	CLOCKS(addsub_large_Element_2w_h0h7(c,b));
	CLOCKS(addsub4_Element_2w_h0h7(a,b,c,d));
	CLOCKS(naddsub_Element_2w_h0h7(a,b,c,d));*/


	CLOCKS(mul_schoolbook_2w_h0h7(c,a,b));
	CLOCKS(mul_karatsuba_2w_h0h7(c,a,b));
	CLOCKS(mul_Element_2w_h0h7(c,a,b));
	CLOCKS(mul_Element_2w_h0h7(c,c,b));
	CLOCKS(mul_Element_2w_h0h7(c,b,c));
	CLOCKS(sqr_schoolbook_2w_h0h7(c,a));
	CLOCKS(sqr_karatsuba_2w_h0h7(c,a));
	CLOCKS(sqr_Element_2w_h0h7(c,a));

	CLOCKS(compress_Element_2w_h0h7(c));
	CLOCKS(compress2_Element_2w_h0h7(c,a));
	CLOCKS(new_compressfast_Element_2w_h0h7(c));
	CLOCKS(new_compressfast2_Element_2w_h0h7(c,a));

}
