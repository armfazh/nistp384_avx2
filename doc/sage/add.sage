load arith.sage
load("../python/trees.py")
Gx = Fp(0xaa87ca22be8b05378eb1c71ef320ad746e1d3b628ba79b9859f741e082542a385502f25dbf55296c3a545e3872760ab7)
Gy = Fp(0x3617de4a96262c6f5d9e98bf9292dc29f8f41dbd289a147ce9da3113b5f0b8c00a60b1ce1d7e819d7a431d7c90ea0e5f)
G = [ Gx,Gy ]
ecc_a = Fp(-3)
ecc_b = Fp(0xb3312fa7e23ee7e4988e056be3f82d19181d9c6efe8141120314088f5013875ac656398d8a2ed19d2a85c8edd3ec2aef)

E = EllipticCurve(Fp,[ecc_a,ecc_b])


def to_Jac(P):
	X = P[0]
	Y = P[1]
	Z = Fp(1)
	return [X,Y,Z]

def to_Proy(P):
	X = P[0]
	Y = P[1]
	Z = Fp(1)
	return [X,Y,Z]

def Jac_to_Affine(P):
	X = P[0]
	Y = P[1]
	Z = P[2]
	return [X/Z**2,Y/Z**3]

def Proy_to_Affine(P):
	X = P[0]
	Y = P[1]
	Z = P[2]
	return [X/Z,Y/Z]

#Returns Q+P
# [EFD] add-2001-b
# 2001 Bernstein http://cr.yp.to/nistp224.html opt-idea53.c ecadd.
def add_short(Q,P):
	X1,Y1,Z1 = Q
	X2,Y2,Z2 = P
	ZZ1 = Z1**2
	ZZZ1 = Z1*ZZ1
	ZZ2 = Z2**2
	ZZZ2 = Z2*ZZ2
	A = X1*ZZ2
	B = X2*ZZ1-A
	c = Y1*ZZZ2
	d = Y2*ZZZ1-c
	e = B**2
	f = B*e
	g = A*e
	h = Z1*Z2
	f2g = 2*g+f
	X3 = d**2-f2g
	Z3 = B*h
	gx = g-X3
	Y3 = d*gx-c*f
	return X3,Y3,Z3

#Returns 2P
# (EFD) dbl-2004-hmv
# 2004 Hankerson–Menezes–Vanstone, page 91.
def doub_short(P):
	X1,Y1,Z1 = P
	half = Fp(1)/Fp(2)
	T1 = Z1**2
	T2 = X1-T1
	T1 = X1+T1
	T2 = T2*T1
	T2 = 3*T2
	Y3 = 2*Y1
	Z3 = Y3*Z1
	Y3 = Y3**2
	T3 = Y3*X1
	Y3 = Y3**2
	Y3 = half*Y3
	X3 = T2**2
	T1 = 2*T3
	X3 = X3-T1
	T1 = T3-X3
	T1 = T1*T2
	Y3 = T1-Y3
	return [X3,Y3,Z3]
	
#Returns Q+P
#Alg, 4 Costello
# a=-3
def mixadd_complete(Q,P):
	global ecc_b
	X1,Y1,Z1 = Q
	X2,Y2 = P	
	t0 = X2*X1;		t1 = Y2*Y1;		t3 = X2+Y2;
	t4 = X1+Y1;		t3 = t3*t4;		t4 = t0+t1;
	t3 = t3-t4;		t4 = Y2*Z1;		t4 = t4+Y1;
	Y3 = X2*Z1;		Y3 = Y3+X1;		Z3 = ecc_b*Z1;
	X3 = Y3-Z3;		Z3 = 2*X3;		X3 = X3+Z3;
	Z3 = t1-X3;		X3 = t1+X3;		Y3 = ecc_b*Y3;
	t1 = 2*Z1;		t2 = t1+Z1;		Y3 = Y3-t2;
	Y3 = Y3-t0;		t1 = 2*Y3;		Y3 = t1+Y3;
	t1 = 2*t0;		t0 = t1+t0;		t0 = t0-t2;
	t1 = t4*Y3;		t2 = t0*Y3;		Y3 = X3*Z3;
	Y3 = Y3+t2;		X3 = t3*X3;		X3 = X3-t1;
	Z3 = t4*Z3;		t1 = t3*t0;		Z3 = Z3+t1;
	return X3,Y3,Z3
#Returns Q+P
#Alg, 4 Costello
# a=-3
def add_complete(Q,P):
	global ecc_b
	X1,Y1,Z1 = Q
	X2,Y2,Z2 = P
	t0 = X1*X2;		t1 = Y1*Y2;		t2 = Z1*Z2
	t3 = X1+Y1;		t4 = X2+Y2;		t3 = t3*t4
	t4 = t0+t1;		t3 = t3-t4;		t4 = Y1+Z1
	X3 = Y2+Z2;		t4 = t4*X3;		X3 = t1+t2
	t4 = t4-X3;		X3 = X1+Z1;		Y3 = X2+Z2
	X3 = X3*Y3;		Y3 = t0+t2;		Y3 = X3-Y3
	Z3 = ecc_b*t2;	X3 = Y3-Z3;		Z3 = 2*X3
	X3 = X3+Z3;		Z3 = t1-X3;		X3 = t1+X3
	Y3 = ecc_b*Y3;	t1 = 2*t2;		t2 = t1+t2
	Y3 = Y3-t2;		Y3 = Y3-t0;		t1 = 2*Y3
	Y3 = t1+Y3;		t1 = 2*t0;		t0 = t1+t0
	t0 = t0-t2;		t1 = t4*Y3;		t2 = t0*Y3
	Y3 = X3*Z3;		Y3 = Y3+t2;		X3 = t3*X3
	X3 = X3-t1;		Z3 = t4*Z3;		t1 = t3*t0
	Z3 = Z3+t1;
	return X3,Y3,Z3
	
#Returns 2P
#Alg, 6 Costello
# a=-3
def doub_complete(P):
	global ecc_b
	X,Y,Z = P
	t0 = X**2;			t1 = Y**2;			t2 = Z**2
	t3 = X*Y;			t3 = 2*t3;			Z3 = X*Z
	Z3 = 2*Z3;			Y3 = ecc_b*t2;		Y3 = Y3-Z3
	X3 = 2*Y3;			Y3 = X3+Y3;			X3 = t1-Y3
	Y3 = t1+Y3;			Y3 = X3*Y3;			X3 = X3*t3
	t3 = 2*t2;			t2 = t2+t3;			Z3 = ecc_b*Z3
	Z3 = Z3-t2;			Z3 = Z3-t0;			t3 = 2*Z3
	Z3 = Z3+t3;			t3 = 2*t0;			t0 = t3+t0
	t0 = t0-t2;			t0 = t0*Z3;			Y3 = Y3+t0
	t0 = Y*Z;			t0 = 2*t0;			Z3 = t0*Z3
	X3 = X3-Z3;			Z3 = t0*t1;			Z3 = 2*Z3
	Z3 = 2*Z3
	return [X3,Y3,Z3]


def test_ecc():
	J = to_Jac(G)
	P = to_Proy(G)

	_2J = doub_short(J)
	_2P = doub_complete(P)

	print(Jac_to_Affine(_2J)==Proy_to_Affine(_2P))

	_3J = add_short(_2J,J)
	_3P = add_complete(_2P,P)

	print(Jac_to_Affine(_3J)==Proy_to_Affine(_3P))

	_iJ = _2J
	_iP = _2P
	_kP = _2P
	for i in range(1000):
		_iJ = add_short(_iJ,J)
		_iP = add_complete(_iP,P)
		_kP = mixadd_complete(_kP,[Gx,Gy])

	print(Jac_to_Affine(_iJ)==Proy_to_Affine(_iP))
	print(Jac_to_Affine(_iJ)==Proy_to_Affine(_kP))
	return True

def test_ecc():
	pass

##################
# Main

print("Testing: add.sage")
print("ecc: {0}".format(test_ecc()))




	
