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
	b0 = _mm_add_epi64(b0, _mm_slli_si128(_mm_and_si128(mask20, a13), 1));	\
	b1 = _mm_add_epi64(b1, _mm_srli_epi64(a13, 20));						\
	b1 = _mm_sub_epi64(b1, _mm_slli_epi64(_mm_and_si128(mask16, a13), 12));	\
	b2 = _mm_sub_epi64(b2, _mm_srli_si128(a13, 2));						\
	b3 = _mm_add_epi64(b3, _mm_slli_epi64(_mm_and_si128(mask8, a13), 20));	\
	b4 = _mm_add_epi64(b4, _mm_srli_si128(a13, 1));						    \
	b4 = _mm_add_epi64(b4, _mm_slli_si128(_mm_and_si128(mask4, a13), 3));	\
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


#define sqr_school_3x3(r0,r1,r2,r3,r4,s0,s1,s2) \
do{                                             \
	__m128i t2 = MUL128(s0,s2);                 \
	r0 = MUL128(s0,s0);                         \
	r1 = MUL128(s0,s1);                         \
	r1 = ADD128(r1,r1);                         \
 	r2 = MUL128(s1,s1);                         \
 	r2 = ADD128(r2,ADD128(t2,t2));              \
	r3 = MUL128(s1,s2);                         \
	r3 = ADD128(r3,r3);                         \
	r4 = MUL128(s2,s2);                         \
}while(0)

#define sqr_school_4x4(r0,r1,r2,r3,r4,r5,r6,s0,s1,s2,s3) \
do{                                                      \
	__m128i t2 = MUL128(s0,s2);                          \
	__m128i t4 = MUL128(s1,s3);                          \
	r0 = MUL128(s0,s0);                                  \
	r1 = MUL128(s0,s1);                                  \
	r1 = ADD128(r1,r1);                                  \
 	r2 = MUL128(s1,s1);                                  \
 	r2 = ADD128(r2,ADD128(t2,t2));                       \
	r3 = MUL128(s0,s3);                                  \
	r3 = ADD128(r3,MUL128(s1,s2));                       \
	r3 = ADD128(r3,r3);                                  \
	r4 = MUL128(s2,s2);                                  \
 	r4 = ADD128(r4,ADD128(t4,t4));                       \
	r5 = MUL128(s2,s3);                                  \
	r5 = ADD128(r5,r5);                                  \
	r6 = MUL128(s3,s3);                                  \
}while(0)

#define sqr_karat_7x7(h0,h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11,h12,  \
               f0,f1,f2,f3,f4,f5,f6)                              \
do{                                                               \
 	__m128i o0,o1,o2,o3,o4,o5,o6;                                 \
	__m128i p0,p1,p2,p3,p4;                                       \
	__m128i q0,q1,q2,q3,q4,q5,q6;                                 \
	sqr_school_4x4(o0,o1,o2,o3,o4,o5,o6,f0,f1,f2,f3);             \
	sqr_school_3x3(p0,p1,p2,p3,p4,f4,f5,f6);                      \
	sqr_school_4x4(q0,q1,q2,q3,q4,q5,q6,                          \
		ADD128(f0,f4),                                            \
		ADD128(f1,f5),                                            \
		ADD128(f2,f6),                                            \
		f3);                                                      \
    __m128i ref0 = SUB128(o4,p0);                                 \
    __m128i ref1 = SUB128(o5,p1);                                 \
    __m128i ref2 = SUB128(o6,p2);                                 \
	h0 = o0;                         h8  = SUB128(SUB128(q4,p4),ref0);  \
	h1 = o1;                         h9  = SUB128(q5,ref1);       \
	h2 = o2;                         h10 = SUB128(q6,ref2);       \
	h3 = o3;                         h11 = p3;                    \
	h4 = ADD128(ref0,SUB128(q0,o0)); h12 = p4;                    \
	h5 = ADD128(ref1,SUB128(q1,o1));                              \
	h6 = ADD128(ref2,SUB128(q2,o2));                              \
	h7 = SUB128(SUB128(q3,o3),p3);                                \
}while(0)

#define sqr_karate_7x7(h0,h1,h2,h3,h4,h5,h6,h7,                      \
               f0,f1,f2,f3)                                          \
do{                                                                  \
 	__m128i o0p0,o1p1,o2p2,o3p3,o4p4,o5p5,o6p6;                      \
	__m128i q0,q1,q2,q3,q4,q5,q6;                                    \
	sqr_school_4x4(o0p0,o1p1,o2p2,o3p3,o4p4,o5p5,o6p6,f0,f1,f2,f3);  \
	__m128i sF0 = ADD128(f0,SHUF128(f0,0x4E));                       \
	__m128i sF1 = ADD128(f1,SHUF128(f1,0x4E));                       \
	__m128i sF2 = ADD128(f2,SHUF128(f2,0x4E));                       \
	__m128i sF3 = ADD128(f3,SHUF128(f3,0x4E));                       \
                                                                     \
	sqr_school_4x4(q0,q1,q2,q3,q4,q5,q6,                             \
				  sF0,sF1,sF2,sF3);                                  \
																	 \
	h0 = ADD128(o0p0,BLEND32128(SUB128(q4,ADD128(o4p4,SHUF128(o4p4,0x4E))),ZERO128,0x33));  \
	h1 = ADD128(o1p1,BLEND32128(SUB128(q5,ADD128(o5p5,SHUF128(o5p5,0x4E))),ZERO128,0x33));  \
	h2 = ADD128(o2p2,BLEND32128(SUB128(q6,ADD128(o6p6,SHUF128(o6p6,0x4E))),ZERO128,0x33));  \
	h3 = o3p3;                                                       \
	h4 = ADD128(o4p4,BLEND32128(SUB128(q0,ADD128(o0p0,SHUF128(o0p0,0x4E))),ZERO128,0xCC));  \
	h5 = ADD128(o5p5,SUB128(q1,ADD128(o1p1,SHUF128(o1p1,0x4E))));    \
	h6 = ADD128(o6p6,SUB128(q2,ADD128(o2p2,SHUF128(o2p2,0x4E))));    \
	h7 = SUB128(q3,ADD128(o3p3,SHUF128(o3p3,0x4E)));                 \
}while(0)



void sqr_karatsuba_1w_h0h7(uint64_t *  C)
{
	const __m128i ones44 = _mm_set1_epi64x(((uint64_t)1<<44)-1);
	const __m128i ones36 = _mm_set1_epi64x(((uint64_t)1<<36)-1);
	const __m128i shuf48 = _mm_set_epi64x(0x800D0C0B0A090880,0x8005040302010080);
	const __m128i shuf32 = _mm_set_epi64x(0x800B0A0908808080,0x8003020100808080);
	__m128i a0a7,a1a8,a2a9,a3a10,a4a11,a5a12,a6a13;
	__m128i x0y0,x1y1,x2y2,x3y3,x4y4,x5y5,x6y6,x7y7,x8y8,x9y9,x10y10,x11y11,x12y12;
	__m128i z0z8,z1z9,z2z10,z3z11,z4z12,z5,z6,z7;

	a0a7  = LOAD128(C+0);
	a1a8  = LOAD128(C+1);
	a2a9  = LOAD128(C+2);
	a3a10 = LOAD128(C+3);
	a4a11 = LOAD128(C+4);
	a5a12 = LOAD128(C+5);
	a6a13 = LOAD128(C+6);

	/**
	 * Calculates
	 * 	X = A[0:7]  * B[0:7]
	 * 	Y = A[7:14] * B[7:14]
	 * Stores in [X|Y]
	 */
	sqr_karat_7x7(x0y0,x1y1,x2y2,x3y3,x4y4,x5y5,x6y6,x7y7,x8y8,x9y9,x10y10,x11y11,x12y12,
				  a0a7,a1a8,a2a9,a3a10,a4a11,a5a12,a6a13);

	__m128i sA0_4 = ADD128(UPKL64128(a0a7,a4a11),UPKH64128(a0a7,a4a11));
	__m128i sA1_5 = ADD128(UPKL64128(a1a8,a5a12),UPKH64128(a1a8,a5a12));
	__m128i sA2_6 = ADD128(UPKL64128(a2a9,a6a13),UPKH64128(a2a9,a6a13));
	__m128i sA3_7 = ADD128(UPKL64128(a3a10,ZERO128),UPKH64128(a3a10,ZERO128));

	/**
	 * Calculates
	 *  sA[0:7] = A[0:7] + A[7:14]
	 *  sB[0:7] = B[0:7] + B[7:14]
 	 * 	Z = sA[0:7] * sB[0:7]
	 */
	sqr_karate_7x7(z0z8,z1z9,z2z10,z3z11,z4z12,z5,z6,z7,
				   sA0_4,sA1_5,sA2_6,sA3_7);

	/**
	 * Combining partial results from Karatsuba
	 */
	__m128i z8  = SHUF128(z0z8 ,0x4E);
	__m128i z9  = SHUF128(z1z9 ,0x4E);
	__m128i z10 = SHUF128(z2z10,0x4E);
	__m128i z11 = SHUF128(z3z11,0x4E);
	__m128i z12 = SHUF128(z4z12,0x4E);

	__m128i y7  = SHUF128(x7y7,0x4E);
	__m128i y8  = SHUF128(x8y8,0x4E);
	__m128i y9  = SHUF128(x9y9,0x4E);
	__m128i y10 = SHUF128(x10y10,0x4E);
	__m128i y11 = SHUF128(x11y11,0x4E);
	__m128i y12 = SHUF128(x12y12,0x4E);

	__m128i ref0 = SUB128(x7y7,  SHUF128(x0y0,0x4E));
	__m128i ref1 = SUB128(x8y8,  SHUF128(x1y1,0x4E));
	__m128i ref2 = SUB128(x9y9,  SHUF128(x2y2,0x4E));
	__m128i ref3 = SUB128(x10y10,SHUF128(x3y3,0x4E));
	__m128i ref4 = SUB128(x11y11,SHUF128(x4y4,0x4E));
	__m128i ref5 = SUB128(x12y12,SHUF128(x5y5,0x4E));
	__m128i ref6 = SHUF128(x6y6,0x4E);

	__m128i c0  = x0y0;                             __m128i c14 = SUB128(SUB128(z7 ,y7 ),ref0);
	__m128i c1  = x1y1;                             __m128i c15 = SUB128(SUB128(z8 ,y8 ),ref1);
	__m128i c2  = x2y2;                             __m128i c16 = SUB128(SUB128(z9 ,y9 ),ref2);
	__m128i c3  = x3y3;                             __m128i c17 = SUB128(SUB128(z10,y10),ref3);
	__m128i c4  = x4y4;                             __m128i c18 = SUB128(SUB128(z11,y11),ref4);
	__m128i c5  = x5y5;                             __m128i c19 = SUB128(SUB128(z12,y12),ref5);
	__m128i c6  = x6y6;                             __m128i c20 = ref6;
	__m128i c7  = ADD128(SUB128(z0z8, x0y0),ref0);  __m128i c21 = y7 ;
	__m128i c8  = ADD128(SUB128(z1z9, x1y1),ref1);  __m128i c22 = y8 ;
	__m128i c9  = ADD128(SUB128(z2z10,x2y2),ref2);  __m128i c23 = y9 ;
	__m128i c10 = ADD128(SUB128(z3z11,x3y3),ref3);  __m128i c24 = y10;
	__m128i c11 = ADD128(SUB128(z4z12,x4y4),ref4);  __m128i c25 = y11;
	__m128i c12 = ADD128(SUB128(z5,   x5y5),ref5);  __m128i c26 = y12;
	__m128i c13 = SUB128(SUB128(z6,   x6y6),ref6);  __m128i c27 = ZERO128;

	/**
	 * Modular reduction
	 * (2^8)p = (2^8)(2^384-2^128-2^96+2^32-1)
	 *        = 2^136+2^104-2^40+2^8
	 */
	__m128i c12c19 = UPKL64128(c12,c19);
	__m128i c11c18 = UPKL64128(c11,c18);
	__m128i c10c17 = UPKL64128(c10,c17);
	__m128i c9c16  = UPKL64128(c9 ,c16);
	__m128i c8c15  = UPKL64128(c8 ,c15);
	__m128i c7c14  = UPKL64128(c7 ,c14);
	__m128i c6c13  = UPKL64128(c6 ,c13);
	__m128i l,h;
#define ModularReduction(XX,X0,X1,X2,X3,X4,X5,X6)  \
		l = _mm_shuffle_epi8(XX, shuf48);  \
		h = SHR128(XX, 48);                \
		X0 = ADD128(X0, l);                \
		X2 = ADD128(X2, h);                \
		                                   \
		l = SHL128(AND128(XX, ones44),12); \
		h = SHR128(XX, 44);                \
		X1 = SUB128(X1, l);                \
		X3 = SUB128(X3, h);                \
		                                   \
		l = SHL128(AND128(XX, ones36),20); \
		h = SHR128(XX, 36);                \
		X3 = ADD128(X3, l);                \
		X5 = ADD128(X5, h);                \
		                                   \
		l = _mm_shuffle_epi8(XX, shuf32);  \
		h = SHR128(XX, 32);                \
		X4 = ADD128(X4, l);                \
		X6 = ADD128(X6, h);

	__m128i c20c27 = UPKL64128(c20,c27);    ModularReduction(c20c27,c6c13,c7c14,c8c15,c9c16,c10c17,c11c18,c12c19);   __m128i c5c12 = UPKL64128(c5,c12c19);
	__m128i c19c26 = ALIGNR128(c26,c12c19); ModularReduction(c19c26,c5c12,c6c13,c7c14,c8c15, c9c16,c10c17,c11c18);   __m128i c4c11 = UPKL64128(c4,c11c18);
	__m128i c18c25 = ALIGNR128(c25,c11c18); ModularReduction(c18c25,c4c11,c5c12,c6c13,c7c14, c8c15, c9c16,c10c17);   __m128i c3c10 = UPKL64128(c3,c10c17);
	__m128i c17c24 = ALIGNR128(c24,c10c17); ModularReduction(c17c24,c3c10,c4c11,c5c12,c6c13, c7c14, c8c15, c9c16);   __m128i c2c9  = UPKL64128(c2, c9c16);
	__m128i c16c23 = ALIGNR128(c23, c9c16); ModularReduction(c16c23, c2c9,c3c10,c4c11,c5c12, c6c13, c7c14, c8c15);   __m128i c1c8  = UPKL64128(c1, c8c15);
	__m128i c15c22 = ALIGNR128(c22, c8c15); ModularReduction(c15c22, c1c8, c2c9,c3c10,c4c11, c5c12, c6c13, c7c14);   __m128i c0c7  = UPKL64128(c0, c7c14);
	__m128i c14c21 = ALIGNR128(c21, c7c14); ModularReduction(c14c21, c0c7, c1c8, c2c9,c3c10, c4c11, c5c12, c6c13);
#undef ModularReduction

	STORE128(C+0,c0c7 );
	STORE128(C+1,c1c8 );
	STORE128(C+2,c2c9 );
	STORE128(C+3,c3c10);
	STORE128(C+4,c4c11);
	STORE128(C+5,c5c12);
	STORE128(C+6,c6c13);
}


inline void sqr_schoolbook_1w_h0h7(uint64_t *  C)
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

inline void sqr_Element_1w_h0h7(uint64_t *  C)
{
	sqr_karatsuba_1w_h0h7(C);
//	sqr_schoolbook_1w_h0h7(C);
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
	Element_1w_H0H7 Tab_1,Tab_2,Tab_3;
	uint64_t *T[5];
	T[0] = pA;
	T[1] = pC;
	T[2] = Tab_1;
	T[3] = Tab_2;
	T[4] = Tab_3;

	/* alpha_1 */
	copy_Element_1w_h0h7(T[1],T[0]);

	/* alpha_2 */
	sqrn_Element_1w_h0h7(T[1],1);
	mul_Element_1w_h0h7(T[1],T[1],T[0]);
	compress_Element_1w_h0h7(T[1]);

	/* alpha_3 */
	copy_Element_1w_h0h7(T[2],T[1]);
	sqrn_Element_1w_h0h7(T[2],1);
	mul_Element_1w_h0h7(T[2],T[2],T[0]);
	compress_Element_1w_h0h7(T[2]);

	/* alpha_6 */
	copy_Element_1w_h0h7(T[3],T[2]);
	sqrn_Element_1w_h0h7(T[3],3);
	mul_Element_1w_h0h7(T[3],T[3],T[2]);
	compress_Element_1w_h0h7(T[3]);

	/* alpha_12 */
	copy_Element_1w_h0h7(T[4],T[3]);
	sqrn_Element_1w_h0h7(T[4],6);
	mul_Element_1w_h0h7(T[4],T[4],T[3]);
	compress_Element_1w_h0h7(T[4]);

	/* alpha_15 */
	sqrn_Element_1w_h0h7(T[4],3);
	mul_Element_1w_h0h7(T[4],T[4],T[2]);
	compress_Element_1w_h0h7(T[4]);

	/* alpha_30 */
	copy_Element_1w_h0h7(T[3],T[4]);
	sqrn_Element_1w_h0h7(T[3],15);
	mul_Element_1w_h0h7(T[3],T[3],T[4]);
	compress_Element_1w_h0h7(T[3]);

	/* (alpha_30)^2 */
	sqrn_Element_1w_h0h7(T[3],1);

	/* T_3 = a^(2^31-1) = (alpha_30)^2*alpha_1 */
	copy_Element_1w_h0h7(T[2],T[3]);
	mul_Element_1w_h0h7(T[2],T[2],T[0]);
	compress_Element_1w_h0h7(T[2]);

	/* (alpha_30)^(2^2) */
	sqrn_Element_1w_h0h7(T[3],1);

	/* T_1 = a^(2^32-1) = (alpha_30)^(2^2)*alpha_2 */
	copy_Element_1w_h0h7(T[4],T[3]);
	mul_Element_1w_h0h7(T[4],T[4],T[1]);
	compress_Element_1w_h0h7(T[4]);

	/* T_2 = a^(2^32-3) = (alpha_30)^(2^2)*alpha_1 */
	mul_Element_1w_h0h7(T[3],T[3],T[0]);
	compress_Element_1w_h0h7(T[3]);

	copy_Element_1w_h0h7(T[1],T[2]);
	for(i=0;i<7;i++)
	{
		sqrn_Element_1w_h0h7(T[1],32);
		mul_Element_1w_h0h7(T[1],T[1],T[4]);
		compress_Element_1w_h0h7(T[1]);
	}
	sqrn_Element_1w_h0h7(T[1],33);
	mul_Element_1w_h0h7(T[1],T[1],T[4]);
	compress_Element_1w_h0h7(T[1]);

	sqrn_Element_1w_h0h7(T[1],96);
	mul_Element_1w_h0h7(T[1],T[1],T[3]);
	compress_Element_1w_h0h7(T[1]);
//	new_compressfast_Element_1w_h0h7(T[1]);
}