//
// Created by armfazh on 6/20/16.
//

#include "test.h"
#include "pointmul.h"
#include <stdio.h>

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>

#define LABEL "Test passed? [%s]\n"
#define OK "Ok"
#define ERROR "No"

#define P384 NID_secp384r1

void BN_to_str_bytes(uint8_t *str_num, BIGNUM *n)
{
	int i;
	uint8_t tmp;
	uint8_t end = BN_num_bytes(n);

	BN_bn2bin(n,str_num);

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
void to_point(Point_XY_1way * P,const EC_GROUP*ec_group, EC_POINT * OSSL_P)
{
	STR_BYTES str_x,str_y;
	Element_1w_H0H7 x,y;
	BIGNUM * Px = BN_new();
	BIGNUM * Py = BN_new();
	EC_POINT_get_affine_coordinates_GFp(ec_group,OSSL_P,Px,Py,NULL);
	BN_to_str_bytes(str_x, Px);
	BN_to_str_bytes(str_y, Py);
	str_bytes_To_Element_1w_h0h7(x,str_x);
	str_bytes_To_Element_1w_h0h7(y,str_y);
	interleave(P->XY,x,y);
	BN_free(Px);
	BN_free(Py);
}

int compare_element(BIGNUM* x , uint8_t *y)
{
	STR_BYTES bufX;
	BN_to_str_bytes(bufX, x);
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
	EC_KEY_free(ec_key);
}

void test_pointmul()
{
	long int cnt = 0;
	int i,test;

	Point_XY_1way P,kG;

	EC_KEY * ec_key = EC_KEY_new_by_curve_name(P384);
	const EC_GROUP * ec_group = EC_KEY_get0_group(ec_key);
	BIGNUM * ec_order = BN_new();
	EC_GROUP_get_order(ec_group,ec_order,NULL);

	/* Fixed point multiplication */
	EC_POINT * OSSL_kG = EC_POINT_new(ec_group);
	EC_POINT * OSSL_Q  = EC_POINT_new(ec_group);
	BIGNUM * k = BN_new();
	BIGNUM * k1 = BN_new();
	STR_BYTES str_k,str_k1;

	printf("Fixed point test:");
	cnt = 0;
	for(i=0;i<TEST_TIMES;i++)
	{
		BN_rand_range(k,ec_order);
		EC_POINT_mul(ec_group,OSSL_kG,k,NULL,NULL,NULL);

		BN_to_str_bytes(str_k, k);
		fixed_point_multiplication(&kG,str_k);
		test = compare_point(ec_group,OSSL_kG,&kG);
		if(!test)
		{
			char* s=NULL;
			STR_BYTES buf;
			BN_to_str_bytes(buf, k);
			printf("\nOP_k: \n");printf("\n");print_str_bytes(buf);
			printf("\nTH_k: \n");print_str_bytes(str_k);
			print_affine_1way(&kG);
			printf("%s\n",s=EC_POINT_point2hex(ec_group,OSSL_kG,POINT_CONVERSION_UNCOMPRESSED,NULL)); OPENSSL_free(s);
			break;
		}
		cnt += test;
	}
	printf(" %ld %s\n",cnt , cnt == TEST_TIMES? "OK" : "FAIL" );

	/* Variable point multiplication */
	printf("Variable point test:");
	BN_rand_range(k,ec_order);
	EC_POINT_mul(ec_group,OSSL_kG,k,NULL,NULL,NULL);
	cnt = 0;
	for(i=0;i<TEST_TIMES;i++)
	{
		BN_rand_range(k,ec_order);
		EC_POINT_mul(ec_group,OSSL_Q,NULL,OSSL_kG,k,NULL);

		BN_to_str_bytes(str_k, k);
		to_point(&P,ec_group,OSSL_kG);
		variable_point_multiplication(&kG,str_k,&P);
		test = compare_point(ec_group,OSSL_Q,&kG);
		if(!test)
		{
			STR_BYTES buf;
			char* s = NULL;
			BN_to_str_bytes(buf, k);

			printf("\nTH_k : \n");print_str_bytes(str_k);
			printf("TH_P : \n");print_affine_1way(&P);
			printf("TH_kP: \n");print_affine_1way(&kG);
			printf("OP_k : \n");print_str_bytes(buf);
			printf("OP_P : \n");printf("%s\n",s=EC_POINT_point2hex(ec_group,OSSL_kG,POINT_CONVERSION_UNCOMPRESSED,NULL)); OPENSSL_free(s);
			printf("OP_kP: \n");printf("%s\n",s=EC_POINT_point2hex(ec_group,OSSL_Q,POINT_CONVERSION_UNCOMPRESSED,NULL));  OPENSSL_free(s);
			break;
		}
		cnt += test;
	}
	printf(" %ld %s\n",cnt , cnt == TEST_TIMES? "OK" : "FAIL" );

	/* Double point multiplication */
	printf("Double point test:");
	BN_rand_range(k,ec_order);
	EC_POINT_mul(ec_group,OSSL_kG,k,NULL,NULL,NULL);
	cnt = 0;
	for(i=0;i<TEST_TIMES;i++)
	{
		BN_rand_range(k,ec_order);
		BN_rand_range(k1,ec_order);
		EC_POINT_mul(ec_group,OSSL_Q,k,OSSL_kG,k1,NULL);

		BN_to_str_bytes(str_k, k);
		BN_to_str_bytes(str_k1, k1);
		to_point(&P,ec_group,OSSL_kG);
		double_point_multiplication(&kG,str_k,str_k1,&P);
		test = compare_point(ec_group,OSSL_Q,&kG);
		if(!test)
		{
			STR_BYTES buf,buf1;
			char* s = NULL;
			BN_to_str_bytes(buf, k);
			BN_to_str_bytes(buf1, k1);
			printf("TH_k : \n");print_str_bytes(str_k);
			printf("TH_k1: \n");print_str_bytes(str_k1);
			printf("TH_P : \n");print_affine_1way(&P);
			printf("TH_kP: \n");print_affine_1way(&kG);
			printf("OP_k : \n");print_str_bytes(buf);
			printf("OP_k1: \n");print_str_bytes(buf1);
			printf("OP_P : \n");printf("%s\n",s=EC_POINT_point2hex(ec_group,OSSL_kG,POINT_CONVERSION_UNCOMPRESSED,NULL)); OPENSSL_free(s);
			printf("OP_kP: \n");printf("%s\n",s=EC_POINT_point2hex(ec_group,OSSL_Q,POINT_CONVERSION_UNCOMPRESSED,NULL));  OPENSSL_free(s);
			break;
		}
		cnt += test;
	}
	printf(" %ld %s\n",cnt , cnt == TEST_TIMES? "OK" : "FAIL" );


	EC_POINT_free(OSSL_Q);
	EC_POINT_free(OSSL_kG);
	BN_free(k);
	BN_free(k1);
	BN_free(ec_order);
	EC_KEY_free(ec_key);
}