#include<stdio.h>
#include <str_bytes.h>
#include <ecc.h>
#include <pointmul.h>
#include <string.h>
#include "element_1w_h0h7.h"
#include "element_2w_h0h7.h"
extern uint64_t TableSign_w4_36k[NUM_LUT*8*2*6];

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>

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

void str_bytes_to_BN(BIGNUM *n, uint8_t *str_num)
{
	int i;
	STR_BYTES buf;
	uint8_t tmp;
	uint8_t end = SIZE_STR_BYTES;

	for(i=0;i<SIZE_STR_BYTES ;i++)
	{
		buf[SIZE_STR_BYTES-i-1] = str_num[i];
	}
	BN_bin2bn(buf,SIZE_STR_BYTES,n);
}

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

void OSSL_print_int(BIGNUM* num)
{
	STR_BYTES buf;
	BN_to_str_bytes(buf, num);
	print_str_bytes(buf);
}
void OSSL_print_point(EC_POINT* point,const EC_GROUP * ec_group)
{
	char*s;
	printf("%s\n",s=EC_POINT_point2hex(ec_group,point,POINT_CONVERSION_UNCOMPRESSED,NULL));
	OPENSSL_free(s);
}

int main()
{
	int i=0;
	printf("=== MAIN === \n");

#if 0 /* === Element 1w ===  */
	printf("=== Element 1w === \n");

	Element_1w_H0H7 a,b,c,d;
	random_Element_1w_h0h7(a);
	random_Element_1w_h0h7(b);
	print_Element_1w_h0h7(a);
//	print_Element_1w_h0h7(b);

//	printex_Element_1w_h0h7(a);
//	print_python_Element_1w_h0h7(a);
//	Element_1w_h0h7_To_str_bytes(B,a);
//	print_str_bytes(B);

//	random_Element_1w_h0h7(a);
//	random_Element_1w_h0h7(b);

//	print_Element_1w_h0h7(a);
//	print_Element_1w_h0h7(b);

//	add_Element_1w_h0h7(c,a,b);
//	printf("add:\n");print_Element_1w_h0h7(c);
//
//	sub_Element_1w_h0h7(d,a,b);
//	printf("sub:\n");
//	sizes_Element_1w_h0h7(d);
//	print_Element_1w_h0h7(d);
//
//	neg_Element_1w_h0h7(a);
//	sizes_Element_1w_h0h7(a);
//	printf("neg:\n");print_Element_1w_h0h7(a);

//	mul_Element_1w_h0h7(c,b,a);
//	printf("mul:\n");
//	compress_Element_1w_h0h7(c);
//	print_Element_1w_h0h7(c);

//	sqr_Element_1w_h0h7(a);
//	printf("sqr:\n");
//	compress_Element_1w_h0h7(a);
//	print_Element_1w_h0h7(a);


//	for(i=0;i<40;i++)
//		add_Element_1w_h0h7(c,c,a);
//
//	sizes_Element_1w_h0h7(c);
//	new_compressfast_Element_1w_h0h7(c);
//	sizes_Element_1w_h0h7(c);
//	print_Element_1w_h0h7(c);

	inv_Element_1w_h0h7(c,a);
	print_Element_1w_h0h7(c);
#endif

#if 0 /* === Element 2w ===  */
	printf("=== Element 2w === \n");
	Element_2w_H0H7 a,b,c,d;

	random_Element_2w_h0h7(a);
	random_Element_2w_h0h7(b);
	print_Element_2w_h0h7(a);
	print_Element_2w_h0h7(b);

	addsub_Element_2w_h0h7(c,a,b,0,0);
	addsub_Element_2w_h0h7(d,a,b,0,1);
	compress_Element_2w_h0h7(d);
	printf("equal: %s\n",compare_Element_2w_h0h7(c,d)?"yes":"no");

	addsub_Element_2w_h0h7(c,a,b,1,0);
	addsub_Element_2w_h0h7(d,a,b,1,1);
	compress_Element_2w_h0h7(d);
	printf("equal: %s\n",compare_Element_2w_h0h7(c,d)?"yes":"no");

#endif


#if 0 /* 1way ecc-operations  */
	Point_XY_1way G;
	Point_XYZ_1way pP,pQ;

	getGenerator(&G);
	printf("Gxy:\n");print_affine_1way(&G);
	toProjective(&pQ,&G);
	toProjective(&pP,&G);
	printf("Gxyz:\n");print_proj_1way(&pQ);
	_1way_doubling(&pQ);
	printf("2Gxyz:\n");print_proj_1way(&pQ);
	for(i=0;i<1000;i++)
		_1way_full_addition_law(&pP,&pQ);
	printf("3Gxyz:\n");print_proj_1way(&pP);

	/*for(i=0;i<1000;i++)
	_1way_doubling(&pQ);
	printf("2Gxyz:\n");print_proj_1way(&pQ);
	for(i=0;i<1000;i++)
	_1way_mix_addition_law(&pQ,&pP);
	printf("3Gxyz:\n");print_proj_1way(&pQ);
	*/
	/*negatePoint(&pP,&pQ);
	printf("-Gxyz:\n");print_proj_1way(&pP);
	getIdentityProj(&pP);
	printf("0:\n");print_proj_1way(&pP);*/



#endif

#if 0  /* testing w-naf */
	STR_BYTES a;
	ALIGN int8_t exp[392];
	int len;

	random_str_bytes(a);
	for(i=0;i<SIZE_STR_BYTES;i++)
	{
		exp[i] = 0;
	}
	print_str_bytes(a);
	len = wnaf(exp,a,8);
	printf("[");
	for(i=0;i<len;i++)
	{
		printf("%d, ",exp[i]);
	}
	printf("]\n");
#endif

#if 0  /* testing recoding */
	STR_BYTES a;
	ALIGN int8_t exp[392];
	int len;

	random_str_bytes(a);
	for(i=0;i<SIZE_STR_BYTES;i++)
	{
		exp[i] = 0;
	}
	print_str_bytes(a);
	len = recoding(exp,a,OMEGA_VAR_PMUL);
	printf("[");
	for(i=0;i<len;i++)
	{
		printf("%d, ",exp[i]);
		if (i%8==7)printf("\n");
	}
	printf("]\n");
#endif

#if 0 /* testing precompute */

	Point_XY_1way P;
	const int num_points = 1<<(OMEGA_DYNAMIC-2);
	Point_XYZ_1way Tab[num_points];

	getGenerator(&P);

	precompute_points(Tab,&P);
	for(i<0;i<num_points;i++)
	{
		printf("%d:\n",2*i+1);
		print_Element_2w_h0h7(Tab[i].XY);
		print_Element_2w_h0h7(Tab[i].ZZ);
	}
#endif

#if 0 /* reading point protected */

	Point_XY_1way P;
	Point_XYZ_1way Q, Tab[1<<(OMEGA_VAR_PMUL-2)];
	int num_points= 1<<(OMEGA_VAR_PMUL-2);

	getGenerator(&P);
	precompute_points(Tab,&P,OMEGA_VAR_PMUL);
//	for(i=0;i<num_points;i++)
//	{
//		printf("%dP\n",2*i+1);
//		print_Element_2w_h0h7(Tab[i].XY);
//		print_Element_2w_h0h7(Tab[i].ZZ);
//	}
	int index = 1;
	printf("%dP\n",index);
	read_point_protected(&Q,index,Tab);
	print_Element_2w_h0h7(Q.XY);
	print_Element_2w_h0h7(Q.ZZ);
	index = -1;
	printf("%dP\n",index);
	read_point_protected(&Q,index,Tab);
	print_Element_2w_h0h7(Q.XY);
	print_Element_2w_h0h7(Q.ZZ);
#endif

#if 0 /* testing variable point mult */

	/* openssl */
	EC_KEY * ec_key = EC_KEY_new_by_curve_name(NID_secp384r1);
	const EC_GROUP * ec_group = EC_KEY_get0_group(ec_key);
	BIGNUM * ec_order = BN_new();
	EC_GROUP_get_order(ec_group,ec_order,NULL);

	BIGNUM * OSSL_k = BN_new();
	BIGNUM * OSSL_Px = BN_new();
	BIGNUM * OSSL_Py = BN_new();
	EC_POINT * OSSL_Q  = EC_POINT_new(ec_group);
	EC_POINT * OSSL_P = EC_POINT_new(ec_group);

	/* library */
	Point_XY_1way P,Q;
	STR_BYTES k,px,py;
	Element_1w_H0H7 X,Y;
	int match;

	((uint64_t*)k)[5] = 0x70169fc9e76b21bd;
	((uint64_t*)k)[4] = 0x3f60854cd626f376;
	((uint64_t*)k)[3] = 0xe32805674d176412;
	((uint64_t*)k)[2] = 0x8103533112f70e8e;
	((uint64_t*)k)[1] = 0xfc7a280dd6f3cb31;
	((uint64_t*)k)[0] = 0x3080454203641340;

	((uint64_t*)px)[5] = 0xd37260b00ade94f1;
	((uint64_t*)px)[4] = 0xcbb29b2ca213a94e;
	((uint64_t*)px)[3] = 0x6e78fb9d2f872833;
	((uint64_t*)px)[2] = 0x8b3194c569b028e3;
	((uint64_t*)px)[1] = 0xe00704040aaa0bec;
	((uint64_t*)px)[0] = 0xcdb0863c93933a70;

	((uint64_t*)py)[5] = 0x68cc9be25e01858b;
	((uint64_t*)py)[4] = 0xd8bde3da73978867;
	((uint64_t*)py)[3] = 0xe95a40eb4108c527;
	((uint64_t*)py)[2] = 0x7ec24a05e7dbc46b;
	((uint64_t*)py)[1] = 0xc9c8a1fe1e215949;
	((uint64_t*)py)[0] = 0xa02dcbe96db4efb6;


	str_bytes_To_Element_1w_h0h7(X,px);
	str_bytes_To_Element_1w_h0h7(Y,py);
	interleave(P.XY,X,Y);

	str_bytes_to_BN(OSSL_k, k);
	str_bytes_to_BN(OSSL_Px, px);
	str_bytes_to_BN(OSSL_Py, py);
	EC_POINT_set_affine_coordinates_GFp(ec_group,OSSL_P,OSSL_Px,OSSL_Py,NULL);
	EC_POINT_mul(ec_group,OSSL_Q,NULL,OSSL_P,OSSL_k,NULL);

	printf("O k: \n");OSSL_print_int(OSSL_k);
	printf("O P: \n");OSSL_print_point(OSSL_P,ec_group);
	printf("O Q: \n");OSSL_print_point(OSSL_Q,ec_group);
	printf("%s\n",EC_POINT_is_on_curve(ec_group,OSSL_P,NULL)?"YES":"NO");
	printf("%s\n",EC_POINT_is_on_curve(ec_group,OSSL_Q,NULL)?"YES":"NO");

	variable_point_multiplication(&Q,k,&P);

	printf("k: \n");print_str_bytes(k);
	printf("P: \n");print_Element_2w_h0h7(P.XY);
	printf("Q: \n");print_Element_2w_h0h7(Q.XY);

	match = compare_point(ec_group,OSSL_Q,&Q);
	printf("equal %s\n",match?"YES":"NO");

	/*
	//for(i=0;i<1000;i++)
	{
//		BN_rand_range(k,ec_order);
		EC_POINT_mul(ec_group,OSSL_kG,k,NULL,NULL,NULL);
//		BN_rand_range(k,ec_order);
		EC_POINT_mul(ec_group,OSSL_Q,NULL,OSSL_kG,k,NULL);

//		to_littleEndian(str_k,k);
		to_point(&P,ec_group,OSSL_kG);
		variable_point_multiplication(&kG,str_k,&P);

		STR_BYTES buf;
		test = compare_point(ec_group,OSSL_Q,&kG);
		if(!test)
		{
			char* s = NULL;
			BN_to_str_bytes(buf,k);
			printf("\nTH_k : \n");print_str_bytes(str_k);
			printf("TH_P : \n");print_affine_1way(&P);
			printf("TH_kP: \n");print_affine_1way(&kG);
			printf("OP_k : \n");print_str_bytes(buf);
			printf("OP_P : \n");printf("%s\n",s=EC_POINT_point2hex(ec_group,OSSL_kG,POINT_CONVERSION_UNCOMPRESSED,NULL)); OPENSSL_free(s);
			printf("OP_kP: \n");printf("%s\n",s=EC_POINT_point2hex(ec_group,OSSL_Q,POINT_CONVERSION_UNCOMPRESSED,NULL));  OPENSSL_free(s);
//			break;
		}
	}*/

//
//	random_str_bytes(k);
//	random_str_bytes(k);
//	printf("k: \n");print_str_bytes(k);
//	variable_point_multiplication(&kP,k,&P);
//	printf("kP: \n");print_Element_2w_h0h7(kP.XY);

#endif
#if 1 /*test doubling bug */
	Point_XYZ_1way P;
	Element_1w_H0H7 X,Y,Z;
	X[0 ] = 0x007a7200;      Y[0 ] = 0x0d94c280;    Z[0 ] = 0x0ac9d800;
	X[2 ] = 0x018be208;      Y[2 ] = 0x0a81515c;    Z[2 ] = 0x02a44cf4;
	X[4 ] = 0x0fe7ed3a;      Y[4 ] = 0x071a0fcc;    Z[4 ] = 0x03416e5b;
	X[6 ] = 0x0f1a7afa;      Y[6 ] = 0x096c44fc;    Z[6 ] = 0x11b8a004;
	X[8 ] = 0x0b0d113c;      Y[8 ] = 0x05440ec6;    Z[8 ] = 0x056746a8;
	X[10] = 0x00e58361;      Y[10] = 0x09b8dcc3;    Z[10] = 0x0d3581d4;
	X[12] = 0x0d42f6af;      Y[12] = 0x0cb8ccc5;    Z[12] = 0x0093f928;
	X[1 ] = 0x0acc78ea;      Y[1 ] = 0x0558badd;    Z[1 ] = 0x0327e661;
	X[3 ] = 0x0f844863;      Y[3 ] = 0x010842b0;    Z[3 ] = 0x0b636b18;
	X[5 ] = 0x0b02b530;      Y[5 ] = 0x0eec19ba;    Z[5 ] = 0x0a454e83;
	X[7 ] = 0x0e81c072;      Y[7 ] = 0x0a96328f;    Z[7 ] = 0x052929c2;
	X[9 ] = 0x0d9b4102;      Y[9 ] = 0x036af6d8;    Z[9 ] = 0x018e02c4;
	X[11] = 0x07abd878;      Y[11] = 0x09a3144e;    Z[11] = 0x0d802e59;
	X[13] = 0x0f37f93d;      Y[13] = 0x0d1559aa;    Z[13] = 0x06b0b8e8;

	interleave(P.XY,X,Y);
	interleave(P.ZZ,Z,Z);

	print_Element_2w_h0h7(P.XY);
	print_Element_2w_h0h7(P.ZZ);

	_1way_doubling(&P);
	print_Element_2w_h0h7(P.XY);
	print_Element_2w_h0h7(P.ZZ);



#endif


#if 0 /* testing double_point mult */
	Point_XY_1way G, Q, k0G_k1Q;

	getGenerator(&G);
	getGenerator(&Q);
	STR_BYTES k0,k1;
	random_str_bytes(k0);
	random_str_bytes(k1);

	printf("k0: ");print_str_bytes(k0);
	printf("k1: ");print_str_bytes(k1);
	double_point_multiplication(&k0G_k1Q,k0,k1,&Q);
	print_Element_2w_h0h7(k0G_k1Q.XY);

#endif

#if 0 /* testing 2way full addition */
	Point_XYZ_2way P,Q;
	Point_XY_1way G,k0G,k1G,k2G,k3G;
	STR_BYTES k0,k1,k2,k3;
	Element_1w_H0H7 one,x0,y0,x1,y1,x2,y2,x3,y3;


	memset(one,0,sizeof(Element_1w_H0H7));
	one[0] = 1;
	getGenerator(&G);
	random_str_bytes(k0);
	random_str_bytes(k1);
	random_str_bytes(k2);
	random_str_bytes(k3);
	variable_point_multiplication(&k0G,k0,&G);
	variable_point_multiplication(&k1G,k1,&G);
	variable_point_multiplication(&k2G,k2,&G);
	variable_point_multiplication(&k3G,k3,&G);

	deinterleave(x0,y0,k0G.XY);
	deinterleave(x1,y1,k1G.XY);
	deinterleave(x2,y2,k2G.XY);
	deinterleave(x3,y3,k3G.XY);

	interleave(P.X,x0,x1);
	interleave(P.Y,y0,y1);
	interleave(P.Z,one,one);
	interleave(Q.X,x2,x3);
	interleave(Q.Y,y2,y3);
	interleave(Q.Z,one,one);

	printf("P.X:\n");print_Element_2w_h0h7(P.X);
	printf("P.Y:\n");print_Element_2w_h0h7(P.Y);
	printf("P.Z:\n");print_Element_2w_h0h7(P.Z);

	printf("Q.X:\n");print_Element_2w_h0h7(Q.X);
	printf("Q.Y:\n");print_Element_2w_h0h7(Q.Y);
	printf("Q.Z:\n");print_Element_2w_h0h7(Q.Z);
	for(i=0;i<100;i++)
		_2way_full_addition_law(&P,&Q);
	printf("P+Q.X:\n");print_Element_2w_h0h7(P.X);
	printf("P+Q.Y:\n");print_Element_2w_h0h7(P.Y);
	printf("P+Q.Z:\n");print_Element_2w_h0h7(P.Z);

#endif

#if 0  /* Query to table for fixed point multiplication */

	Point_XYZ_1way P;
	int index;
	i = 14;
	uint8_t *Table = (uint8_t *)TableSign_w4_36k+SIZE_ONE_LUT*i;

	index = -5;
	query_table(&P,Table,index);
	printf("P.XY:\n");
	print_Element_2w_h0h7(P.XY);
	print_Element_2w_h0h7(P.ZZ);

#endif

#if 0 /* Fixed point mult */
	Point_XY_1way kP;
	STR_BYTES k={
			0x11,0x8f,0x32,0x38,0x56,0x91,0xe8,0xb2,
			0x0c,0x9a,0x45,0x93,0x74,0x91,0x3c,0x53,
			0x73,0x4f,0x04,0x19,0xa1,0x4f,0x8e,0x8f,
			0xd0,0x67,0x6f,0x82,0xde,0xdd,0x6e,0x25,
			0x92,0x88,0x31,0x2f,0xae,0x9e,0x77,0x66,
			0xc7,0x94,0x02,0x66,0x93,0x80,0x46,0x0f
	};
	int8_t K[98],len;

	printf("k:\n");print_str_bytes(k);
	len = recoding_signed_scalar_w4(K,k);
	for(i=0;i<96;i++)
	{
		printf("%d, ",K[i]);
		if(i%24==23)printf(" \n");
	}
	if(len)
	printf("%d \n",K[i]);
	fixed_point_multiplication(&kP, k);
	printf("P.XY:\n");
	print_Element_2w_h0h7(kP.XY);

#endif
	return 0*i;

}
