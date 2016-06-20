//
// Created by armfazh on 6/20/16.
//

#include "test.h"
#include "pointmul.h"
#include <stdio.h>
#include <string.h>

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>

#define LABEL "Test passed? [%s]\n"
#define OK "Ok"
#define ERROR "No"

#define P384 NID_secp384r1

void to_littleEndian(uint8_t *str_num, BIGNUM* n)
{
	BN_bn2bin(n,str_num);
	int i;
	uint8_t tmp;
	uint8_t end = BN_num_bytes(n);
	for(i=0;i<(end+1)/2 ;i++)
	{
		tmp  = str_num[i];
		str_num[i] = str_num[end-i-1];
		str_num[end-i-1] = tmp;
	}
	for(i=end;i<SIZE_STR_BYTES;i++)
	{
		str_num[i] = 0;
	}
}

int compare_element(BIGNUM* x , uint8_t *y)
{
	STR_BYTES bufX;
	to_littleEndian(bufX,x);
//	printf("OP: ");print_str_bytes(bufX);
//	printf("TH: ");print_str_bytes(y);
	return areEqual_str_bytes(bufX,y);
}
int compare_point(const EC_GROUP * ec_group, const EC_POINT * P , Point_XY_1way * Q)
{
	STR_BYTES sQx,sQy;
	Element_1w_H0H7 Qx,Qy;
	BIGNUM *Px,*Py;
	Px = BN_new();
	Py = BN_new();
	deinterleave(Qx,Qy,Q->XY);
	Element_1w_h0h7_To_str_bytes(sQx,Qx);
	Element_1w_h0h7_To_str_bytes(sQy,Qy);
	EC_POINT_get_affine_coordinates_GFp(ec_group,P,Px,Py,NULL);

	int ret = compare_element(Px,sQx) && compare_element(Py,sQy);
	BN_free(Px);
	BN_free(Py);
	return ret;
}

void test_ecc()
{
	Point_XY_1way P,G;
	Point_XYZ_1way pP,pG;

	getGenerator(&G);
	getGenerator(&P);
	EC_KEY * ec_key = EC_KEY_new_by_curve_name(P384);
	const EC_GROUP * ec_group = EC_KEY_get0_group(ec_key);
	BIGNUM * ec_order = BN_new();
	EC_GROUP_get_order(ec_group,ec_order,NULL);
	const EC_POINT * OSSL_G = EC_GROUP_get0_generator(ec_group);
	EC_POINT * OSSL_2G = EC_POINT_new(ec_group);
	EC_POINT * OSSL_3G = EC_POINT_new(ec_group);

	printf("Generator: ");
	printf(LABEL,compare_point(ec_group,OSSL_G,&G)?OK:ERROR);

	EC_POINT_dbl(ec_group,OSSL_2G,OSSL_G,NULL);
	EC_POINT_add(ec_group,OSSL_3G,OSSL_2G,OSSL_G,NULL);

	toProjective(&pG,&G);
	toProjective(&pP,&P);
	_1way_doubling(&pG);
	_1way_full_addition_law(&pP,&pG);

	toAffine(&G,&pG);
	toAffine(&P,&pP);
	printf("Doubling: ");
	printf(LABEL,compare_point(ec_group,OSSL_2G,&G)?OK:ERROR);
	printf("Full addition: ");
	printf(LABEL,compare_point(ec_group,OSSL_3G,&P)?OK:ERROR);

	EC_POINT_free(OSSL_2G);
	EC_POINT_free(OSSL_3G);
	BN_free(ec_order);
	EC_KEY_free(ec_key);
}

void test_pointmul()
{
	int cnt = 0;
	int i,test;

	Point_XY_1way G,kG;
	getGenerator(&G);

	EC_KEY * ec_key = EC_KEY_new_by_curve_name(P384);
	const EC_GROUP * ec_group = EC_KEY_get0_group(ec_key);
	BIGNUM * ec_order = BN_new();
	EC_GROUP_get_order(ec_group,ec_order,NULL);
//	const EC_POINT * OSSL_G = EC_GROUP_get0_generator(ec_group);

	/* Fixed point multiplication */
	EC_POINT * OSSL_kG = EC_POINT_new(ec_group);
	BIGNUM * k = BN_new();
	STR_BYTES str_k;

	printf("Fixed point test:");
	for(i=0;i<TEST_TIMES;i++)
	{
		BN_rand_range(k,ec_order);
		EC_POINT_mul(ec_group,OSSL_kG,k,NULL,NULL,NULL);

		to_littleEndian(str_k,k);
		fixed_point_multiplication(&kG,str_k);
		test = compare_point(ec_group,OSSL_kG,&kG);
		if(!test)
		{
			STR_BYTES buf;
			BN_print_fp(stdout,k);printf("\n");
			to_littleEndian(buf,k);
			printf("\nOP_k: \n");print_str_bytes(buf);
			printf("\nTH_k: \n");print_str_bytes(str_k);
			print_affine_1way(&kG);
			printf("%s\n",EC_POINT_point2hex(ec_group,OSSL_kG,POINT_CONVERSION_UNCOMPRESSED,NULL));
			break;
		}
		cnt += test;
	}
	printf(" %ld %s\n",cnt , cnt == TEST_TIMES? "OK" : "FAIL" );

	EC_POINT_free(OSSL_kG);
	BN_free(k);
	BN_free(ec_order);
	EC_KEY_free(ec_key);

}