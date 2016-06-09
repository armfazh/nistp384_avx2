
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
    p1 = Z**2;		q1 = X*Y;
    p2 = Y*Z;		q2 = X*Z;
    
    l0 = 3*p0;
    l1 = 3*p1;		r0 = 2*q1;
    t1 = l0-l1;
    l2 = 2*p2;		r2 = 2*q2;

    p3 = ecc_b*p1;	q3 = ecc_b*r2;
    l3 = p3-r2;		r6 = q3-l1;
    l4 = 3*l3;		r7 = r6-p0;
    l5 = q0-l4;		r3 = 3*r7;
    l6 = q0+l4;		
    
    r4 = l2*r3;		l7 = l5*l6;
    t8 = l5*r0;		t2 = t1*r3;
    r5 = l2*q0;
    X3 = t8-r4;		Y3 = l7+t2;    
    Z3 = 4*r5;
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
    t0 =  3*p0;		u0 =  3*Z1;
    t7 = X2+Y2;		u1 = q0+Y1;
    t8 = X1+Y1;		u7 = q1+X1;
    p2 = ecc_b*Z1;	q2 = ecc_b*u7;
    t9 = u7-p2;		u8 = q2-p0;
    pp = t7*t8;
    t6 = p0+p1;
    t3 = pp-t6;		u9 = u8-u0
    t9 =  3*t9;		u2 =  3*u9;
    t1 = p1+t9;
    t2 = p1-t9;		u3 = t0-u0;
    p3 = t1*t2;		q3 = u2*u3;
    p4 = t1*t3;		q4 = u2*u1;
    p5 = u1*t2;		q5 = t3*u3;
    X3 = p4-q4;
    Y3 = p3+q3;
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
# parallel_mixadd()
parallel_doub()


