#include "clocks.h"
#include "ecc.h"
#include <stdio.h>

void bench_ecc()
{
	long int BENCH = 1000;

	printf("=====  ecc =====\n");

	Point_XY_1way P;
	Point_XYZ_1way Q,R;
	Point_XYZ_2way P_2w,Q_2w;
	random_Element_2w_h0h7(P.XY);
	random_Element_2w_h0h7(Q.XY);
	random_Element_2w_h0h7(Q.ZZ);
	CLOCKS(_1way_doubling(&Q));
	CLOCKS(_1way_mix_addition_law(&Q,&P));
	CLOCKS(_1way_full_addition_law(&Q,&R));
	CLOCKS(_2way_full_addition_law(&P_2w,&Q_2w));
	BENCH /= 5;
	CLOCKS(toProjective(&Q,&P));
	CLOCKS(toAffine(&P,&Q));
}