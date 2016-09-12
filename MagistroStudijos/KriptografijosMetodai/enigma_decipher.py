#!/usr/bin/python2.7

alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
lambda_rotor = [[10, 2, 21, 18, 23, 6, 16, 14, 8, 11, 1, 25, 15, 20, 0, 24, 17, 19, 22, 5, 4, 3, 9, 12, 13, 7],
                [20, 3, 24, 18, 8, 5, 15, 4, 7, 11, 0, 13, 9, 22, 12, 23, 10, 1, 19, 21, 17, 16, 2, 25, 6, 14]]
key = [15, 12]
cipher1 = [19, 8, 7, 24, 25, 23, 1, 10, 13, 16, 17, 3, 16, 17, 23, 13, 0, 2, 21, 8, 0, 17, 8, 20, 12, 15, 19, 13, 10, 13, 8, 25, 3, 14, 16, 18, 2, 24, 23, 2, 9, 6, 10, 24, 21, 10, 10, 21, 22, 11, 9, 20, 3, 19, 6]
cipher2 = [12, 2, 24, 6, 12, 0, 25, 3, 24, 5, 1, 14, 9, 2, 15, 6, 10, 19, 12, 0, 8, 10, 20, 15, 24, 16, 5, 17, 15, 24, 2, 22, 19, 5, 20, 1, 25, 19, 25, 13, 14, 19, 21, 11, 1, 10, 14, 12, 9, 22, 20, 24, 1, 1, 17]

sigma = [2, 4, 0, 6, 1, 11, 3, 8, 7, 13, 16, 5, 15, 9, 18, 12, 10, 19, 14, 17, 25, 22, 21, 24, 23, 20]

def q(letter, m):
    return (letter + m) % len(alphabet)

def encipher_letter(cypher_letter, letter_pos):
    #estimate intermediates
    n = len(alphabet)
    m = [letter_pos % n, letter_pos / n]

    #encipher
    temp = q(cypher_letter, (m[0] + key[0]))
    temp = lambda_rotor[0][temp]
    temp = q(temp, -(m[0] + key[0]))
    temp = q(temp, (m[1] + key[1]))
    temp = lambda_rotor[1][temp]
    temp = q(temp, -(m[1] + key[1]))
    return temp

def decipher_letter(cypher_letter, letter_pos):
    #estimate intermediates
    n = len(alphabet)
    m = [letter_pos % n, letter_pos / n]

    #Estimate reverse lambda rotors
    rev_lambda = [[0] * len(lambda_rotor[0]), [0]*len(lambda_rotor[1])]

    for i in range(0, len(lambda_rotor[0])):
        rev_lambda[0][lambda_rotor[0][i]] = i

    for i in range(0, len(lambda_rotor[1])):
        rev_lambda[1][lambda_rotor[1][i]] = i

    #decipher
    temp = q(cypher_letter, (m[1] + key[1]))
    temp = rev_lambda[1][temp]
    temp = q(temp, -(m[1] + key[1]))
    temp = q(temp, (m[0] + key[0]))
    temp = rev_lambda[0][temp]
    temp = q(temp, -(m[0] + key[0]))
    return temp

text = ""
for idx, c in enumerate(cipher1):
    text += alphabet[decipher_letter(c, idx)];
print text


text = ""
for idx, c in enumerate(cipher2):
    enc = encipher_letter(c, idx)
    transform_enc = sigma[enc]
    dec = decipher_letter(transform_enc, idx)
    text += alphabet[dec]
print text
