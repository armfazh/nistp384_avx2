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

	STR_BYTES A,B,C;
	random_str_bytes(A);
	random_str_bytes(B);
	print_str_bytes(A);
	print_str_bytes(B);

	str_bytes_To_Element_1w_h0h7(a,A);
	str_bytes_To_Element_1w_h0h7(b,B);
//	printex_Element_1w_h0h7(a);
//	print_python_Element_1w_h0h7(a);
//	singleH0H7_To_str_bytes(B,a);
//	print_str_bytes(B);

//	random_Element_1w_h0h7(a);
//	random_Element_1w_h0h7(b);

//	print_Element_1w_h0h7(a);
//	print_Element_1w_h0h7(b);

//	add_Element_1w_h0h7(c,a,b);
//	printf("add:\n");print_Element_1w_h0h7(c);
//
//	sub_Element_1w_h0h7(d,a,b);
//	printf("sub:\n");
//	sizes_Element_1w_h0h7(d);
//	print_Element_1w_h0h7(d);
//
//	neg_Element_1w_h0h7(a);
//	sizes_Element_1w_h0h7(a);
//	printf("neg:\n");print_Element_1w_h0h7(a);

	mul_Element_1w_h0h7(c,b,a);
	printf("mul:\n");
	printex_Element_1w_h0h7(c);
	sizes_Element_1w_h0h7(c);
	compressfast_Element_1w_h0h7(c);
	sizes_Element_1w_h0h7(c);
	printex_Element_1w_h0h7(c);
	print_Element_1w_h0h7(c);

#endif

	return 0*i;
}
