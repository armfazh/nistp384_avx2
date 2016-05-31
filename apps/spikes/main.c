#include<stdio.h>
#include <str_bytes.h>
#include "element_1w_h0h7.h"

int main()
{
	printf("=== MAIN === \n");


#if 1 /* === Element 1w ===  */
	printf("=== Element 1w === \n");

	STR_BYTES  A;
	random_str_bytes(A);
	Element_1w_H0H7 a,b,c;

	print_str_bytes(A);
	str_bytes_To_Element_1w_h0h7(a,A);
	printex_Element_1w_h0h7(a);
//	random_Element_1w_h0h7(a);
//	random_Element_1w_h0h7(b);
//
//	printex_Element_1w_h0h7(a);
//	print_Element_1w_h0h7(b);

//	add_Element_1w_h0h7(c,a,b);
//	print_Element_1w_h0h7(c);

#endif

	return 0;
}
