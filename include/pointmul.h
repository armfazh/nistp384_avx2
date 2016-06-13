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
int recoding(int8_t * K,const uint8_t *p8_r, int w);
void recoding_signed_scalar_fold2w4(uint64_t *list_signs, uint64_t *list_digits, uint8_t *r);
void query_table(Point_XY_2way *P, const uint8_t * table,uint64_t * secret_signs,uint64_t *secret_digits);
void fixed_point_multiplication(Point_XY_1way* kP, uint8_t *k);

#define OMEGA_FIXED 6
void read_point_protected(Point_XYZ_1way * P,int8_t index,Point_XYZ_1way * Table);
void variable_point_multiplication(
		Point_XY_1way * kP,
		uint8_t *k,
		Point_XY_1way * P);

#define OMEGA_STATIC 7
#define OMEGA_DYNAMIC 5
int wnaf(int8_t * K, const uint8_t *p8_r, int w);
void precompute_points(Point_XYZ_1way * table, Point_XY_1way * P,const int OMEGA);
void read_point(Point_XYZ_1way * P, int8_t abs_index);
void double_point_multiplication(
		Point_XY_1way * kP_lQ,
		uint8_t *k, uint8_t *l,
		Point_XY_1way * Q);
#endif /* _NISTP384_AVX2_POINTMUL_H_ */

