#ifndef _ECC_H_
#define _ECC_H_

#include "str_bytes.h"
#include "element_1w_h0h7.h"
#include "element_2w_h0h7.h"


typedef ALIGN struct point_projective_2way{
	Element_2w_H0H7 X;
	Element_2w_H0H7 Y;
	Element_2w_H0H7 Z;
} PointXYZ_2way;
typedef ALIGN struct point_affine_2way{
	Element_2w_H0H7 X;
	Element_2w_H0H7 Y;
} Point_XY_2way;


typedef ALIGN struct point_projective_1way{
	Element_2w_H0H7 XY;
	Element_2w_H0H7 ZZ;
} Point_XYZ_1way;

typedef ALIGN struct point_affine_1way{
	Element_2w_H0H7 XY;
} Point_XY_1way;
/******************************
 * Point util
 ******************************/
void getGenerator(Point_XY_1way *G);
void toAffine(Point_XY_1way *aP, Point_XYZ_1way *pP);
void toProjective(Point_XYZ_1way *pP, Point_XY_1way *aP);
void print_affine_1way(Point_XY_1way* P);
void print_proj_1way(Point_XYZ_1way* P);
/******************************
 * Fixed-point
 ******************************/

void _1way_full_addition_law(Point_XYZ_1way *Q, Point_XYZ_1way *P);
void _1way_mix_addition_law(Point_XYZ_1way * Q, Point_XY_1way *P);
void _1way_doubling(Point_XYZ_1way *P);

void _2way_full_addition_law(PointXYZ_2way *Q, PointXYZ_2way *P);
void _2way_mix_addition_law(PointXYZ_2way * Q, Point_XY_2way *P);
void _2way_doubling(PointXYZ_2way *P);


/******************************
 * Double-point mult
 ******************************/

typedef ALIGN struct pointxytz_precompute_2w_h0h7{
	Element_2w_H0H7 subaddYX;
	Element_2w_H0H7 _2dT_2Z;
} PointXYZT_precompute_2w_H0H7;

typedef ALIGN struct pointxytz_2w_h0h7{
	Element_2w_H0H7 XY;
	Element_2w_H0H7 TZ;
} PointXYZT_2w_H0H7;

void precompute_points(PointXYZT_precompute_2w_H0H7 * table, PointXYZT_2w_H0H7* P);
void doubling_2w_H0H7(PointXYZT_2w_H0H7 * P);
void mixaddition_2w_H0H7(PointXYZT_2w_H0H7 *Q, PointXYZT_precompute_2w_H0H7 *P);
void fulladdition_2w_H0H7(PointXYZT_2w_H0H7 *Q, PointXYZT_2w_H0H7 *P);
void read_point(PointXYZT_precompute_2w_H0H7 * P, int8_t index);
#endif /* _ECC_H_ */
