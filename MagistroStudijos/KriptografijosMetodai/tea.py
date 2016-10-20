#!/usr/bin/python3.5

def rotr(val, r_bits):
    max_bits = 8
    return ((val & (2**max_bits-1)) >> r_bits%max_bits) | (val << (max_bits-(r_bits%max_bits)) & (2**max_bits-1))

def rotl(val, r_bits):
    return rotr(val, -r_bits)

def sum(x1, x2):
    return (x1 + x2) % 256

def sub(x1, x2):
    return (x1 - x2) % 256

def tea_iteration_encipher(l, r, k0, k1, k2):
    term0 = sum(rotl(l, 2), k1)
    term1 = sum(rotr(l, 2), k2)
    term2 = sum(l, k0)
    xor = term0 ^ term1 ^ term2
    return (sum(xor, r), l)

def tea_iteration_decipher(l, r, k0, k1, k2):
    term0 = sum(rotl(l, 2), k1)
    term1 = sum(rotr(l, 2), k2)
    term2 = sum(l, k0)
    xor = term0 ^ term1 ^ term2
    return (sub(r, xor), l)

def tea_encipher(m, k):
    l, r = tea_iteration_encipher(m[0], m[1], k[0], k[1], k[2])
    l, r = tea_iteration_encipher(l, r,       k[1], k[2], k[0])
    l, r = tea_iteration_encipher(l, r,       k[2], k[0], k[1])
    return r, l

def tea_decipher(m, k):
    l, r = tea_iteration_decipher(m[0], m[1], k[2], k[0], k[1])
    l, r = tea_iteration_decipher(l, r,       k[1], k[2], k[0])
    l, r = tea_iteration_decipher(l, r,       k[0], k[1], k[2])
    return r, l

print("====== TST ========")
input = [[ord('l'), ord('a')], [ord('b'), ord('a')]]
key = [32, 54, 115]
cypher = [tea_encipher(input[0], key), tea_encipher(input[1], key)]
out = ""
out = chr(tea_decipher(cypher[0], key)[0]) + chr(tea_decipher(cypher[0], key)[1])
out += chr(tea_decipher(cypher[1], key)[0]) + chr(tea_decipher(cypher[1], key)[1])
print(out)

print("======= ECB ========")
input = [[54, 218], [128, 118], [190, 189], [172, 44], [254, 57], [14, 123], [118, 224], [10, 173], [248, 125], [48, 145], [6, 213], [197, 194]]
key = [108, 97, 116]
out = ""
for cypher in input:
    plain = tea_decipher(cypher, key)
    out += chr(plain[0]) + chr(plain[1])
print(out)


print("======= CBC ========")
input = [[31, 93], [239, 80], [44, 220], [71, 63], [221, 83], [48, 228], [184, 115], [154, 0], [222, 104], [158, 20], [26, 218]]
iv = [ord('a'), ord('i')]
key = [108, 97, 116]
out = ""
for cypher in input:
    plain = tea_decipher(cypher, key)
    out += chr(plain[0] ^ iv[0]) + chr(plain[1] ^ iv[1])
    iv = cypher
print(out)

print("======= OFB ========")
input = [[242, 19], [167, 197], [22, 228], [121, 217], [168, 145], [239, 74], [90, 22], [164, 38], [93, 69], [174, 247], [195, 15], [253, 238], [173, 101], [33, 37], [237, 116]]
iv = [ord('p'), ord('r')]
key = [108, 97, 116]
out = ""
for cypher in input:
    enc = tea_encipher(iv, key)
    out += chr(enc[0] ^ cypher[0]) + chr(enc[1] ^ cypher[1])
    iv = enc
print(out)






