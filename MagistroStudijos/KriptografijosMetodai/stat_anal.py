#!/usr/bin/python3.5

from scipy import stats
import re
import math

input1 = [82, 201, 246, 136, 58, 208, 76, 40, 104, 210, 112, 239, 132, 17, 223, 200, 82, 205, 10, 255, 24, 189, 5, 177, 222, 195, 108, 200, 154, 150, 173, 121, 128, 84, 250, 215, 13, 223, 0, 46, 111, 7, 23, 66, 135, 227, 136, 239, 160, 244, 63, 142, 132, 78, 0, 174, 43, 182, 77, 174, 198, 21, 0, 110, 136, 122, 251, 71, 122, 111, 204, 160, 129, 36, 27, 52, 145, 120, 55, 35, 212, 107, 50, 226, 170, 198, 63, 18, 230, 235, 217, 41, 198, 145, 79, 197, 217, 143, 165]
input2 = [89, 8, 218, 147, 247, 238, 181, 101, 117, 103, 148, 189, 36, 58, 87, 116, 218, 1, 87, 61, 241, 201, 66, 47, 93, 137, 240, 135, 69, 217, 94, 131, 96, 207, 149, 167, 217, 29, 229, 147, 129, 148, 254, 184, 25, 149, 69, 183, 37, 195, 248, 254, 108, 248, 171, 19, 67, 169, 255, 31, 129, 4, 57, 181, 116, 189, 67, 103, 173, 188, 5, 147, 203, 72, 30, 124, 89, 25, 79, 87, 143, 62, 236, 86, 165, 31, 103, 177, 110, 119, 52, 215, 165, 77, 95, 174, 48, 107, 60]

def ones_count(x):
    return bin(x).count('1')

def count_pattern(pattern, x):
    return len(re.findall(r'(?=(' + pattern + '))', x))

def to_bin(x):
    num = 0;
    for idx, i in enumerate(x):
        num |= i << (8*idx)
    return str(bin(num))[2:]

def get_bits_count(x):
    ones = 0;
    for i in x:
        ones += ones_count(i)

    zeros = len(x) * 8 - ones;

    return [zeros, ones]

def get_diff_bits(bitstr, d):
    count = 0
    for i in range(0, len(bitstr) - d + 1):
        if bitstr[i] != bitstr[i + d - 1]:
            count += 1;
    return count;


def single_bit_test(data, limit):
    n = len(data) * 8
    [N0, N1] = get_bits_count(data)
    T = (N1 - N0)**2 / n
    P = 1 - stats.chi2.cdf(T, 1)
    print("single bit test.")
    print("N0 =", N0, "N1 =", N1)
    print("T =", T, "P =", P)
    print("Is accepted: ", P > limit)

def two_bit_test(data, limit):
    n = len(data) * 8
    [N0, N1] = get_bits_count(data)
    N00 = count_pattern("00", to_bin(data))
    N01 = count_pattern("01", to_bin(data))
    N10 = count_pattern("10", to_bin(data))
    N11 = count_pattern("11", to_bin(data))
    T = 4 / (n - 1) * (N00**2 + N01**2 + N10**2 + N11**2) - 2 / n * (N0 ** 2 + N1 ** 2) + 1
    P = 1 - stats.chi2.cdf(T, 2)
    print("two bit test.")
    print("N00 =", N00, "N01 =", N01, "N10 =", N10, "N11 =", N11, "N0 =", N0, "N1 =", N1)
    print("T =", T, "P =", P)
    print("Is accepted: ", P > limit/2)

def autocorelation_test(data, d, limit):
    print("autocorellation bit test. d =", d)
    n = len(data) * 8
    T = (2 * get_diff_bits(to_bin(data), d) - n + d) / math.sqrt(n - d)
    if T < 0:
        P = stats.norm.cdf(T)
    else:
        P = 1 - stats.norm.cdf(T)
    print("Xd =", get_diff_bits(to_bin(data), d))
    print("T =", T, "P =", P)
    print("Is accepted: ", P > 0.1)

print("I Sifras ")
single_bit_test(input1, 0.1)
two_bit_test(input1, 0.1)
autocorelation_test(input1, 2, 0.1)
autocorelation_test(input1, 3, 0.1)
autocorelation_test(input1, 4, 0.1)

print()
print("II Sifras ")
single_bit_test(input2, 0.1)
two_bit_test(input2, 0.1)
autocorelation_test(input2, 2, 0.1)
autocorelation_test(input2, 3, 0.1)
autocorelation_test(input2, 4, 0.1)















