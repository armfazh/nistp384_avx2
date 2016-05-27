#ifndef _STR_BYTES_H_ /* _STR_BYTES_H_ */
#define _STR_BYTES_H_

#include <stdint.h>
#include "avx2.h"

#define SIZE_STR_BYTES 48
typedef ALIGN uint8_t STR_BYTES[SIZE_STR_BYTES];

void random_str_bytes(uint8_t *A);
void print_str_bytes(const uint8_t * A);
int areEqual_str_bytes(uint8_t* A, uint8_t* B);

#endif /* _STR_BYTES_H_ */
