
N = 384
num_words = 14
rho = 27.5
p = 2**N-2**128-2**96+2**32-1
Fp = GF(p)

powers = [ int(ceil(rho*i)) for i in range(num_words) ]
bits   = [ int(ceil(rho*(i+1))-ceil(rho*i)) for i in range(num_words) ]
toVect = lambda a : [ (a>>pow)%2**b for pow,b in zip(powers,bits) ]
fromVect = lambda V: sum([v*2**pow for pow,v in zip(powers,V)])%p

Add = lambda X,Y : [x+y for x,y in zip(X,Y)]
Sub = lambda X,Y : [x-y for x,y in zip(X,Y)]
Dot = lambda X,Y : [x*y for x,y in zip(X,Y)]

Hex = lambda V: map(hex,V)

size = lambda x:  floor(log(abs(x),2))+1 if x!=0 else 0
sizes = lambda V: map(size,V) 


def Pi384i(X,i):
	if i==0:
		return X
	elif i%2==0:
		a13 = X[-1]
		return Add([0]+X[:-1],[2*a13, -2**5*a13, 0, 2**14*a13,2**19*a13,0,0,0, 0,0,0, 0,0,0])
	else:
		a13 = X[-1]
		return Add([0]+X[:-1],[2*a13, -2**6*a13, 0, 2**15*a13,2**19*a13,0,0,0, 0,0,0, 0,0,0])

def Pi384_bis(X,i):
    if i==0:
        return X
    elif i%2==0:
        a13 = X[-1]
        Y = [0] + X[:-1]
        Y[0] += 2*a13
        Y[1] -= (a13 % 2**22)<<5
        Y[2] -= (a13>>22)
        Y[3] += (a13 % 2**13)<<14
        Y[4] += (a13>>13)
        Y[4] += (a13 % 2**9)<<19
        Y[5] += (a13>>9)
        return Y
    else:
        a13 = X[-1]
        Y = [0] + X[:-1]
        Y[0] += 2*a13
        Y[1] -= (a13 % 2**21)<<6
        Y[2] -= (a13>>21)
        Y[3] += (a13 % 2**12)<<15
        Y[4] += (a13>>12)
        Y[4] += (a13 % 2**9)<<19
        Y[5] += (a13>>9)
        return Y

def Muli(A,B):
	C = [0]*num_words
	Y = A
	for i,b in enumerate(B):
		if i%2==0:
			bV = [b]*num_words
		else:
			bV = [2*b, b]*(num_words>>1)
		Y = Pi384i(Y,i)
		C = Add(C,Dot(Y,bV))
	return C

a = randrange(p)
b = randrange(p)
a = 0xd45ee95817055d255aa35831b70d32669ac99f33632e5a768de7e81bf854c27c46e3fbf2abbacd29ec4aff517369c667
b = 0x5cdb18ec543caf32fb3bb0ec2a5c388f966bdcea977e013e67fce141a13ee97087dc3d214174820e1154b49bc6cdb2ab
A = toVect(a)
B = toVect(b)
C = Muli(A,B)
print(fromVect(C) == (a*b%p))




