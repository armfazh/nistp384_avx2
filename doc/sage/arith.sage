
N = 384
num_words = 14
rho = 27.5
p = 2**N-2**128-2**96+2**32-1
Fp = GF(p)

toVect = lambda a : [ (a>>int(math.ceil(rho*i)))%(2**int(math.ceil(rho-(i%2)))) for i in range(num_words) ]
fromVect = lambda V: sum([v*2**int(math.ceil(rho*i)) for i,v in enumerate(V)])%p

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
A = toVect(a)
B = toVect(b)
C = Muli(A,B)
print( fromVect(C) == (a*b%p) )


