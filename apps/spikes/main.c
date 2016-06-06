#include<stdio.h>
#include <str_bytes.h>
#include "element_1w_h0h7.h"

int main()
{
	int i=0;
	printf("=== MAIN === \n");


#if 1 /* === Element 1w ===  */
	printf("=== Element 1w === \n");

	Element_1w_H0H7 a,b,c,d;

	random_Element_1w_h0h7(a);
	random_Element_1w_h0h7(b);

	print_Element_1w_h0h7(a);
	print_Element_1w_h0h7(b);

	add_Element_1w_h0h7(c,a,b);
	printf("add:\n");print_Element_1w_h0h7(c);

	sub_Element_1w_h0h7(d,a,b);
	printf("sub:\n");print_Element_1w_h0h7(d);

	neg_Element_1w_h0h7(a);
	printf("neg:\n");print_Element_1w_h0h7(a);

#endif

	return 0*i;
}
