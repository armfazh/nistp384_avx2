#include "element_2w_h0h7.h"
#include "element_1w_h0h7.h"


void interleave(argElement_2w_H0H7 C, argElement_1w_H0H7 LOW, argElement_1w_H0H7 HIGH)
{
	__m256i A0  = LOAD(LOW+0);
	__m256i A4  = LOAD(LOW+1);
	__m256i A8  = LOAD(LOW+2);
	__m256i A12 = LOAD(LOW+3);

	__m256i B0  = LOAD(HIGH+0);
	__m256i B4  = LOAD(HIGH+1);
	__m256i B8  = LOAD(HIGH+2);
	__m256i B12 = LOAD(HIGH+3);

	C[0] = _mm256_permute2x128_si256(A0,B0,0x20);
	C[1] = _mm256_permute2x128_si256(A0,B0,0x31);
	C[2] = _mm256_permute2x128_si256(A4,B4,0x20);
	C[3] = _mm256_permute2x128_si256(A4,B4,0x31);
	C[4] = _mm256_permute2x128_si256(A8,B8,0x20);
	C[5] = _mm256_permute2x128_si256(A8,B8,0x31);
	C[6] = _mm256_permute2x128_si256(A12,B12,0x20);
}

void deinterleave(argElement_1w_H0H7 LOW, argElement_1w_H0H7 HIGH, argElement_2w_H0H7 A)
{
	STORE(LOW  + 0, _mm256_permute2x128_si256(A[0], A[1], 0x20));
	STORE(HIGH + 0, _mm256_permute2x128_si256(A[0], A[1], 0x31));
	STORE(LOW  + 1, _mm256_permute2x128_si256(A[2], A[3], 0x20));
	STORE(HIGH + 1, _mm256_permute2x128_si256(A[2], A[3], 0x31));
	STORE(LOW  + 2, _mm256_permute2x128_si256(A[4], A[5], 0x20));
	STORE(HIGH + 2, _mm256_permute2x128_si256(A[4], A[5], 0x31));
	STORE(LOW  + 3, _mm256_castsi128_si256(_mm256_castsi256_si128(A[6])));
	STORE(HIGH + 3, _mm256_castsi128_si256(_mm256_extracti128_si256(A[6],1)));
}
void str_bytes_to_Element_2w_h0h7(argElement_2w_H0H7 pC, uint8_t * p8A)
{

}

void random_Element_2w_h0h7(argElement_2w_H0H7 X_Y)
{
	Element_1w_H0H7 X,Y;
	random_Element_1w_h0h7(X);
	random_Element_1w_h0h7(Y);
	interleave(X_Y,X,Y);
}

void print_Element_2w_h0h7(argElement_2w_H0H7 X_Y)
{
	Element_1w_H0H7 X,Y;
	deinterleave(X,Y,X_Y);
	print_Element_1w_h0h7(X);
	print_Element_1w_h0h7(Y);
}

void print_python_Element_2w_h0h7(argElement_2w_H0H7 X_Y)
{
	Element_1w_H0H7 X,Y;
	deinterleave(X,Y,X_Y);
	print_python_Element_1w_h0h7(X);
	print_python_Element_1w_h0h7(Y);
}

void printex_Element_2w_h0h7(argElement_2w_H0H7 X_Y)
{
	Element_1w_H0H7 X,Y;
	deinterleave(X,Y,X_Y);
	printex_Element_1w_h0h7(X);
	printex_Element_1w_h0h7(Y);
}

int compare_Element_2w_h0h7(argElement_2w_H0H7 X0_X1, argElement_2w_H0H7 Y0_Y1)
{
	Element_1w_H0H7 X0,X1;
	Element_1w_H0H7 Y0,Y1;
	deinterleave(X0,X1,X0_X1);
	deinterleave(Y0,Y1,Y0_Y1);
	return compare_Element_1w_h0h7(X0, Y0) && compare_Element_1w_h0h7(X1, Y1);
}

void sizes_Element_2w_h0h7(argElement_2w_H0H7 X_Y)
{
	Element_1w_H0H7 X,Y;
	deinterleave(X,Y,X_Y);
	sizes_Element_1w_h0h7(X);
	sizes_Element_1w_h0h7(Y);
}

inline void add_Element_2w_h0h7(argElement_2w_H0H7 C,argElement_2w_H0H7 A,argElement_2w_H0H7 B)
{
	int i=0;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
		C[i] = ADD(A[i],B[i]);
}

static const uint64_t CONST_2P_2P_H0H7[2*NUM_WORDS_64B_NISTP384] = {
	0x1ffffefe,0x1ffffffe,0x1ffffefe,0x1ffffffe,
	0x2000101e,0x1ffffffe,0x2000101e,0x1ffffffe,
	0x1ffffffe,0x1ffffffe,0x1ffffffe,0x1ffffffe,
	0x1fefdffe,0x1ffffffe,0x1fefdffe,0x1ffffffe,
	0x1efdfffe,0x1ffffffe,0x1efdfffe,0x1ffffffe,
	0x1ffffffe,0x1ffffffe,0x1ffffffe,0x1ffffffe,
	0x1ffffffe,0x101ffffe,0x1ffffffe,0x101ffffe
};

static const uint64_t CONST_2P_00_H0H7[2*NUM_WORDS_64B_NISTP384] = {
		0x1ffffefe,0x1ffffffe,0x0000000,0x0000000,
		0x2000101e,0x1ffffffe,0x0000000,0x0000000,
		0x1ffffffe,0x1ffffffe,0x0000000,0x0000000,
		0x1fefdffe,0x1ffffffe,0x0000000,0x0000000,
		0x1efdfffe,0x1ffffffe,0x0000000,0x0000000,
		0x1ffffffe,0x1ffffffe,0x0000000,0x0000000,
		0x1ffffffe,0x101ffffe,0x0000000,0x0000000};

static const uint64_t CONST_2_32P_ELEMENT[2*NUM_WORDS_64B_NISTP384] = {
		0x1ffffefe00000000,0x1ffffffe00000000,0x1ffffefe00000000,0x1ffffffe00000000,
		0x2000101e00000000,0x1ffffffe00000000,0x2000101e00000000,0x1ffffffe00000000,
		0x1ffffffe00000000,0x1ffffffe00000000,0x1ffffffe00000000,0x1ffffffe00000000,
		0x1fefdffe00000000,0x1ffffffe00000000,0x1fefdffe00000000,0x1ffffffe00000000,
		0x1efdfffe00000000,0x1ffffffe00000000,0x1efdfffe00000000,0x1ffffffe00000000,
		0x1ffffffe00000000,0x1ffffffe00000000,0x1ffffffe00000000,0x1ffffffe00000000,
		0x1ffffffe00000000,0x101ffffe00000000,0x1ffffffe00000000,0x101ffffe00000000
};


inline void sub_Element_2w_h0h7(argElement_2w_H0H7 __restrict C, argElement_2w_H0H7 __restrict A, argElement_2w_H0H7 __restrict B)
{
	argElement_2w_H0H7 _2P = (argElement_2w_H0H7)CONST_2P_2P_H0H7;
	int i=0;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
		C[i] = ADD(A[i],SUB(_2P[i],B[i]));
}

/**
 * Given
 * 		A = [X | Y]
 * Cumputes:
 * 	if permutation == 0
 * 		C = [X|Y] + [2p|0] + [-Y|X]
 * 		C = [ X+2p-Y | Y+X ]
 * 	if permutation == 1
 * 		C = [Y|X] + [2p|0] + [-X|Y]
 * 		C = [ Y+2p-X | Y+X ]
 * 	if permutation != {0,1}
 * 		undefined
 */
inline void subadd_Element_2w_h0h7(
		argElement_2w_H0H7 __restrict C,
		argElement_2w_H0H7 __restrict A,
		const int permutation)
{
	const __m256i mask_subadd = _mm256_set_epi64x(0,0,-1, -1);
	argElement_2w_H0H7 _2P_00 = (argElement_2w_H0H7)CONST_2P_00_H0H7;
	int i=0;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		__m256i M=ZERO,N=ZERO,PA;
		PA = PERM64(A[i],0x4E);
		if(permutation==0)
		{
			M = A[i];
			N = PA;
		}
		else if(permutation==1)
		{
			N = A[i];
			M = PA;
		}
		C[i] = ADD(ADD(M,_2P_00[i]),SUB(XOR(N,mask_subadd),mask_subadd));
	}
}

/**
 * Given
 * 		A = [X |Y ]
 * Returns
 * 		C = [2P-X | Y]
 */
inline void negZZ_Element_2w_h0h7(argElement_2w_H0H7 C,argElement_2w_H0H7 A)
{
	const __m256i mask_subadd = _mm256_set_epi64x(0,0,-1, -1);
	argElement_2w_H0H7 _2P_00 = (argElement_2w_H0H7)CONST_2P_00_H0H7;
	int i=0;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		C[i] = ADD(_2P_00[i],SUB(XOR(A[i],mask_subadd),mask_subadd));
	}
}

inline void addsub_large_Element_2w_h0h7(argElement_2w_H0H7 A, argElement_2w_H0H7 B)
{
	const __m256i _2_to_34P[NUM_WORDS_128B_NISTP384] = {
			/*[TODO]*/
			_mm256_set_epi64x(0x3ffffff800000000,0x3ffffffc00000000,0x3ffffff800000000,0x3ffffffc00000000),
			_mm256_set_epi64x(0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000),
			_mm256_set_epi64x(0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000),
			_mm256_set_epi64x(0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000),
			_mm256_set_epi64x(0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000),
			_mm256_set_epi64x(0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000),
			_mm256_set_epi64x(0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000,0x3ffffffc00000000)
	};


	int i=0;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		__m256i add = ADD(A[i],B[i]);
		__m256i sub = ADD(A[i],SUB(_2_to_34P[i], B[i]));
		A[i] = add;
		B[i] = sub;
	}
}

/**
 * Computes:
 * 		A = A+B
 * 		B = A-B
 */
inline void addsub_Element_2w_h0h7(argElement_2w_H0H7 __restrict A, argElement_2w_H0H7 __restrict B)
{
	argElement_2w_H0H7 _2P = (argElement_2w_H0H7)CONST_2P_2P_H0H7;
	int i=0;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		__m256i D,C;
		D = ADD(A[i], B[i]);
		C = ADD(A[i],SUB(_2P[i],B[i]));
		A[i] = D;
		B[i] = C;
	}
}

/**
 * Computes:
 * 		C = A+B
 * 		D = A-B
 */
inline void addsub4_Element_2w_h0h7(
		argElement_2w_H0H7 __restrict C, argElement_2w_H0H7 __restrict D,
		argElement_2w_H0H7 __restrict A, argElement_2w_H0H7 __restrict B)
{
	argElement_2w_H0H7 _2P = (argElement_2w_H0H7)CONST_2P_2P_H0H7;
	int i=0;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		__m256i T0,T1;
		T0 = ADD(A[i], B[i]);
		T1 = ADD(A[i],SUB(_2P[i],B[i]));
		C[i] = T0;
		D[i] = T1;
	}
}

/**
 * Computes:
 * 		C = -A+B
 * 		D = -A-B
 */
inline void naddsub_Element_2w_h0h7(
		argElement_2w_H0H7 __restrict C, argElement_2w_H0H7 __restrict D,
		argElement_2w_H0H7 __restrict A, argElement_2w_H0H7 __restrict B)
{
	argElement_2w_H0H7 _2P = (argElement_2w_H0H7)CONST_2P_2P_H0H7;

	int i=0;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		__m256i T = SUB(_2P[i],A[i]);
		C[i] = ADD(T,B[i]);
		D[i] = SUB(T,B[i]);
	}
}

/* Pi transformation */
#define PI_2w()								\
	tmp = b6;								\
	b6 = b5; 								\
	b5 = b4; 								\
	b4 = b3; 								\
	b3 = b2; 								\
	b2 = b1; 								\
	b1 = b0; 								\
	b0 = SHLi_128(tmp, 8);					\
	a13 = SHRi_128(tmp, 8);					\
	b0 = ADD(b0, SHL(AND(mask20, a13), 8)); \
	b1 = ADD(b1, SHR(a13, 20));				\
	b1 = SUB(b1, SHL(AND(mask16, a13), 12));\
	b2 = SUB(b2, SHR(a13, 16));				\
	b3 = ADD(b3, SHL(AND(mask8, a13), 20)); \
	b4 = ADD(b4, SHR(a13, 8));				\
	b4 = ADD(b4, SHL(AND(mask4, a13), 24)); \
	b5 = ADD(b5, SHR(a13, 4));

/**
 *
 * */
void mul_Element_2w_h0h7(__m256i *  C, __m256i * A, __m256i *  B)
{
	int i,j;
	const __m256i mask20 = _mm256_set_epi64x(0x0,((uint64_t)1<<20)-1,0x0,((uint64_t)1<<20)-1);
	const __m256i mask16 = _mm256_set_epi64x(0x0,((uint64_t)1<<16)-1,0x0,((uint64_t)1<<16)-1);
	const __m256i mask8  = _mm256_set_epi64x(0x0,((uint64_t)1<< 8)-1,0x0,((uint64_t)1<< 8)-1);
	const __m256i mask4  = _mm256_set_epi64x(0x0,((uint64_t)1<< 4)-1,0x0,((uint64_t)1<< 4)-1);
	const __m256i M[2] = { _mm256_set1_epi64x(0x0706050403020100), _mm256_set1_epi64x(0x0F0E0D0C0B0A0908) };

	__m256i ai,tmp,a13;
	__m256i b0,b1,b2,b3,b4,b5,b6;
	__m256i c0,c1,c2,c3,c4,c5,c6;

	b0 = LOAD(B+0);
	b1 = LOAD(B+1);
	b2 = LOAD(B+2);
	b3 = LOAD(B+3);
	b4 = LOAD(B+4);
	b5 = LOAD(B+5);
	b6 = LOAD(B+6);

	ai = _mm256_shuffle_epi8(LOAD(A + 0), M[0]);
	c0 = MUL(b0,ai);
	c1 = MUL(b1,ai);
	c2 = MUL(b2,ai);
	c3 = MUL(b3,ai);
	c4 = MUL(b4,ai);
	c5 = MUL(b5,ai);
	c6 = MUL(b6,ai);

	i=1;
	for(j=0;j<2;j++)
	{
		for ( ; i < 7; i++)
		{
			PI_2w();

			ai = _mm256_shuffle_epi8(LOAD(A + i), M[j]);
			c0 = ADD(c0, MUL(b0, ai));
			c1 = ADD(c1, MUL(b1, ai));
			c2 = ADD(c2, MUL(b2, ai));
			c3 = ADD(c3, MUL(b3, ai));
			c4 = ADD(c4, MUL(b4, ai));
			c5 = ADD(c5, MUL(b5, ai));
			c6 = ADD(c6, MUL(b6, ai));
		}
		i=0;
	}

	STORE(C+0, c0);
	STORE(C+1, c1);
	STORE(C+2, c2);
	STORE(C+3, c3);
	STORE(C+4, c4);
	STORE(C+5, c5);
	STORE(C+6, c6);
}

void sqr_Element_2w_h0h7(__m256i *  C)
{
	int i;
	Element_2w_H0H7 A,B;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		A[i] = B[i] = C[i];
	}
	mul_Element_2w_h0h7(C,A,B);
}


void compress_Element_2w_h0h7(__m256i * C)
{
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE) - 1;
	const __m256i mask   = _mm256_set_epi32 (0x0, ones, 0, ones,0x0, ones, 0, ones);
	const __m256i mask20 = _mm256_set_epi64x(0x0,((uint64_t)1<<20)-1,0x0,((uint64_t)1<<20)-1);
	const __m256i mask16 = _mm256_set_epi64x(0x0,((uint64_t)1<<16)-1,0x0,((uint64_t)1<<16)-1);
	const __m256i mask8  = _mm256_set_epi64x(0x0,((uint64_t)1<< 8)-1,0x0,((uint64_t)1<< 8)-1);
	const __m256i mask4  = _mm256_set_epi64x(0x0,((uint64_t)1<< 4)-1,0x0,((uint64_t)1<< 4)-1);
	const argElement_2w_H0H7 _2_32P = (argElement_2w_H0H7)CONST_2_32P_ELEMENT;

	__m256i h0_h7,  h1_h8,  h2_h9, h3_h10,
			h4_h11, h5_h12, h6_h13, h13, h6;

	__m256i c0 = LOAD(C+0);
	__m256i c1 = LOAD(C+1);
	__m256i c2 = LOAD(C+2);
	__m256i c3 = LOAD(C+3);
	__m256i c4 = LOAD(C+4);
	__m256i c5 = LOAD(C+5);
	__m256i c6 = LOAD(C+6);

	c0 = ADD(c0,_2_32P[0]);
	c1 = ADD(c1,_2_32P[1]);
	c2 = ADD(c2,_2_32P[2]);
	c3 = ADD(c3,_2_32P[3]);
	c4 = ADD(c4,_2_32P[4]);
	c5 = ADD(c5,_2_32P[5]);
	c6 = ADD(c6,_2_32P[6]);

	h6_h13 = SHR(c6, VECT_BASE);
	c6 = AND(c6, mask);

	h6  = SHLi_128(h6_h13, 8);
	h13 = SHRi_128(h6_h13, 8);
	c0 = ADD(c0,h6);
	c0 = ADD(c0, SHL(AND(mask20, h13), 8));
	c1 = ADD(c1, SHR(h13, 20));
	c1 = SUB(c1, SHL(AND(mask16, h13), 12));
	c2 = SUB(c2, SHR(h13, 16));
	c3 = ADD(c3, SHL(AND(mask8, h13), 20));
	c4 = ADD(c4, SHR(h13, 8));
	c4 = ADD(c4, SHL(AND(mask4, h13), 24));
	c5 = ADD(c5, SHR(h13, 4));

	h0_h7 = SHR(c0, VECT_BASE);
	c0 = AND(c0, mask);
	c1 = ADD(c1, h0_h7);

	h1_h8 = SHR(c1, VECT_BASE);
	c1 = AND(c1, mask);
	c2 = ADD(c2, h1_h8);

	h2_h9 = SHR(c2, VECT_BASE);
	c2 = AND(c2, mask);
	c3 = ADD(c3, h2_h9);

	h3_h10 = SHR(c3, VECT_BASE);
	c3 = AND(c3, mask);
	c4 = ADD(c4, h3_h10);

	h4_h11 = SHR(c4, VECT_BASE);
	c4 = AND(c4, mask);
	c5 = ADD(c5, h4_h11);

	h5_h12 = SHR(c5, VECT_BASE);
	c5 = AND(c5, mask);
	c6 = ADD(c6, h5_h12);

	h6_h13 = SHR(c6, VECT_BASE);
	c6 = AND(c6, mask);

	h6  = SHLi_128(h6_h13, 8);
	h13 = SHRi_128(h6_h13, 8);
	c0 = ADD(c0, h6);
	c0 = ADD(c0, SHL(AND(mask20, h13), 8));
	c1 = SUB(c1, SHL(AND(mask16, h13), 12));
	c3 = ADD(c3, SHL(AND(mask8, h13), 20));
	c4 = ADD(c4, SHL(AND(mask4, h13), 24));
	c5 = ADD(c5, SHR(h13, 4));

	STORE(C+0,c0);
	STORE(C+1,c1);
	STORE(C+2,c2);
	STORE(C+3,c3);
	STORE(C+4,c4);
	STORE(C+5,c5);
	STORE(C+6,c6);
}

void compress2_Element_2w_h0h7(__m256i * C, __m256i * D)
{
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE) - 1;
	const __m256i mask   = _mm256_set_epi32 (0x0, ones, 0, ones,0x0, ones, 0, ones);
	const __m256i mask20 = _mm256_set_epi64x(0x0,((uint64_t)1<<20)-1,0x0,((uint64_t)1<<20)-1);
	const __m256i mask16 = _mm256_set_epi64x(0x0,((uint64_t)1<<16)-1,0x0,((uint64_t)1<<16)-1);
	const __m256i mask8  = _mm256_set_epi64x(0x0,((uint64_t)1<< 8)-1,0x0,((uint64_t)1<< 8)-1);
	const __m256i mask4  = _mm256_set_epi64x(0x0,((uint64_t)1<< 4)-1,0x0,((uint64_t)1<< 4)-1);
	const argElement_2w_H0H7 _2_32P = (argElement_2w_H0H7)CONST_2_32P_ELEMENT;

	__m256i c0 = LOAD(C+0);                      		__m256i d0 = LOAD(D+0);
	__m256i c1 = LOAD(C+1);                      		__m256i d1 = LOAD(D+1);
	__m256i c2 = LOAD(C+2);                      		__m256i d2 = LOAD(D+2);
	__m256i c3 = LOAD(C+3);                      		__m256i d3 = LOAD(D+3);
	__m256i c4 = LOAD(C+4);                      		__m256i d4 = LOAD(D+4);
	__m256i c5 = LOAD(C+5);                      		__m256i d5 = LOAD(D+5);
	__m256i c6 = LOAD(C+6);                      		__m256i d6 = LOAD(D+6);

	__m256i h0_h7,  h1_h8,  h2_h9,  h3_h10;      		__m256i f0_f7,  f1_f8,  f2_f9,  f3_f10;
	__m256i h4_h11, h5_h12, h6_h13, h13, h6;     		__m256i f4_f11, f5_f12, f6_f13, f13, f6;

	c0 = ADD(c0,_2_32P[0]);                             d0 = ADD(d0,_2_32P[0]);
	c1 = ADD(c1,_2_32P[1]);                             d1 = ADD(d1,_2_32P[1]);
	c2 = ADD(c2,_2_32P[2]);                             d2 = ADD(d2,_2_32P[2]);
	c3 = ADD(c3,_2_32P[3]);                             d3 = ADD(d3,_2_32P[3]);
	c4 = ADD(c4,_2_32P[4]);                             d4 = ADD(d4,_2_32P[4]);
	c5 = ADD(c5,_2_32P[5]);                             d5 = ADD(d5,_2_32P[5]);
	c6 = ADD(c6,_2_32P[6]);                             d6 = ADD(d6,_2_32P[6]);

	h6_h13 = SHR(c6, VECT_BASE);                 		f6_f13 = SHR(d6, VECT_BASE);
	c6 = AND(c6, mask);                          		d6 = AND(d6, mask);

	h6  = SHLi_128(h6_h13, 8);                   		f6  = SHLi_128(f6_f13, 8);
	h13 = SHRi_128(h6_h13, 8);                   		f13 = SHRi_128(f6_f13, 8);
	c0 = ADD(c0,h6);                             		d0 = ADD(d0,f6);
	c0 = ADD(c0, SHL(AND(mask20, h13), 8));      		d0 = ADD(d0, SHL(AND(mask20, f13), 8));
	c1 = ADD(c1, SHR(h13, 20));                  		d1 = ADD(d1, SHR(f13, 20));
	c1 = SUB(c1, SHL(AND(mask16, h13), 12));     		d1 = SUB(d1, SHL(AND(mask16, f13), 12));
	c2 = SUB(c2, SHR(h13, 16));                  		d2 = SUB(d2, SHR(f13, 16));
	c3 = ADD(c3, SHL(AND(mask8, h13), 20));      		d3 = ADD(d3, SHL(AND(mask8, f13), 20));
	c4 = ADD(c4, SHR(h13, 8));                   		d4 = ADD(d4, SHR(f13, 8));
	c4 = ADD(c4, SHL(AND(mask4, h13), 24));      		d4 = ADD(d4, SHL(AND(mask4, f13), 24));
	c5 = ADD(c5, SHR(h13, 4));                   		d5 = ADD(d5, SHR(f13, 4));

	h0_h7 = SHR(c0, VECT_BASE);                  		f0_f7 = SHR(d0, VECT_BASE);
	c0 = AND(c0, mask);                          		d0 = AND(d0, mask);
	c1 = ADD(c1, h0_h7);                         		d1 = ADD(d1, f0_f7);

	h1_h8 = SHR(c1, VECT_BASE);                  		f1_f8 = SHR(d1, VECT_BASE);
	c1 = AND(c1, mask);                          		d1 = AND(d1, mask);
	c2 = ADD(c2, h1_h8);                         		d2 = ADD(d2, f1_f8);

	h2_h9 = SHR(c2, VECT_BASE);                  		f2_f9 = SHR(d2, VECT_BASE);
	c2 = AND(c2, mask);                          		d2 = AND(d2, mask);
	c3 = ADD(c3, h2_h9);                         		d3 = ADD(d3, f2_f9);

	h3_h10 = SHR(c3, VECT_BASE);                 		f3_f10 = SHR(d3, VECT_BASE);
	c3 = AND(c3, mask);                          		d3 = AND(d3, mask);
	c4 = ADD(c4, h3_h10);                        		d4 = ADD(d4, f3_f10);

	h4_h11 = SHR(c4, VECT_BASE);                 		f4_f11 = SHR(d4, VECT_BASE);
	c4 = AND(c4, mask);                          		d4 = AND(d4, mask);
	c5 = ADD(c5, h4_h11);                        		d5 = ADD(d5, f4_f11);

	h5_h12 = SHR(c5, VECT_BASE);                 		f5_f12 = SHR(d5, VECT_BASE);
	c5 = AND(c5, mask);                          		d5 = AND(d5, mask);
	c6 = ADD(c6, h5_h12);                        		d6 = ADD(d6, f5_f12);

	h6_h13 = SHR(c6, VECT_BASE);                 		f6_f13 = SHR(d6, VECT_BASE);
	c6 = AND(c6, mask);                          		d6 = AND(d6, mask);

	h6  = SHLi_128(h6_h13, 8);                   		f6  = SHLi_128(f6_f13, 8);
	h13 = SHRi_128(h6_h13, 8);                   		f13 = SHRi_128(f6_f13, 8);
	c0 = ADD(c0, h6);                            		d0 = ADD(d0, f6);
	c0 = ADD(c0, SHL(AND(mask20, h13), 8));      		d0 = ADD(d0, SHL(AND(mask20,f13), 8));
	c1 = SUB(c1, SHL(AND(mask16, h13), 12));     		d1 = SUB(d1, SHL(AND(mask16,f13), 12));
	c3 = ADD(c3, SHL(AND(mask8, h13), 20));      		d3 = ADD(d3, SHL(AND(mask8, f13), 20));
	c4 = ADD(c4, SHL(AND(mask4, h13), 24));      		d4 = ADD(d4, SHL(AND(mask4, f13), 24));
	c5 = ADD(c5, SHR(h13, 4));                   		d5 = ADD(d5, SHR(f13, 4));
	                                             		                                             
	STORE(C+0,c0);                               		STORE(D+0,d0);
	STORE(C+1,c1);                               		STORE(D+1,d1);
	STORE(C+2,c2);                               		STORE(D+2,d2);
	STORE(C+3,c3);                               		STORE(D+3,d3);
	STORE(C+4,c4);                               		STORE(D+4,d4);
	STORE(C+5,c5);                               		STORE(D+5,d5);
	STORE(C+6,c6);                               		STORE(D+6,d6);
}

void new_compressfast_Element_2w_h0h7(__m256i * C)
{
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE) - 1;
	const __m256i mask   = _mm256_set_epi32 (0x0, ones, 0, ones,0x0, ones, 0, ones);
	const __m256i mask20 = _mm256_set_epi64x(0x0,((uint64_t)1<<20)-1,0x0,((uint64_t)1<<20)-1);
	const __m256i mask16 = _mm256_set_epi64x(0x0,((uint64_t)1<<16)-1,0x0,((uint64_t)1<<16)-1);
	const __m256i mask8  = _mm256_set_epi64x(0x0,((uint64_t)1<< 8)-1,0x0,((uint64_t)1<< 8)-1);
	const __m256i mask4  = _mm256_set_epi64x(0x0,((uint64_t)1<< 4)-1,0x0,((uint64_t)1<< 4)-1);

	__m256i A0,A1,A2,A3,A4,A5,A6;
	__m256i l0,l1,l2,l3,l4,l5,l6;
	__m256i m0,m1,m2,m3,m4,m5,m6,m13;
	__m256i c0,c1,c2,c3,c4,c5,c6;

	A0 = LOAD(C+0);
	A1 = LOAD(C+1);
	A2 = LOAD(C+2);
	A3 = LOAD(C+3);
	A4 = LOAD(C+4);
	A5 = LOAD(C+5);
	A6 = LOAD(C+6);

	l0 = AND(A0,mask);	m0 = SHR(A0,VECT_BASE);
	l1 = AND(A1,mask);	m1 = SHR(A1,VECT_BASE);
	l2 = AND(A2,mask);	m2 = SHR(A2,VECT_BASE);
	l3 = AND(A3,mask);	m3 = SHR(A3,VECT_BASE);
	l4 = AND(A4,mask);	m4 = SHR(A4,VECT_BASE);
	l5 = AND(A5,mask);	m5 = SHR(A5,VECT_BASE);
	l6 = AND(A6,mask);	m6 = SHR(A6,VECT_BASE);

	c0 = ADD(l0,SHLi_128(m6,8));
	c1 = ADD(l1,m0);
	c2 = ADD(l2,m1);
	c3 = ADD(l3,m2);
	c4 = ADD(l4,m3);
	c5 = ADD(l5,m4);
	c6 = ADD(l6,m5);

	m13 = SHRi_128(m6,8);
	c0 = ADD(c0, SHL(AND(mask20,m13), 8));
	c1 = ADD(c1, SHR(m13,20));
	c1 = SUB(c1, SHL(AND(mask16,m13),12));
	c2 = SUB(c2, SHR(m13,16));
	c3 = ADD(c3, SHL(AND(mask8 ,m13),20));
	c4 = ADD(c4, SHR(m13, 8));
	c4 = ADD(c4, SHL(AND(mask4 ,m13),24));
	c5 = ADD(c5, SHR(m13, 4));

	STORE(C+0,c0);
	STORE(C+1,c1);
	STORE(C+2,c2);
	STORE(C+3,c3);
	STORE(C+4,c4);
	STORE(C+5,c5);
	STORE(C+6,c6);
}

void new_compressfast2_Element_2w_h0h7(__m256i * C,__m256i * D)
{
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE) - 1;
	const __m256i mask   = _mm256_set_epi32 (0x0, ones, 0, ones,0x0, ones, 0, ones);
	const __m256i mask20 = _mm256_set_epi64x(0x0,((uint64_t)1<<20)-1,0x0,((uint64_t)1<<20)-1);
	const __m256i mask16 = _mm256_set_epi64x(0x0,((uint64_t)1<<16)-1,0x0,((uint64_t)1<<16)-1);
	const __m256i mask8  = _mm256_set_epi64x(0x0,((uint64_t)1<< 8)-1,0x0,((uint64_t)1<< 8)-1);
	const __m256i mask4  = _mm256_set_epi64x(0x0,((uint64_t)1<< 4)-1,0x0,((uint64_t)1<< 4)-1);

	__m256i C0 = LOAD(C+0);                                __m256i D0 = LOAD(D+0);
	__m256i C1 = LOAD(C+1);                                __m256i D1 = LOAD(D+1);
	__m256i C2 = LOAD(C+2);                                __m256i D2 = LOAD(D+2);
	__m256i C3 = LOAD(C+3);                                __m256i D3 = LOAD(D+3);
	__m256i C4 = LOAD(C+4);                                __m256i D4 = LOAD(D+4);
	__m256i C5 = LOAD(C+5);                                __m256i D5 = LOAD(D+5);
	__m256i C6 = LOAD(C+6);                                __m256i D6 = LOAD(D+6);
	                                                                                               
	__m256i l_C0 = AND(C0,mask);	                       __m256i l_D0 = AND(D0,mask);	        
	__m256i l_C1 = AND(C1,mask);	                       __m256i l_D1 = AND(D1,mask);	        
	__m256i l_C2 = AND(C2,mask);	                       __m256i l_D2 = AND(D2,mask);	        
	__m256i l_C3 = AND(C3,mask);	                       __m256i l_D3 = AND(D3,mask);	        
	__m256i l_C4 = AND(C4,mask);	                       __m256i l_D4 = AND(D4,mask);	        
	__m256i l_C5 = AND(C5,mask);	                       __m256i l_D5 = AND(D5,mask);	        
	__m256i l_C6 = AND(C6,mask);                           __m256i l_D6 = AND(D6,mask);            
	                                                                                               
	__m256i m_C0 = SHR(C0,VECT_BASE);                      __m256i m_D0 = SHR(D0,VECT_BASE);       
	__m256i m_C1 = SHR(C1,VECT_BASE);                      __m256i m_D1 = SHR(D1,VECT_BASE);       
	__m256i m_C2 = SHR(C2,VECT_BASE);                      __m256i m_D2 = SHR(D2,VECT_BASE);       
	__m256i m_C3 = SHR(C3,VECT_BASE);                      __m256i m_D3 = SHR(D3,VECT_BASE);       
	__m256i m_C4 = SHR(C4,VECT_BASE);                      __m256i m_D4 = SHR(D4,VECT_BASE);       
	__m256i m_C5 = SHR(C5,VECT_BASE);                      __m256i m_D5 = SHR(D5,VECT_BASE);       
	__m256i m_C6 = SHR(C6,VECT_BASE);                      __m256i m_D6 = SHR(D6,VECT_BASE);       
	                                                                                               
	__m256i c0 = ADD(l_C0,SHLi_128(m_C6,8));               __m256i d0 = ADD(l_D0,SHLi_128(m_D6,8));
	__m256i c1 = ADD(l_C1,m_C0);                           __m256i d1 = ADD(l_D1,m_D0);            
	__m256i c2 = ADD(l_C2,m_C1);                           __m256i d2 = ADD(l_D2,m_D1);            
	__m256i c3 = ADD(l_C3,m_C2);                           __m256i d3 = ADD(l_D3,m_D2);            
	__m256i c4 = ADD(l_C4,m_C3);                           __m256i d4 = ADD(l_D4,m_D3);            
	__m256i c5 = ADD(l_C5,m_C4);                           __m256i d5 = ADD(l_D5,m_D4);            
	__m256i c6 = ADD(l_C6,m_C5);                           __m256i d6 = ADD(l_D6,m_D5);            
	                                                                                               
	__m256i m_C13 = SHRi_128(m_C6,8);                      __m256i m_D13 = SHRi_128(m_D6,8);       
	c0 = ADD(c0,SHL(AND(mask20,m_C13), 8));                d0 = ADD(d0,SHL(AND(mask20,m_D13), 8)); 
	c1 = ADD(c1,SHR(m_C13,20));                            d1 = ADD(d1,SHR(m_D13,20));             
	c1 = SUB(c1,SHL(AND(mask16,m_C13),12));                d1 = SUB(d1,SHL(AND(mask16,m_D13),12)); 
	c2 = SUB(c2,SHR(m_C13,16));                            d2 = SUB(d2,SHR(m_D13,16));             
	c3 = ADD(c3,SHL(AND(mask8 ,m_C13),20));                d3 = ADD(d3,SHL(AND(mask8 ,m_D13),20)); 
	c4 = ADD(c4,SHR(m_C13, 8));                            d4 = ADD(d4,SHR(m_D13, 8));             
	c4 = ADD(c4,SHL(AND(mask4 ,m_C13),24));                d4 = ADD(d4,SHL(AND(mask4 ,m_D13),24)); 
	c5 = ADD(c5,SHR(m_C13, 4));                            d5 = ADD(d5,SHR(m_D13, 4));             
	                                                                                               
	STORE(C+0,c0);                                         STORE(D+0,d0);
	STORE(C+1,c1);                                         STORE(D+1,d1);
	STORE(C+2,c2);                                         STORE(D+2,d2);
	STORE(C+3,c3);                                         STORE(D+3,d3);
	STORE(C+4,c4);                                         STORE(D+4,d4);
	STORE(C+5,c5);                                         STORE(D+5,d5);
	STORE(C+6,c6);                                         STORE(D+6,d6);
}
