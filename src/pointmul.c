#include <string.h>
#include <math.h>
#include "pointmul.h"
#include "table_sign.h"
#include "table_verif.h"
#include <stdio.h>

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
int8_t recoding_signed_scalar_w4(int8_t *list_digits, uint8_t *r)
{
	const int OMEGA = 4;
	int i,j;
	int8_t carry=0;
	uint8_t nibble_low, nibble_hig;
	int8_t value,digit;

	for(i=0;i<2;i++)
	{
		for(j=0;j<24;j++)
		{
			nibble_low = r[24*i+j] & 0xF;
			value = nibble_low + carry;
			carry = value >= (1 << (OMEGA - 1));
			digit = value-((1 << OMEGA)&(-carry));

			list_digits[48*i+2*j+0] = digit;
//			printf("(i:%d,v:%x,c:%x,d:%d), ",24*i+j,value,carry,digit);

			nibble_hig = (r[24*i+j] >> 4) & 0xF;
			value = nibble_hig + carry;
			carry = value >= (1 << (OMEGA - 1));
			digit = value-((1 << OMEGA)&(-carry));
			list_digits[48*i+2*j+1] = digit;
//			printf("(i:%d,v:%x,c:%x,d:%d), ",24*i+j,value,carry,digit);
		}
	}
	list_digits[48*i] = carry;//This is could be equal to 1 iff |r| = 384
	return carry;
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
#define rightshift_bits(r,bits) \
{\
    uint64_t bit5 = r[5]<<(64-(bits));\
    uint64_t bit4 = r[4]<<(64-(bits));\
    uint64_t bit3 = r[3]<<(64-(bits));\
    uint64_t bit2 = r[2]<<(64-(bits));\
    uint64_t bit1 = r[1]<<(64-(bits));\
    r[5] = (r[5]>>(bits));\
    r[4] = (r[4]>>(bits)) | bit5;\
    r[3] = (r[3]>>(bits)) | bit4;\
    r[2] = (r[2]>>(bits)) | bit3;\
    r[1] = (r[1]>>(bits)) | bit2;\
    r[0] = (r[0]>>(bits)) | bit1;\
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
		rightshift_bits(r,1);
		i++;
	}
	return i;
}

int recoding(int8_t * K,const uint8_t *p8_r, const int w)
{
	int i, t;
	int64_t digit,sign;
	ALIGN uint64_t r[6];

	t = (int)ceil((SIZE_STR_BYTES*8)/(float)(w-1));
	for(i=0;i<6;i++)
	{
		r[i] = ((uint64_t*)p8_r)[i];
	}
	for(i=0;i<t;i++)
	{
		digit = r[0] & (((uint64_t)1<<w)-1);
		digit -= ((uint64_t)1<<(w-1));
		sign = digit>>63;
		K[i] = (int8_t)(digit&0xFF);
		SUB384(r,sign,digit);
		rightshift_bits(r,w-1);
	}
	K[i++] = r[0];
	return i;
}
void read_point_protected(Point_XYZ_1way * P,int8_t index,Point_XYZ_1way * Table)
{
	Point_XYZ_1way _Q;
	uint64_t i,j,num_points,abs_index;
	num_points = 1<<(OMEGA_VAR_PMUL-2);
	abs_index = index<0?-index:index;
	abs_index >>=1;

	for(j=0;j<NUM_WORDS_128B_NISTP384;j++)
	{
		P->XY[j] = ZERO;
		P->ZZ[j] = ZERO;
	}
	for(i=0;i<num_points;i++)
	{
		uint64_t bit = (i^abs_index)>0;
		__m256i mask = _mm256_set1_epi64x(bit-1);
		for(j=0;j<NUM_WORDS_128B_NISTP384;j++)
		{
			P->XY[j] = XOR(P->XY[j],AND(mask,Table[i].XY[j]));
			P->ZZ[j] = XOR(P->ZZ[j],AND(mask,Table[i].ZZ[j]));
		}
	}
	negatePoint(&_Q,P);
	int64_t bit = ((int64_t)index)>>63;
	__m256i mask = _mm256_set1_epi64x(bit);
	for(j=0;j<NUM_WORDS_128B_NISTP384;j++)
	{
		P->XY[j] = XOR(ANDNOT(mask,P->XY[j]), AND(mask,_Q.XY[j]));
	}
}

/**
 * compute c = a-b
 */
#define SUB384_words(c,a,b)                     \
	__asm__ __volatile__ (                      \
		"movq	(%1), %%rax   \n\t"         \
		"subq   (%2), %%rax   \n\t"         \
		"movq  %%rax,   (%0)    \n\t"         \
		"movq  8(%1), %%rax   \n\t"         \
		"sbbq  8(%2), %%rax   \n\t"         \
		"movq  %%rax,  8(%0)   \n\t"         \
		"movq 16(%1), %%rax   \n\t"         \
		"sbbq 16(%2), %%rax   \n\t"         \
		"movq  %%rax, 16(%0)   \n\t"         \
		"movq 24(%1), %%rax   \n\t"         \
		"sbbq 24(%2), %%rax   \n\t"         \
		"movq  %%rax, 24(%0)   \n\t"         \
		"movq 32(%1), %%rax   \n\t"         \
		"sbbq 32(%2), %%rax   \n\t"         \
		"movq  %%rax, 32(%0)   \n\t"         \
		"movq 40(%1), %%rax   \n\t"         \
		"sbbq 40(%2), %%rax   \n\t"         \
		"movq  %%rax, 40(%0)   \n\t"         \
		:                            \
		: "r"(c), "r"(a), "r"(b)                   \
        : "cc","%rax","memory")
void variable_point_multiplication(
		Point_XY_1way * kP,
		uint8_t *k,
		Point_XY_1way * P)
{
	int8_t L[80];
	int len,i,j;
	uint64_t _k[6];
	Point_XYZ_1way _Q,Q,R;
	Point_XYZ_1way Table[1<<(OMEGA_VAR_PMUL-2)];
	uint64_t * p64k = (uint64_t*)k;

	const uint64_t ecc_order[6] = {
			0xecec196accc52973,0x581a0db248b0a77a,
			0xc7634d81f4372ddf,0xffffffffffffffff,
			0xffffffffffffffff,0xffffffffffffffff
	};
	uint64_t mask = -(p64k[0]&0x1);
	SUB384_words(_k,ecc_order,p64k);
	for(i=0;i<6;i++)
	{
		_k[i] = (p64k[i]&mask)^(_k[i]&(~mask));
	}
	len = recoding(L,(uint8_t*)_k,OMEGA_VAR_PMUL);
	precompute_points(Table,P,OMEGA_VAR_PMUL);
	read_point_protected(&Q,L[len-1],Table);
	for(i=len-2;i>=0;i--)
	{
		for(j=0;j<(OMEGA_VAR_PMUL-1);j++)
		{
			_1way_doubling(&Q);
		}
		read_point_protected(&R,L[i],Table);
		_1way_full_addition_law(&Q,&R);
	}
	negatePoint(&_Q,&Q);
	__m256i vmask = _mm256_set1_epi64x(mask);
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		Q.XY[i] = XOR(AND(vmask,Q.XY[i]),ANDNOT(vmask,_Q.XY[i]));
	}
	/* convert to affine coordinates */
	toAffine(kP,&Q);
}


void query_table(Point_XYZ_1way *Q, const uint8_t * table,int8_t digit)
{
	int i;
	const int num_points = 1<<(OMEGA_FIXED_PMUL-1);
	ALIGN uint8_t XY[2*SIZE_STR_BYTES];
	__m256i * strQ = (__m256i*)XY;
	Element_1w_H0H7 X,Y,_Y;
	int8_t abs_digit;

	digit = (digit&((1<<(OMEGA_FIXED_PMUL-1))-1))-(digit&(1<<(OMEGA_FIXED_PMUL-1)));
	abs_digit = digit<0? -digit:digit;
	//printf("%d, ",digit);

	/* Set Point at Infinity in Affine coord. */
	for(i=0;i<12;i++)
	{
		((uint64_t*)strQ)[i] = 0;
	}
	((uint64_t*)strQ)[6] = (digit==0);

	/* Pass over the Look-up table. */
	for(i=0;i<num_points;i++)
	{
		uint64_t bit = ((i+1)^abs_digit)>0;
		__m256i mask = _mm256_set1_epi64x(bit-1);
		__m256i P0 = LOAD(table+3*i+0);
		__m256i P1 = LOAD(table+3*i+1);
		__m256i P2 = LOAD(table+3*i+2);
		strQ[0] = XOR(strQ[0],AND(P0,mask));
		strQ[1] = XOR(strQ[1],AND(P1,mask));
		strQ[2] = XOR(strQ[2],AND(P2,mask));
	}
	/* Convert to vector representation */
	str_bytes_To_Element_1w_h0h7(X,XY+0);
	str_bytes_To_Element_1w_h0h7(Y,XY+SIZE_STR_BYTES);

	/* Determine P or -P using the sign of digit */
	for(i=0;i<NUM_WORDS_64B_NISTP384;i++)
		_Y[i] = Y[i];
	neg_Element_1w_h0h7(_Y);
	compress_Element_1w_h0h7(_Y);

	int64_t mask = ((int64_t)digit)>>63;
	for(i=0;i<NUM_WORDS_64B_NISTP384;i++)
	{
		Y[i] = (Y[i]&(~mask))^(_Y[i]&mask);
	}

	/* Package X,Y,Z=1 coordinates. */
	interleave(Q->XY,X,Y);
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		Q->ZZ[i] = ZERO;
	}
	Q->ZZ[0] = _mm256_set_epi64x(0,digit!=0,0,digit!=0);
}


ALIGN Point_XYZ_1way CONST_2_384G_XY ={
		{
				0x7dc885c,0xa5127bf,0xfbc853f,0x2cc2064,
				0xed2ff2a,0xf1383e8,0xfe7d204,0xa6509a5,
				0x8e1fad8,0xc96f1b9,0x293457b,0x0b5e4a2,
				0xe34b12f,0x7ad61d6,0x078a216,0xbe5a278,
				0x5ceb499,0xdae509e,0x1ce20ad,0x64622ae,
				0x3937d20,0x67cf514,0x419011a,0x41a0a35,
				0x67eb2ff,0x007fbbe,0x2371038,0x000c755
		},
		{
		0x1,0x0,0x1,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0,
		0x0,0x0,0x0,0x0
		}
};

/**
 * Given:
 *      STR_BYTES r
 * Computes
 *      rB = [r]B
 * Ensuring that B is the generator of NIST-P384
 *
 * This function will use a pre-computed table of 36.75KB.
 * Folding 2 means four queries at the same time.
 */
void fixed_point_multiplication(Point_XY_1way* kP, uint8_t *k)
{
	int i;
	__m256i mask;
	int64_t carry;
	int8_t K[98];
	Point_XYZ_1way * _2384G = &CONST_2_384G_XY;
	Point_XYZ_1way P,Q;

	/* Obatining a singed digit representation */
	carry = (int64_t)recoding_signed_scalar_w4(K,k);

	/* Iterating over the odd digits */
	i=0;
	uint8_t *Table = ((uint8_t*)TableSign_w4_36k)+SIZE_ONE_LUT*i;
	query_table(&Q, Table, K[2*i+1]);
	for(i=1;i<NUM_LUT;i++)
	{
		uint8_t *Table = ((uint8_t*)TableSign_w4_36k)+SIZE_ONE_LUT*i;
		query_table(&P, Table, K[2*i+1]);
		_1way_full_addition_law(&Q, &P);
	}

	/* Computing Q = (2**4)Q */
	_1way_doubling(&Q);	_1way_doubling(&Q);
	_1way_doubling(&Q);	_1way_doubling(&Q);

	/* Iterating over the even digits */
	for(i=0;i<NUM_LUT;i++)
	{
		uint8_t *Table = ((uint8_t*)TableSign_w4_36k)+SIZE_ONE_LUT*i;
		query_table(&P, Table, K[2*i+0]);
		_1way_full_addition_law(&Q, &P);
	}

	/* if carry==1 then Q+= (2**384)P */
	mask = _mm256_set1_epi64x(-carry);
	P.XY[0] = XOR(AND(mask,_2384G->XY[0]),ANDNOT(mask,_mm256_set_epi64x(0,1,0,0)));
	P.ZZ[0] = AND(mask,_2384G->ZZ[0]);
	for(i=1;i<NUM_WORDS_128B_NISTP384;i++)
	{
		P.XY[i] = AND(mask,_2384G->XY[i]);
		P.ZZ[i] = _2384G->ZZ[i];
	}
	_1way_full_addition_law(&Q, &P);

	/* convert to affine coordinates */
	toAffine(kP,&Q);
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

