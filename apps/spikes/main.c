#include<stdio.h>
#include <str_bytes.h>
#include <ecc.h>
#include <pointmul.h>
#include <string.h>
#include "element_1w_h0h7.h"
#include "element_2w_h0h7.h"
extern uint64_t TableSign_w4_36k[NUM_LUT*8*2*6];
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

#if 0  /* testing recoding */
	STR_BYTES a;
	ALIGN int8_t exp[392];
	int len;

	random_str_bytes(a);
	for(i=0;i<SIZE_STR_BYTES;i++)
	{
		exp[i] = 0;
	}
	print_str_bytes(a);
	len = recoding(exp,a,OMEGA_VAR_PMUL);
	printf("[");
	for(i=0;i<len;i++)
	{
		printf("%d, ",exp[i]);
		if (i%8==7)printf("\n");
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

#if 0 /* reading point protected */

	Point_XY_1way P;
	Point_XYZ_1way Q, Tab[1<<(OMEGA_VAR_PMUL-2)];
	int num_points= 1<<(OMEGA_VAR_PMUL-2);

	getGenerator(&P);
	precompute_points(Tab,&P,OMEGA_VAR_PMUL);
//	for(i=0;i<num_points;i++)
//	{
//		printf("%dP\n",2*i+1);
//		print_Element_2w_h0h7(Tab[i].XY);
//		print_Element_2w_h0h7(Tab[i].ZZ);
//	}
	int index = 1;
	printf("%dP\n",index);
	read_point_protected(&Q,index,Tab);
	print_Element_2w_h0h7(Q.XY);
	print_Element_2w_h0h7(Q.ZZ);
	index = -1;
	printf("%dP\n",index);
	read_point_protected(&Q,index,Tab);
	print_Element_2w_h0h7(Q.XY);
	print_Element_2w_h0h7(Q.ZZ);
#endif

#if 0 /* testing variable point mult */
	Point_XY_1way P, kP;
	getGenerator(&P);

	STR_BYTES k;
	random_str_bytes(k);
	printf("k: \n");print_str_bytes(k);
	variable_point_multiplication(&kP,k,&P);
	printf("kP: \n");print_Element_2w_h0h7(kP.XY);

	random_str_bytes(k);
	random_str_bytes(k);
	printf("k: \n");print_str_bytes(k);
	variable_point_multiplication(&kP,k,&P);
	printf("kP: \n");print_Element_2w_h0h7(kP.XY);

#endif

#if 0 /* testing double_point mult */
	Point_XY_1way G, Q, k0G_k1Q;

	getGenerator(&G);
	getGenerator(&Q);
	STR_BYTES k0,k1;
	random_str_bytes(k0);
	random_str_bytes(k1);

	printf("k0: ");print_str_bytes(k0);
	printf("k1: ");print_str_bytes(k1);
	double_point_multiplication(&k0G_k1Q,k0,k1,&Q);
	print_Element_2w_h0h7(k0G_k1Q.XY);

#endif

#if 0 /* testing 2way full addition */
	Point_XYZ_2way P,Q;
	Point_XY_1way G,k0G,k1G,k2G,k3G;
	STR_BYTES k0,k1,k2,k3;
	Element_1w_H0H7 one,x0,y0,x1,y1,x2,y2,x3,y3;


	memset(one,0,sizeof(Element_1w_H0H7));
	one[0] = 1;
	getGenerator(&G);
	random_str_bytes(k0);
	random_str_bytes(k1);
	random_str_bytes(k2);
	random_str_bytes(k3);
	variable_point_multiplication(&k0G,k0,&G);
	variable_point_multiplication(&k1G,k1,&G);
	variable_point_multiplication(&k2G,k2,&G);
	variable_point_multiplication(&k3G,k3,&G);

	deinterleave(x0,y0,k0G.XY);
	deinterleave(x1,y1,k1G.XY);
	deinterleave(x2,y2,k2G.XY);
	deinterleave(x3,y3,k3G.XY);

	interleave(P.X,x0,x1);
	interleave(P.Y,y0,y1);
	interleave(P.Z,one,one);
	interleave(Q.X,x2,x3);
	interleave(Q.Y,y2,y3);
	interleave(Q.Z,one,one);

	printf("P.X:\n");print_Element_2w_h0h7(P.X);
	printf("P.Y:\n");print_Element_2w_h0h7(P.Y);
	printf("P.Z:\n");print_Element_2w_h0h7(P.Z);

	printf("Q.X:\n");print_Element_2w_h0h7(Q.X);
	printf("Q.Y:\n");print_Element_2w_h0h7(Q.Y);
	printf("Q.Z:\n");print_Element_2w_h0h7(Q.Z);
	for(i=0;i<100;i++)
		_2way_full_addition_law(&P,&Q);
	printf("P+Q.X:\n");print_Element_2w_h0h7(P.X);
	printf("P+Q.Y:\n");print_Element_2w_h0h7(P.Y);
	printf("P+Q.Z:\n");print_Element_2w_h0h7(P.Z);

#endif

#if 0  /* Query to table for fixed point multiplication */

	Point_XYZ_1way P;
	int index;
	i = 14;
	uint8_t *Table = (uint8_t *)TableSign_w4_36k+SIZE_ONE_LUT*i;

	index = -5;
	query_table(&P,Table,index);
	printf("P.XY:\n");
	print_Element_2w_h0h7(P.XY);
	print_Element_2w_h0h7(P.ZZ);

#endif

#if 1 /* Fixed point mult */
	Point_XY_1way kP;
	STR_BYTES k={
			0x11,0x8f,0x32,0x38,0x56,0x91,0xe8,0xb2,
			0x0c,0x9a,0x45,0x93,0x74,0x91,0x3c,0x53,
			0x73,0x4f,0x04,0x19,0xa1,0x4f,0x8e,0x8f,
			0xd0,0x67,0x6f,0x82,0xde,0xdd,0x6e,0x25,
			0x92,0x88,0x31,0x2f,0xae,0x9e,0x77,0x66,
			0xc7,0x94,0x02,0x66,0x93,0x80,0x46,0x0f
	};
	int8_t K[98],len;

	printf("k:\n");print_str_bytes(k);
	len = recoding_signed_scalar_w4(K,k);
	for(i=0;i<96;i++)
	{
		printf("%d, ",K[i]);
		if(i%24==23)printf(" \n");
	}
	if(len)
	printf("%d \n",K[i]);
	fixed_point_multiplication(&kP, k);
	printf("P.XY:\n");
	print_Element_2w_h0h7(kP.XY);

#endif
	return 0*i;

}
