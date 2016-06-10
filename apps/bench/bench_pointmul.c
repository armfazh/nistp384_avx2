#include "clocks.h"
#include "pointmul.h"
#include <stdio.h>

void bench_pointmul()
{
	long int BENCH = 1000;

	printf("=====  point mul =====\n");

	STR_BYTES a,b;
	Point_XY_1way P,R;
	Point_XYZ_1way Q;
	Point_XYZ_1way tableA[1<<(OMEGA_DYNAMIC-2)];
	int8_t wnaf_exp[392] = {0};

	random_Element_2w_h0h7(Q.XY);
	random_Element_2w_h0h7(Q.ZZ);
//	CLOCKS_RANDOM(
//			random_str_bytes(a),
//			wnaf(wnaf_exp,a,4);
//	);
//	CLOCKS_RANDOM(
//			random_str_bytes(a),
//			wnaf(wnaf_exp,a,5);
//	);
//	CLOCKS_RANDOM(
//			random_str_bytes(a),
//			wnaf(wnaf_exp,a,8);
//	);
	CLOCKS(precompute_points(tableA,&P));
	BENCH /= 5;
	CLOCKS_RANDOM(
	    random_str_bytes(a);
	    random_str_bytes(b),
		double_point_multiplication(&P,a,b,&R);
	);

}