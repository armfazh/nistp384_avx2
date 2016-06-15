//
// Created by armfazh on 6/15/16.
//
#include <openssl/ec.h>
#include<openssl/ecdsa.h>
#include<openssl/objects.h>


#define P256 NID_X9_62_prime256v1
#define P384 NID_secp384r1



void print_point(EC_GROUP*ec_group,EC_POINT*P)
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

int main()
{
	int i=0;
	EC_KEY   * ec_key;
	EC_GROUP * ec_group;
	EC_POINT * G;
	EC_METHOD* method;

	printf("OpenSSL version: %s\n", SSLeay_version(SSLEAY_VERSION));
//	printf("compiled with: %s\n", SSLeay_version(SSLEAY_CFLAGS));
	printf("built on: %s\n", SSLeay_version(SSLEAY_BUILT_ON));
	printf("located on: %s\n", SSLeay_version(SSLEAY_DIR));


	printf("ECC Key type: %s\n", OBJ_nid2sn(P384));
	ec_key = EC_KEY_new_by_curve_name(P384);

	ECParameters_print_fp(stdout,ec_key);

	ec_group = EC_KEY_get0_group(ec_key);
	G = EC_GROUP_get0_generator(ec_group);
	printf("G: \n");print_point(ec_group,G);
	method = EC_GFp_nist_method();
	BIGNUM *n = BN_new();
	BIGNUM *m = BN_new();

	EC_POINT *_2G = EC_POINT_new(ec_group);
	EC_POINT *_3G = EC_POINT_new(ec_group);

	EC_POINT_dbl(ec_group,_2G,G,NULL);
	printf("2G: \n");print_point(ec_group,_2G);
	EC_POINT_add(ec_group,_3G,_2G,G,NULL);
	printf("3G: \n");print_point(ec_group,_3G);


	BN_free(n);
	BN_free(m);
	EC_POINT_free(_2G);
	EC_POINT_free(_3G);
	EC_KEY_free(ec_key);
	return i;
}
