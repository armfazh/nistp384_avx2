
from sympy import cse, symbols, numbered_symbols
from sympy.simplify.cse_main import opt_cse, tree_cse

ecc_b = symbols("ecc_b")

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

def doub_complete_2w(P):
    global ecc_b
    X,Y,Z = P
    p0 = X**2;		q0 = Y**2;
    p1 = X*Y;		q1 = Y*Z;
    p2 = 2*X*Z;		q2 = Z**2;
    p3 = ecc_b*p2;	q3 = ecc_b*q2;
    
    l0 = 3*p0;		r0 = 1*q0
    l1 = p3-p0;		r1 = q3-p2;
    l2 = 3*q2;		r2 = 3*r1;
    l3 = l0-l2;		r3 = r0+r2;
    l4 = l1-l2;		r4 = r0-r2;
    l5 = 3*l4;		r5 = 1*r4;
    
    p4 = l3*l5;		q4 = r3*r5;
    p5 = p1*r5;		q5 = q1*l5;
    1==1;			q6 = q1*r0;
    
    X3 = 2*(p5-q5);	Y3 = p4+q4;    
    Z3 = 8*q6;
    return [X3,Y3,Z3]



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

def mixadd_complete_2w(Q,P):
    global ecc_b
    X1,Y1,Z1 = Q
    X2,Y2 = P

    p0 = X1*X2;		q0 = Z1*Y2;
    p1 = Y1*Y2;		q1 = Z1*X2;
    
    l0 =  3*p0;		r0 =  3*Z1;
    l1 = X2+Y2;		r1 = q0+Y1;
    l2 = X1+Y1;		r2 = q1+X1;
    p2 = ecc_b*Z1;	q2 = ecc_b*r2;
    l3 = r2-p2;		r3 = q2-p0;
    pp = l1*l2;		1==1;
    l4 = p0+p1;
    l5 = pp-l4;		r4 = r3-r0
    l6 =  3*l3;		r5 =  3*r4;
    l7 = p1+l6;		r5 = r5+0;
    l8 = p1-l6;		r6 = l0-r0;
    
    p3 = l7*l8;		q3 = r5*r6;
    p4 = l7*l5;		q4 = r5*r1;
    p5 = r1*l8;		q5 = l5*r6;
    
    X3 = p4-q4;		Y3 = p3+q3;
    Z3 = p5+q5;
    return X3,Y3,Z3


def com_sub_elim():
    X1,Y1,Z1,X2,Y2 = symbols('X1 Y1 Z1 X2 Y2')
    Q = [X1,Y1,Z1]
    P = [X2,Y2]
    Rx,Ry,Rz = mixadd_complete(Q,P)
    tree = tree_cse([Rx,Ry,Rz], numbered_symbols('e'))
    print(tree)

def parallel_mixadd():
    X1,Y1,Z1,X2,Y2 = symbols('X1 Y1 Z1 X2 Y2')
    Q = [X1,Y1,Z1]
    P = [X2,Y2]
    R0 = mixadd_complete(Q,P)
    R1 = mixadd_complete_2w(Q,P)
    print(R0==R1)

def parallel_doub():
    X1,Y1,Z1 = symbols('X1 Y1 Z1')
    Q = [X1,Y1,Z1]
    R0 = doub_complete(Q)
    R1 = doub_complete_2w(Q)
    print(R0==R1)

#com_sub_elim()
parallel_mixadd()
parallel_doub()


