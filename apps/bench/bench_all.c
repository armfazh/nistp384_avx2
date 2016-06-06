#include "bench.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	srand((unsigned int)time(NULL));
	printf("===== Benchmarking: NIST-P384_avx2 =====\n");

	bench_element_1w_h0h7();

	return 0;
}


