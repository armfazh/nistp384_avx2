#include <stdio.h>
#include <stdlib.h>
#include "../bench/clocks.h"
#include <nettle/sha1.h>
#include <nettle/ecdsa.h>
#include <nettle/ecc-curve.h>
#include <nettle/yarrow.h>
#include <gmp.h>

void print_point(struct ecc_point* P)
{
	mpz_t x,y;
	mpz_init(x);
	mpz_init(y);
	ecc_point_get(P,x,y);
	gmp_printf("x: %Zx\n",x);
	gmp_printf("y: %Zx\n",y);
	mpz_clear(x);
	mpz_clear(y);
}

int main()
{
	struct ecc_point P,Q;
	struct ecc_scalar k;
	struct yarrow256_ctx yarrow;
	struct yarrow_source sources[2];
	int v;
	mpz_t a;

	yarrow256_init(&yarrow, 2, sources);

	if( !yarrow256_is_seeded(&yarrow) )
	{
		uint8_t seed_file[YARROW256_SEED_FILE_SIZE];
		printf("The random generator must be seeded\n");
		yarrow256_seed(&yarrow,sizeof(seed_file),seed_file);
		printf("Seeded: %s\n",yarrow256_is_seeded(&yarrow)?"Yes":"No");
	}

	mpz_init(a);

	ecc_point_init(&P, &nettle_secp_384r1);
	ecc_point_init(&Q, &nettle_secp_384r1);
	print_point(&P);
	ecc_scalar_init(&k, &nettle_secp_384r1);
	ecc_scalar_random(&k, &yarrow, (nettle_random_func*)yarrow256_random);
	ecc_scalar_get(&k, a);
	gmp_printf("scalar: %Zx\n", a);

	// Fixed point mult
	ecc_point_mul_g(&P, &k);
	print_point(&P);
	// variable point mult
	ecc_point_mul(&Q, &k, &P);
	//Key gen
	ecdsa_generate_keypair(&P, &k, &yarrow, (nettle_random_func*)yarrow256_random);
	//signature
	unsigned char digest[SHA256_DIGEST_SIZE];
	struct dsa_signature signature;
	dsa_signature_init(&signature);
	ecdsa_sign(&k, &yarrow, (nettle_random_func*)yarrow256_random, SHA256_DIGEST_SIZE, digest, &signature);
	v = ecdsa_verify(&P, SHA256_DIGEST_SIZE, digest, &signature);
	printf("verif: %d\n", v);
#if 1
	long BENCH = 100;
	CLOCKS(ecc_point_mul_g(&P, &k));
	CLOCKS(ecc_point_mul(&Q, &k, &P));
	CLOCKS(ecdsa_generate_keypair(&P, &k, &yarrow, (nettle_random_func*)yarrow256_random));
	CLOCKS(ecdsa_sign(&k, &yarrow, (nettle_random_func*)yarrow256_random, SHA256_DIGEST_SIZE, digest, &signature));
	CLOCKS(ecdsa_verify(&P, SHA256_DIGEST_SIZE, digest, &signature));
#endif
	dsa_signature_clear(&signature);
	ecc_point_clear(&P);
	ecc_point_clear(&Q);
	ecc_scalar_clear(&k);

	mpz_clear(a);

	return 0;
}
