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
	singleH0H7_To_str_bytes(a, A);
	singleH0H7_To_str_bytes(b, B);
	return areEqual_str_bytes(a,b);
}

void print_python_Element_1w_h0h7(uint64_t *A)
{
	int i;
	printf("s = [ ");
	for(i=0;i<(NUM_WORDS_64B_NISTP384)-1;i+=2)
	{
		if( ((signed)A[i])<0)		printf("-");
		printf("0x%.8lx, ", A[i] );
	}
	for(i=1;i<(NUM_WORDS_64B_NISTP384)-1;i+=2)
	{
		if( ((signed)A[i])<0)		printf("-");
		printf("0x%.8lx, ", A[i] );
	}
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
	singleH0H7_To_str_bytes(a, A);
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
	const uint64_t mask0 = (((uint64_t)1)<<VECT_BASE0)-1;
	const uint64_t mask1 = (((uint64_t)1)<<VECT_BASE1)-1;
	const uint64_t *p64A = (uint64_t*)p8A;

	pC[0 ] =  p64A[0]>>0;
	pC[2 ] = (p64A[0]>>VECT_BASE0);
	pC[4 ] = (p64A[0]>>(VECT_BASE0+VECT_BASE1)) | (p64A[1]<<9);

	pC[6 ] = (p64A[1]>>19);
	pC[8 ] = (p64A[1]>>(19+VECT_BASE1)) | (p64A[2]<<18);

	pC[10] = (p64A[2]>>10);
	pC[12] = (p64A[2]>>(10+VECT_BASE1)) | (p64A[3]<<VECT_BASE1);

	pC[1 ] = (p64A[3]>>1);
	pC[3 ] = (p64A[3]>>(1+VECT_BASE1));
	pC[5 ] = (p64A[3]>>(1+VECT_BASE0+VECT_BASE1)) | (p64A[4]<<8);

	pC[7 ] = (p64A[4]>>19);
	pC[9 ] = (p64A[4]>>(19+VECT_BASE0)) | (p64A[5]<<17);

	pC[11] = (p64A[5]>>10);
	pC[13] = (p64A[5]>>(10+VECT_BASE0));

	pC[ 0] &= mask0;		pC[ 1] &= mask1;
	pC[ 2] &= mask1;		pC[ 3] &= mask0;
	pC[ 4] &= mask0;		pC[ 5] &= mask1;
	pC[ 6] &= mask1;		pC[ 7] &= mask0;
	pC[ 8] &= mask0;		pC[ 9] &= mask1;
	pC[10] &= mask1;		pC[11] &= mask0;
	pC[12] &= mask0;		pC[13] &= mask1;

}

void singleH0H7_To_str_bytes(uint8_t *p8C, uint64_t *puA)
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

	__int128_t tmp = a[13]>>(VECT_BASE1-1);
	a[13] &= (((__int128_t)1<<(VECT_BASE1-1))-1);

	a[0] += tmp;
	a[2] -= tmp<<4;
	a[6] += tmp<<13;
	a[8] += tmp<<18;

	c[0] =              (a[4 ]<<(VECT_BASE0+VECT_BASE1))   + (a[2 ]<<VECT_BASE0)     + (a[0]) ;
	c[1] = (c[0]>>64) + (a[8 ]<<(19+VECT_BASE1))  + (a[6 ]<<19);
	c[2] = (c[1]>>64) + (a[12]<<(10+VECT_BASE1))  + (a[10]<<10);
	c[3] = (c[2]>>64) + (a[5 ]<<(1+VECT_BASE0+VECT_BASE1)) + (a[3 ]<<(1+VECT_BASE1)) + (a[1]<<1);
	c[4] = (c[3]>>64) + (a[9 ]<<(19+VECT_BASE0))  + (a[7 ]<<19);
	c[5] = (c[4]>>64) + (a[13]<<(10+VECT_BASE0))  + (a[11]<<10);

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
		0x1ffffffc,0x0ffffffe,
		0x0800003e,0x1ffffffe,
		0x1fffffff,0x0ffffffe,
		0x0fff7ffe,0x1ffffffe,
		0x1feffffe,0x0ffffffe,
		0x0ffffffe,0x1ffffffe,
		0x1ffffffe,0x0ffffffe
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


static void mul_schoolbook_Element_1w_h0h7(uint64_t *C, uint64_t *A, uint64_t *B)
{
	int i;
	const __m128i mask22 = _mm_set_epi64x(0x0,((uint64_t)1<<22)-1);
	const __m128i mask21 = _mm_set_epi64x(0x0,((uint64_t)1<<21)-1);
	const __m128i mask13 = _mm_set_epi64x(0x0,((uint64_t)1<<13)-1);
	const __m128i mask12 = _mm_set_epi64x(0x0,((uint64_t)1<<12)-1);
	const __m128i mask9 = _mm_set_epi64x(0x0,((uint64_t)1<<9)-1);
	__m128i ai, aH, aL, tmp,a13;
	__m128i b0,b1,b2,b3,b4,b5,b6;
	__m128i c0,c1,c2,c3,c4,c5,c6;

	b0 = _mm_load_si128((__m128i*)B+0);
	b1 = _mm_load_si128((__m128i*)B+1);
	b2 = _mm_load_si128((__m128i*)B+2);
	b3 = _mm_load_si128((__m128i*)B+3);
	b4 = _mm_load_si128((__m128i*)B+4);
	b5 = _mm_load_si128((__m128i*)B+5);
	b6 = _mm_load_si128((__m128i*)B+6);

	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)A+0),0x44);
	c0 = _mm_mul_epi32(b0, ai);
	c1 = _mm_mul_epi32(b1, ai);
	c2 = _mm_mul_epi32(b2, ai);
	c3 = _mm_mul_epi32(b3, ai);
	c4 = _mm_mul_epi32(b4, ai);
	c5 = _mm_mul_epi32(b5, ai);
	c6 = _mm_mul_epi32(b6, ai);


	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)A+1),0x44);
	aH = _mm_add_epi64(ai, ai);
	aL = _mm_blend_epi32(ai, aH, 0x3);
	aH = _mm_blend_epi32(ai, aH, 0xC);

	tmp = b6;
	b6 = b5;
	b5 = b4;
	b4 = b3;
	b3 = b2;
	b2 = b1;
	b1 = b0;
	b0 = _mm_shuffle_epi32(tmp,0x4E);

	a13 = _mm_move_epi64(b0);
	b0 = _mm_add_epi64(b0,a13);
	b1 = _mm_sub_epi64(b1,_mm_slli_epi64(_mm_and_si128(mask21,a13),6));
	b2 = _mm_sub_epi64(b2,_mm_srli_epi64(a13,21));
	b3 = _mm_add_epi64(b3,_mm_slli_epi64(_mm_and_si128(mask12,a13),15));
	b4 = _mm_add_epi64(b4,_mm_srli_epi64(a13,12));
	b4 = _mm_add_epi64(b4,_mm_slli_epi64(_mm_and_si128(mask9,a13),19));
	b5 = _mm_add_epi64(b5,_mm_srli_epi64(a13,9));

	c0 = _mm_add_epi64(c0,_mm_mul_epi32(b0, aL));
	c1 = _mm_add_epi64(c1,_mm_mul_epi32(b1, aH));
	c2 = _mm_add_epi64(c2,_mm_mul_epi32(b2, aL));
	c3 = _mm_add_epi64(c3,_mm_mul_epi32(b3, aH));
	c4 = _mm_add_epi64(c4,_mm_mul_epi32(b4, aL));
	c5 = _mm_add_epi64(c5,_mm_mul_epi32(b5, aH));
	c6 = _mm_add_epi64(c6,_mm_mul_epi32(b6, aL));

	goto end;
	ai = _mm_shuffle_epi32(_mm_load_si128((__m128i*)A+2),0x44);

	tmp = b6;
	b6 = b5;
	b5 = b4;
	b4 = b3;
	b3 = b2;
	b2 = b1;
	b1 = b0;

	a13 = _mm_move_epi64(tmp);
	b0 = _mm_add_epi64(b0,_mm_add_epi64(a13,a13));
	b1 = _mm_sub_epi64(b1,_mm_slli_epi64(_mm_and_si128(mask22,a13),5));
	b2 = _mm_sub_epi64(b2,_mm_srli_epi64(a13,22));
	b3 = _mm_add_epi64(b3,_mm_slli_epi64(_mm_and_si128(mask13,a13),14));
	b4 = _mm_add_epi64(b4,_mm_srli_epi64(a13,13));
	b4 = _mm_add_epi64(b4,_mm_slli_epi64(_mm_and_si128(mask9,a13),19));
	b5 = _mm_add_epi64(b5,_mm_srli_epi64(a13,9));

	c0 = _mm_add_epi64(c0,_mm_mul_epi32(b0, ai));
	c1 = _mm_add_epi64(c1,_mm_mul_epi32(b1, ai));
	c2 = _mm_add_epi64(c2,_mm_mul_epi32(b2, ai));
	c3 = _mm_add_epi64(c3,_mm_mul_epi32(b3, ai));
	c4 = _mm_add_epi64(c4,_mm_mul_epi32(b4, ai));
	c5 = _mm_add_epi64(c5,_mm_mul_epi32(b5, ai));
	c6 = _mm_add_epi64(c6,_mm_mul_epi32(b6, ai));
	end:

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


#define mul19_128(A)\
	A = _mm_shuffle_epi32(_mm_add_epi64(_mm_add_epi64(_mm_sllv_epi64(A, shift_4),_mm_sllv_epi64(A, shift_1)),A),0x4E);


void sqrn_Element_1w_h0h7(uint64_t * A, const int times)
{}

inline void sqr_Element_1w_h0h7(uint64_t *A)
{
	sqrn_Element_1w_h0h7(A, 1);
}


void compress_Element_1w_h0h7(uint64_t *A)
{
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE0) - 1;
	const __m128i mask = _mm_set_epi32(0, ones, 0, ones);

	__m128i c0 = _mm_load_si128((__m128i*)A+0);
	__m128i c1 = _mm_load_si128((__m128i*)A+1);
	__m128i c2 = _mm_load_si128((__m128i*)A+2);
	__m128i c3 = _mm_load_si128((__m128i*)A+3);
	__m128i c4 = _mm_load_si128((__m128i*)A+4);
	__m128i c5 = _mm_load_si128((__m128i*)A+5);
	__m128i c6 = _mm_load_si128((__m128i*)A+6);

	__m128i h0_h7,  h1_h8,  h2_h9, h3_h10,
			h4_h11, h5_h12, h6_h13;

	h0_h7 = _mm_srli_epi64(c0, VECT_BASE0);
	c0 = _mm_and_si128(c0, mask);
	c1 = _mm_add_epi64(c1, h0_h7);

	h1_h8 = _mm_srli_epi64(c1, VECT_BASE1);
	c1 = _mm_and_si128(c1, mask);
	c2 = _mm_add_epi64(c2, h1_h8);

	h2_h9 = _mm_srli_epi64(c2, VECT_BASE0);
	c2 = _mm_and_si128(c2, mask);
	c3 = _mm_add_epi64(c3, h2_h9);

	h3_h10 = _mm_srli_epi64(c3, VECT_BASE1);
	c3 = _mm_and_si128(c3, mask);
	c4 = _mm_add_epi64(c4, h3_h10);

	h4_h11 = _mm_srli_epi64(c4, VECT_BASE0);
	c4 = _mm_and_si128(c4, mask);
	c5 = _mm_add_epi64(c5, h4_h11);

	h5_h12 = _mm_srli_epi64(c5, VECT_BASE1);
	c5 = _mm_and_si128(c5, mask);
	c6 = _mm_add_epi64(c6, h5_h12);

	h6_h13 = _mm_srli_epi64(c6, VECT_BASE0);
	c6 = _mm_and_si128(c6, mask);

	/**
	 * LOW  h7  ->  h0
	 * HIGH h15 ->  h7
	 **/
	c0 = _mm_add_epi64(c0,_mm_blend_epi32(h6_h13,_mm_setzero_si128(),0x3));
	/**
	 * LOW  h7   \/  h0
	 * HIGH h15  /\  h7
	 **/
	c0 = _mm_add_epi64(c0,_mm_shuffle_epi32(h6_h13,0x4E));

	h0_h7 = _mm_srli_epi64(c0, VECT_BASE0);
	c0 = _mm_and_si128(c0, mask);
	c1 = _mm_add_epi64(c1, h0_h7);

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
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE0) - 1;
	const __m256i mask  = _mm256_set1_epi64x(ones);

	__m256i A0,A1,A2,A3;
	__m256i l0,l1,l2,l3;
	__m256i m0,m1,m2,m3;
	__m256i _m0,_m1,_m2,_m3;
	__m256i h0,h1,h2,h3;
	__m256i c0,c1,c2,c3;

	A0 = LOAD(pA+0);
	A1 = LOAD(pA+1);
	A2 = LOAD(pA+2);
	A3 = LOAD(pA+3);

	l0 = AND(A0,mask);
	l1 = AND(A1,mask);
	l2 = AND(A2,mask);
	l3 = AND(A3,mask);

	m0 = SHR(A0,VECT_BASE0);
	m1 = SHR(A1,VECT_BASE0);
	m2 = SHR(A2,VECT_BASE0);
	m3 = SHR(A3,VECT_BASE0);

	m0 = AND(m0,mask);
	m1 = AND(m1,mask);
	m2 = AND(m2,mask);
	m3 = AND(m3,mask);

	h0 = SHR(A0,2*VECT_BASE1);
	h1 = SHR(A1,2*VECT_BASE1);
	h2 = SHR(A2,2*VECT_BASE1);
	h3 = SHR(A3,2*VECT_BASE1);

	_m3 = SHUF(ADD(m3,SHR_128(m3)),0x4E);
	h3 = SHUF(ADD(h3,SHR_128(h3)),0x4E);

	_m0 = _mm256_permute2f128_si256(_m3,m0,0x21);
	_m1 = _mm256_permute2f128_si256(m0,m1,0x21);
	_m2 = _mm256_permute2f128_si256(m1,m2,0x21);
	_m3 = _mm256_permute2f128_si256(m2,m3,0x21);

	c0 = ADD(l0,_m0);
	c1 = ADD(l1,_m1);
	c2 = ADD(l2,_m2);
	c3 = ADD(l3,_m3);

	c0 = ADD(c0,h3);
	c1 = ADD(c1,h0);
	c2 = ADD(c2,h1);
	c3 = ADD(c3,h2);

	STORE(pA+0,c0);
	STORE(pA+1,c1);
	STORE(pA+2,c2);
	STORE(pA+3,c3);
}

void new_compressfast_Element_1w_h0h7(uint64_t * pA)
{
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE0) - 1;
	const __m256i mask  = _mm256_set1_epi64x(ones);

	__m256i A0,A1,A2,A3;
	__m256i l0,l1,l2,l3;
	__m256i m0,m1,m2,m3;
	__m256i _m0,_m1,_m2,_m3;
	__m256i c0,c1,c2,c3;

	A0 = LOAD(pA+0);
	A1 = LOAD(pA+1);
	A2 = LOAD(pA+2);
	A3 = LOAD(pA+3);

	l0 = AND(A0,mask);
	l1 = AND(A1,mask);
	l2 = AND(A2,mask);
	l3 = AND(A3,mask);

	m0 = SHR(A0,VECT_BASE1);
	m1 = SHR(A1,VECT_BASE1);
	m2 = SHR(A2,VECT_BASE1);
	m3 = SHR(A3,VECT_BASE1);

	_m3 = SHUF(ADD(m3,SHR_128(m3)),0x4E);

	_m0 = _mm256_permute2f128_si256(_m3,m0,0x21);
	_m1 = _mm256_permute2f128_si256(m0,m1,0x21);
	_m2 = _mm256_permute2f128_si256(m1,m2,0x21);
	_m3 = _mm256_permute2f128_si256(m2,m3,0x21);

	c0 = ADD(l0,_m0);
	c1 = ADD(l1,_m1);
	c2 = ADD(l2,_m2);
	c3 = ADD(l3,_m3);

	STORE(pA+0,c0);
	STORE(pA+1,c1);
	STORE(pA+2,c2);
	STORE(pA+3,c3);
}

#define copy_Element_1w_h0h7(C,A)\
	STORE(C+0,LOAD(A+0));\
	STORE(C+1,LOAD(A+1));\
	STORE(C+2,LOAD(A+2));\
	STORE(C+3,LOAD(A+3));

void invsqrt_Element_1w_h0h7(uint64_t * __restrict pC, uint64_t * __restrict pA, const int only_inverse)
{
	Element_1w_H0H7 x0,x1;
	uint64_t * T[4];

	T[0] = x0;
	T[1] = pC;
	T[2] = x1;
	T[3] = pA;

	copy_Element_1w_h0h7(T[1],T[3]);
	sqrn_Element_1w_h0h7(T[1],1);
	mul_Element_1w_h0h7(T[1],T[1],T[3]);
	compressfast_Element_1w_h0h7(T[1]);

	copy_Element_1w_h0h7(T[0],T[1]);
	sqrn_Element_1w_h0h7(T[0],1);
	mul_Element_1w_h0h7(T[0],T[0],T[3]);
	compressfast_Element_1w_h0h7(T[0]);

	copy_Element_1w_h0h7(T[1],T[0]);
	sqrn_Element_1w_h0h7(T[1],3);
	mul_Element_1w_h0h7(T[1],T[1],T[0]);
	compressfast_Element_1w_h0h7(T[1]);

	copy_Element_1w_h0h7(T[2],T[1]);
	sqrn_Element_1w_h0h7(T[2],6);
	mul_Element_1w_h0h7(T[2],T[2],T[1]);
	compressfast_Element_1w_h0h7(T[2]);

	copy_Element_1w_h0h7(T[1],T[2]);
	sqrn_Element_1w_h0h7(T[1],12);
	mul_Element_1w_h0h7(T[1],T[1],T[2]);
	compressfast_Element_1w_h0h7(T[1]);

	sqrn_Element_1w_h0h7(T[1],3);
	mul_Element_1w_h0h7(T[1],T[1],T[0]);
	compressfast_Element_1w_h0h7(T[1]);

	copy_Element_1w_h0h7(T[2],T[1]);
	sqrn_Element_1w_h0h7(T[2],27);
	mul_Element_1w_h0h7(T[2],T[2],T[1]);
	compressfast_Element_1w_h0h7(T[2]);

	copy_Element_1w_h0h7(T[1],T[2]);
	sqrn_Element_1w_h0h7(T[1],54);
	mul_Element_1w_h0h7(T[1],T[1],T[2]);
	compressfast_Element_1w_h0h7(T[1]);

	sqrn_Element_1w_h0h7(T[1],3);
	mul_Element_1w_h0h7(T[1],T[1],T[0]);
	compressfast_Element_1w_h0h7(T[1]);

	copy_Element_1w_h0h7(T[2],T[1]);
	sqrn_Element_1w_h0h7(T[2],111);
	mul_Element_1w_h0h7(T[2],T[2],T[1]);
	compressfast_Element_1w_h0h7(T[2]);

	copy_Element_1w_h0h7(T[1],T[2]);
	sqrn_Element_1w_h0h7(T[1],1);
	mul_Element_1w_h0h7(T[1],T[1],T[3]);
	compressfast_Element_1w_h0h7(T[1]);

	sqrn_Element_1w_h0h7(T[1],223);
	mul_Element_1w_h0h7(T[1],T[1],T[2]);
	compressfast_Element_1w_h0h7(T[1]);

	if(only_inverse != 0)
	{
		sqrn_Element_1w_h0h7(T[1],2);
		mul_Element_1w_h0h7(T[1],T[1],T[3]);
		compressfast_Element_1w_h0h7(T[1]);
	}

}
