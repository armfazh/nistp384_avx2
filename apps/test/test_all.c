#include "test.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(void)
{
	srand((unsigned int)time(NULL));
	printf("===== Checking: NIST-P384_avx2 =====\n");

	test_Element_1w_h0h7();
	
	return 0;
}
