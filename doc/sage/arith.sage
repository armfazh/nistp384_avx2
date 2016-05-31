import math

N = 255
num_words = 10
rho = N/num_words
p = 2**N-19
#p = 2**384-2**128-2**96+2**32-1
Fp = GF(p)

#toVect = lambda a : [ (a>>int(math.ceil(rho*i)))%(2**int(math.ceil(rho-(i%2)))) for i in range(num_words) ]
#fromVect = lambda V: sum([v*2**int(math.ceil(rho*i)) for i,v in enumerate(V)])%p

Add = lambda X,Y : [x+y for x,y in zip(X,Y)]
Sub = lambda X,Y : [x-y for x,y in zip(X,Y)]
Dot = lambda X,Y : [x*y for x,y in zip(X,Y)]

toVect = lambda a : [ (a>>int(math.ceil(25.5*i)))%(2**int(math.ceil(25.5-(i%2)))) for i in range(10) ]
fromVect = lambda V: sum([v*2**int(math.ceil(25.5*i)) for i,v in enumerate(V)])%p

Hex = lambda V: map(hex,V)

mul_19= lambda i,j:19 if i+j>=10 else 1
mul_2 = lambda i,j: 2 if (i%2==1 and j%2==1) else 1
line =lambda i: [ A[i]*B[t]*mul_19(i,t)*mul_2(i,t) for t in [ (-i+j)%10 for j in range(10)] ]
size = lambda x:  floor(log(abs(x),2))+1
sizes = lambda V: map(size,V) 

def integer_mult(A,B):
	c = [0]*len(A)
	for i,a in enumerate(A):
		for j,b in enumerate(B):
			c[(i+j)%10] += a*b*mul_19(i,j)*mul_2(i,j)
	return c


def Pi(X):
	return [19*X[-1]] + X[:-1]

def Mul(X,Y):
	Z = [0]*num_words
	for x in X:
		Z = Add(Z,Dot(Y,[x]*num_words))
		Y = Pi(Y)
	return Z




