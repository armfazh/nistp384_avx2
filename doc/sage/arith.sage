
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

