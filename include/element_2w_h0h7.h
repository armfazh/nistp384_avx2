#ifndef _ELEMENT_2W_H0H7_H_
#define _ELEMENT_2W_H0H7_H_

#include <stdint.h>
#include "avx2.h"

#define NUM_WORDS_128B_NISTP384 7
typedef ALIGN __m256i Element_2w_H0H7[NUM_WORDS_128B_NISTP384];
typedef __m256i * argElement_2w_H0H7;

void random_Element_2w_h0h7(argElement_2w_H0H7 X_Y);
void print_Element_2w_h0h7(argElement_2w_H0H7 X_Y);
void str_bytes_To_Element_2w_h0h7(argElement_2w_H0H7 pC, uint8_t *p8A);
void printex_Element_2w_h0h7(argElement_2w_H0H7 X_Y);
void print_python_Element_2w_h0h7(argElement_2w_H0H7 X_Y);
int compare_Element_2w_h0h7(argElement_2w_H0H7 X0_X1,argElement_2w_H0H7 Y0_Y1);
void sizes_Element_2w_h0h7(argElement_2w_H0H7 X_Y);


void interleave(argElement_2w_H0H7 C, uint64_t * LOW, uint64_t * HIGH);
void deinterleave(uint64_t * LOW, uint64_t * HIGH, argElement_2w_H0H7 A);
void add_Element_2w_h0h7(argElement_2w_H0H7  C,argElement_2w_H0H7 A,argElement_2w_H0H7 B);
void sub_Element_2w_h0h7(argElement_2w_H0H7 C,argElement_2w_H0H7 A,argElement_2w_H0H7 B);
void addsub_Element_2w_h0h7(
		argElement_2w_H0H7 C,
		argElement_2w_H0H7 A,
		argElement_2w_H0H7 B,
		const int subadd,
		const int large);

void mul_Element_2w_h0h7(__m256i * C, __m256i * A, __m256i * B);

void sqr_Element_2w_h0h7(__m256i * C,__m256i *  A);
void compress_Element_2w_h0h7(__m256i * C);
void compress2_Element_2w_h0h7(__m256i * C, __m256i * D);

void new_compressfast_Element_2w_h0h7(__m256i * C);
void new_compressfast2_Element_2w_h0h7(__m256i * C,__m256i * D);

void mul_schoolbook_2w_h0h7(__m256i *  C, __m256i * A, __m256i *  B);
void mul_karatsuba_2w_h0h7(__m256i *  C, __m256i * A, __m256i *  B);
void sqr_schoolbook_2w_h0h7(__m256i *  C,__m256i * A);
void sqr_karatsuba_2w_h0h7 (__m256i *  C,__m256i * A);

#define copy_Element_2w_h0h7(C,A) \
	C[0] = A[0];                  \
	C[1] = A[1];                  \
	C[2] = A[2];                  \
	C[3] = A[3];                  \
	C[4] = A[4];                  \
	C[5] = A[5];                  \
	C[6] = A[6];                  \

#endif /* _ELEMENT_2W_H0H7_H_ */