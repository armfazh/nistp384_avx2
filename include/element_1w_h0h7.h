#ifndef NISTP384_AVX2_ELEMENT_1W_H
#define NISTP384_AVX2_ELEMENT_1W_H

#include <stdint.h>
#include "avx2.h"

#define MEM_SIZE_NISTP384 16
typedef ALIGN uint64_t Element_1w_H0H7[MEM_SIZE_NISTP384];
typedef uint64_t * argElement_1w_H0H7;
#define NUM_WORDS_64B_NISTP384 14
#define NUM_WORDS_256B_NISTP384 4

#define VECT_BASE 28


void random_Element_1w_h0h7(uint64_t *A);
void print_Element_1w_h0h7(uint64_t *A);
void printex_Element_1w_h0h7(uint64_t *A);
void print_python_Element_1w_h0h7(uint64_t *A);
void sizes_Element_1w_h0h7(uint64_t *C);

int compare_Element_1w_h0h7(uint64_t *A, uint64_t *B);

void to_1w_h0h7(uint64_t *C);
void from_1w_h0h7(uint64_t *C);
void str_bytes_To_Element_1w_h0h7(uint64_t *__restrict pC, uint8_t *__restrict p8A);
void Element_1w_h0h7_To_str_bytes(uint8_t *__restrict p8C, uint64_t *__restrict pA);

void neg_Element_1w_h0h7(uint64_t *pA);
void add_Element_1w_h0h7(uint64_t *C, uint64_t *A, uint64_t *B);
void sub_Element_1w_h0h7(uint64_t *C, uint64_t *A, uint64_t *B);
void addsub_Element_1w_h0h7(uint64_t *pA, uint64_t *pB);
void naddsub_Element_1w_h0h7(uint64_t *pC, uint64_t *pD, uint64_t *pA, uint64_t *pB);
void mul_schoolbook_Element_1w_h0h7(uint64_t *C, uint64_t *A, uint64_t *B);
void mul_Element_1w_h0h7(uint64_t *C, uint64_t *A, uint64_t *B);
void sqr_Element_1w_h0h7(uint64_t *A);
void inv_Element_1w_h0h7(uint64_t * __restrict pC, uint64_t * __restrict pA);
void compressfast_Element_1w_h0h7(uint64_t *A);
void new_compressfast_Element_1w_h0h7(uint64_t *A);
void compress_Element_1w_h0h7(uint64_t *A);
void sqrn_Element_1w_h0h7(uint64_t *A, int times);

#endif /* NISTP384_AVX2_ELEMENT_1W_H */

