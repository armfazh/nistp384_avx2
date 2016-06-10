
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

def doub_complete_2w(P):
    global ecc_b
    X,Y,Z = P
    p0 = X**2;      q0 = Y**2;
    p1 = X*Y;       q1 = Y*Z;
    p2 = 2*X*Z;     q2 = Z**2;
    p3 = ecc_b*p2;  q3 = ecc_b*q2;
    
    l0 = p3-p0;     r0 = q3-p2;
    l1 = 3*p0;      r1 = 1*q0
    l2 = 3*q2;      r2 = 3*r0;
    l3 = l1-l2;     r3 = r1+r2;
    l4 = l0-l2;     r4 = r1-r2;
    l5 = 3*l4;      r5 = 1*r4;
    
    p4 = l3*l5;     q4 = r3*r5;
    p5 = p1*r5;     q5 = q1*l5;
    1==1;           q6 = q1*r1;
    
    X3 = 2*(p5-q5); Y3 = p4+q4;    
    Z3 = 8*q6;
    return [X3,Y3,Z3]

def mixadd_complete_2w(Q,P):
    global ecc_b
    X1,Y1,Z1 = Q
    X2,Y2 = P

    p0 = X1*X2;     q0 = Z1*Y2;
    p1 = Y1*Y2;     q1 = Z1*X2;
    
    l0 =  3*p0;     r0 =  3*Z1;
    l1 = X2+Y2;     r1 = q0+Y1;
    l2 = X1+Y1;     r2 = q1+X1;
    p2 = ecc_b*Z1;  q2 = ecc_b*r2;
    l3 = r2-p2;     r3 = q2-p0;
    p3 = l1*l2;     
    l4 = p0+p1;
    l5 = p3-l4;     r5 = r3-r0
    l6 =  3*l3;     r6 =  3*r5;
    l7 = p1+l6;     r7 = r6;
    l8 = p1-l6;     r8 = l0-r0;
    
    p4 = l7*l8;     q4 = r7*r8;
    p5 = l7*l5;     q5 = r7*r1;
    p6 = r1*l8;     q6 = l5*r8;
    
    X3 = p5-q5;     Y3 = p4+q4;
    Z3 = p6+q6;
    return X3,Y3,Z3

def fulladd_complete(Q,P):
    global ecc_b
    X1,Y1,Z1 = Q
    X2,Y2,Z2 = P
    t0 = X1 * X2;     t1 = Y1 * Y2;     t2 = Z1 * Z2;
    t3 = X1 + Y1;     t4 = X2 + Y2;     t3 = t3 * t4;
    t4 = t0 + t1;     t3 = t3 - t4;     t4 = Y1 + Z1;
    X3 = Y2 + Z2;     t4 = t4 * X3;     X3 = t1 + t2;
    t4 = t4 - X3;     X3 = X1 + Z1;     Y3 = X2 + Z2;
    X3 = X3 * Y3;     Y3 = t0 + t2;     Y3 = X3 - Y3;
    Z3 = ecc_b*t2;    X3 = Y3 - Z3;     Z3 = X3 + X3;
    X3 = X3 + Z3;     Z3 = t1 - X3;     X3 = t1 + X3;
    Y3 = ecc_b*Y3;    t1 = t2 + t2;     t2 = t1 + t2;
    Y3 = Y3 - t2;     Y3 = Y3 - t0;     t1 = Y3 + Y3;
    Y3 = t1 + Y3;     t1 = t0 + t0;     t0 = t1 + t0;
    t0 = t0 - t2;     t1 = t4 * Y3;     t2 = t0 * Y3;
    Y3 = X3 * Z3;     Y3 = Y3 + t2;     X3 = t3 * X3;
    X3 = X3 - t1;     Z3 = t4 * Z3;     t1 = t3 * t0;
    Z3 = Z3 + t1;
    return X3,Y3,Z3


def fulladd_complete_2w(Q,P):
    global ecc_b
    X1,Y1,Z1 = Q
    X2,Y2,Z2 = P
    l1 = X1 + Y1;     r1 = X1 + Z1;   
    l2 = X2 + Y2;     r2 = X2 + Z2;   
    
    p0 = X1 * X2;     q0 = Y1 * Y2;
    p1 = l1 * l2;     q1 = r1 * r2;
    
    1==1;             m1 = Y1 + Z1;  
    1==1;             m2 = Y2 + Z2;
    p2 = Z1 * Z2;     q2 = m1 * m2;
    
    l0 = 3*p0;        r0 = 3*p2;        
    l3 = p0 + p2;     
    l4 = q1 - l3;     

    p3 = ecc_b*l4;    q3 = ecc_b*p2;    
    l5 = p3 - p0;     r5 = l4 - q3;     
    l6 = l5 - r0;     r6 = r5;          

    l7 = 3*l6;        r7 = 3*r6;                
    l8 = l0 - r0;     r8 = q0 - r7;     
    1==1;             l9 = q0 + r7;   
    lA = p0 + q0;     rA = q0 + p2;
    lB = p1 - lA;     rB = q2 - rA;
    
    p4 = lB * l9;     q4 = rB * l7;    
    p5 = l9 * r8;     q5 = l7 * l8;
    p6 = lB * l8;     q6 = rB * r8;
    
    X3 = p4 - q4;     Y3 = p5 + q5;
    Z3 = p6 + q6;
    return X3,Y3,Z3





def com_sub_elim():
    X1,Y1,Z1,X2,Y2 = symbols('X1 Y1 Z1 X2 Y2')
    Q = [X1,Y1,Z1]
    P = [X2,Y2]
    Rx,Ry,Rz = mixadd_complete(Q,P)
    tree = tree_cse([Rx,Ry,Rz], numbered_symbols('e'))
    print(tree)

def parallel_fulladd():
    X1,Y1,Z1,X2,Y2,Z2 = symbols('X1 Y1 Z1 X2 Y2 Z2')
    Q = [X1,Y1,Z1]
    P = [X2,Y2,Z2]
    R0 = fulladd_complete(Q,P)
    R1 = fulladd_complete_2w(Q,P)
    return (R0==R1)

def parallel_mixadd():
    X1,Y1,Z1,X2,Y2 = symbols('X1 Y1 Z1 X2 Y2')
    Q = [X1,Y1,Z1]
    P = [X2,Y2]
    R0 = mixadd_complete(Q,P)
    R1 = mixadd_complete_2w(Q,P)
    return (R0==R1)

def parallel_doub():
    X1,Y1,Z1 = symbols('X1 Y1 Z1')
    Q = [X1,Y1,Z1]
    R0 = doub_complete(Q)
    R1 = doub_complete_2w(Q)
    return (R0==R1)

print("Testing: trees.py")
# com_sub_elim()
print("fulladd: {0}".format(parallel_fulladd()))
# print("mixadd:  {0}".format(parallel_mixadd()))
# print("doub:    {0}".format(parallel_doub()))


