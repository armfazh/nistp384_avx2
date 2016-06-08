#ifndef _ECC_H_
#define _ECC_H_

#include "str_bytes.h"
#include "element_1w_h0h7.h"
#include "element_2w_h0h7.h"

typedef ALIGN struct point_projective_1way{
	Element_1w_H0H7 X;
	Element_1w_H0H7 Y;
	Element_1w_H0H7 Z;
} PointXYZ_1way;

typedef ALIGN struct point_projective_2way{
	Element_2w_H0H7 X;
	Element_2w_H0H7 Y;
	Element_2w_H0H7 Z;
} PointXYZ_2way;

typedef ALIGN struct point_affine_1way{
	Element_1w_H0H7 X;
	Element_1w_H0H7 Y;
} Point_XY_1way;

typedef ALIGN struct point_affine_2way{
	Element_2w_H0H7 X;
	Element_2w_H0H7 Y;
} Point_XY_2way;


/******************************
 * Fixed-point
 ******************************/

#define NUM_LUT (28)
#define SIZE_POINT (3*384/8)
#define SIZE_ONE_LUT (8*SIZE_POINT)
#define SIZE_ALL_LUT (NUM_LUT*SIZE_POINT)

void div4(unsigned char * number_div_4,const unsigned char * number);
void word64_multiplier(uint64_t*C,const uint64_t*A, int numA,const uint64_t*B, int numB);
void recoding_signed_scalar_fold2w4(uint64_t *list_signs, uint64_t *list_digits, uint8_t *r);
void query_table(Point_XY_2way *P, const uint8_t * table,uint64_t * secret_signs,uint64_t *secret_digits);

void _1way_full_addition_law(PointXYZ_1way *Q, PointXYZ_1way *P);
void _1way_mix_addition_law(PointXYZ_1way * Q, Point_XY_1way *P);
void _1way_doubling(PointXYZ_1way *P);

void _2way_full_addition_law(PointXYZ_2way *Q, PointXYZ_2way *P);
void _2way_mix_addition_law(PointXYZ_2way * Q, Point_XY_2way *P);
void _2way_doubling(PointXYZ_2way *P);

void fixed_point_multiplication(Point_XY_1way* kP, uint8_t *k);

/******************************
 * Double-point mult
 ******************************/

#define OMEGA_STATIC 5
#define OMEGA_DYNAMIC 5
typedef ALIGN struct pointxytz_precompute_2w_h0h7{
	Element_2w_H0H7 subaddYX;
	Element_2w_H0H7 _2dT_2Z;
} PointXYZT_precompute_2w_H0H7;

typedef ALIGN struct pointxytz_2w_h0h7{
	Element_2w_H0H7 XY;
	Element_2w_H0H7 TZ;
} PointXYZT_2w_H0H7;

void precompute_points(PointXYZT_precompute_2w_H0H7 * table, PointXYZT_2w_H0H7* P);
int wnaf(int8_t * K, const uint8_t *p8_r, int w);
void doubling_2w_H0H7(PointXYZT_2w_H0H7 * P);
void mixaddition_2w_H0H7(PointXYZT_2w_H0H7 *Q, PointXYZT_precompute_2w_H0H7 *P);
void fulladdition_2w_H0H7(PointXYZT_2w_H0H7 *Q, PointXYZT_2w_H0H7 *P);
void read_point(PointXYZT_precompute_2w_H0H7 * P, int8_t index);
void double_point_multiplication(Point_XY_2way * kP_lQ, const uint8_t *k, uint8_t *l, Point_XY_2way * A);
#endif /* _ECC_H_ */
