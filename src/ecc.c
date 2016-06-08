#include "ecc.h"
#include <string.h>
#include "table_sign.h"
#include "table_verif.h"

void word64_multiplier(
		uint64_t*C,
		const uint64_t*A, int numA,
		const uint64_t*B, int numB)
{
	int i,j;
#define mul64x64(Z,X,Y)	__asm__ __volatile__ (\
			"movq 0(%3), %%rax     ;"\
			"mulq 0(%4)            ;"\
			"addq %%rax, %0        ;"\
			"adcq %%rdx, %1        ;"\
			"adcq $0x0,  %2        ;"\
	:/* out  */ "+r" ((Z)[0]),"+r" ((Z)[1]),"+r" ((Z)[2])\
	:/* in   */ "r" (X),"r" (Y)\
	:/* regs */  "memory","cc","%rax","%rdx","%r8","%r9","%r10");

	for(i=0;i<numA;i++)
	{
		for(j=0;j<numB;j++)
		{
			mul64x64(C+i+j,A+i,B+j);
		}
	}
#undef mul64x64
}

/**
 * Recoding to a signed radix 2^OMEGA (fold2w4)
 * Given:
 *      r   A 256-bit integer
 * Returns:
 *      (-1)^(S[i])*K[1] for i \in [0,64]
 * such that
 *      K[i] \in {0, 1, 2, ..., 2^OMEGA}
 *      S[i]=000..0  if k[i] is positive
 *      S[i]=111..1  if k[i] is negative
 *
 * K[i] = 64 bits (quad-word)
 * K_i  = 4 bits (nibble)
 *
 * K[ 0, 1, 2, 3] = [ n_0, n_1,   n_2,  n_3]
 * K[ 4, 5, 6, 7] = [ n_4, n_5,   n_6,  n_7]
 * K[ 8, 9,10,11] = [ n_8, n_9,  n_10, n_11]
 * K[12,13,14,15] = [n_12, n_13, n_14, n_15]
 * ...
 * K[60,61,62,63] = [n_60, n_61, n_62, n_63]
 *
 */
void recoding_signed_scalar_fold2w4(uint64_t *list_signs, uint64_t *list_digits, uint8_t *r)
{
	const int OMEGA = 4;
	int i,j;
	int8_t carry=0;
	uint8_t nibble_low, nibble_hig;
	int8_t value,digit;

	for(i=0;i<2;i++)
	{
		for(j=0;j<28;j++)
		{
			nibble_low = r[28*i+j] & 0xF;
			value = nibble_low + carry;
			carry = value >= (1 << (OMEGA - 1));
			digit = ((value^(-carry))+carry)&0xF;

			list_digits[56*i+2*j+0] = (int64_t) digit;
			list_signs [56*i+2*j+0] = (int64_t) -carry;
//			printf("%s%x,",-carry?"-":"+",digit);

			nibble_hig = (r[28*i+j] >> 4) & 0xF;
			value = nibble_hig + carry;
			carry = value >= (1 << (OMEGA - 1));
			digit = ((value^(-carry))+carry)&0xF;

			list_digits[56*i+2*j+1] = (int64_t) digit;
			list_signs [56*i+2*j+1] = (int64_t) -carry;
//			printf("%s%x,",-carry?"-":"+",digit);
		}
	}//list_digits[112] = carry;//This is always equal to 0 iff r < 2**447
}


static void query_table_fold2w4(Point_XY_2way *P, const uint8_t * table,uint64_t * secret_signs,uint64_t *secret_digits)
{
	const __m256i _P[16] = {
			SET1_64(0xfffffff),	SET1_64(0xffffffe),
			SET1_64(0xfffffff),	SET1_64(0xfffffff),
			SET1_64(0xfffffff),	SET1_64(0xfffffff),
			SET1_64(0xfffffff),	SET1_64(0xfffffff),
			SET1_64(0xfffffff),	SET1_64(0xfffffff),
			SET1_64(0xfffffff),	SET1_64(0xfffffff),
			SET1_64(0xfffffff),	SET1_64(0xfffffff),
			SET1_64(0xfffffff),	SET1_64(0xfffffff)
	};
	const __m256i one = SET1_64(1);
	int i,j;
	__m256i mask[9];
	__m256i P_addYX[7], P_subYX[7];
	__m256i digits = LOAD(secret_digits);
	__m256i signs  = LOAD(secret_signs);
	__m256i iiii = ZERO;
	uint64_t * p64Table = (uint64_t*)table;

	/* create a set of masks */
	for(i=0;i<9;i++)
	{
		/**
		 * Determine if iiii is different from digits
		 * using they following relation:
		 *    mask = (x-y) OR (y-x)
		 *    63th bit = 1   if X   equal   Y
		 *    63th bit = 0   if X not equal Y
		 * */
		mask[i] = OR(SUB(digits,iiii),SUB(iiii,digits));
		/* propagate 63th bit to the whole 64-bit word. */
		mask[i] = _mm256_shuffle_epi32(_mm256_srai_epi32(mask[i],32),0xE5);
		iiii = ADD(iiii,one);
	}
	/**
	 * Queries to the table for points 1B,2B,3B,...,8B.
	 * acc = \sum 1B&¬mask[1] + 2B&¬mask[2] + 3B&¬mask[3] + ... + 8B&¬mask[8]
	 * if mask[i] == all_zeros for some i € {1,2,...,8}
	 * 	     then iB was selected
	 * if mask[i] == all_ones for all i
	 * 	     then no point was selected
	 */
	for(j=0;j<7;j++)//num of 64-bit words
	{
		P_addYX[j] = ZERO;
		P_subYX[j] = ZERO;
		for(i=0;i<8;i++)//num of multiples {1B,2B,3B,...,8B}
		{
			__m256i addYX,subYX;
			BROADCASTQ(addYX,p64Table+24*j+2*i+0);
			BROADCASTQ(subYX,p64Table+24*j+2*i+1);

			P_addYX[j] = XOR(P_addYX[j],ANDNOT(mask[i+1],addYX));
			P_subYX[j] = XOR(P_subYX[j],ANDNOT(mask[i+1],subYX));
		}
	}
	/**
	 * In case that the multiple queried be the 0B,
	 * then to construct the point at infinity
	 * we just append a 1 (one).
	 */
	P_addYX[0] = XOR(P_addYX[0], ANDNOT(mask[0],XOR(P_addYX[0],one)));
	P_subYX[0] = XOR(P_subYX[0], ANDNOT(mask[0],XOR(P_subYX[0],one)));
	/**
	 * Point Sign Verification (Part 1/2)
	 * if secret_sign == 1
	 *    addYX <- subYX
	 *    subYX <- addYX
	 * otherwise
	 *    they remain unchanged
	 */
	for(j=0;j<7;j++)
	{
		__m256i swap = AND(XOR(P_addYX[j], P_subYX[j]), signs);
		P_addYX[j] = XOR(P_addYX[j], swap);
		P_subYX[j] = XOR(P_subYX[j], swap);
	}

	str_bytes_to_Element_2w_h0h7(P->X,P_addYX);
	str_bytes_to_Element_2w_h0h7(P->Y,P_subYX);

	/**
	 * Point Sign Verification (Part 2/2)
	 * if signs == 111111111
	 *    _2dYX <-- -_2dYX + P
	 * otherwise
	 *    _2dYX <--  _2dYX + P
	 */
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		P->X[i] = ADD( XOR(P->X[i],signs), SUB(_P[i],signs));
	}
}

void query_table(Point_XY_2way *P, const uint8_t * table,uint64_t * secret_signs,uint64_t *secret_digits)
{
	query_table_fold2w4(P,table,secret_signs,secret_digits);
}

/**
 *
 */
void _2way_full_addition_law(PointXYZ_2way * Q,  PointXYZ_2way *P)
{
	__m256i * X1 = Q->X; __m256i * X2 = P->X;
	__m256i * Y1 = Q->Y; __m256i * Y2 = P->Y;
	__m256i * Z1 = Q->Z; __m256i * Z2 = P->Z;


}

/**
 *
 */
void _2way_mix_addition_law(PointXYZ_2way *Q, Point_XY_2way *P)
{
	__m256i * X1 = Q->X;
	__m256i * Y1 = Q->Y;
	__m256i * Z1 = Q->Z;
	__m256i * X2 = P->X;
	__m256i * Y2 = P->Y;

}

/**
 *
 */
void _2way_doubling(PointXYZ_2way *P)
{
	__m256i * X1 = P->X;
	__m256i * Y1 = P->Y;
	__m256i * Z1 = P->Z;

}

/**
 *
 */
void _1way_full_addition_law(PointXYZ_1way * Q, PointXYZ_1way *P)
{
	uint64_t * X1 = Q->X; uint64_t * X2 = P->X;
	uint64_t * Y1 = Q->Y; uint64_t * Y2 = P->Y;
	uint64_t * Z1 = Q->Z; uint64_t * Z2 = P->Z;

}

/**
 *
 */
void _1way_mix_addition_law(PointXYZ_1way * Q, Point_XY_1way *P)
{
	__m256i * X1 = Q->X; __m256i * X2 = P->X;
	__m256i * Y1 = Q->Y; __m256i * Y2 = P->Y;
	__m256i * Z1 = Q->Z;

}

/**
 *
 */
void _1way_doubling(PointXYZ_1way *P)
{
	uint64_t * X1 = P->X;
	uint64_t * Y1 = P->Y;
	uint64_t * Z1 = P->Z;
}


/**
 * Given Q = [P3,P2,P1,P0]
 * Computes Q0 as:
 * 		Q0 = 16^3 ( 16^2 ( 16^1 P3 + P2) + P1) + P0
 *
 */
void join_points_1w_H0H7(PointXYZ_1way *Q0, PointXYZ_2way *Q)
{
    PointXYZ_1way Q1;

    deinterleave(Q0->X,Q1.X,Q->X);
    deinterleave(Q0->Y,Q1.Y,Q->Y);

    _1way_doubling(&Q1);
    _1way_doubling(&Q1);
    _1way_doubling(&Q1);
    _1way_doubling(&Q1);
    _1way_full_addition_law(Q0,&Q1);
}

/**
 * Given:
 *      STR_BYTES r
 * Computes
 *      rB = [r]B
 * Ensuring that B is the generator of NIST-P384
 *
 * This function will use a pre-computed table of 36.75KB.
 * Folding 4 means four queries at the same time.
 * Using w=4, means that scalar will be partitioned in
 * 4-bit signed digits.
 * This produces to compute 28 iterations in the main loop.
 * as follows:
 *		S_0 = r_0 + 16^4 r_4 + 16^8 r_8  + ... + 16^108 r_108
 *		S_1 = r_1 + 16^4 r_5 + 16^8 r_9  + ... + 16^108 r_109
 *		S_2 = r_2 + 16^4 r_6 + 16^8 r_10 + ... + 16^108 r_110
 *		S_3 = r_3 + 16^4 r_7 + 16^8 r_11 + ... + 16^108 r_111
 * Then recombining partial sums with:
 *		S = S_0 + 16^1 S_1 + 16^2 S_2 + 16^3 S_3.
 */
static void fixed_point_multiplication_fold2w4(Point_XY_1way* kP, uint8_t *k)
{
	int i;
	PointXYZ_2way Q;
	PointXYZT_2w_H0H7 Q0;
	Point_XY_2way P;
	ALIGN uint64_t K[112];
	ALIGN uint64_t S[112];
	const Element_2w_H0H7 one_half = {
			SET1_64(0x0000000),SET1_64(0xfffffff),
			SET1_64(0x0000000),SET1_64(0xfffffff),
			SET1_64(0x0000000),SET1_64(0xfffffff),
			SET1_64(0x0000000),SET1_64(0xfffffff),
			SET1_64(0x0000000),SET1_64(0xfffffff),
			SET1_64(0x0000000),SET1_64(0xfffffff),
			SET1_64(0x0000000),SET1_64(0xfffffff),
			SET1_64(0x8000000),SET1_64(0x7ffffff)
	};
 	recoding_signed_scalar_fold2w4(S,K,k);

	Q.Z[0] = SET1_64(2);
	for(i=1;i<NUM_WORDS_128B_NISTP384;i++)
	{
		Q.Z[i] = ZERO;
	}

	for(i=0;i<NUM_LUT;i++)
	{
        query_table_fold2w4(&P, ((uint8_t*)TableSign_w4_3675k)+SIZE_ONE_LUT*i,S+4*i,K+4*i);
		_2way_mix_addition_law(&Q, &P);
	}
	join_points_1w_H0H7(&Q0, &Q);

	/* convert to affine coordinates */
	Element_1w_H0H7 Z,X,Y,invZ;
	deinterleave(X,Y,Q0.XY);
	deinterleave(invZ,Z,Q0.TZ);
	inv_Element_1w_h0h7(invZ,Z);
	mul_Element_1w_h0h7(X,X,invZ);compress_Element_1w_h0h7(X);
	mul_Element_1w_h0h7(Y,Y,invZ);compress_Element_1w_h0h7(Y);

	Element_1w_h0h7_To_str_bytes(kP->X, X);
	Element_1w_h0h7_To_str_bytes(kP->Y, Y);
}

void fixed_point_multiplication(Point_XY_1way* kP, uint8_t *k)
{
	fixed_point_multiplication_fold2w4(kP,k);
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

#define copy_Element_1w_h0h7(C,A)\
	STORE(C+0,LOAD(A+0));\
	STORE(C+1,LOAD(A+1));\
	STORE(C+2,LOAD(A+2));\
	STORE(C+3,LOAD(A+3));

#define is_greater_equal_one(r)  \
(     	(r[6]!=0)                \
	||	(r[5]!=0)                \
	||	(r[4]!=0)                \
	||	(r[3]!=0)                \
	||	(r[2]!=0)                \
	||	(r[1]!=0)                \
	||	(r[0]>=(uint64_t)1)      \
)
#define is_odd(r) ((r[0]&0x1)==1)
#define div_2(r) \
{\
    uint64_t bit6 = r[6]<<63;\
    uint64_t bit5 = r[5]<<63;\
    uint64_t bit4 = r[4]<<63;\
    uint64_t bit3 = r[3]<<63;\
    uint64_t bit2 = r[2]<<63;\
    uint64_t bit1 = r[1]<<63;\
    r[7] = (r[6]>>1);\
    r[6] = (r[5]>>1) | bit6;\
    r[5] = (r[4]>>1) | bit5;\
    r[4] = (r[3]>>1) | bit4;\
    r[2] = (r[2]>>1) | bit3;\
    r[1] = (r[1]>>1) | bit2;\
    r[0] = (r[0]>>1) | bit1;\
}
#define SUB384(b,sign,value)        \
	__asm__ __volatile__ (          \
		"subq	%7, %0 \n\t"        \
		"sbbq	%9, %1 \n\t"        \
		"sbbq	%9, %2 \n\t"        \
		"sbbq	%9, %3 \n\t"        \
		"sbbq	%9, %4 \n\t"        \
		"sbbq	%9, %5 \n\t"        \
		"sbbq	%9, %6 \n\t"        \
		: "+r"((b)[0]), "+r"((b)[1]), "+r"((b)[2]), "+r"((b)[3]), \
		  "+r"((b)[4]), "+r"((b)[5]), "+r"((b)[6])                \
		: "r"(sign),"r"(value)  \
        : "cc", "memory")

int wnaf(int8_t * K,const uint8_t *p8_r, int w)
{
	int i = 0;
	int64_t value;
	ALIGN uint64_t r[8];

	r[7] = 0;
	for(i=0;i<SIZE_STR_BYTES;i++)
	{
		((uint8_t*)r)[i] = p8_r[i];
	}

	i=0;
	while(is_greater_equal_one(r))
	{
		if(is_odd(r))
		{
			value = r[0] & (((uint64_t)1<<w)-1);
			if(value>(1<<(w-1)))
			{
				value = value - (1<<w);
			}
			int64_t sign=value>>63;
			SUB384(r,sign,value);
		}
		else
		{
			value = 0;
		}
		K[i] = (int8_t)(value&0xFF);
		div_2(r);
		i++;
	}
	return i;
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

void precompute_points(PointXYZT_precompute_2w_H0H7 * table, PointXYZT_2w_H0H7* P)
{
	const int num = (1<<(OMEGA_DYNAMIC-2));
	int i=0;

	PointXYZT_2w_H0H7 iP;
	PointXYZT_precompute_2w_H0H7 _2P_precmp;

	memcpy(&iP,P,sizeof(PointXYZT_2w_H0H7));
	doubling_2w_H0H7(P);

//	printf("1P:\n");
//	print_Element_2w_h0h7(table[0].subaddYX);
//	print_Element_2w_h0h7(table[0]._2dT_2Z);

	for(i=1;i<num;i++)
	{
		mixaddition_2w_H0H7(&iP,&_2P_precmp);
	}
}

void read_point(PointXYZT_precompute_2w_H0H7 * P, int8_t index)
{
	uint8_t abs_index_r = index > 0 ? index: -index;
	abs_index_r >>= 1;
//	printf("r_indx:%d\n",abs_index_r);
	const uint64_t * ptr_point = &TableVerification_static_w7[3*7*abs_index_r];
	const Element_1w_H0H7 two = {
			0x2,0x0,0x0,0x0,
			0x0,0x0,0x0,0x0,
			0x0,0x0,0x0,0x0,
			0x0,0x0,0x0,0x0};
	Element_1w_H0H7 add,sub,_2dT;

	str_bytes_To_Element_1w_h0h7(add,(uint8_t*)(ptr_point+0));
	str_bytes_To_Element_1w_h0h7(sub,(uint8_t*)(ptr_point+7));
	str_bytes_To_Element_1w_h0h7(_2dT,(uint8_t*)(ptr_point+14));

//	print_Element_1w_h0h7(add);
//	print_Element_1w_h0h7(sub);
//	print_Element_1w_h0h7(_2dT);
	if(index<0)/*negative*/
	{
		neg_Element_1w_h0h7(_2dT);
		compress_Element_1w_h0h7(_2dT);
		interleave(P->subaddYX,add,sub);
	}
	else
	{
		interleave(P->subaddYX,sub,add);
	}
	interleave(P->_2dT_2Z,_2dT,(argElement_1w_H0H7)two);
//	print_Element_2w_h0h7(P->subaddYX);
//	print_Element_2w_h0h7(P->_2dT_2Z);
}

void double_point_multiplication(Point_XY_2way * kP_lQ, const uint8_t *k, uint8_t *l, Point_XY_2way * A)
{
		int i;
		int8_t wnaf_k[450]={0};
		int8_t wnaf_l[450]={0};

		PointXYZ_2way Q;
		PointXYZ_2way tableA[1<<(OMEGA_DYNAMIC-2)];

		int T_k = wnaf(wnaf_k,k, OMEGA_STATIC);
//		for(i=l_r-1;i>=0;i--) printf("%d, ",wnaf_r[i]);printf("\n");
		int T_l = wnaf(wnaf_l,l, OMEGA_DYNAMIC);
//	    for(i=l_h-1;i>=0;i--) printf("%d, ",wnaf_h[i]);printf("\n");
		int T = T_l > T_k ? T_l : T_k;
//		printf("l:%d lh: %d lr: %d\n",l,l_h,l_r);

		precompute_points(tableA,A);

		/* Set Identity */

		for(i=l-1;i>=0;i--)
		{
			doubling_2w_H0H7(&Q);
			/* known point addition */
//			printf("i:j:%d w_r:%d\n",l-4-i,wnaf_r[i]);
			if(wnaf_k[i] != 0)
			{
				PointXYZT_precompute_2w_H0H7 P;
				read_point(&P,wnaf_k[i]);
//				printf("\tsubadd: ");print_Element_2w_h0h7(P.subaddYX);
//				printf("\t_2dT2Z: ");print_Element_2w_h0h7(P._2dT_2Z);
				mixaddition_2w_H0H7(&Q,&P);
			}

//			printf("i:%d w_h:%d\n",i,wnaf_h[i]);
			/* unknown point addition */
			if(wnaf_l[i] != 0)
			{
				uint8_t abs_index_h = wnaf_l[i]> 0 ? wnaf_l[i]: -wnaf_l[i];
				abs_index_h >>= 1;
//				printf("h_indx:%d\n",abs_index_h);
				PointXYZT_precompute_2w_H0H7 * P = &tableA[abs_index_h];
				if(wnaf_l[i] < 0)
				{
					int ii=0;
					PointXYZT_precompute_2w_H0H7 _P;
    				for(ii=0;ii<NUM_WORDS_128B_NISTP384;ii++)
					{
        				_P.subaddYX[ii] = _mm256_permute4x64_epi64(P->subaddYX[ii], 0x4E);
    				}
					//negZZ_Element_2w_h0h7(_P._2dT_2Z,P->_2dT_2Z);
//					printf("\tsubadd: ");print_Element_2w_h0h7(_P.subaddYX);
//					printf("\t_2dT2Z: ");print_Element_2w_h0h7(_P._2dT_2Z);
					compress_Element_2w_h0h7(_P._2dT_2Z);
					mixaddition_2w_H0H7(&Q,&_P);
				}
				else
				{
//					printf("\tsubadd: ");print_Element_2w_h0h7(P->subaddYX);
//					printf("\t_2dT2Z: ");print_Element_2w_h0h7(P->_2dT_2Z);
					mixaddition_2w_H0H7(&Q,P);
				}
			}
//			printf("\tQ->XY: ");print_Element_2w_h0h7(Q.XY);
//			printf("\tQ->TZ: ");print_Element_2w_h0h7(Q.TZ);
//			if(i==l-4-21)
//				break;
		}
//	printf("\tQ->XY: ");print_Element_2w_h0h7(Q.XY);
//	printf("\tQ->TZ: ");print_Element_2w_h0h7(Q.TZ);


	/* convert to affine coordinates */
	Element_1w_H0H7 invZ,Z,X,Y;
	inv_Element_1w_h0h7(invZ,Z);
	mul_Element_1w_h0h7(X,X,invZ);compress_Element_1w_h0h7(X);
	mul_Element_1w_h0h7(Y,Y,invZ);compress_Element_1w_h0h7(Y);

	Element_1w_h0h7_To_str_bytes(kP_lQ->X, X);
	Element_1w_h0h7_To_str_bytes(kP_lQ->Y, Y);
}


