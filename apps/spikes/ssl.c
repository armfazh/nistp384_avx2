//
// Created by armfazh on 6/15/16.
//
#include <openssl/ec.h>
#include <openssl/ecdh.h>
#include <openssl/ecdsa.h>
#include<openssl/objects.h>
#include "../bench/clocks.h"

#define P256 NID_X9_62_prime256v1
#define P384 NID_secp384r1

void print_point_proy(EC_GROUP*ec_group,EC_POINT*P)
{
	BIGNUM *x = BN_new();
	BIGNUM *y = BN_new();
	BIGNUM *z = BN_new();

	if (EC_POINT_get_Jprojective_coordinates_GFp(ec_group, P, x, y,z, NULL))
	{
		printf("x: ");	BN_print_fp(stdout, x);	printf("\n");
		printf("y: ");	BN_print_fp(stdout, y);	printf("\n");
		printf("z: ");	BN_print_fp(stdout, z);	printf("\n");
	}
	BN_free(x);
	BN_free(y);
	BN_free(z);
}
void print_point_affine(EC_GROUP*ec_group,EC_POINT*P)
{
	BIGNUM *x = BN_new();
	BIGNUM *y = BN_new();

	if (EC_POINT_get_affine_coordinates_GFp(ec_group, P, x, y, NULL))
	{
		printf("x: ");	BN_print_fp(stdout, x);	printf("\n");
		printf("y: ");	BN_print_fp(stdout, y);	printf("\n");
	}
	BN_free(x);
	BN_free(y);
}

void print_str_bytes(const uint8_t * A)
{
	int i;

	printf("0x");
	for(i=48-1;i>=0;i--)
	{
		printf("%02x", A[i]);
	}
	printf("\n");
}
int main()
{
	int i=0;
	EC_KEY   * ec_key;
	EC_GROUP * ec_group;
	EC_POINT * G;
	EC_METHOD* method;
	BIGNUM   * ec_order = BN_new();

	printf("OpenSSL version: %s\n", SSLeay_version(SSLEAY_VERSION));
//	printf("compiled with: %s\n", SSLeay_version(SSLEAY_CFLAGS));
//	printf("built on: %s\n", SSLeay_version(SSLEAY_BUILT_ON));
//	printf("located on: %s\n", SSLeay_version(SSLEAY_DIR));


//	printf("ECC Key type: %s\n", OBJ_nid2sn(P384));
	ec_key = EC_KEY_new_by_curve_name(P384);
	EC_KEY * alice_key = EC_KEY_new_by_curve_name(P384);

//	ECParameters_print_fp(stdout,ec_key);

	ec_group = EC_KEY_get0_group(ec_key);
	EC_GROUP_get_order(ec_group,ec_order,NULL);
	G = EC_GROUP_get0_generator(ec_group);
	printf("G: \n");print_point_affine(ec_group,G);
	method = EC_GFp_nist_method();
	BIGNUM *n = BN_new();
	BIGNUM *m = BN_new();

	EC_POINT *_2G = EC_POINT_new(ec_group);
	EC_POINT *_3G = EC_POINT_new(ec_group);

	EC_POINT_dbl(ec_group,_2G,G,NULL);
//	printf("2G: \n");print_point(ec_group,_2G);
	EC_POINT_add(ec_group,_3G,_2G,G,NULL);
//	printf("3G: \n");print_point(ec_group,_3G);

	EC_POINT *kG = EC_POINT_new(ec_group);
	BIGNUM * k = BN_new();

	do {
		BN_rand_range(k, ec_order);
	}while (BN_is_zero(k));
	EC_KEY_generate_key(ec_key);

	printf("k: ");	BN_print_fp(stdout, k);	printf("\n");
	EC_POINT_mul(ec_group,kG,k,NULL,NULL,NULL);

	printf("kG: \n");
	print_point_proy(ec_group,kG);
	print_point_affine(ec_group,kG);

	//if(EC_GROUP_have_precompute_mult(ec_group) == 0)
	EC_GROUP_precompute_mult(ec_group,NULL);


	EC_KEY_generate_key(ec_key);
	EC_KEY_generate_key(alice_key);
	unsigned char *shared_secret;
	int field_size = EC_GROUP_get_degree(ec_group);
	int size = (field_size+7)/8;
	shared_secret = malloc(size);
	ECDH_compute_key(shared_secret,size,EC_KEY_get0_public_key(ec_key),alice_key,NULL);

	print_str_bytes(shared_secret);
	EC_KEY_set_asn1_flag(ec_key, OPENSSL_EC_NAMED_CURVE);
	EC_KEY_set_asn1_flag(alice_key, OPENSSL_EC_NAMED_CURVE);
//	goto end;

	long BENCH=200;
	printf("Variable point:\n");
	CLOCKS_RANDOM(
			BN_rand_range(k, ec_order),
			EC_POINT_mul(ec_group,kG,NULL,kG,k,NULL);
			EC_POINT_get_affine_coordinates_GFp(ec_group,kG,n,m,NULL)
	);

	printf("Fixed point:\n");
	CLOCKS_RANDOM(
			BN_rand_range(k, ec_order),
			EC_POINT_mul(ec_group,kG,k,NULL,NULL,NULL);
			EC_POINT_get_affine_coordinates_GFp(ec_group,kG,n,m,NULL)
	);

	printf("Double point:\n");
	CLOCKS_RANDOM(
			BN_rand_range(k, ec_order),
			EC_POINT_mul(ec_group,kG,k,_3G,m,NULL);
			EC_POINT_get_affine_coordinates_GFp(ec_group,kG,n,m,NULL)
	);

	printf("ECDH Key:\n");
	CLOCKS(ECDH_compute_key(shared_secret,size,EC_KEY_get0_public_key(ec_key),alice_key,NULL));

	ECDSA_SIG *sig=NULL;
	char message [128];
	printf("ECDSA Sign:\n");
	CLOCKS(
			sig = ECDSA_do_sign(message,128,ec_key);
			ECDSA_SIG_free(sig);
	);

	printf("ECDSA Sign:\n");
	CLOCKS_RANDOM(
			sig = ECDSA_do_sign(message,128,ec_key),
			ECDSA_do_verify(message, 128, sig, ec_key);
	);
	ECDSA_SIG_free(sig);
end:
	free(shared_secret);
	BN_free(n);
	BN_free(m);
	EC_POINT_free(_2G);
	EC_POINT_free(_3G);
	EC_KEY_free(ec_key);
	return i;
}