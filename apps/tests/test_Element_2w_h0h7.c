#include "tests.h"
#include "element_2w_h0h7.h"
#include <stdio.h>

void test_Element_2w_h0h7()
{
	int64_t i;
	int64_t cnt =0 , match=0;
	Element_2w_H0H7 a,b,c,e,f;

	printf("===== 2-way =====\n");
	/**
	* Test identity:
	*    (a^2-b^2) == (a+b)(a-b)
	*/
	printf("Test mul/sqr: ");
	cnt = 0;
	for(i=0;i<TEST_TIMES;i++)
	{
		random_Element_2w_h0h7(a);
		random_Element_2w_h0h7(b);

		add_Element_2w_h0h7(e,a,b);
		sub_Element_2w_h0h7(f,a,b);
		compress_Element_2w_h0h7(f);

		mul_Element_2w_h0h7(e,e,f);
		compress_Element_2w_h0h7(e);

		sqr_Element_2w_h0h7(a);
		compress_Element_2w_h0h7(a);
		sqr_Element_2w_h0h7(b);
		compress_Element_2w_h0h7(b);
		sub_Element_2w_h0h7(c, a, b);

		match = compare_Element_2w_h0h7(c, e)==0;
		if(!match)
		{
			printf("A:\n");print_Element_2w_h0h7(a);print_Element_2w_h0h7(c);
			printf("B:\n");print_Element_2w_h0h7(b);print_Element_2w_h0h7(e);
			break;
		}
		cnt += match;
	}
	printf(" %ld %s\n",cnt , cnt == TEST_TIMES? "OK" : "FAIL" );

}
