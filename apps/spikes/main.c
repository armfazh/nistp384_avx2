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
//	random_str_bytes(A);
//	random_str_bytes(B);
//	print_str_bytes(A);
//	print_str_bytes(B);
//
//	str_bytes_To_Element_1w_h0h7(a,A);
//	str_bytes_To_Element_1w_h0h7(b,B);
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

//	mul_Element_1w_h0h7(c,b,a);
//	printf("mul:\n");
//	compress_Element_1w_h0h7(c);
//
//	for(i=0;i<40;i++)
//		add_Element_1w_h0h7(c,c,a);
//
//	sizes_Element_1w_h0h7(c);
//	new_compressfast_Element_1w_h0h7(c);
//	sizes_Element_1w_h0h7(c);
//	print_Element_1w_h0h7(c);

	Element_1w_H0H7 e,f;
	random_Element_1w_h0h7(a);
	random_Element_1w_h0h7(b);
	printf("a: ");print_Element_1w_h0h7(a);
	printf("b: ");print_Element_1w_h0h7(b);

	add_Element_1w_h0h7(e,a,b);
	sub_Element_1w_h0h7(f,a,b);compress_Element_1w_h0h7(f);

	printf("e: ");print_Element_1w_h0h7(e);
	printf("f: ");print_Element_1w_h0h7(f);

	mul_Element_1w_h0h7(e,e,f);
	compress_Element_1w_h0h7(e);

	printf("e*f: ");print_Element_1w_h0h7(e);

	sqr_Element_1w_h0h7(a);compress_Element_1w_h0h7(a);
	printf("a^2: ");print_Element_1w_h0h7(a);
	sqr_Element_1w_h0h7(b);compress_Element_1w_h0h7(b);
	printf("b^2: ");print_Element_1w_h0h7(b);
	sub_Element_1w_h0h7(c, a, b); compress_Element_1w_h0h7(c);

	printf("Pass: %d\n",compare_Element_1w_h0h7(c,e));

#endif

	return 0*i;
}
