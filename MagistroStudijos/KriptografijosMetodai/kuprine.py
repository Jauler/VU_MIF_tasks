#!/usr/bin/python3.5

import fractions

V = [37885, 222959, 155422, 16244, 118869, 154093, 13586, 89459]
C = [740802, 586709, 621933, 497670, 548718, 621933, 155422, 497670, 586709, 467840, 638177, 481426, 586709, 467840, 155422, 562304, 621933, 510836, 467840, 497670]
p = 242992
w_init = 1463

V = [43217, 106102, 25925, 49538, 17093, 5507, 38822, 125152]
C = [301508, 220387, 323810, 193449, 257179, 345539, 25925, 345539, 274272, 137534, 257179, 170849, 220387, 257179, 345539]
p = 207420
w_init = 1181

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

def decipher_letter(V, s, c):
    _w = [vi*s%p for vi in V]
    print(_w)
    off = 0
    num = 0
    c = c * s % p
    for w in reversed(_w):
        if c >= w:
            num |= 1 << off
            c -= w
        off += 1
    return num

if fractions.gcd(V[0], p) == 1:
    s = w_init * modinv(V[0], p) % p
else:
    raise Exception('Not supported')

text_i = [decipher_letter(V, s, x) for x in C]
text_s = [chr(i) for i in text_i]

print(''.join(text_s))






