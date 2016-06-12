#include "bench.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <random.h>

int main(void)
{
	randomize();
	printf("===== Benchmarking: NIST-P384_avx2 =====\n");

	bench_element_1w_h0h7();
	bench_element_2w_h0h7();
	bench_ecc();
	bench_pointmul();
	return 0;
}


