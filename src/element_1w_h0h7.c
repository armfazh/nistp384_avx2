#include "element_1w_h0h7.h"
#include <str_bytes.h>
#include <stdio.h>

void random_Element_1w_h0h7(uint64_t *A)
{
	STR_BYTES a;
	random_str_bytes(a);
	str_bytes_To_Element_1w_h0h7(A, a);
}

int compare_Element_1w_h0h7(uint64_t *A, uint64_t *B)
{
	STR_BYTES a,b;
	compress_Element_1w_h0h7(A);
	compress_Element_1w_h0h7(B);
	Element_1w_h0h7_To_str_bytes(a, A);
	Element_1w_h0h7_To_str_bytes(b, B);
	return areEqual_str_bytes(a,b);
}

void print_python_Element_1w_h0h7(uint64_t *A)
{
	int i;
	printf("s = [ ");
	for(i=0;i<(NUM_WORDS_64B_NISTP384)-1;i+=2)
	{
//		if( ((signed)A[i])<0)		printf("-");
		printf("0x%.8lx, ", A[i] );
	}
	for(i=1;i<(NUM_WORDS_64B_NISTP384)-1;i+=2)
	{
//		if( ((signed)A[i])<0)		printf("-");
		printf("0x%.8lx, ", A[i] );
	}
//	if( ((signed)A[i])<0)		printf("-");
	printf("0x%.8lx] \n", A[i] );
}


void printex_Element_1w_h0h7(uint64_t *A)
{
	int i;
	for(i=(NUM_WORDS_64B_NISTP384)-1;i>0;i-=2)
	{
		printf("%8.16lx ", A[i]);
	}
	for(i=(NUM_WORDS_64B_NISTP384)-2;i>=0;i-=2)
	{
		printf("%8.16lx ", A[i]);
	}
	printf("\n");
}

void print_Element_1w_h0h7(uint64_t *A)
{
	STR_BYTES a;
	Element_1w_h0h7_To_str_bytes(a, A);
	print_str_bytes(a);
}

void sizes_Element_1w_h0h7(uint64_t *C)
{
	int i;
	printf("[");

	for(i=(NUM_WORDS_64B_NISTP384)-1;i>0;i-=2)
	{
		printf("%s%llu ", ((int64_t )C[i])<0?"-":"+", 64-_lzcnt_u64((unsigned long long int) labs((int64_t)C[i])));
	}
	for(i=(NUM_WORDS_64B_NISTP384)-2;i>=0;i-=2)
	{
		printf("%s%llu ", ((int64_t )C[i])<0?"-":"+", 64-_lzcnt_u64((unsigned long long int) labs((int64_t)C[i])));
	}
	printf("]\n");
}

void to_1w_h0h7(uint64_t *C)
{
	Element_1w_H0H7 T;
	int i;
	for(i=0;i<NUM_WORDS_64B_NISTP384;i++)
	{
		T[i] = C[i];
	}
	C[0]  = T[0];	C[1]  = T[8];
	C[2]  = T[1];	C[3]  = T[9];
	C[4]  = T[2];	C[5]  = T[10];
	C[6]  = T[3];	C[7]  = T[11];
	C[8]  = T[4];	C[9]  = T[12];
	C[10] = T[5];	C[11] = T[13];
	C[12] = T[6];	C[13] = T[14];
	C[14] = T[7];	C[15] = T[15];
}

void from_1w_h0h7(uint64_t *C)
{
	Element_1w_H0H7 T;
	int i;
	for(i=0;i<NUM_WORDS_64B_NISTP384;i++)
	{
		T[i] = C[i];
	}
	C[0] = T[0];	C[8]  = T[1];
	C[1] = T[2];	C[9]  = T[3];
	C[2] = T[4];	C[10] = T[5];
	C[3] = T[6];	C[11] = T[7];
	C[4] = T[8];	C[12] = T[9];
	C[5] = T[10];	C[13] = T[11];
	C[6] = T[12];	C[14] = T[13];
	C[7] = T[14];	C[15] = T[15];
}


/**
 * Converts between STR_BYTES to Element_1w_H0H7
 * */
void str_bytes_To_Element_1w_h0h7(uint64_t *__restrict pC, uint8_t *__restrict p8A)
{
	int i;
	const uint64_t mask = (((uint64_t)1)<<VECT_BASE)-1;
	const uint64_t *p64A = (uint64_t*)p8A;

	pC[0 ] =  p64A[0]>>0;
	pC[2 ] = (p64A[0]>>VECT_BASE);
	pC[4 ] = (p64A[0]>>(2*VECT_BASE)) | (p64A[1]<<8);

	pC[6 ] = (p64A[1]>>20);
	pC[8 ] = (p64A[1]>>(20+VECT_BASE)) | (p64A[2]<<16);

	pC[10] = (p64A[2]>>12);
	pC[12] = (p64A[2]>>(12+VECT_BASE)) | (p64A[3]<<24);

	pC[1 ] = (p64A[3]>>4);
	pC[3 ] = (p64A[3]>>(4+VECT_BASE));
	pC[5 ] = (p64A[3]>>(4+2*VECT_BASE)) | (p64A[4]<<4);

	pC[7 ] = (p64A[4]>>24);
	pC[9 ] = (p64A[4]>>(24+VECT_BASE)) | (p64A[5]<<12);

	pC[11] = (p64A[5]>>16);
	pC[13] = (p64A[5]>>(16+VECT_BASE));

	for(i=0;i<NUM_WORDS_64B_NISTP384;i++)
	{
		pC[i] &= mask;
	}
}

void Element_1w_h0h7_To_str_bytes(uint8_t *p8C, uint64_t *puA)
{
	/**
	* It only accepts positive coefficients.
	* In order to remove negative coefficients, compute compress()
	*/
	int i;
	int64_t *pA = (int64_t*)puA;
	__int128_t a[NUM_WORDS_64B_NISTP384];
	__int128_t c[6];
	int64_t * p64C = (int64_t*)p8C;
	for(i=0;i< NUM_WORDS_64B_NISTP384;i++)
	{
		a[i] = (__int128_t)pA[i];
	}

	__int128_t tmp = a[13]>>(VECT_BASE-8);
	a[13] &= (((__int128_t)1<<(VECT_BASE-8))-1);

	a[0] += tmp;
	a[2] -= tmp<<4;
	a[6] += tmp<<12;
	a[8] += tmp<<16;

	c[0] =              (a[4 ]<<( 2*VECT_BASE))  + (a[2 ]<<VECT_BASE)     + (a[0]) ;
	c[1] = (c[0]>>64) + (a[8 ]<<(20+VECT_BASE))  + (a[6 ]<<20);
	c[2] = (c[1]>>64) + (a[12]<<(12+VECT_BASE))  + (a[10]<<12);
	c[3] = (c[2]>>64) + (a[5 ]<<(4+2*VECT_BASE)) + (a[3 ]<<(4+VECT_BASE)) + (a[1]<<4);
	c[4] = (c[3]>>64) + (a[9 ]<<(24+VECT_BASE))  + (a[7 ]<<24);
	c[5] = (c[4]>>64) + (a[13]<<(16+VECT_BASE))  + (a[11]<<16);

	tmp = (c[5]>>64);

	c[0] += tmp-(tmp<<32);
	c[1] += tmp<<32;
	c[2] += tmp;

	for(i=0;i<6;i++)
	{
		p64C[i]=c[i];
	}
}

inline void add_Element_1w_h0h7(uint64_t *pC, uint64_t *pA, uint64_t *pB)
{
	int i=0;
	for(i=0;i<NUM_WORDS_256B_NISTP384;i++)
	{
		__m256i A = LOAD(pA+i);
		__m256i B = LOAD(pB+i);
		STORE(pC+i,ADD(A,B));
	}
}

static const Element_1w_H0H7 CONST_2P_ELEMENT = {
		0x1ffffefe,0x1ffffffe,
		0x2000101e,0x1ffffffe,
		0x1ffffffe,0x1ffffffe,
		0x1fefdffe,0x1ffffffe,
		0x1efdfffe,0x1ffffffe,
		0x1ffffffe,0x1ffffffe,
		0x1ffffffe,0x101ffffe
};

static const Element_1w_H0H7 CONST_2_32P_ELEMENT = {
        0x1ffffefe00000000,0x1ffffffe00000000,
		0x2000101e00000000,0x1ffffffe00000000,
		0x1ffffffe00000000,0x1ffffffe00000000,
		0x1fefdffe00000000,0x1ffffffe00000000,
		0x1efdfffe00000000,0x1ffffffe00000000,
		0x1ffffffe00000000,0x1ffffffe00000000,
		0x1ffffffe00000000,0x101ffffe00000000
};

void neg_Element_1w_h0h7(uint64_t *pA)
{
	int i=0;
	for(i=0;i<NUM_WORDS_256B_NISTP384;i++)
	{
		__m256i A = LOAD(pA+i);
		__m256i _2P = LOAD(CONST_2P_ELEMENT+i);
		STORE(pA+i,SUB(_2P,A));
	}
}

inline void sub_Element_1w_h0h7(uint64_t *pC, uint64_t *pA, uint64_t *pB)
{
	int i=0;
	for(i=0;i<NUM_WORDS_256B_NISTP384;i++)
	{
		__m256i A = LOAD(pA+i);
		__m256i B = LOAD(pB+i);
		__m256i _2P = LOAD(CONST_2P_ELEMENT+i);
		STORE(pC+i,ADD(A,SUB(_2P,B)));
	}
}
inline void addsub_Element_1w_h0h7(uint64_t *pA, uint64_t *pB)
{
	__m256i* _2P = (__m256i*)CONST_2P_ELEMENT;
	int i=0;
	for(i=0;i<NUM_WORDS_256B_NISTP384;i++)
	{
		__m256i A = LOAD(pA+i);
		__m256i B = LOAD(pB+i);
		__m256i C = ADD(A,B);
		__m256i D = ADD(A,SUB(_2P[i],B));
		STORE(pA+i,C);
		STORE(pB+i,D);
	}
}
/**
 * Computes:
 *
 * C = -(B+A) as  C = (2P-A)-B
 * D =  (B-A) as  D = (2P-A)+B
 */
inline void naddsub_Element_1w_h0h7(uint64_t *pC, uint64_t *pD, uint64_t *pA, uint64_t *pB)
{
	__m256i* _2P = (__m256i*)CONST_2P_ELEMENT;
	int i=0;
	for(i=0;i<NUM_WORDS_256B_NISTP384;i++)
	{
		__m256i A = LOAD(pA+i);
		__m256i B = LOAD(pB+i);
		__m256i T = SUB(_2P[i],A);
		__m256i C = SUB(T,B);
		__m256i D = ADD(T,B);
		STORE(pC+i,C);
		STORE(pD+i,D);
	}
}
#define PI_1w() \
	tmp = b6;	\
	b6 = b5;	\
	b5 = b4;	\
	b4 = b3;	\
	b3 = b2;	\
	b2 = b1;	\
	b1 = b0;	\
	b0 = _mm_slli_si128(tmp, 8);											\
	a13 = _mm_srli_si128(tmp, 8);											\
	b0 = _mm_add_epi64(b0, _mm_slli_epi64(_mm_and_si128(mask20, a13), 8));	\
	b1 = _mm_add_epi64(b1, _mm_srli_epi64(a13, 20));						\
	b1 = _mm_sub_epi64(b1, _mm_slli_epi64(_mm_and_si128(mask16, a13), 12));	\
	b2 = _mm_sub_epi64(b2, _mm_srli_epi64(a13, 16));						\
	b3 = _mm_add_epi64(b3, _mm_slli_epi64(_mm_and_si128(mask8, a13), 20));	\
	b4 = _mm_add_epi64(b4, _mm_srli_epi64(a13, 8));						    \
	b4 = _mm_add_epi64(b4, _mm_slli_epi64(_mm_and_si128(mask4, a13), 24));	\
	b5 = _mm_add_epi64(b5, _mm_srli_epi64(a13, 4));

static void mul_schoolbook_Element_1w_h0h7(uint64_t *C, uint64_t *A, uint64_t *B)
{
	int i,j;
	const __m128i mask20 = _mm_set_epi64x(0x0,((uint64_t)1<<20)-1);
	const __m128i mask16 = _mm_set_epi64x(0x0,((uint64_t)1<<16)-1);
	const __m128i mask8 = _mm_set_epi64x(0x0,((uint64_t)1<<8)-1);
	const __m128i mask4 = _mm_set_epi64x(0x0,((uint64_t)1<<4)-1);
	const __m128i M[2] = { _mm_set1_epi64x(0x0706050403020100), _mm_set1_epi64x(0x0F0E0D0C0B0A0908) };

	__m128i ai,tmp,a13;
	__m128i b0,b1,b2,b3,b4,b5,b6;
	__m128i c0,c1,c2,c3,c4,c5,c6;

	b0 = _mm_load_si128((__m128i*)B+0);
	b1 = _mm_load_si128((__m128i*)B+1);
	b2 = _mm_load_si128((__m128i*)B+2);
	b3 = _mm_load_si128((__m128i*)B+3);
	b4 = _mm_load_si128((__m128i*)B+4);
	b5 = _mm_load_si128((__m128i*)B+5);
	b6 = _mm_load_si128((__m128i*)B+6);

	ai = _mm_shuffle_epi8(_mm_load_si128((__m128i *) A + 0), M[0]);
	c0 = _mm_mul_epi32(b0, ai);
	c1 = _mm_mul_epi32(b1, ai);
	c2 = _mm_mul_epi32(b2, ai);
	c3 = _mm_mul_epi32(b3, ai);
	c4 = _mm_mul_epi32(b4, ai);
	c5 = _mm_mul_epi32(b5, ai);
	c6 = _mm_mul_epi32(b6, ai);

	i=1;
	for(j=0;j<2;j++)
	{
		for (; i < 7; i++)
		{
			/* Pi transformation */
			PI_1w()
			ai = _mm_shuffle_epi8(_mm_load_si128((__m128i *) A + i), M[j]);
			c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
			c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
			c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
			c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
			c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
			c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
			c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
		}
		i=0;
	}

	_mm_store_si128((__m128i*)C+0,c0);
	_mm_store_si128((__m128i*)C+1,c1);
	_mm_store_si128((__m128i*)C+2,c2);
	_mm_store_si128((__m128i*)C+3,c3);
	_mm_store_si128((__m128i*)C+4,c4);
	_mm_store_si128((__m128i*)C+5,c5);
	_mm_store_si128((__m128i*)C+6,c6);
}

inline void mul_Element_1w_h0h7(uint64_t *pC, uint64_t *pA, uint64_t *pB)
{
	mul_schoolbook_Element_1w_h0h7(pC, pA, pB);
}



void sqrn_Element_1w_h0h7(uint64_t *  C,int times)
{
	int i;
	for(i=0;i<times;i++)
	{
		sqr_Element_1w_h0h7(C);
		compress_Element_1w_h0h7(C);
	}
}
#define copy_Element_1w_h0h7(C,A)\
	STORE(C+0,LOAD(A+0));\
	STORE(C+1,LOAD(A+1));\
	STORE(C+2,LOAD(A+2));\
	STORE(C+3,LOAD(A+3));

inline void sqr_Element_1w_h0h7(uint64_t *  C)
{
	const __m128i mask20 = _mm_set_epi64x(0x0,((uint64_t)1<<20)-1);
	const __m128i mask16 = _mm_set_epi64x(0x0,((uint64_t)1<<16)-1);
	const __m128i mask8  = _mm_set_epi64x(0x0,((uint64_t)1<< 8)-1);
	const __m128i mask4  = _mm_set_epi64x(0x0,((uint64_t)1<< 4)-1);

	__m128i ai,tmp,a13;
	__m128i b0,b1,b2,b3,b4,b5,b6;
	__m128i c0,c1,c2,c3,c4,c5,c6;

	b0 = _mm_load_si128((__m128i*)C+0);
	b1 = _mm_load_si128((__m128i*)C+1);
	b2 = _mm_load_si128((__m128i*)C+2);
	b3 = _mm_load_si128((__m128i*)C+3);
	b4 = _mm_load_si128((__m128i*)C+4);
	b5 = _mm_load_si128((__m128i*)C+5);
	b6 = _mm_load_si128((__m128i*)C+6);

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 0), 0x44);
	c0 = _mm_mul_epi32(b0, ai);
	c1 = _mm_mul_epi32(b1, ai);
	c2 = _mm_mul_epi32(b2, ai);
	c3 = _mm_mul_epi32(b3, ai);
	c4 = _mm_mul_epi32(b4, ai);
	c5 = _mm_mul_epi32(b5, ai);
	c6 = _mm_mul_epi32(b6, ai);
	PI_1w();

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 1), 0x44);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 2), 0x44);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 3), 0x44);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 4), 0x44);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 5), 0x44);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 6), 0x44);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 0), 0xEE);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 1), 0xEE);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 2), 0xEE);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 3), 0xEE);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 4), 0xEE);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 5), 0xEE);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));
	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)C + 6), 0xEE);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));

	_mm_store_si128((__m128i*)C+0, c0);
	_mm_store_si128((__m128i*)C+1, c1);
	_mm_store_si128((__m128i*)C+2, c2);
	_mm_store_si128((__m128i*)C+3, c3);
	_mm_store_si128((__m128i*)C+4, c4);
	_mm_store_si128((__m128i*)C+5, c5);
	_mm_store_si128((__m128i*)C+6, c6);
}

inline void sqr_complex_Element_1w_h0h7(uint64_t *A)
{
	const __m128i mask20 = _mm_set_epi64x(0x0,((uint64_t)1<<20)-1);
	const __m128i mask16 = _mm_set_epi64x(0x0,((uint64_t)1<<16)-1);
	const __m128i mask8 = _mm_set_epi64x(0x0,((uint64_t)1<<8)-1);
	const __m128i mask4 = _mm_set_epi64x(0x0,((uint64_t)1<<4)-1);

	__m128i ai,ai2,tmp,a13;
	__m128i b0,b1,b2,b3,b4,b5,b6;
	__m128i c0,c1,c2,c3,c4,c5,c6;

	b0 = _mm_load_si128((__m128i*)A+0);
	b1 = _mm_load_si128((__m128i*)A+1);
	b2 = _mm_load_si128((__m128i*)A+2);
	b3 = _mm_load_si128((__m128i*)A+3);
	b4 = _mm_load_si128((__m128i*)A+4);
	b5 = _mm_load_si128((__m128i*)A+5);
	b6 = _mm_load_si128((__m128i*)A+6);

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 0), 0x44);
	ai2 = _mm_add_epi64(ai,ai);
	c0 = _mm_mul_epi32(b0, ai);
	c1 = _mm_mul_epi32(b1, ai2);
	c2 = _mm_mul_epi32(b2, ai2);
	c3 = _mm_mul_epi32(b3, ai2);
	c4 = _mm_mul_epi32(b4, ai2);
	c5 = _mm_mul_epi32(b5, ai2);
	c6 = _mm_mul_epi32(b6, ai2);

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 1), 0x44);
	ai2 = _mm_add_epi64(ai,ai);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai2));
	/*c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));*/
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai2));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai2));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai2));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai2));

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 2), 0x44);
	ai2 = _mm_add_epi64(ai,ai);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai2));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai2));
	/*c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));*/
	/*c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));*/
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai2));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai2));

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 3), 0x44);
	ai2 = _mm_add_epi64(ai,ai);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai2));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai2));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai2));
	/*c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));*/
	/*c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));*/
	/*c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));*/
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 4), 0x44);
	ai2 = _mm_add_epi64(ai,ai);
	/*c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai2));*/
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai2));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai2));
	/*c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));*/
	/*c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));*/
	/*c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));*/

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 5), 0x44);
	ai2 = _mm_add_epi64(ai,ai);
	/*c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));*/
	/*c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));*/
	/*c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));*/
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai2));
	/*c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));*/
	/*c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));*/

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 6), 0x44);
	/*c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));*/
	/*c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));*/
	/*c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));*/
	/*c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));*/
	/*c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));*/
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	/*c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));*/


	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 0), 0xEE);
	ai2 = _mm_add_epi64(ai,ai);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai2));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai2));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai2));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai2));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai2));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai2));

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 1), 0xEE);
	ai2 = _mm_add_epi64(ai,ai);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai2));
	/*c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));*/
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai2));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai2));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai2));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai2));

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 2), 0xEE);
	ai2 = _mm_add_epi64(ai,ai);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai2));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai2));
	/*c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));*/
	/*c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));*/
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai2));
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai2));

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 3), 0xEE);
	ai2 = _mm_add_epi64(ai,ai);
	c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai2));
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai2));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai2));
	/*c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));*/
	/*c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));*/
	/*c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));*/
	c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 4), 0xEE);
	ai2 = _mm_add_epi64(ai,ai);
	/*c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));*/
	c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai2));
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai2));
	/*c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));*/
	/*c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));*/
	/*c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));*/

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 5), 0xEE);
	ai2 = _mm_add_epi64(ai,ai);
	/*c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));*/
	/*c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));*/
	/*c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));*/
	c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai2));
	/*c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));*/
	/*c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));*/

	PI_1w();
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i *) A + 6), 0xEE);
	/*c0 = _mm_add_epi64(c0, _mm_mul_epi32(b0, ai));*/
	/*c1 = _mm_add_epi64(c1, _mm_mul_epi32(b1, ai));*/
	/*c2 = _mm_add_epi64(c2, _mm_mul_epi32(b2, ai));*/
	/*c3 = _mm_add_epi64(c3, _mm_mul_epi32(b3, ai));*/
	/*c4 = _mm_add_epi64(c4, _mm_mul_epi32(b4, ai));*/
	c5 = _mm_add_epi64(c5, _mm_mul_epi32(b5, ai));
	/*c6 = _mm_add_epi64(c6, _mm_mul_epi32(b6, ai));*/


	_mm_store_si128((__m128i*)A+0,c0);
	_mm_store_si128((__m128i*)A+1,c1);
	_mm_store_si128((__m128i*)A+2,c2);
	_mm_store_si128((__m128i*)A+3,c3);
	_mm_store_si128((__m128i*)A+4,c4);
	_mm_store_si128((__m128i*)A+5,c5);
	_mm_store_si128((__m128i*)A+6,c6);
}


void compress_Element_1w_h0h7(uint64_t *A)
{
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE) - 1;
	const __m128i mask = _mm_set_epi32(0, ones, 0, ones);
	const __m128i mask20 = _mm_set_epi64x(0x0,((uint64_t)1<<20)-1);
	const __m128i mask16 = _mm_set_epi64x(0x0,((uint64_t)1<<16)-1);
	const __m128i mask8 = _mm_set_epi64x(0x0,((uint64_t)1<<8)-1);
	const __m128i mask4 = _mm_set_epi64x(0x0,((uint64_t)1<<4)-1);
	const __m128i* _2_32P = (__m128i*)CONST_2_32P_ELEMENT;

	__m128i c0 = _mm_load_si128((__m128i*)A+0);
	__m128i c1 = _mm_load_si128((__m128i*)A+1);
	__m128i c2 = _mm_load_si128((__m128i*)A+2);
	__m128i c3 = _mm_load_si128((__m128i*)A+3);
	__m128i c4 = _mm_load_si128((__m128i*)A+4);
	__m128i c5 = _mm_load_si128((__m128i*)A+5);
	__m128i c6 = _mm_load_si128((__m128i*)A+6);

	__m128i h0_h7,  h1_h8,  h2_h9, h3_h10,
			h4_h11, h5_h12, h6_h13, h13, h6;

	c0 = _mm_add_epi64(c0,_2_32P[0]);
	c1 = _mm_add_epi64(c1,_2_32P[1]);
	c2 = _mm_add_epi64(c2,_2_32P[2]);
	c3 = _mm_add_epi64(c3,_2_32P[3]);
	c4 = _mm_add_epi64(c4,_2_32P[4]);
	c5 = _mm_add_epi64(c5,_2_32P[5]);
	c6 = _mm_add_epi64(c6,_2_32P[6]);

	h6_h13 = _mm_srli_epi64(c6, VECT_BASE);
	c6 = _mm_and_si128(c6, mask);

	h6  = _mm_slli_si128(h6_h13, 8);
	h13 = _mm_srli_si128(h6_h13, 8);
	c0 = _mm_add_epi64(c0,h6);
	c0 = _mm_add_epi64(c0, _mm_slli_epi64(_mm_and_si128(mask20, h13), 8));
	c1 = _mm_add_epi64(c1, _mm_srli_epi64(h13, 20));
	c1 = _mm_sub_epi64(c1, _mm_slli_epi64(_mm_and_si128(mask16, h13), 12));
	c2 = _mm_sub_epi64(c2, _mm_srli_epi64(h13, 16));
	c3 = _mm_add_epi64(c3, _mm_slli_epi64(_mm_and_si128(mask8, h13), 20));
	c4 = _mm_add_epi64(c4, _mm_srli_epi64(h13, 8));
	c4 = _mm_add_epi64(c4, _mm_slli_epi64(_mm_and_si128(mask4, h13), 24));
	c5 = _mm_add_epi64(c5, _mm_srli_epi64(h13, 4));

	h0_h7 = _mm_srli_epi64(c0, VECT_BASE);
	c0 = _mm_and_si128(c0, mask);
	c1 = _mm_add_epi64(c1, h0_h7);

	h1_h8 = _mm_srli_epi64(c1, VECT_BASE);
	c1 = _mm_and_si128(c1, mask);
	c2 = _mm_add_epi64(c2, h1_h8);

	h2_h9 = _mm_srli_epi64(c2, VECT_BASE);
	c2 = _mm_and_si128(c2, mask);
	c3 = _mm_add_epi64(c3, h2_h9);

	h3_h10 = _mm_srli_epi64(c3, VECT_BASE);
	c3 = _mm_and_si128(c3, mask);
	c4 = _mm_add_epi64(c4, h3_h10);

	h4_h11 = _mm_srli_epi64(c4, VECT_BASE);
	c4 = _mm_and_si128(c4, mask);
	c5 = _mm_add_epi64(c5, h4_h11);

	h5_h12 = _mm_srli_epi64(c5, VECT_BASE);
	c5 = _mm_and_si128(c5, mask);
	c6 = _mm_add_epi64(c6, h5_h12);

	h6_h13 = _mm_srli_epi64(c6, VECT_BASE);
	c6 = _mm_and_si128(c6, mask);

	h6  = _mm_slli_si128(h6_h13, 8);
	h13 = _mm_srli_si128(h6_h13, 8);
	c0 = _mm_add_epi64(c0, h6);
	c0 = _mm_add_epi64(c0, _mm_slli_epi64(_mm_and_si128(mask20, h13), 8));
	c1 = _mm_sub_epi64(c1, _mm_slli_epi64(_mm_and_si128(mask16, h13), 12));
	c3 = _mm_add_epi64(c3, _mm_slli_epi64(_mm_and_si128(mask8, h13), 20));
	c4 = _mm_add_epi64(c4, _mm_slli_epi64(_mm_and_si128(mask4, h13), 24));
	c5 = _mm_add_epi64(c5, _mm_srli_epi64(h13, 4));

	_mm_store_si128((__m128i*)A+0,c0);
	_mm_store_si128((__m128i*)A+1,c1);
	_mm_store_si128((__m128i*)A+2,c2);
	_mm_store_si128((__m128i*)A+3,c3);
	_mm_store_si128((__m128i*)A+4,c4);
	_mm_store_si128((__m128i*)A+5,c5);
	_mm_store_si128((__m128i*)A+6,c6);
}

void compressfast_Element_1w_h0h7(uint64_t *pA)
{
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE) - 1;
	const __m128i mask  = _mm_set1_epi64x(ones);
	const __m128i mask20 = _mm_set_epi64x(0x0,((uint64_t)1<<20)-1);
	const __m128i mask16 = _mm_set_epi64x(0x0,((uint64_t)1<<16)-1);
	const __m128i mask8 = _mm_set_epi64x(0x0,((uint64_t)1<<8)-1);
	const __m128i mask4 = _mm_set_epi64x(0x0,((uint64_t)1<<4)-1);

	__m128i A0,A1,A2,A3,A4,A5,A6;
	__m128i l0,l1,l2,l3,l4,l5,l6;
	__m128i m0,m1,m2,m3,m4,m5,m6,m13;
	__m128i h0,h1,h2,h3,h4,h5,h6,h12,h13;
	__m128i c0,c1,c2,c3,c4,c5,c6;

	A0 = _mm_load_si128((__m128i*)pA+0);
	A1 = _mm_load_si128((__m128i*)pA+1);
	A2 = _mm_load_si128((__m128i*)pA+2);
	A3 = _mm_load_si128((__m128i*)pA+3);
	A4 = _mm_load_si128((__m128i*)pA+4);
	A5 = _mm_load_si128((__m128i*)pA+5);
	A6 = _mm_load_si128((__m128i*)pA+6);

	l0 = _mm_and_si128(A0,mask);	m0 = _mm_and_si128(mask,_mm_srli_epi64(A0,VECT_BASE));	h0 = _mm_srli_epi64(A0,2*VECT_BASE);
	l1 = _mm_and_si128(A1,mask);	m1 = _mm_and_si128(mask,_mm_srli_epi64(A1,VECT_BASE));	h1 = _mm_srli_epi64(A1,2*VECT_BASE);
	l2 = _mm_and_si128(A2,mask);	m2 = _mm_and_si128(mask,_mm_srli_epi64(A2,VECT_BASE));	h2 = _mm_srli_epi64(A2,2*VECT_BASE);
	l3 = _mm_and_si128(A3,mask);	m3 = _mm_and_si128(mask,_mm_srli_epi64(A3,VECT_BASE));	h3 = _mm_srli_epi64(A3,2*VECT_BASE);
	l4 = _mm_and_si128(A4,mask);	m4 = _mm_and_si128(mask,_mm_srli_epi64(A4,VECT_BASE));	h4 = _mm_srli_epi64(A4,2*VECT_BASE);
	l5 = _mm_and_si128(A5,mask);	m5 = _mm_and_si128(mask,_mm_srli_epi64(A5,VECT_BASE));	h5 = _mm_srli_epi64(A5,2*VECT_BASE);
	l6 = _mm_and_si128(A6,mask);	m6 = _mm_and_si128(mask,_mm_srli_epi64(A6,VECT_BASE));	h6 = _mm_srli_epi64(A6,2*VECT_BASE);

	c0 = _mm_add_epi64(l0,_mm_slli_si128(_mm_add_epi64(m6,h5),8));
	c1 = _mm_add_epi64(l1,_mm_add_epi64(m0,_mm_slli_si128(h6,8)));
	c2 = _mm_add_epi64(l2,_mm_add_epi64(m1,h0));
	c3 = _mm_add_epi64(l3,_mm_add_epi64(m2,h1));
	c4 = _mm_add_epi64(l4,_mm_add_epi64(m3,h2));
	c5 = _mm_add_epi64(l5,_mm_add_epi64(m4,h3));
	c6 = _mm_add_epi64(l6,_mm_add_epi64(m5,h4));

	h12 = _mm_srli_si128(h5,8);
	h13 = _mm_srli_si128(h6,8);

	c0 = _mm_add_epi64(c0,_mm_slli_epi64(h12,8));
	c1 = _mm_sub_epi64(c1,_mm_slli_epi64(h12,12));
	c3 = _mm_add_epi64(c3,_mm_slli_epi64(h12,20));
	c4 = _mm_add_epi64(c4,_mm_slli_epi64(h12,24));

	c1 = _mm_add_epi64(c1,_mm_slli_epi64(h13,8));
	c2 = _mm_sub_epi64(c2,_mm_slli_epi64(h13,12));
	c4 = _mm_add_epi64(c4,_mm_slli_epi64(h13,20));
	c5 = _mm_add_epi64(c5,_mm_slli_epi64(h13,24));

	m13 = _mm_srli_si128(m6,8);
	c0 = _mm_add_epi64(c0, _mm_slli_epi64(_mm_and_si128(mask20,m13), 8));
	c1 = _mm_add_epi64(c1, _mm_srli_epi64(m13,20));
	c1 = _mm_sub_epi64(c1, _mm_slli_epi64(_mm_and_si128(mask16,m13),12));
	c2 = _mm_sub_epi64(c2, _mm_srli_epi64(m13,16));
	c3 = _mm_add_epi64(c3, _mm_slli_epi64(_mm_and_si128(mask8 ,m13),20));
	c4 = _mm_add_epi64(c4, _mm_srli_epi64(m13, 8));
	c4 = _mm_add_epi64(c4, _mm_slli_epi64(_mm_and_si128(mask4 ,m13),24));
	c5 = _mm_add_epi64(c5, _mm_srli_epi64(m13, 4));

	_mm_store_si128((__m128i*)pA+0,c0);
	_mm_store_si128((__m128i*)pA+1,c1);
	_mm_store_si128((__m128i*)pA+2,c2);
	_mm_store_si128((__m128i*)pA+3,c3);
	_mm_store_si128((__m128i*)pA+4,c4);
	_mm_store_si128((__m128i*)pA+5,c5);
	_mm_store_si128((__m128i*)pA+6,c6);
}

void new_compressfast_Element_1w_h0h7(uint64_t * pA)
{
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE) - 1;
	const __m128i mask  = _mm_set1_epi64x(ones);
	const __m128i mask20 = _mm_set_epi64x(0x0,((uint64_t)1<<20)-1);
	const __m128i mask16 = _mm_set_epi64x(0x0,((uint64_t)1<<16)-1);
	const __m128i mask8 = _mm_set_epi64x(0x0,((uint64_t)1<<8)-1);
	const __m128i mask4 = _mm_set_epi64x(0x0,((uint64_t)1<<4)-1);

	__m128i A0,A1,A2,A3,A4,A5,A6;
	__m128i l0,l1,l2,l3,l4,l5,l6;
	__m128i m0,m1,m2,m3,m4,m5,m6,m13;
	__m128i c0,c1,c2,c3,c4,c5,c6;

	A0 = _mm_load_si128((__m128i*)pA+0);
	A1 = _mm_load_si128((__m128i*)pA+1);
	A2 = _mm_load_si128((__m128i*)pA+2);
	A3 = _mm_load_si128((__m128i*)pA+3);
	A4 = _mm_load_si128((__m128i*)pA+4);
	A5 = _mm_load_si128((__m128i*)pA+5);
	A6 = _mm_load_si128((__m128i*)pA+6);

	l0 = _mm_and_si128(A0,mask);	m0 = _mm_srli_epi64(A0,VECT_BASE);
	l1 = _mm_and_si128(A1,mask);	m1 = _mm_srli_epi64(A1,VECT_BASE);
	l2 = _mm_and_si128(A2,mask);	m2 = _mm_srli_epi64(A2,VECT_BASE);
	l3 = _mm_and_si128(A3,mask);	m3 = _mm_srli_epi64(A3,VECT_BASE);
	l4 = _mm_and_si128(A4,mask);	m4 = _mm_srli_epi64(A4,VECT_BASE);
	l5 = _mm_and_si128(A5,mask);	m5 = _mm_srli_epi64(A5,VECT_BASE);
	l6 = _mm_and_si128(A6,mask);	m6 = _mm_srli_epi64(A6,VECT_BASE);

	c0 = _mm_add_epi64(l0,_mm_slli_si128(m6,8));
	c1 = _mm_add_epi64(l1,m0);
	c2 = _mm_add_epi64(l2,m1);
	c3 = _mm_add_epi64(l3,m2);
	c4 = _mm_add_epi64(l4,m3);
	c5 = _mm_add_epi64(l5,m4);
	c6 = _mm_add_epi64(l6,m5);

	m13 = _mm_srli_si128(m6,8);
	c0 = _mm_add_epi64(c0, _mm_slli_epi64(_mm_and_si128(mask20,m13), 8));
	c1 = _mm_add_epi64(c1, _mm_srli_epi64(m13,20));
	c1 = _mm_sub_epi64(c1, _mm_slli_epi64(_mm_and_si128(mask16,m13),12));
	c2 = _mm_sub_epi64(c2, _mm_srli_epi64(m13,16));
	c3 = _mm_add_epi64(c3, _mm_slli_epi64(_mm_and_si128(mask8 ,m13),20));
	c4 = _mm_add_epi64(c4, _mm_srli_epi64(m13, 8));
	c4 = _mm_add_epi64(c4, _mm_slli_epi64(_mm_and_si128(mask4 ,m13),24));
	c5 = _mm_add_epi64(c5, _mm_srli_epi64(m13, 4));

	_mm_store_si128((__m128i*)pA+0,c0);
	_mm_store_si128((__m128i*)pA+1,c1);
	_mm_store_si128((__m128i*)pA+2,c2);
	_mm_store_si128((__m128i*)pA+3,c3);
	_mm_store_si128((__m128i*)pA+4,c4);
	_mm_store_si128((__m128i*)pA+5,c5);
	_mm_store_si128((__m128i*)pA+6,c6);
}


void inv_Element_1w_h0h7(uint64_t * __restrict pC, uint64_t * __restrict pA)
{
	int i;
	copy_Element_1w_h0h7(pC,pA);
	for (i = 382; i > 128; i--)
	{
		sqr_Element_1w_h0h7(pC);
		compress_Element_1w_h0h7(pC);
		mul_Element_1w_h0h7(pC,pC,pA);
		compress_Element_1w_h0h7(pC);
	}
	sqr_Element_1w_h0h7(pC);
	compress_Element_1w_h0h7(pC);
	for (i = 127; i >= 96; i--)
	{
		sqr_Element_1w_h0h7(pC);
		compress_Element_1w_h0h7(pC);
		mul_Element_1w_h0h7(pC,pC,pA);
		compress_Element_1w_h0h7(pC);
	}
	for (i = 95; i >=32; i--)
	{
		sqr_Element_1w_h0h7(pC);
		compress_Element_1w_h0h7(pC);
	}
	for (i = 31; i > 1; i--)
	{
		sqr_Element_1w_h0h7(pC);
		compress_Element_1w_h0h7(pC);
		mul_Element_1w_h0h7(pC,pC,pA);
		compress_Element_1w_h0h7(pC);
	}
	sqr_Element_1w_h0h7(pC);
	compress_Element_1w_h0h7(pC);

	sqr_Element_1w_h0h7(pC);
	compress_Element_1w_h0h7(pC);
	mul_Element_1w_h0h7(pC,pC,pA);
	compress_Element_1w_h0h7(pC);
	/*for (i = 382; i >= 0; i--)
	{
		sqr_Element_1w_h0h7(pC);
		compress_Element_1w_h0h7(pC);
		if( i== 128 || i== 1 || (32<=i && i<96))
		{
			continue;
		}
		else
		{
			mul_Element_1w_h0h7(pC,pC,pA);
			compress_Element_1w_h0h7(pC);
		}
	}*/
}
