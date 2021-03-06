
N = 384
num_words = 14
rho = 28
p = 2**N-2**128-2**96+2**32-1
Fp = GF(p)

Add = lambda X,Y : [x+y for x,y in zip(X,Y)]
Sub = lambda X,Y : [x-y for x,y in zip(X,Y)]
Dot = lambda X,Y : [x*y for x,y in zip(X,Y)]

# Using PolynomialRing
var1 = [c+str(p) for c in 'ab' for p in range(num_words)]
BB = PolynomialRing(ZZ,names=var1)
BB.inject_variables()

PP.<alpha> = PolynomialRing(BB)
R.<x> = PP.quotient_ring(alpha**384-alpha**128-alpha**96+alpha**32-1)
Avars = BB.gens()[:num_words]
Bvars = BB.gens()[num_words:]
A = [ a for i,a in enumerate(Avars) ]
B = [ b for i,b in enumerate(Bvars) ]

def integer_mult(A,B):
	C = [0]*num_words
	for i,a in enumerate(A):
		for j,b in enumerate(B):
			k = (i+j)%num_words
			C[k] += (a*x**int(ceil(rho*i)))*(b*x**int(ceil(rho*j)))
	return C
C = integer_mult(A,B)
Cp = sum(C)

def Pi384(X,i):
	if i==0:
		return X
	else:
		a13 = X[-1]
		return Add([0]+X[:-1],[x**8*a13, -x**12*a13, 0, x**20*a13,x**24*a13,0,0,0, 0,0,0, 0,0,0])
	
def Mul(A,B):
	C = [0]*num_words
	Y = A
	for i,b in enumerate(B):
		bV = [b]*num_words
		Y = Pi384(Y,i)
		C = Add(C,Dot(Y,bV))
	return C

Z = Mul(A,B)
Zp = sum([ z*x**int(ceil(rho*i)) for i,z in enumerate(Z) ])

print(Cp == Zp)


