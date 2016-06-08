
from sympy import cse, symbols, numbered_symbols
from sympy.simplify.cse_main import opt_cse, tree_cse

ecc_b = symbols("ecc_b")

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


X1,Y1,Z1,X2,Y2 = symbols('X1 Y1 Z1 X2 Y2')
Q = [X1,Y1,Z1]
P = [X2,Y2]
Rx,Ry,Rz = mixadd_complete(Q,P)
tree = tree_cse([Rx,Ry,Rz], numbered_symbols('e'))
print(tree)
