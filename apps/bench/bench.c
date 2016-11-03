#include "clocks.h"
#include "bench.h"
#include <stdio.h>
#include <openssl/bn.h>
#include <openssl/objects.h>
#include <openssl/ec.h>
#include <random.h>

int main(void)
{
	randomize();
	printf("===== Benchmarking: NIST-P384_avx2 =====\n");
//
//long BENCH=1000;
//	BN_CTX * ctx = BN_CTX_new();
//	BN_CTX_init(ctx);
//	BIGNUM *c =BN_new();
//	BIGNUM *a =BN_new();
//	BIGNUM *b =BN_new();
//
//const BIGNUM *prime = BN_get0_nist_prime_384();
//	printf("Mod add:\n");
//	CLOCKS_RANDOM(
//			BN_rand_range(a,prime),
//			BN_mod_add(c,a,b,prime,ctx)
//	);
//	printf("Mod sub:\n");
//	CLOCKS_RANDOM(
//			BN_rand_range(a,prime),
//			BN_mod_sub(c,a,b,prime,ctx)
//	);
//	printf("Mod mult:\n");
//	CLOCKS_RANDOM(
//			BN_rand_range(a,prime),
//			BN_mod_mul(c,a,b,prime,ctx)
//	);
//	printf("Mod sqr:\n");
//	CLOCKS_RANDOM(
//			BN_rand_range(a,prime),
//			BN_mod_sqr(c,a,prime,ctx)
//	);
//	 BENCH=300;
//	printf("Mod inv:\n");
//	CLOCKS_RANDOM(
//			BN_rand_range(a,prime),
//			BN_mod_inverse(c,a,prime,ctx)
//	);

//	bench_element_1w_h0h7();
	bench_element_2w_h0h7();
	bench_ecc();
	bench_pointmul();

//	BN_CTX_free(ctx);
	return 0;
}


