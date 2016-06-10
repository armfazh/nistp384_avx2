#include <stdio.h>
#include "ecc.h"

static const uint64_t BASE_G [2*NUM_WORDS_64B_NISTP384]= {
		0x2760ab7,0x8ba79b9,0x0ea0e5f,0x289a147,
		0x545e387,0xe1d3b62,0x431d7c9,0x8f41dbd,
		0x5296c3a,0x20ad746,0xe819d7a,0x92dc29f,
		0xf25dbf5,0x1c71ef3,0xb1ce1d7,0xe98bf92,
		0xa385502,0x05378eb,0x8c00a60,0x2c6f5d9,
		0xe082542,0xa22be8b,0x13b5f0b,0xe4a9626,
		0x859f741,0x00aa87c,0xce9da31,0x003617d
};
static const uint64_t ECC_PARAM_B [2*NUM_WORDS_64B_NISTP384]= {
		0x3ec2aef,0xfe81411,0x3ec2aef,0xfe81411,
		0x85c8edd,0x81d9c6e,0x85c8edd,0x81d9c6e,
		0xed19d2a,0xf82d191,0xed19d2a,0xf82d191,
		0x398d8a2,0xe056be3,0x398d8a2,0xe056be3,
		0x75ac656,0xe7e4988,0x75ac656,0xe7e4988,
		0x8f50138,0xfa7e23e,0x8f50138,0xfa7e23e,
		0x2031408,0x00b3312,0x2031408,0x00b3312
};

void getGenerator(Point_XY_1way *G)
{
	int i;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		G->XY[i] = LOAD(BASE_G+i);
	}
}

void toAffine(Point_XY_1way *aP, Point_XYZ_1way *pP)
{
	Element_1w_H0H7 invZ,Z;
	Element_2w_H0H7 invZ_2w;
	deinterleave(Z,invZ,pP->ZZ);
	inv_Element_1w_h0h7(invZ,Z);
	interleave(invZ_2w,invZ,invZ);
	mul_Element_2w_h0h7(aP->XY,invZ_2w,pP->XY);
	compress_Element_2w_h0h7(aP->XY);
}

void toProjective(Point_XYZ_1way *pP, Point_XY_1way *aP)
{
	int i;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		pP->XY[i] = aP->XY[i];
		pP->ZZ[i] = _mm256_setzero_si256();
	}
	pP->ZZ[0] = _mm256_set_epi64x(0,1,0,1);
}
void print_affine_1way(Point_XY_1way* P)
{
	print_Element_2w_h0h7(P->XY);
}
void print_proj_1way(Point_XYZ_1way* P)
{
	Element_1w_H0H7 Z,_;
	print_Element_2w_h0h7(P->XY);
	deinterleave(Z,_,P->ZZ);
	print_Element_1w_h0h7(Z);
}



/**
 *
 */
void _2way_full_addition_law(PointXYZ_2way * Q,  PointXYZ_2way *P)
{
//	__m256i * X1 = Q->X; __m256i * X2 = P->X;
//	__m256i * Y1 = Q->Y; __m256i * Y2 = P->Y;
//	__m256i * Z1 = Q->Z; __m256i * Z2 = P->Z;

}

/**
 *
 */
void _2way_mix_addition_law(PointXYZ_2way *Q, Point_XY_2way *P)
{
//	__m256i * X1 = Q->X;
//	__m256i * Y1 = Q->Y;
//	__m256i * Z1 = Q->Z;
//	__m256i * X2 = P->X;
//	__m256i * Y2 = P->Y;

}

/**
 *
 */
void _2way_doubling(PointXYZ_2way *P)
{
//	__m256i * X1 = P->X;
//	__m256i * Y1 = P->Y;
//	__m256i * Z1 = P->Z;

}

/**
 *
 */
void _1way_full_addition_law(Point_XYZ_1way * Q, Point_XYZ_1way *P)
{
//	uint64_t * XY1 = Q->XY; uint64_t * XY2 = P->XY;
//	uint64_t * Z1 = Q->Z; 	uint64_t * Z2 = P->Z;

}

/**
 *
 */
void _1way_mix_addition_law(Point_XYZ_1way * Q, Point_XY_1way *P)
{
	int i;
	argElement_2w_H0H7 XY1 = Q->XY;	argElement_2w_H0H7 XY2 = P->XY;
	argElement_2w_H0H7 ZZ1 = Q->ZZ;
	argElement_2w_H0H7 BB = (argElement_2w_H0H7)ECC_PARAM_B;

	Element_2w_H0H7 XZ1,YZ1,YX2;
	Element_2w_H0H7 p0q0,p1q1,p2q2,p3q3,p4q4,p5q5,p6q6,q6p6;
	Element_2w_H0H7 Z1r2,r2q2,p2p0,p3r3,l4r0,p1l0,l6r0,p5p4,q5q4;
	Element_2w_H0H7 l0r0,l1r1,l2r2,l3r3,l4r4,l5r5,l6r6,l7r7,l8r8,l5r1;

	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		XZ1[i] = BLEND32(XY1[i],ZZ1[i],0xF0);
		YZ1[i] = PERM128(XY1[i],ZZ1[i],0x21);
		YX2[i] = PERM64(XY2[i],0x4E);
	}

/*	p0 = X1*X2;     q0 = Z1*Y2*/
	mul_Element_2w_h0h7(p0q0,XZ1,XY2);
	compress_Element_2w_h0h7(p0q0);
/*	p1 = Y1*Y2;     q1 = Z1*X2*/
	mul_Element_2w_h0h7(p1q1,YZ1,YX2);
	compress_Element_2w_h0h7(p1q1);

//	printf("\tp0q0:\n");print_Element_2w_h0h7(p0q0);
//	printf("\tp1q1:\n");print_Element_2w_h0h7(p1q1);
/*	l0 =  3*p0;     r0 =  3*Z1*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		__m256i p0Z1 = BLEND32(p0q0[i],ZZ1[i],0xF0);
		l0r0[i] = ADD(SHL(p0Z1,1),p0Z1);
	}
/*	l1 = X2+Y2;     r1 = q0+Y1*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		__m256i X2q0 = BLEND32(XY2[i],p0q0[i],0xF0);
		__m256i Y2Y1 = BLEND32(YX2[i],XY1[i],0xF0);
		l1r1[i] = ADD(X2q0,Y2Y1);
	}
/*	l2 = X1+Y1;     r2 = q1+X1*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		__m256i X1q1 = BLEND32(XY1[i],p1q1[i],0xF0);
		__m256i YX1 = PERM64(XY1[i],0x4E);
		l2r2[i] = ADD(X1q1,YX1);
	}

//	printf("\tl0r0:\n");print_Element_2w_h0h7(l0r0);
//	printf("\tl1r1:\n");print_Element_2w_h0h7(l1r1);
//	printf("\tl2r2:\n");print_Element_2w_h0h7(l2r2);

/*	p2 = ecc_b*Z1;  q2 = ecc_b*r2*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		Z1r2[i] = BLEND32(ZZ1[i], l2r2[i], 0xF0);
	}
	mul_Element_2w_h0h7(p2q2,Z1r2,BB);
	compress_Element_2w_h0h7(p2q2);
/*	l3 = r2-p2;     r3 = q2-p0*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		r2q2[i] = PERM128(l2r2[i], p2q2[i], 0x31);
		p2p0[i] = PERM128(p0q0[i], p2q2[i], 0x02);
	}
	sub_Element_2w_h0h7(l3r3,r2q2,p2p0);
/*	p3 = l1*l2*/
	mul_Element_2w_h0h7(p3q3,l1r1,l2r2);
	compress_Element_2w_h0h7(p3q3);
//	printf("\tp2q2:\n");print_Element_2w_h0h7(p2q2);
//	printf("\tl3r3:\n");print_Element_2w_h0h7(l3r3);
//	printf("\tp3q3:\n");print_Element_2w_h0h7(p3q3);
/*	l4 = p0+p1*/
	add_Element_2w_h0h7(l4r4,p0q0,p1q1);
/*	l5 = p3-l4;     r5 = r3-r0*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		p3r3[i] = BLEND32(p3q3[i], l3r3[i], 0xF0);
		l4r0[i] = BLEND32(l4r4[i], l0r0[i], 0xF0);
	}
	sub_Element_2w_h0h7(l5r5,p3r3,l4r0);
/*	l6 =  3*l3;     r6 =  3*r5*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		__m256i l3r5 = BLEND32(l3r3[i],l5r5[i],0xF0);
		l6r6[i] = ADD(SHL(l3r5,1),l3r5);
	}
//	printf("\tl4r4:\n");print_Element_2w_h0h7(l4r4);
//	printf("\tl5r5:\n");print_Element_2w_h0h7(l5r5);
//	printf("\tl6r6:\n");print_Element_2w_h0h7(l6r6);
/*	l7 = p1+l6;     r7 = r6;         */
	add_Element_2w_h0h7(l7r7,p1q1,l6r6);
/*	l8 = p1-l6;     r8 = l0-r0*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		p1l0[i] = PERM128(p1q1[i], l0r0[i], 0x20);
		l6r0[i] = BLEND32(l6r6[i], l0r0[i], 0xF0);
	}
	sub_Element_2w_h0h7(l8r8,p1l0,l6r0);
/*	p4 = l7*l8;     q4 = r7*r8*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		l7r7[i] = BLEND32(l7r7[i], l6r6[i], 0xF0);
	}
	compress_Element_2w_h0h7(l5r5);
	compress_Element_2w_h0h7(l7r7);
	compress_Element_2w_h0h7(l8r8);
	mul_Element_2w_h0h7(p4q4,l7r7,l8r8);
	compress_Element_2w_h0h7(p4q4);
//	printf("\tl7r7:\n");print_Element_2w_h0h7(l7r7);
//	printf("\tl8r8:\n");print_Element_2w_h0h7(l8r8);
//	printf("\tp4q4:\n");print_Element_2w_h0h7(p4q4);
/*	p5 = l7*l5;     q5 = r7*r1*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		l5r1[i] = BLEND32(l5r5[i], l1r1[i], 0xF0);
	}
	mul_Element_2w_h0h7(p5q5,l7r7,l5r1);
	compress_Element_2w_h0h7(p5q5);
/*	p6 = r1*l8;     q6 = l5*r8*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		l5r1[i] = PERM64(l5r1[i],0x4E);
	}
	mul_Element_2w_h0h7(p6q6,l5r1,l8r8);
	compress_Element_2w_h0h7(p6q6);

//	printf("\tp5q5:\n");print_Element_2w_h0h7(p5q5);
//	printf("\tp6q6:\n");print_Element_2w_h0h7(p6q6);
/*	X3 = p5-q5;     Y3 = p4+q4*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		p5p4[i] = PERM128(p5q5[i],p4q4[i],0x20);
		q5q4[i] = PERM128(p5q5[i],p4q4[i],0x31);
		q6p6[i] = PERM64(p6q6[i],0x4E);
	}
	addsub_Element_2w_h0h7(Q->XY,p5p4,q5q4,1,0);
/*	Z3 = p6+q6*/
	add_Element_2w_h0h7(Q->ZZ,p6q6,q6p6);

//	printf("\tQ->XY:\n");print_Element_2w_h0h7(Q->XY);
//	printf("\tQ->ZZ:\n");print_Element_2w_h0h7(Q->ZZ);
}

/**
 *
 */
void _1way_doubling(Point_XYZ_1way *P)
{
	int i;
	argElement_2w_H0H7 XY = P->XY;
	argElement_2w_H0H7 ZZ = P->ZZ;
	argElement_2w_H0H7 BB = (argElement_2w_H0H7)ECC_PARAM_B;

	const __m256i shift_1Z = _mm256_set_epi64x(64,64,1,1);
	const __m256i shift_10 = _mm256_set_epi64x(0,0,1,1);

	Element_2w_H0H7 YZ,XZ;
	Element_2w_H0H7 p0q0,p1q1,p2q2,p3q3,p4q4,p5q5,q6;
	Element_2w_H0H7 p0p2,p5p4,q5q4;
	Element_2w_H0H7 l0r0,l1r1,l2r2,l3r3,l4r4,l5r5,r5l5;
	Element_2w_H0H7 q2r0,l0r1;

	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		YZ[i] = PERM128(XY[i],ZZ[i],0x21);
		XZ[i] = BLEND32(ADD(XY[i],XY[i]),ZZ[i],0xF0);
	}

/*	p0 = X**2;		q0 = Y**2;		*/
	mul_Element_2w_h0h7(p0q0,XY,XY);
	compress_Element_2w_h0h7(p0q0);
/*	p1 = X*Y;		q1 = Y*Z;       */
	mul_Element_2w_h0h7(p1q1,XY,YZ);
	compress_Element_2w_h0h7(p1q1);
/*  p2 = 2*X*Z;		q2 = Z**2;      */
	mul_Element_2w_h0h7(p2q2,XZ,ZZ);
	compress_Element_2w_h0h7(p2q2);
/*  p3 = ecc_b*p2;	q3 = ecc_b*q2;  */
	mul_Element_2w_h0h7(p3q3,p2q2,BB);
	compress_Element_2w_h0h7(p3q3);

//	printf("\tp0q0:\n");print_Element_2w_h0h7(p0q0);
//	printf("\tp1q1:\n");print_Element_2w_h0h7(p1q1);
//	printf("\tp2q2:\n");print_Element_2w_h0h7(p2q2);
//	printf("\tp3q3:\n");print_Element_2w_h0h7(p3q3);

/*	l0 = p3-p0;		r0 = q3-p2;		*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		p0p2[i] = PERM128(p0q0[i],p2q2[i],0x20);
	}
	sub_Element_2w_h0h7(l0r0,p3q3,p0p2);
/*  l1 = 3*p0;		r1 = 1*q0*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		l1r1[i] = ADD(SHLV(p0q0[i],shift_1Z),p0q0[i]);
	}
/*  l2 = 3*q2;		r2 = 3*r0;*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		q2r0[i] = PERM128(p2q2[i],l0r0[i],0x31);
		l2r2[i] = ADD(SHL(q2r0[i],1),q2r0[i]);
	}
/*  l3 = l1-l2;		r3 = r1+r2;*/
	addsub_Element_2w_h0h7(l3r3,l1r1,l2r2,1,0);
/*  l4 = l0-l2;		r4 = r1-r2;*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		l0r1[i] = BLEND32(l0r0[i], l1r1[i], 0xF0);
	}
	sub_Element_2w_h0h7(l4r4,l0r1,l2r2);
/*  l5 = 3*l4;		r5 = 1*r4;*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		l5r5[i] = ADD(SHLV(l4r4[i],shift_1Z),l4r4[i]);
	}
	compress_Element_2w_h0h7(l5r5);
	compress_Element_2w_h0h7(l3r3);
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		r5l5[i] = PERM64(l5r5[i],0x4E);
	}

//	printf("\tl3r3:\n");print_Element_2w_h0h7(l3r3);
//	printf("\tl5r5:\n");print_Element_2w_h0h7(l5r5);
/*  p4 = l3*l5;		q4 = r3*r5;*/
	mul_Element_2w_h0h7(p4q4,l3r3,l5r5);
/*  p5 = p1*r5;		q5 = q1*l5;*/
	mul_Element_2w_h0h7(p5q5,p1q1,r5l5);
/*  empty;			q6 = q1*r1;*/
	mul_Element_2w_h0h7(q6,p1q1,l1r1);
//	compress_Element_2w_h0h7(p4q4);
//	compress_Element_2w_h0h7(p5q5);
//	compress_Element_2w_h0h7(  q6);

//	printf("\tp4q4:\n");print_Element_2w_h0h7(p4q4);
//	printf("\tp5q5:\n");print_Element_2w_h0h7(p5q5);
//	printf("\tq6  :\n");print_Element_2w_h0h7(q6  );
/*  X3 = 2*(p5-q5);	Y3 = p4+q4;    */
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		p5p4[i] = PERM128(p5q5[i],p4q4[i],0x20);
		q5q4[i] = PERM128(p5q5[i],p4q4[i],0x31);
	}
	addsub_Element_2w_h0h7(P->XY,p5p4,q5q4,1,1);
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		P->XY[i] = SHLV(P->XY[i],shift_10);
	}
	compress_Element_2w_h0h7(P->XY);
/*  Z3 = 8*q6;*/
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		P->ZZ[i] = PERM64(SHL(q6[i],3),0xEE);
	}
	compress_Element_2w_h0h7(P->ZZ);
//	printf("\tP->XY:\n");print_Element_2w_h0h7(P->XY);
//	printf("\tP->Z :\n");print_Element_2w_h0h7(P->Z );
}



static inline int are_equal(uint8_t  * X, uint8_t  * Y)
{
	int i=0;
	int zero =0;
	for(i=0;i<SIZE_STR_BYTES;i++)
	{
		zero |= X[i]^Y[i];
	}
	return zero==0;
}

/**
 * Computes the doubling of ONE point
 * stored in P = {XY,ZT}
 **/
void doubling_2w_H0H7(PointXYZT_2w_H0H7 * P)
{

}

void fulladdition_2w_H0H7(PointXYZT_2w_H0H7 *Q, PointXYZT_2w_H0H7 *P)
{

}

/*
 * Full addition from Hisil page 6.
 */
void mixaddition_2w_H0H7(PointXYZT_2w_H0H7 *Q, PointXYZT_precompute_2w_H0H7 *P)
{

}



