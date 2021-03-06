#include "tests.h"
#include "str_bytes.h"
#include "element_1w_h0h7.h"
#include <stdio.h>

void test_Element_1w_h0h7()
{
	int64_t i;
	int64_t cnt =0 , match=0;
	Element_1w_H0H7 a,b,c,d,e,f;

	printf("===== 1-way =====\n");
	/**
	* Test identity:
	*    (a^2-b^2) == (a+b)(a-b)
	*/
	printf("Test mul/sqr: ");
	cnt = 0;
	for(i=0;i<TEST_TIMES;i++)
	{
		random_Element_1w_h0h7(a);
		random_Element_1w_h0h7(b);

		add_Element_1w_h0h7(e,a,b);
		sub_Element_1w_h0h7(f,a,b);compress_Element_1w_h0h7(f);
		mul_Element_1w_h0h7(e,e,f);
		compress_Element_1w_h0h7(e);

		sqr_Element_1w_h0h7(a);compress_Element_1w_h0h7(a);
		sqr_Element_1w_h0h7(b);compress_Element_1w_h0h7(b);
		sub_Element_1w_h0h7(c, a, b); compress_Element_1w_h0h7(c);

		match = compare_Element_1w_h0h7(c,e)==0;
		if(!match)
		{
			printf("A:\n");print_Element_1w_h0h7(a);
			printf("B:\n");print_Element_1w_h0h7(b);
			break;
		}
		cnt += match;
	}
	printf(" %ld %s\n",cnt , cnt == TEST_TIMES? "OK" : "FAIL" );
#if 1
	/**
	* Test identity:
	*    (a*b*a^1) == b
	*/
	printf("Test mul/inv: ");
	cnt = 0;
	for(i=0;i<TEST_TIMES;i++)
	{
		random_Element_1w_h0h7(a);
		random_Element_1w_h0h7(b);

        inv_Element_1w_h0h7(d,a);
        mul_Element_1w_h0h7(a,a,b);
        compress_Element_1w_h0h7(a);
		mul_Element_1w_h0h7(a,a,d);
		compress_Element_1w_h0h7(a);

		match = compare_Element_1w_h0h7(a,b)==0;
		if(!match)
		{
			printf("A:\n");print_Element_1w_h0h7(a);
			printf("B:\n");print_Element_1w_h0h7(b);
			break;
		}
		cnt += match;
	}
	printf(" %ld %s\n",cnt , cnt == TEST_TIMES? "OK" : "FAIL" );
#endif
}

