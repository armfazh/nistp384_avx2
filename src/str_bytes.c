#include "str_bytes.h"
#include "random.h"
#include <stdio.h>
#include <string.h>

void print_str_bytes(const uint8_t * A)
{
	int i;

	printf("0x");
	for(i=SIZE_STR_BYTES-1;i>=0;i--)
	{
		printf("%02x", A[i]);
	}
	printf("\n");
}

void random_str_bytes(uint8_t *A)
{
	random_bytes(A,SIZE_STR_BYTES);
}

int areEqual_str_bytes(uint8_t* A, uint8_t* B)
{
	return memcmp(A,B,sizeof(uint8_t)*SIZE_STR_BYTES)==0;
}
