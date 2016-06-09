#ifndef _NISTP384_AVX2_POINTMUL_H_
#define _NISTP384_AVX2_POINTMUL_H_

#include <stdint.h>
#include "ecc.h"
#define NUM_LUT (28)
#define SIZE_POINT (3*384/8)
#define SIZE_ONE_LUT (8*SIZE_POINT)
#define SIZE_ALL_LUT (NUM_LUT*SIZE_POINT)

void div4(unsigned char * number_div_4,const unsigned char * number);
void word64_multiplier(uint64_t*C,const uint64_t*A, int numA,const uint64_t*B, int numB);
void recoding_signed_scalar_fold2w4(uint64_t *list_signs, uint64_t *list_digits, uint8_t *r);
void query_table(Point_XY_2way *P, const uint8_t * table,uint64_t * secret_signs,uint64_t *secret_digits);
#define OMEGA_STATIC 5


#define OMEGA_DYNAMIC 5
int wnaf(int8_t * K, const uint8_t *p8_r, int w);
void fixed_point_multiplication(Point_XY_1way* kP, uint8_t *k);
void double_point_multiplication(Point_XY_2way * kP_lQ, const uint8_t *k, uint8_t *l, Point_XY_2way * A);

#endif /* _NISTP384_AVX2_POINTMUL_H_ */

