#!/usr/bin/python3.5

from gmpy2 import mpz
import fractions

# mano
n = mpz(2687877080950902194160714845570568186540285498289)
e = mpz(391719044089)
d = mpz(1562283790058104878275187093946203993004368317129)
c = mpz(2427868627995403381967145272206117242396621386449)

e_a = mpz(410668762391)
c_a = mpz(451749460574894754071617993476375198277813392972)

A='abcdefghijklmnopqrstuvwxyz'
def i_skaiciu(text):
    t=''
    for r in text:
        if r in A:
            ind=A.index(r)+1
            if ind<10: t=t+'0'+str(ind)
            else: t=t+str(ind)
    return int(t,10)

def i_teksta(M):
    n=M
    text=''
    while n>0:
        ind=n%100
        ind=ind-1
        if (ind>=0) & (ind<len(A)):
            text+=A[ind]
            n=(n-ind+1)//100
        else:
            text+='?'
            n=(n-ind+1)//100
    return text[::-1]

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

print(i_teksta(pow(c, d, n)));

# search for non even division
t = e * d - 1
while t % 2 == 0:
    t = t // 2;
print("t =", t);

# search for a that is not a**t (mod n) == 1
a = 532
while pow(a, t, n) == 1:
    a += 1
a = pow(a, t, n)
print("a =", a)

# search for another value of a which will have mod 1
while True:
    a_before = a
    a = pow(a, 2, n);
    if a == 1:
        break;

a = a_before;
print(a)

d = fractions.gcd(a - 1, n)
print(d)
q = d
p = n // q
print(q, d)

n_new = (p - 1) * (q - 1)
print(n_new)

d_a = modinv(e_a, n_new)
print(d_a)

print(i_teksta(pow(c_a, d_a, n)));








