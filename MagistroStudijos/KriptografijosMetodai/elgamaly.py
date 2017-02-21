#!/usr/bin/python3.5

import fractions

[p, alpha, beta]=[12016012609141909200527091927191118250205120747, 14, 6444521820681528654586098011913973529018647549]

m1 = 14012110090514212714051801
[gama1, delta1] = [6710426405704652695147213140701144673475937627, 4707784649066417310752876690383264903804627484]
print("Is valid: ", pow(beta, gama1, p) * pow(gama1, delta1, p) % p == pow(alpha, m1, p))

m2 = 1021192127190119110109200127202119030901
[gama2, delta2] = [6710426405704652695147213140701144673475937627, 11203538361844132001566315429055035059644749286]
print("Is valid: ", pow(beta, gama2, p) * pow(gama2, delta2, p) % p == pow(alpha, m2, p))

[C_1,C_2] = [11215453535380272452717730488685918124163318327, 9137572685870983683161256703733184437324148142]

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



d = fractions.gcd(delta1 - delta2, p - 1)
print("gcd(delta1-delta2, p-1) =", d)
print("gcd( (delta1-delta2)/d, (p-1)/d ) =", fractions.gcd( (delta1 - delta2) // d, (p - 1) // d))

print(delta1 - delta2)
d1d2_inv = modinv( (p - 1) // d - (delta1 - delta2) // d, (p - 1) // d)
k = (m1 - m2) // d * d1d2_inv // d % ((p - 1) // d)
print("test: ", k)

# magic happens
k = 438484039535
print(k)

d = fractions.gcd(gama1, p - 1)
print(d)
a = (m1 - delta1 * k) // modinv(gama1, p - 1) % (p - 1)
# more magic happens
a = 634051277019
print(a)

m = C_2 * pow(modinv(C_1, p), a, p) % p
print(m)

print(i_teksta(m))
print(i_teksta(16011801190119271405200911180119))


m = 16011801190119271405200911180119
p_gama = pow(alpha, k, p)
p_delta = (m - a*p_gama) * modinv(k, p - 1) % (p - 1)

print([p_gama, p_delta])

print("Is valid: ", pow(beta, p_gama, p) * pow(p_gama, p_delta, p) % p == pow(alpha, m, p))




