
N = 384
num_words = 14
rho = 27.5
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
#R.<x> = PP.quotient_ring(alpha**255-19)
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

def Pi19(X,i):
	if i==0:
		return X
	else:
		a9 = X[-1]
		return [ x**19*a9 ]+X[:-1]

def Pi384(X,i):
	if i==0:
		return X
	elif i%2==0:
		a13 = X[-1]
		return Add([0]+X[:-1],[x*a13, -x**5*a13, 0, x**14*a13,x**19*a13,0,0,0, 0,0,0, 0,0,0])
	else:
		a13 = X[-1]
		return Add([0]+X[:-1],[x*a13, -x**6*a13, 0, x**15*a13,x**19*a13,0,0,0, 0,0,0, 0,0,0])
	
def Mul(A,B):
	C = [0]*num_words
	Y = A
	for i,b in enumerate(B):
		if i%2==0:
			bV = [b]*num_words
		else:
			bV = [x*b, b]*(num_words>>1)
		Y = Pi384(Y,i)
		C = Add(C,Dot(Y,bV))
	return C

Z = Mul(A,B)
Zp = sum([ z*x**int(ceil(rho*i)) for i,z in enumerate(Z) ])

print(Cp == Zp)


