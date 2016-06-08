#include <stdlib.h>
#include <stdio.h>
#include "random.h"

void randomize()
{
	FILE * ff = fopen("/dev/random","r");
	unsigned int seed;
	fread(&seed,sizeof(unsigned int),1,ff);
	srand(seed);
	fclose(ff);
}

void random_bytes(uint8_t *A, int length)
{
	int i;
	for(i=0; i<length; i++)
	{
		A[i] = (uint8_t) rand();
	}
}