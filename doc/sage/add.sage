load arith.sage
load("../python/trees.py")
Gx = Fp(0xaa87ca22be8b05378eb1c71ef320ad746e1d3b628ba79b9859f741e082542a385502f25dbf55296c3a545e3872760ab7)
Gy = Fp(0x3617de4a96262c6f5d9e98bf9292dc29f8f41dbd289a147ce9da3113b5f0b8c00a60b1ce1d7e819d7a431d7c90ea0e5f)
G = [ Gx,Gy ]
ecc_a = Fp(-3)
ecc_b = Fp(0xb3312fa7e23ee7e4988e056be3f82d19181d9c6efe8141120314088f5013875ac656398d8a2ed19d2a85c8edd3ec2aef)

E = EllipticCurve(Fp,[ecc_a,ecc_b])
ecc_order = 39402006196394479212279040100143613805079739270465446667946905279627659399113263569398956308152294913554433653942643

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
	Z = P[2]
	if Z==0:
		return [ Fp(0),Fp(1),Fp(0)]
	else:
		X = P[0]
		Y = P[1]
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
# 2004 Hankerson-Menezes-Vanstone, page 91.
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

def create_table(P,OMEGA):
	num_points = (2**(OMEGA-2))
	T = [0]*num_points
	_2P = doub_complete_2w(P)
	T[0] = P
	for i in range(1,num_points):
		T[i] = fulladd_complete_2w(T[i-1],_2P)
	return T

def recoding(k,w):
	t = int(ceil(log(k,2)/(w-1)))
	E = []
	for i in range(t):
		digit = (k%2**w)-2**(w-1)
		k = (k-digit)>>(w-1)
		E += [ digit ]
	E += [ k ]
	return E

def variable_pmul(k,w,P):
    L = recoding(k,w)
    Tab = create_table(P,w)
    d = L[-1]
    Q = deepcopy(Tab[abs(d)>>1])
    if d < 0:
        Q[1] = -Q[1]
    for i in reversed(range(len(L)-1)):
        d = L[i]
        print(i,d)
        print([hex(int(x)) for x in Q])
        for j in range(w-1):
            Q = doub_complete_2w(Q)
        R = deepcopy(Tab[abs(d)>>1])
        if d < 0:
			R[1] = -R[1]
        Q = fulladd_complete_2w(Q,R)
    print(Q)
    return Q

def wnaf(k,w):
	E = []
	mods = lambda d,w :d if d<2**(w-1) else d-2**(w)
	while(k>0):
		if k%2 == 1:
			digit = mods(k%2**w,w)
			k -= digit
			E += [ digit ]
		else:
			E += [0]
		k>>=1;
	return E

def double_pmul(k0,w0,P,k1,w1,TabSta):
	K0 = wnaf(k0,w0)
	K1 = wnaf(k1,w1)
	K0 += [0]*(len(K1)-len(K0))
	K1 += [0]*(len(K0)-len(K1))
	Q = [Fp(0),Fp(1),Fp(0)]
	TabDyn = create_table(P,w1)
	for d0,d1 in reversed(zip(K0,K1)):
		Q = doub_complete_2w(Q)
		if d0 != 0:
			R = deepcopy(TabDyn[abs(d0)>>1])
			if d0 < 0:
				R[1] = -R[1]
			Q = fulladd_complete_2w(Q,R)
		if d1 != 0:
			R = deepcopy(TabSta[abs(d1)>>1])
			if d1 < 0:
				R[1] = -R[1]
			Q = fulladd_complete_2w(Q,R)
	return Q

def inv(a):
	c = deepcopy(a)
	for i in reversed(range(383)):
		c = (c**2)#%p
		if i==128 or i==1 or (32<=i<96):
			continue
		else:
			c = (c*a)#%p
	return c

def testing_fixed_pmul():
	pass
	
def testing_variable_pmul():
	global ecc_order,Gx,Gy,E
	OMEGA_FIXED_VAR = 6
	k = randrange(ecc_order)
	G = E([ Gx,Gy,Fp(1) ])
	projQ = variable_pmul(k,OMEGA_FIXED_VAR,list(G))
	Q = Proy_to_Affine(projQ)
	R = k*G
	print(R[0]==Q[0] and R[1]==Q[1])


def testing_double_pmul():
	global ecc_order,Gx,Gy
	OMEGA_DYN = 4
	OMEGA_STA = 4
	k0 = randrange(ecc_order)
	k1 = randrange(ecc_order)
	G = E([ Gx,Gy,Fp(1) ])
	P = G#E.random_point()
	TabSta = create_table([Gx,Gy,Fp(1)],OMEGA_STA)
	projQ = double_pmul(k0,OMEGA_STA,list(P),k1,OMEGA_DYN,TabSta)
	Q = Proy_to_Affine(projQ)

	R = k0*P+k1*G
	return R[0]==Q[0] and R[1]==Q[1]

def toWords(num,word_size):
	S = []
	if num==0: return [0]
	while num>0:
		S += [ num%2**word_size ]
		num >>= word_size
	return S

def toC(num,word_size):
	return ",".join([ "0x{num:0{width}x}".format(num=n,width=word_size>>2) for n in toWords(num,word_size) ])

def toC_interleaved(numA,numB,word_size):
	wA = toWords(numA,word_size)
	wB = toWords(numB,word_size)
	return ",".join([ "0x{num:0{width}x}".format(num=nn,width=word_size>>2) for n in zip(wA,wB) for nn in n ])

def print_tableSta():
	G = E([Gx,Gy,Fp(1)])
	OMEGA_STA = 7
	for i in range(1<<(OMEGA_STA-2)):
		P = (2*i+1)*G
		print("/* {0}*G */".format(2*i+1))
		#print("{0},".format(toC_interleaved(int(P[0]),int(P[1]),64)))
		print("{0},".format(toC(int(P[0]),64)))
		print("{0},".format(toC(int(P[1]),64)))


##################
# Main

print("Testing: add.sage")
#print("ecc: {0}".format(test_ecc()))
#print("double_pmul: {0}".format(testing_double_pmul()))
#print("double_pmul: {0}".format(testing_variable_pmul()))


X1 = Fp(0x5a90d91c792a0df5b3119d33b04f3b78ffc4801ab6f69f28bdb9ac13575d4ed3bbb3581c37cb66b262033ad05503945f)
Y1 = Fp(0x39675b92f4ca941ee06a89d984138876d1705825f0e6b46db7a4bd2803bca0d507876cef7fb9da703a168644b8d43d6e)
Z1 = Fp(1)
X2 = Fp(0x8a313cae9260184b2517d821c1e6a08b81d4ff1fe2c57f1975eec03a2e90cf0ae0313adba1d1e428338ba0aefce01b63)
Y2 = Fp(0x7f4c2891af8d24b72a2ca836855e3156194f97e444f3d095280643487940c337dde36fff77f79bfa485c79974c869d16)
Z2 = Fp(1)

P = [X1,Y1,Z1]
Q = [X2,Y2,Z2]
for i in range(100):
	P = fulladd_complete_2w(P,Q)
for i in P:
	print(hex(int(i)))
