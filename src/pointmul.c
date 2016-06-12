#include <string.h>
#include <stdio.h>
#include "pointmul.h"
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


void query_table_fold2w4(Point_XY_2way *P, const uint8_t * table,uint64_t * secret_signs,uint64_t *secret_digits)
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

//	str_bytes_to_Element_2w_h0h7(P->X,P_addYX);
//	str_bytes_to_Element_2w_h0h7(P->Y,P_subYX);

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


#define copy_Element_1w_h0h7(C,A)\
	STORE(C+0,LOAD(A+0));\
	STORE(C+1,LOAD(A+1));\
	STORE(C+2,LOAD(A+2));\
	STORE(C+3,LOAD(A+3));

#define is_greater_equal_one(r)  \
(     	(r[5]!=0)                \
	||	(r[4]!=0)                \
	||	(r[3]!=0)                \
	||	(r[2]!=0)                \
	||	(r[1]!=0)                \
	||	(r[0]>=(uint64_t)1)      \
)
#define is_odd(r) ((r[0]&0x1)==1)
#define div_2(r) \
{\
    uint64_t bit5 = r[5]<<63;\
    uint64_t bit4 = r[4]<<63;\
    uint64_t bit3 = r[3]<<63;\
    uint64_t bit2 = r[2]<<63;\
    uint64_t bit1 = r[1]<<63;\
    r[5] = (r[5]>>1);\
    r[4] = (r[4]>>1) | bit5;\
    r[3] = (r[3]>>1) | bit4;\
    r[2] = (r[2]>>1) | bit3;\
    r[1] = (r[1]>>1) | bit2;\
    r[0] = (r[0]>>1) | bit1;\
}
#define SUB384(b,sign,value)                   \
	__asm__ __volatile__ (                     \
		"subq	%6, %0 \n\t"                   \
		"sbbq	%7, %1 \n\t"                   \
		"sbbq	%7, %2 \n\t"                   \
		"sbbq	%7, %3 \n\t"                   \
		"sbbq	%7, %4 \n\t"                   \
		"sbbq	%7, %5 \n\t"                   \
		: "+r"(b[0]), "+r"(b[1]), "+r"(b[2]),  \
          "+r"(b[3]), "+r"(b[4]), "+r"(b[5])   \
		: "r"(value), "r"(sign)     \
        : "cc", "memory")

int wnaf(int8_t * K,const uint8_t *p8_r, int w)
{
	int i = 0;
	int64_t value,sign;
	ALIGN uint64_t r[6];

	for(i=0;i<6;i++)
	{
		r[i] = ((uint64_t*)p8_r)[i];
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
			sign=value>>63;
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
 * Given Q = [P3,P2,P1,P0]
 * Computes Q0 as:
 * 		Q0 = 16^3 ( 16^2 ( 16^1 P3 + P2) + P1) + P0
 *
 */
void join_points_1w_H0H7(Point_XYZ_1way *Q0, Point_XYZ_2way *Q)
{

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
	Point_XYZ_2way Q;
	Point_XY_2way P;
	ALIGN uint64_t K[112];
	ALIGN uint64_t S[112];
	recoding_signed_scalar_fold2w4(S,K,k);

//	Q.Z[0] = SET1_64(2);
	for(i=1;i<NUM_WORDS_128B_NISTP384;i++)
	{
//		Q.Z[i] = ZERO;
	}

	for(i=0;i<NUM_LUT;i++)
	{
		query_table_fold2w4(&P, ((uint8_t*)TableSign_w4_3675k)+SIZE_ONE_LUT*i,S+4*i,K+4*i);
		_2way_mix_addition_law(&Q, &P);
	}
//	join_points_1w_H0H7(&Q0, &Q);

	/* convert to affine coordinates */
	//toAffine(kP,&Q);
}

void fixed_point_multiplication(Point_XY_1way* kP, uint8_t *k)
{
	fixed_point_multiplication_fold2w4(kP,k);
}

void precompute_points(Point_XYZ_1way * table, Point_XY_1way * P,const int OMEGA)
{
	const int num = (1<<(OMEGA-2));
	int i=0;
	Point_XYZ_1way _2P;
	toProjective(&_2P,P);
	toProjective(&table[0],P);
	_1way_doubling(&_2P);

	for(i=1;i<num;i++)
	{
		memcpy(&table[i],&table[i-1],sizeof(Point_XYZ_1way));
		_1way_full_addition_law(&table[i],&_2P);
	}
}
inline void read_point(Point_XYZ_1way * P, int8_t abs_index)
{
	int i;
	const uint64_t * ptr_point = &TableVerification_static_w7[2*6*abs_index];
	Element_1w_H0H7 x,y;
	str_bytes_To_Element_1w_h0h7(x,(uint8_t*)(ptr_point+0));
	str_bytes_To_Element_1w_h0h7(y,(uint8_t*)(ptr_point+6));
	interleave(P->XY,x,y);
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		P->ZZ[i] = ZERO;
	}
	P->ZZ[0] = _mm256_set_epi64x(0,1,0,1);
}

void double_point_multiplication(
		Point_XY_1way * kP_lQ,
		uint8_t *k, uint8_t *l,
		Point_XY_1way * Q)
{
	int i;
	int8_t wnaf_k[392] = {0};
	int8_t wnaf_l[392] = {0};

	Point_XYZ_1way R;

	Point_XYZ_1way TabDynamic[1<<(OMEGA_DYNAMIC-2)];

	int T_k = wnaf(wnaf_k,k, OMEGA_STATIC);
	int T_l = wnaf(wnaf_l,l, OMEGA_DYNAMIC);
	int T = T_l > T_k ? T_l : T_k;

	precompute_points(TabDynamic,Q,OMEGA_DYNAMIC);

	/* Set Identity */
	getIdentityProj(&R);
	for(i=T;i>=0;i--)
	{
		_1way_doubling(&R);
		/* known point addition */
		if(wnaf_k[i] != 0)
		{
			uint8_t abs_index_k = wnaf_k[i]> 0 ? wnaf_k[i]: -wnaf_k[i];
			abs_index_k >>= 1;
			Point_XYZ_1way P;
			read_point(&P,abs_index_k);
			if(wnaf_k[i] < 0)
			{
				Point_XYZ_1way _P;
				negatePoint(&_P,&P);
				_1way_full_addition_law(&R,&_P);
			}
			else
			{
				_1way_full_addition_law(&R,&P);
			}
		}
		/* unknown point addition */
		if(wnaf_l[i] != 0)
		{
			uint8_t abs_index_h = wnaf_l[i]> 0 ? wnaf_l[i]: -wnaf_l[i];
			abs_index_h >>= 1;
			Point_XYZ_1way * P = &TabDynamic[abs_index_h];
			if(wnaf_l[i] < 0)
			{
				Point_XYZ_1way _P;
				negatePoint(&_P,P);
				_1way_full_addition_law(&R,&_P);
			}
			else
			{
				_1way_full_addition_law(&R,P);
			}
		}
	}
//	printf("R.XY:\n");print_Element_2w_h0h7(R.XY);
//	printf("R.ZZ:\n");print_Element_2w_h0h7(R.ZZ);
	/* convert to affine coordinates */
	toAffine(kP_lQ,&R);
}

