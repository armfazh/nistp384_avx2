#include "clocks.h"
#include "pointmul.h"
#include <stdio.h>

void bench_pointmul()
{
	long int BENCH = 800;

	printf("=====  point mul =====\n");

	STR_BYTES a,b;
	Point_XY_1way P,R;
	Point_XYZ_1way Q;
	Point_XYZ_1way tableFixed[1<<(OMEGA_FIXED-2)];
	Point_XYZ_1way tableDynamic[1<<(OMEGA_DYNAMIC-2)];
	int8_t wnaf_exp[392] = {0};

	CLOCKS_RANDOM(random_str_bytes(a),wnaf(wnaf_exp,a,4));
	CLOCKS_RANDOM(random_str_bytes(a),wnaf(wnaf_exp,a,5));
	CLOCKS_RANDOM(random_str_bytes(a),wnaf(wnaf_exp,a,8));
	CLOCKS_RANDOM(random_str_bytes(a),recoding(wnaf_exp,a,5));
	CLOCKS(read_point_protected(&Q,1,tableFixed));
//	int i;
//	for(i=0;i<(1<<(OMEGA_FIXED-2));i++)
//	{
//		CLOCKS(read_point_protected(&Q,2*i+1,tableFixed));
//		CLOCKS(read_point_protected(&Q,-(2*i+1),tableFixed));
//	}
	return;
	BENCH /= 8;
	CLOCKS(precompute_points(tableFixed,&P,OMEGA_FIXED));
	CLOCKS(precompute_points(tableDynamic,&P,OMEGA_DYNAMIC));
	printf("OMEGA_FIXED: %d \n",OMEGA_FIXED);
	CLOCKS_RANDOM(
			random_str_bytes(a),
			variable_point_multiplication(&P,a,&R)
	);
	printf("OMEGA_STA: %d OMEGA_DYN: %d \n",OMEGA_STATIC,OMEGA_DYNAMIC);
	CLOCKS_RANDOM(
			random_str_bytes(a);
			random_str_bytes(b),
			double_point_multiplication(&P,a,b,&R)
	);

//	oper_second(
//			random_str_bytes(a);
//			random_str_bytes(b),
//			double_point_multiplication(&P,a,b,&R)
//	);
}