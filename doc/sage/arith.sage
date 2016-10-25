
N = 384
num_words = 14
rho = 28
p = 2**N-2**128-2**96+2**32-1
Fp = GF(p)

powers = [ int(ceil(rho*i)) for i in range(num_words) ]
bits   = [ int(ceil(rho*(i+1))-ceil(rho*i)) for i in range(num_words) ]
toVect = lambda a : [ (a>>pow)%2**b for pow,b in zip(powers,bits) ]
fromVect = lambda V: sum([v*2**pow for pow,v in zip(powers,V)])%p

Add = lambda X,Y : [x+y for x,y in zip(X,Y)] if len(X)==len(Y) else []
Sub = lambda X,Y : [x-y for x,y in zip(X,Y)] if len(X)==len(Y) else []
Dot = lambda X,Y : [x*y for x,y in zip(X,Y)] if len(X)==len(Y) else []

Hex = lambda V: map(hex,V)

size = lambda x:  floor(log(abs(x),2))+1 if x!=0 else 0
sizes = lambda V: map(size,V) 

def Pi384_bis(X,i):
    if i==0:
        return X
    else:
        a13 = X[-1]
        Y = [0] + X[:-1]
        Y[0] += (a13 % 2**20)<<8
        Y[1] += (a13>>20)
        Y[1] -= (a13 % 2**16)<<12
        Y[2] -= (a13>>16)
        Y[3] += (a13 % 2**8)<<20
        Y[4] += (a13>>8)
        Y[4] += (a13 % 2**4)<<24
        Y[5] += (a13>>4)
        return Y

def Pi384i(X,i):
    if i==0:
        return X
    else:
        a13 = X[-1]
        return Add([0]+X[:-1],[2**8*a13, -2**12*a13, 0, 2**20*a13, 2**24*a13, 0,0,0, 0,0,0, 0,0,0])

def Muli(A,B):
	C = [0]*num_words
	Y = A
	for i,b in enumerate(B):
		bV = [b]*num_words
		Y = Pi384_bis(Y,i)
		C = Add(C,Dot(Y,bV))
	return C

def test_arith():
	a = randrange(p)
	b = randrange(p)
	a = 0xd45ee95817055d255aa35831b70d32669ac99f33632e5a768de7e81bf854c27c46e3fbf2abbacd29ec4aff517369c667
	b = 0x5cdb18ec543caf32fb3bb0ec2a5c388f966bdcea977e013e67fce141a13ee97087dc3d214174820e1154b49bc6cdb2ab
	c = (a*b)%p
	A = toVect(a)
	B = toVect(b)
	C = Muli(A,B)
	return (c == fromVect(C))

print("Testing: arith.sage")
print("arith: {0}".format(test_arith()))

def integer_mult(A,B):
	C = [0]*(len(A)+len(B)-1)
	for i,a in enumerate(A):
		for j,b in enumerate(B):
			C[i+j] += a*b
	return C

def modular_red(D,i,j):
	C = deepcopy(D)
	X = C[i]

	C[i-14+0] = C[i-14+0] + ((X%2**48)<<8)
	C[i-14+2] = C[i-14+2] + (X>>48)

	C[i-14+1] = C[i-14+1] - ((X%2**44)<<12)
	C[i-14+3] = C[i-14+3] - (X>>44)

	C[i-14+3] = C[i-14+3] + ((X%2**36)<<20)
	C[i-14+5] = C[i-14+5] + (X>>36)

	C[i-14+4] = C[i-14+4] + ((X%2**32)<<24)
	C[i-14+6] = C[i-14+6] + (X>>32)
	
	Y = C[j]

	C[j-14+0] = C[j-14+0] + ((Y%2**48)<<8)
	C[j-14+2] = C[j-14+2] + (Y>>48)

	C[j-14+1] = C[j-14+1] - ((Y%2**44)<<12)
	C[j-14+3] = C[j-14+3] - (Y>>44)

	C[j-14+3] = C[j-14+3] + ((Y%2**36)<<20)
	C[j-14+5] = C[j-14+5] + (Y>>36)

	C[j-14+4] = C[j-14+4] + ((Y%2**32)<<24)
	C[j-14+6] = C[j-14+6] + (Y>>32)

	k = i if i>j else j
	return C[:k]

def reduce_p384(C):
	C = modular_red(C,27,20)
	C = modular_red(C,26,19)
	C = modular_red(C,25,18)
	C = modular_red(C,24,17)
	C = modular_red(C,23,16)
	C = modular_red(C,22,15)
	C = modular_red(C,21,14)
	return C[:num_words]

a0 = 0xd45ee95817055d255aa35831b70d32669ac99f33632e5a768de7e81bf854c27c46e3fbf2abbacd29ec4aff517369c667
a1 = 0x5cdb18ec543caf32fb3bb0ec2a5c388f966bdcea977e013e67fce141a13ee97087dc3d214174820e1154b49bc6cdb2ab
b0 = 0xbd644748d0cb0bcae53aa1e900f7ef05b3f1ebb1950f99a8bb5cf98961bed875947c3c05e6d129fb3aaafafb43fe1a02
b1 = 0xf57d9bba19226fbb5c15474850e3cd333baf101bf2acd4aadc099e112464703b63794b5ec55a7314c5647b1ca81e231f
c0 = a0*b0%p
c1 = a1*b1%p

A0 = toVect(a0)
A1 = toVect(a1)
B0 = toVect(b0)
B1 = toVect(b1)
C0 = integer_mult(A0,B0)+[0]
C1 = integer_mult(A1,B1)+[0]
D0 = reduce_p384(C0)
D1 = reduce_p384(C1)
print(c0 == fromVect(D0))
print(c1 == fromVect(D1))

