#include "element_2w_h0h7.h"
#include "element_1w_h0h7.h"

void str_bytes_To_Element_2w_h0h7(argElement_2w_H0H7 pC, uint8_t * p8A)
{
	int i;
	const uint64_t ones28 = (((uint64_t)1)<<VECT_BASE)-1;
	const uint64_t ones26 = (((uint64_t)1)<<26)-1;
	const __m128i mask28 = _mm_set1_epi64x(ones28);
	const __m128i mask26 = _mm_set1_epi64x(ones26);
	const __m128i *p128A = (__m128i*)p8A;
	__m128i *p128C = (__m128i*)pC;

	p128C[0 ] = p128A[0];
	p128C[2 ] = _mm_srli_epi64(p128A[0],VECT_BASE);
	p128C[4 ] = _mm_xor_si128(_mm_srli_epi64(p128A[0],(2*VECT_BASE)),_mm_slli_epi64(p128A[1],8));

	p128C[6 ] = _mm_srli_epi64(p128A[1],20);
	p128C[8 ] = _mm_xor_si128(_mm_srli_epi64(p128A[1],(20+VECT_BASE)) , _mm_slli_epi64(p128A[2],16));

	p128C[10] = _mm_srli_epi64(p128A[2],12);
	p128C[12] = _mm_xor_si128(_mm_srli_epi64(p128A[2],(12+VECT_BASE)),_mm_slli_epi64(p128A[3],24));

	p128C[1 ] = _mm_srli_epi64(p128A[3],4);
	p128C[3 ] = _mm_srli_epi64(p128A[3],(4+VECT_BASE));
	p128C[5 ] = _mm_xor_si128(_mm_srli_epi64(p128A[3],(4+2*VECT_BASE)),_mm_slli_epi64(p128A[4],4));

	p128C[7 ] = _mm_srli_epi64(p128A[4],24);
	p128C[9 ] = _mm_xor_si128(_mm_srli_epi64(p128A[4],(24+VECT_BASE)),_mm_slli_epi64(p128A[5],12));

	p128C[11] = _mm_srli_epi64(p128A[5],16);
	p128C[13] = _mm_srli_epi64(p128A[5],(16+VECT_BASE));

	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		p128C[i] = _mm_and_si128(p128C[i],mask28);
	}
	p128C[13] = _mm_and_si128(p128C[13],mask26);
}

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

static const uint64_t CONST_2P_ELEMENT_H0H7[2*NUM_WORDS_64B_NISTP384] = {
	0x1ffffefe,0x1ffffffe,0x1ffffefe,0x1ffffffe,
	0x2000101e,0x1ffffffe,0x2000101e,0x1ffffffe,
	0x1ffffffe,0x1ffffffe,0x1ffffffe,0x1ffffffe,
	0x1fefdffe,0x1ffffffe,0x1fefdffe,0x1ffffffe,
	0x1efdfffe,0x1ffffffe,0x1efdfffe,0x1ffffffe,
	0x1ffffffe,0x1ffffffe,0x1ffffffe,0x1ffffffe,
	0x1ffffffe,0x101ffffe,0x1ffffffe,0x101ffffe
};

static const uint64_t CONST_2_32P_ELEMENT_H0H7[2*NUM_WORDS_64B_NISTP384] = {
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
	argElement_2w_H0H7 _2P = (argElement_2w_H0H7)CONST_2P_ELEMENT_H0H7;
	int i=0;
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
		C[i] = ADD(A[i],SUB(_2P[i],B[i]));
}

/**
 * Given A=(A0,A1) and B=(B0,B1)
 * Returns:
 * 		C=(A0+B0    , A1+2p-B1)  if subadd==0
 * 		C=(A0+2p-B0 , A1+B1)     if subadd==1
 * If large==1
 * 	     Pi = 2**34Pi
 * If large==0
 * 	     Pi = 2Pi
 */
inline void addsub_Element_2w_h0h7(
		argElement_2w_H0H7 __restrict C,
		argElement_2w_H0H7 __restrict A,
		argElement_2w_H0H7 __restrict B,
		const int subadd, const int large)
{
	int i;
	const __m256i mask[2] = {
			_mm256_set_epi64x(-1,-1,0,0),
			_mm256_set_epi64x(0,0,-1,-1)
	};
	const argElement_2w_H0H7 PP[2] = {
			(argElement_2w_H0H7) CONST_2P_ELEMENT_H0H7,
			(argElement_2w_H0H7) CONST_2_32P_ELEMENT_H0H7
	};
	for(i=0;i<NUM_WORDS_128B_NISTP384;i++)
	{
		/* Compute:
		 * (-B0, B1) if subadd == 0
		 * ( B0,-B1) if subadd == 1
		 * */
		__m256i _B = SUB(XOR(B[i],mask[subadd]),mask[subadd]);
		/* Compute:
		 * ( PP, 00) if subadd == 0
		 * ( 00, PP) if subadd == 1
		 * */
		__m256i P = AND(PP[large][i],mask[subadd]);
		C[i] = ADD(ADD(A[i],P),_B);
	}
}

#define mul_school_4x4(r0,r1,r2,r3,r4,r5,r6,s0,s1,s2,s3,t0,t1,t2,t3) \
do{                           \
	r0 = MUL(s0,t0);          \
	r1 = MUL(s1,t0);          \
	r2 = MUL(s2,t0);          \
	r3 = MUL(s3,t0);          \
                              \
	r1 = ADD(r1,MUL(s0,t1));  \
	r2 = ADD(r2,MUL(s1,t1));  \
	r3 = ADD(r3,MUL(s2,t1));  \
	r4 =        MUL(s3,t1);   \
	                          \
	r2 = ADD(r2,MUL(s0,t2));  \
	r3 = ADD(r3,MUL(s1,t2));  \
	r4 = ADD(r4,MUL(s2,t2));  \
	r5 =        MUL(s3,t2);   \
	                          \
	r3 = ADD(r3,MUL(s0,t3));  \
	r4 = ADD(r4,MUL(s1,t3));  \
	r5 = ADD(r5,MUL(s2,t3));  \
	r6 =        MUL(s3,t3);   \
	                          \
}while(0)

#define mul_school_3x3(r0,r1,r2,r3,r4,s0,s1,s2,t0,t1,t2) \
do{                           \
	r0 = MUL(s0,t0);          \
	r1 = MUL(s1,t0);          \
	r2 = MUL(s2,t0);          \
                              \
	r1 = ADD(r1,MUL(s0,t1));  \
	r2 = ADD(r2,MUL(s1,t1));  \
	r3 =        MUL(s2,t1);   \
	                          \
	r2 = ADD(r2,MUL(s0,t2));  \
	r3 = ADD(r3,MUL(s1,t2));  \
	r4 =        MUL(s2,t2);   \
	                          \
}while(0)

#define mul_karat_7x7(h0,h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11,h12,    \
               f0,f1,f2,f3,f4,f5,f6,g0,g1,g2,g3,g4,g5,g6)           \
do{                                                                 \
 	__m256i o0,o1,o2,o3,o4,o5,o6;                                   \
	__m256i p0,p1,p2,p3,p4;                                         \
	__m256i q0,q1,q2,q3,q4,q5,q6;                                   \
	mul_school_4x4(o0,o1,o2,o3,o4,o5,o6,f0,f1,f2,f3,g0,g1,g2,g3);   \
	mul_school_3x3(p0,p1,p2,p3,p4,f4,f5,f6,g4,g5,g6);               \
	mul_school_4x4(q0,q1,q2,q3,q4,q5,q6,                            \
		ADD(f0,f4),                                                 \
		ADD(f1,f5),                                                 \
		ADD(f2,f6),                                                 \
		f3,                                                         \
		ADD(g0,g4),                                                 \
		ADD(g1,g5),                                                 \
		ADD(g2,g6),                                                 \
		g3);                                                        \
    __m256i ref0 = SUB(o4,p0);                                      \
    __m256i ref1 = SUB(o5,p1);                                      \
    __m256i ref2 = SUB(o6,p2);                                      \
    __m256i ref3 = SUB(ZERO,p3);                                    \
	h0 = o0;                         h8  = SUB(SUB(q4,p4),ref0);    \
	h1 = o1;                         h9  = SUB(q5,ref1);            \
	h2 = o2;                         h10 = SUB(q6,ref2);            \
	h3 = o3;                         h11 = p3;                      \
	h4 = ADD(ref0,SUB(q0,o0));       h12 = p4;                      \
	h5 = ADD(ref1,SUB(q1,o1));                                      \
	h6 = ADD(ref2,SUB(q2,o2));                                      \
	h7 = ADD(ref3,SUB(q3,o3));                                      \
}while(0)



#define mul_karate_7x7(h0,h1,h2,h3,h4,h5,h6,  h7,                                       \
               f0,f1,f2,f3,g0,g1,g2,g3)                                              \
do{                                                                                  \
 	__m256i o0p0,o1p1,o2p2,o3p3,o4p4,o5p5,o6p6,o7p7;                                      \
	__m256i q0,q1,q2,q3,q4,q5,q6,q7;                                                    \
	mul_school_4x4(o0p0,o1p1,o2p2,o3p3,o4p4,o5p5,o6p6,f0,f1,f2,f3,g0,g1,g2,g3);      \
	__m256i sF0 = ADD(f0,SHUF(f0,0x4E)); __m256i sG0 = ADD(g0,SHUF(g0,0x4E));        \
	__m256i sF1 = ADD(f1,SHUF(f1,0x4E)); __m256i sG1 = ADD(g1,SHUF(g1,0x4E));        \
	__m256i sF2 = ADD(f2,SHUF(f2,0x4E)); __m256i sG2 = ADD(g2,SHUF(g2,0x4E));        \
	__m256i sF3 = ADD(f3,SHUF(f3,0x4E)); __m256i sG3 = ADD(g3,SHUF(g3,0x4E));        \
                                                                                     \
	mul_school_4x4(q0,q1,q2,q3,q4,q5,q6,                                             \
				  sF0,sF1,sF2,sF3,                                                   \
				  sG0,sG1,sG2,sG3);                                                  \
																				     \
	h0 = /*ADD(o0p0,*/BLEND32(SUB(q4,ADD(o4p4,SHUF(o4p4,0x4E))),ZERO,0x33);             \
	h1 = ADD(o1p1,BLEND32(SUB(q5,ADD(o5p5,SHUF(o5p5,0x4E))),ZERO,0x33));             \
	h2 = ADD(o2p2,BLEND32(SUB(q6,ADD(o6p6,SHUF(o6p6,0x4E))),ZERO,0x33));             \
	h3 = ADD(o3p3,BLEND32(SUB(q7,ADD(o7p7,SHUF(o7p7,0x4E))),ZERO,0x33));             \
	h4 = ADD(o4p4,BLEND32(SUB(q0,ADD(o0p0,SHUF(o0p0,0x4E))),ZERO,0xCC));             \
	h5 = ADD(o5p5,BLEND32(SUB(q1,ADD(o1p1,SHUF(o1p1,0x4E))),ZERO,0xCC));             \
	h6 = ADD(o6p6,BLEND32(SUB(q2,ADD(o2p2,SHUF(o2p2,0x4E))),ZERO,0xCC));             \
	h7 = ADD(o7p7,BLEND32(SUB(q3,ADD(o3p3,SHUF(o3p3,0x4E))),ZERO,0xCC));             \
    \
 \
}while(0)


void mul_karatsuba_2w_h0h7(__m256i *  C, __m256i * A, __m256i *  B)
{
	__m256i a0,a1,a2,a3,a4,a5,a6;
	__m256i b0,b1,b2,b3,b4,b5,b6;
	__m256i x0y0,x1y1,x2y2,x3y3,x4y4,x5y5,x6y6,x7y7,x8y8,x9y9,x10y10,x11y11,x12y12;
	__m256i z0,z1,z2,z3,z4,z5,z6,z7;

	a0 = A[0];   b0 = B[0];
	a1 = A[1];   b1 = B[1];
	a2 = A[2];   b2 = B[2];
	a3 = A[3];   b3 = B[3];
	a4 = A[4];   b4 = B[4];
	a5 = A[5];   b5 = B[5];
	a6 = A[6];   b6 = B[6];

	mul_karat_7x7(x0y0,x1y1,x2y2,x3y3,x4y4,x5y5,x6y6,x7y7,x8y8,x9y9,x10y10,x11y11,x12y12,
				  a0,a1,a2,a3,a4,a5,a6,
				  b0,b1,b2,b3,b4,b5,b6);

	__m256i sA0_4 = ADD(UPKL64(a0,a4),UPKH64(a0,a4));
	__m256i sA1_5 = ADD(UPKL64(a1,a5),UPKH64(a1,a5));
	__m256i sA2_6 = ADD(UPKL64(a2,a6),UPKH64(a2,a6));
	__m256i sA3_7 = ADD(UPKL64(a3,ZERO),UPKH64(a3,ZERO));
	__m256i sB0_4 = ADD(UPKL64(b0,b4),UPKH64(b0,b4));
	__m256i sB1_5 = ADD(UPKL64(b1,b5),UPKH64(b1,b5));
	__m256i sB2_6 = ADD(UPKL64(b2,b6),UPKH64(b2,b6));
	__m256i sB3_7 = ADD(UPKL64(b3,ZERO),UPKH64(b3,ZERO));

	mul_karate_7x7(z0,z1,z2,z3,z4,z5,z6,z7,
				   sA0_4,sA1_5,sA2_6,sA3_7,
				   sB0_4,sB1_5,sB2_6,sB3_7);

	C[0] = z0;   C[7]  = z7;
	C[1] = z1;   C[8]  = ZERO;
	C[2] = z2;   C[9]  = ZERO;
	C[3] = z3;   C[10] = ZERO;
	C[4] = z4;   C[11] = ZERO;
	C[5] = z5;   C[12] = ZERO;
	C[6] = z6;   C[13] = ZERO;

	/*
	__m256i x0x8  = UPKL64(x0y0,x8y8  );  __m256i y0y8  = UPKH64(x0y0,x8y8  ); __m256i x0z8  = BLEND32(x0y0,z0,0xCC);  C[0] = ADD(ADD(SHUF(SUB(z0,x0x8 ),0x4E),y0y8 ),x0z8 );
	__m256i x1x9  = UPKL64(x1y1,x9y9  );  __m256i y1y9  = UPKH64(x1y1,x9y9  ); __m256i x1z9  = BLEND32(x1y1,z1,0xCC);  C[1] = ADD(ADD(SHUF(SUB(z1,x1x9 ),0x4E),y1y9 ),x1z9 );
	__m256i x2x10 = UPKL64(x2y2,x10y10);  __m256i y2y10 = UPKH64(x2y2,x10y10); __m256i x2z10 = BLEND32(x2y2,z2,0xCC);  C[2] = ADD(ADD(SHUF(SUB(z2,x2x10),0x4E),y2y10),x2z10);
	__m256i x3x11 = UPKL64(x3y3,x11y11);  __m256i y3y11 = UPKH64(x3y3,x11y11); __m256i x3z11 = BLEND32(x3y3,z3,0xCC);  C[3] = ADD(ADD(SHUF(SUB(z3,x3x11),0x4E),y3y11),x3z11);
	__m256i x4x12 = UPKL64(x4y4,x12y12);  __m256i y4y12 = UPKH64(x4y4,x12y12); __m256i x4z12 = BLEND32(x4y4,z4,0xCC);  C[4] = ADD(ADD(SHUF(SUB(z4,x4x12),0x4E),y4y12),x4z12);
	__m256i x5x13 = UPKL64(x5y5,ZERO);    __m256i y5y13 = UPKH64(x5y5,ZERO);   __m256i x5z13 = BLEND32(x5y5,z5,0xCC);  C[5] = ADD(ADD(SHUF(SUB(z5,x5x13),0x4E),y5y13),x5z13);
	__m256i x6x14 = UPKL64(x6y6,ZERO);    __m256i y6y14 = UPKH64(x6y6,ZERO);   __m256i x6z14 = BLEND32(x6y6,z6,0xCC);  C[6] = ADD(ADD(SHUF(SUB(z6,x6x14),0x4E),y6y14),x6z14);
	 */
//	__m256i x7x15 = UPKL64(x7y7,ZERO);  __m256i y7y15 = UPKH64(x7y7,ZERO); __m256i x7z15 = BLEND32(x7y7,z7,0xCC);  C[7] = ADD(ADD(SHUF(SUB(z7,x7x15),0x4E),y7y15),x7z15);
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
	b0 = ADD(b0, SHLi_128(AND(a13, mask20), 1)); \
	b1 = ADD(b1, SHR(a13, 20));				\
	b1 = SUB(b1, SHL(AND(a13,mask16), 12));\
	b2 = SUB(b2, SHRi_128(a13, 2));				\
	b3 = ADD(b3, SHL(AND(a13,mask8), 20)); \
	b4 = ADD(b4, SHRi_128(a13, 1));				\
	b4 = ADD(b4, SHLi_128(AND(a13,mask4), 3)); \
	b5 = ADD(b5, SHR(a13, 4));

void mul_schoolbook_h0h7(__m256i *  C, __m256i * A, __m256i *  B)
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

/**
 *
 * */
void mul_Element_2w_h0h7(__m256i *  C, __m256i * A, __m256i *  B)
{
//	mul_karatsuba_2w_h0h7(C,A,B);
	mul_schoolbook_h0h7(C,A,B);
}

void sqr_Element_2w_h0h7(__m256i *  C)
{
	const __m256i mask20 = _mm256_set_epi64x(0x0,((uint64_t)1<<20)-1,0x0,((uint64_t)1<<20)-1);
	const __m256i mask16 = _mm256_set_epi64x(0x0,((uint64_t)1<<16)-1,0x0,((uint64_t)1<<16)-1);
	const __m256i mask8  = _mm256_set_epi64x(0x0,((uint64_t)1<< 8)-1,0x0,((uint64_t)1<< 8)-1);
	const __m256i mask4  = _mm256_set_epi64x(0x0,((uint64_t)1<< 4)-1,0x0,((uint64_t)1<< 4)-1);

	__m256i ai,tmp,a13;
	__m256i b0,b1,b2,b3,b4,b5,b6;
	__m256i c0,c1,c2,c3,c4,c5,c6;

	b0 = LOAD(C+0);
	b1 = LOAD(C+1);
	b2 = LOAD(C+2);
	b3 = LOAD(C+3);
	b4 = LOAD(C+4);
	b5 = LOAD(C+5);
	b6 = LOAD(C+6);

	ai = _mm256_shuffle_epi32(LOAD(C + 0), 0x44);
	c0 = MUL(b0, ai);
	c1 = MUL(b1, ai);
	c2 = MUL(b2, ai);
	c3 = MUL(b3, ai);
	c4 = MUL(b4, ai);
	c5 = MUL(b5, ai);
	c6 = MUL(b6, ai);
	PI_2w();

	ai = _mm256_shuffle_epi32(LOAD(C + 1), 0x44);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();

	ai = _mm256_shuffle_epi32(LOAD(C + 2), 0x44);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();

	ai = _mm256_shuffle_epi32(LOAD(C + 3), 0x44);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();

	ai = _mm256_shuffle_epi32(LOAD(C + 4), 0x44);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();
	ai = _mm256_shuffle_epi32(LOAD(C + 5), 0x44);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();
	ai = _mm256_shuffle_epi32(LOAD(C + 6), 0x44);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();

	ai = _mm256_shuffle_epi32(LOAD(C + 0), 0xEE);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();

	ai = _mm256_shuffle_epi32(LOAD(C + 1), 0xEE);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();

	ai = _mm256_shuffle_epi32(LOAD(C + 2), 0xEE);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();

	ai = _mm256_shuffle_epi32(LOAD(C + 3), 0xEE);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();

	ai = _mm256_shuffle_epi32(LOAD(C + 4), 0xEE);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();
	ai = _mm256_shuffle_epi32(LOAD(C + 5), 0xEE);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	PI_2w();
	ai = _mm256_shuffle_epi32(LOAD(C + 6), 0xEE);
	c0 = ADD(c0, MUL(b0, ai));
	c1 = ADD(c1, MUL(b1, ai));
	c2 = ADD(c2, MUL(b2, ai));
	c3 = ADD(c3, MUL(b3, ai));
	c4 = ADD(c4, MUL(b4, ai));
	c5 = ADD(c5, MUL(b5, ai));
	c6 = ADD(c6, MUL(b6, ai));
	
	STORE(C+0, c0);
	STORE(C+1, c1);
	STORE(C+2, c2);
	STORE(C+3, c3);
	STORE(C+4, c4);
	STORE(C+5, c5);
	STORE(C+6, c6);
}


void compress_Element_2w_h0h7(__m256i * C)
{
	const uint64_t ones = ((uint64_t) 1 << VECT_BASE) - 1;
	const __m256i mask   = _mm256_set_epi32 (0x0, ones, 0, ones,0x0, ones, 0, ones);
	const __m256i mask20 = _mm256_set_epi64x(0x0,((uint64_t)1<<20)-1,0x0,((uint64_t)1<<20)-1);
	const __m256i mask16 = _mm256_set_epi64x(0x0,((uint64_t)1<<16)-1,0x0,((uint64_t)1<<16)-1);
	const __m256i mask8  = _mm256_set_epi64x(0x0,((uint64_t)1<< 8)-1,0x0,((uint64_t)1<< 8)-1);
	const __m256i mask4  = _mm256_set_epi64x(0x0,((uint64_t)1<< 4)-1,0x0,((uint64_t)1<< 4)-1);
	const argElement_2w_H0H7 _2_32P = (argElement_2w_H0H7)CONST_2_32P_ELEMENT_H0H7;

	__m256i h0_h7,  h1_h8,  h2_h9, h3_h10,
			h4_h11, h5_h12, h6_h13, h13, h6;

	__m256i c0 = LOAD(C+0);
	__m256i c1 = LOAD(C+1);
	__m256i c2 = LOAD(C+2);
	__m256i c3 = LOAD(C+3);
	__m256i c4 = LOAD(C+4);
	__m256i c5 = LOAD(C+5);
	__m256i c6 = LOAD(C+6);

	/**
	 * Since after a multiplication it could happen
	 * that the sequence contains one or more negative digits,
	 * the, we add a large multiple of the prime P, before
	 * to process the reduction.
	 */
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

	/**
	 * At this point, c3 could be larger than 2^28;
	 * then, we propagate one carry from (c3 -> c4).
	 * This ensures that every digit of output
	 * sequence be less that 2^28.
	 */
	h3_h10 = SHR(c3, VECT_BASE);
	c3 = AND(c3, mask);
	c4 = ADD(c4, h3_h10);

	h4_h11 = SHR(c4, VECT_BASE);
	c4 = AND(c4, mask);
	c5 = ADD(c5, h4_h11);

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
	const argElement_2w_H0H7 _2_32P = (argElement_2w_H0H7)CONST_2_32P_ELEMENT_H0H7;

	__m256i h0_h7,  h1_h8,  h2_h9,  h3_h10;      		__m256i f0_f7,  f1_f8,  f2_f9,  f3_f10;
	__m256i h4_h11, h5_h12, h6_h13, h13, h6;     		__m256i f4_f11, f5_f12, f6_f13, f13, f6;

	__m256i c0 = LOAD(C+0);                      		__m256i d0 = LOAD(D+0);
	__m256i c1 = LOAD(C+1);                      		__m256i d1 = LOAD(D+1);
	__m256i c2 = LOAD(C+2);                      		__m256i d2 = LOAD(D+2);
	__m256i c3 = LOAD(C+3);                      		__m256i d3 = LOAD(D+3);
	__m256i c4 = LOAD(C+4);                      		__m256i d4 = LOAD(D+4);
	__m256i c5 = LOAD(C+5);                      		__m256i d5 = LOAD(D+5);
	__m256i c6 = LOAD(C+6);                      		__m256i d6 = LOAD(D+6);

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

	/**
	 * At this point, c3 could be larger than 2^28;
	 * then, we propagate one carry from (c3 -> c4).
	 * This ensures that every digit of output
	 * sequence be less that 2^28.
	 */
	h3_h10 = SHR(c3, VECT_BASE);                 		f3_f10 = SHR(d3, VECT_BASE);
	c3 = AND(c3, mask);                          		d3 = AND(d3, mask);
	c4 = ADD(c4, h3_h10);                        		d4 = ADD(d4, f3_f10);

	h4_h11 = SHR(c4, VECT_BASE);                 		f4_f11 = SHR(d4, VECT_BASE);
	c4 = AND(c4, mask);                          		d4 = AND(d4, mask);
	c5 = ADD(c5, h4_h11);                        		d5 = ADD(d5, f4_f11);

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

	__m256i h3_h10 = SHR(c3, VECT_BASE);
	c3 = AND(c3, mask);
	c4 = ADD(c4, h3_h10);

	__m256i h4_h11 = SHR(c4, VECT_BASE);
	c4 = AND(c4, mask);
	c5 = ADD(c5, h4_h11);

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

	__m256i h3_h10 = SHR(c3, VECT_BASE);                   __m256i f3_f10 = SHR(c3, VECT_BASE);
	c3 = AND(c3, mask);                                    c3 = AND(c3, mask);
	c4 = ADD(c4, h3_h10);                                  c4 = ADD(c4, f3_f10);

	__m256i h4_h11 = SHR(c4, VECT_BASE);                   __m256i f4_f11 = SHR(c4, VECT_BASE);
	c4 = AND(c4, mask);                                    c4 = AND(c4, mask);
	c5 = ADD(c5, h4_h11);                                  c5 = ADD(c5, f4_f11);
	                                                                                               
	STORE(C+0,c0);                                         STORE(D+0,d0);
	STORE(C+1,c1);                                         STORE(D+1,d1);
	STORE(C+2,c2);                                         STORE(D+2,d2);
	STORE(C+3,c3);                                         STORE(D+3,d3);
	STORE(C+4,c4);                                         STORE(D+4,d4);
	STORE(C+5,c5);                                         STORE(D+5,d5);
	STORE(C+6,c6);                                         STORE(D+6,d6);
}
