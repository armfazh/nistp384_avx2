#include<stdio.h>
#include <str_bytes.h>
#include <ecc.h>
#include <pointmul.h>
#include "element_1w_h0h7.h"
#include "element_2w_h0h7.h"

int main()
{
	int i=0;
	printf("=== MAIN === \n");

#if 0 /* === Element 1w ===  */
	printf("=== Element 1w === \n");

	Element_1w_H0H7 a,b,c,d;
	random_Element_1w_h0h7(a);
	random_Element_1w_h0h7(b);
	print_Element_1w_h0h7(a);
	print_Element_1w_h0h7(b);

//	printex_Element_1w_h0h7(a);
//	print_python_Element_1w_h0h7(a);
//	Element_1w_h0h7_To_str_bytes(B,a);
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
//	print_Element_1w_h0h7(c);

//	sqr_Element_1w_h0h7(a);
//	printf("sqr:\n");
//	compress_Element_1w_h0h7(a);
//	print_Element_1w_h0h7(a);


//	for(i=0;i<40;i++)
//		add_Element_1w_h0h7(c,c,a);
//
//	sizes_Element_1w_h0h7(c);
//	new_compressfast_Element_1w_h0h7(c);
//	sizes_Element_1w_h0h7(c);
//	print_Element_1w_h0h7(c);

	inv_Element_1w_h0h7(c,a);
	print_Element_1w_h0h7(c);


#endif

#if 0 /* === Element 2w ===  */
	printf("=== Element 2w === \n");
	Element_2w_H0H7 a,b,c,d;

	random_Element_2w_h0h7(a);
	random_Element_2w_h0h7(b);
	print_Element_2w_h0h7(a);
	print_Element_2w_h0h7(b);

	addsub_Element_2w_h0h7(c,a,b,0,0);
	addsub_Element_2w_h0h7(d,a,b,0,1);
	compress_Element_2w_h0h7(d);
	printf("equal: %s\n",compare_Element_2w_h0h7(c,d)?"yes":"no");

	addsub_Element_2w_h0h7(c,a,b,1,0);
	addsub_Element_2w_h0h7(d,a,b,1,1);
	compress_Element_2w_h0h7(d);
	printf("equal: %s\n",compare_Element_2w_h0h7(c,d)?"yes":"no");

#endif


#if 0 /* 1way ecc-operations  */
	Point_XY_1way G;
	Point_XYZ_1way pP,pQ;

	getGenerator(&G);
	printf("Gxy:\n");print_affine_1way(&G);
	toProjective(&pQ,&G);
	toProjective(&pP,&G);
	printf("Gxyz:\n");print_proj_1way(&pQ);
	_1way_doubling(&pQ);
	printf("2Gxyz:\n");print_proj_1way(&pQ);
	for(i=0;i<1000;i++)
		_1way_full_addition_law(&pP,&pQ);
	printf("3Gxyz:\n");print_proj_1way(&pP);

	/*for(i=0;i<1000;i++)
	_1way_doubling(&pQ);
	printf("2Gxyz:\n");print_proj_1way(&pQ);
	for(i=0;i<1000;i++)
	_1way_mix_addition_law(&pQ,&pP);
	printf("3Gxyz:\n");print_proj_1way(&pQ);
	*/
	/*negatePoint(&pP,&pQ);
	printf("-Gxyz:\n");print_proj_1way(&pP);
	getIdentityProj(&pP);
	printf("0:\n");print_proj_1way(&pP);*/



#endif

#if 0  /* testing w-naf */
	STR_BYTES a;
	ALIGN int8_t exp[392];
	int len;

	random_str_bytes(a);
	for(i=0;i<SIZE_STR_BYTES;i++)
	{
		exp[i] = 0;
	}
	print_str_bytes(a);
	len = wnaf(exp,a,8);
	printf("[");
	for(i=0;i<len;i++)
	{
		printf("%d, ",exp[i]);
	}
	printf("]\n");
#endif

#if 0 /* testing precompute */

	Point_XY_1way P;
	const int num_points = 1<<(OMEGA_DYNAMIC-2);
	Point_XYZ_1way Tab[num_points];

	getGenerator(&P);

	precompute_points(Tab,&P);
	for(i<0;i<num_points;i++)
	{
		printf("%d:\n",2*i+1);
		print_Element_2w_h0h7(Tab[i].XY);
		print_Element_2w_h0h7(Tab[i].ZZ);
	}
#endif

#if 1 /* testing double_point mult */
	Point_XY_1way G, Q, k0G_k1Q;
	const int num_points = 1<<(OMEGA_STATIC-2);
	Point_XYZ_1way TabSta[num_points];

	getGenerator(&G);
	getGenerator(&Q);

	precompute_points(TabSta,&G,OMEGA_STATIC);
	STR_BYTES k0,k1;

	random_str_bytes(k0);
	random_str_bytes(k1);
	printf("k0: ");print_str_bytes(k0);
	printf("k1: ");print_str_bytes(k1);
	double_point_multiplication(&k0G_k1Q,k0,k1,&Q,TabSta);
	print_Element_2w_h0h7(k0G_k1Q.XY);


#endif
	return 0*i;

}
