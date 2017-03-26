#!/usr/bin/python3.5

getBin = lambda x, n: x >= 0 and str(bin(x))[2:].zfill(n) or "-" + str(bin(x))[3:].zfill(n)
abc_h='ABCDEFGHIJKLMNOP' # h-funcijos reikšmių abecele
def e(m,k): #Kriptosistema
    f=lambda u,v,w:u^((v*v+77*w)%256)
    c=[m[1],f(m[0],m[1],k[0])]
    return [c[1],f(c[0],c[1],k[1])]

def code(m): 
    e=getBin(m[0],8)+getBin(m[1],8)
    h=''
    for i in range(0,4):
        h+=abc_h[int(e[4*i:4*i+4],2)]
    return h

def decod(s): #h-funkcijos reikšmė į bitus
    bt=lambda r: bin(16^r)[3:]
    b=''
    for c in s:
        if c in abc_h:
            b+=bt(abc_h.index(c))
    return b
def hf(h0,r,s): # h-funkcija
    h=[ord(h0[0]),ord(h0[1])]
    k=[ord(r[0]),ord(r[1])]
    l=len(s)
    if l%2==1:
         s=s+s[0]
         l+=1
    for i in range(0,l//2):
        m=[ord(s[2*i])^h[0],ord(s[2*i+1])^h[1]]
        h=e(m,k)
    return code(h)

h0='pi'
r='pi'
s='piktaspiktas'
h = hf(h0,r,s)
print("h(M) = " + h)

print("h(\"pikt\") =    " + decod(hf(h0, r, "pikt")))
print("ascii \"as\" = " + bin(ord('a')) + " " + bin(ord('s')))
print("as after xor  1100101111101011");
print("h(\"rytkar\") = " + decod(hf(h0, r, "rytkar")))
print("h(\"rytkarY;piktas\") = " + hf(h0, r, "rytkarY;piktas"))

print("======================");
print("h(\"pikt\") = " + decod(hf(h0, r, "pikt")))
print("ascii \"as\" = " + bin(ord('a')) + " " + bin(ord('s')))
print("as after xor 1100101111101011");
print("h(\"piktas\") = " + decod(hf(h0, r, "piktas")))

u1 = 105
u2 = 25
print("h(\"piktas\") = " + hf(h0, r, "piktas"))
print("h(\"piktasu1u2\") = " + hf(h0, r, "piktas" + chr(u1) + chr(u2)))
print("h(\"piktasu1u2u1u2\") = " + hf(h0, r, "piktas" + chr(u1) + chr(u2) + chr(u1) + chr(u2)))










