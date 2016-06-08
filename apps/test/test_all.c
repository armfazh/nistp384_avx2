#include "test.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <random.h>

int main(void)
{
	randomize();
	printf("===== Checking: NIST-P384_avx2 =====\n");

	test_Element_1w_h0h7();
	test_Element_2w_h0h7();

	return 0;
}
