#!/usr/bin/python3.5

import operator
from collections import defaultdict


print('==== 1 =====')
alphabet = str('AĄBCČDEĘĖFGHIĮYJKLMNOPRSŠTUŲŪVZŽ')

def freq(cipher, idx, key_len):
    histo = {}
    for l in alphabet:
        histo[l] = 0;

    for c_idx in range(idx, len(cipher), key_len):
        histo[cipher[c_idx]] += 1

    return histo

def decipher_vigenerie_auto(cipher, key):
    result = str("")
    for i, c in enumerate(cipher):
        c_idx = alphabet.index(c)

        if (i - len(key) < 0):
            k_idx = alphabet.index(key[i % len(key)])
        else:
            k_idx = alphabet.index(cipher[i - len(key)])

        t_idx = (c_idx - k_idx) % len(alphabet)
        result += alphabet[t_idx]
    return result


def decipher_vigenerie(cipher, key):
    result = str("")
    for i, c in enumerate(cipher):
        c_idx = alphabet.index(c)
        k_idx = alphabet.index(key[i % len(key)])

        t_idx = (c_idx - k_idx) % len(alphabet)
        result += alphabet[t_idx]
    return result

print(decipher_vigenerie(str('ROEPĘCDŪŲJFEFŲĘVHBEKVĮEAGBOBŲIYOCEKŠČGRCLEĘDCBNŪUHOAGOYCHFAKFHFIĘLHEIGĮACILLHRTVŽYĮOYĮAEISJĖĘKVYAČSVFDGTŽOĘGRHBOCČCLHŽŲESTŠJCJĖRLVJUCTLOHČLCVGŪSTSLČTSBODRCMOJIGROĘYIVĮŪNĄLTŠMVOAČVVNĮGDSKZKUYĮKCUINOŠJLOČRTOCGŪEFOERTSJHDOJFĖKTĮVTŪMHMDKNVRPKPYĮGŪEELĖFEGOČŽOĖBĖRKYMUPIUFCKOKCĘĘKELDPAYRBEIGDCČPĖVĘRTŠFIĄAHĮĖCOCNTĮIVIJDAĄVDMIGFJĄACUJĖIVĮHDEŪFSŪJSŽYĮOINĖĮIPLGŪNCLABPĮLLŪZLLĮČŽOVDUYFLFČBNBNŪOESĖĄATFOGKSBĘRGSYŪŽOGSHŪLVFHFIČMDKNVRP'), 'VOKAS'))



print('==== 2 =====')

abc=str('AĄBCČDEĘĖFGHIĮYJKLMNOPRSŠTUŲŪVZŽ')
def friedm(text, k):
    textn=str("")
    for r in text:
        if r in abc:
            textn+=r
    l=len(textn)
    s=0
    for i in range(k,l):
        if textn[i]==textn[i-k] :
            s+=1
    return  1.*s/(l-k)

t = str('KTŠBALEŽAŠIHĖĮZRIĖSDČZJČIJAĖIKDRAKOĮĄTĘBZFLIUĘYĄCIOFTĘHFAKGCĄTĘJIJĘNČGMIĖŽČĮUSKKUBTKSJBJUFODUFAĖCCAHAYCŲOBSŽKDĘGDDŪŠAGIJSNZKSCSKČČSKSGPĮTVĖŽLRDCGZOĖIEŠYGBEJTDĖĘOĄCIUŽOĮFTSBJSĘNGBAIĄTYŠĖOCKPHLSGŽĮSDĮVŲYJIGCNHĘUHĘKĘBUOCŽĮGMCYFUĘIMFĘDBŲĄCGYĖOKSDOĮTĮHIĖĖACCJVBZCĘTAJVCĮMAFOEHCĮRIKLJAFTCTPĮBIKCIĖIGSGDMKOKSKĮIUĘKPGRGSĖDERSŪSDČJAYYTLGSSGZOIAIĮTĘGKYKTĘJIRVHŪĮOĮĄTĘBZFLKCŪIĄLĖOKJCYNZŪBSSFĮČVCSDLŪIĘKDFĘAGVMĖĮOĮTDĮGSAHJERVCFUHB')
for i in range(2, 30):
    print(i, friedm(t, i))
expected_length = 6;

print(decipher_vigenerie(str('KTŠBALEŽAŠIHĖĮZRIĖSDČZJČIJAĖIKDRAKOĮĄTĘBZFLIUĘYĄCIOFTĘHFAKGCĄTĘJIJĘNČGMIĖŽČĮUSKKUBTKSJBJUFODUFAĖCCAHAYCŲOBSŽKDĘGDDŪŠAGIJSNZKSCSKČČSKSGPĮTVĖŽLRDCGZOĖIEŠYGBEJTDĖĘOĄCIUŽOĮFTSBJSĘNGBAIĄTYŠĖOCKPHLSGŽĮSDĮVŲYJIGCNHĘUHĘKĘBUOCŽĮGMCYFUĘIMFĘDBŲĄCGYĖOKSDOĮTĮHIĖĖACCJVBZCĘTAJVCĮMAFOEHCĮRIKLJAFTCTPĮBIKCIĖIGSGDMKOKSKĮIUĘKPGRGSĖDERSŪSDČJAYYTLGSSGZOIAIĮTĘGKYKTĘJIRVHŪĮOĮĄTĘBZFLKCŪIĄLĖOKJCYNZŪBSSFĮČVCSDLŪIĘKDFĘAGVMĖĮOĮTDĮGSAHJERVCFUHB'), 'STORAS'))




print('==== 3 =====')

t = str('FTĘJIGĄMUŲĖEHFOJBNKOĘKPĮHLOŲTLĮĄĮRKHĘEZRNĘĖUNRNHFTYVIOVJHGLLYYAKŠKLFOŪSŪĮĮNCIIVDDRUĘSKŠRAGVMAUOKSVAGUGCŽČZKCKĮOBNVKNGMJSLHOVOTNKUVATLRĖJAĮGŽĮZKCSFOJIFŲDOČIVJFĖCIYIDĘJUĖCOHĘACŪĘĮZJHSJČZPSGTIGUYSMHRSŽŪTYGNKFŽĮGLCGĄHUĖŪLMŪĄVCŪNGŠTLJVAZSVĮZLMSSKĮČRACGNĖĘIYMZORKKMIĖAĖESNFGBNKDFGTYODUVAY')
for i in range(2, 30):
    print(i, friedm(t, i))
expected_length = 6;

abc=str('AĄBCČDEĘĖFGHIĮYJKLMNOPRSŠTUŲŪVZŽ')
n=len(abc)
def guess(test, k, sifr): #test - dažniausių raidžių eilutė, k - spėjamas šifro raktas
    tst=str('')
    for r in test:
        if r in abc:
            tst+=r
    tstk=str('')
    for r in tst:
        tstk+=abc[(abc.index(r)+k)%n]
    d = defaultdict(int)
    sifrn=str('')
    for r in sifr:
        if r in abc: sifrn+=r
    for r in sifrn:
        if r in tstk: d[r]+=1
    kiek=len(sifrn)
    s=0
    for a in d.keys(): s+=d[a]
    return s/kiek


for i in range(0, expected_length):
    #build a block from text
    block = t[i::expected_length]
    hist = {}
    for l in alphabet:
        hist[l] = guess("IASORT", alphabet.index(l), block)
    hist = sorted(hist.items(), key=operator.itemgetter(1), reverse=True)
    count = 0;
    for h in hist:
        print(h[0], h[1])
        count += 1
        if count > 2:
            break;

    print('======')


print(decipher_vigenerie(str('FTĘJIGĄMUŲĖEHFOJBNKOĘKPĮHLOŲTLĮĄĮRKHĘEZRNĘĖUNRNHFTYVIOVJHGLLYYAKŠKLFOŪSŪĮĮNCIIVDDRUĘSKŠRAGVMAUOKSVAGUGCŽČZKCKĮOBNVKNGMJSLHOVOTNKUVATLRĖJAĮGŽĮZKCSFOJIFŲDOČIVJFĖCIYIDĘJUĖCOHĘACŪĘĮZJHSJČZPSGTIGUYSMHRSŽŪTYGNKFŽĮGLCGĄHUĖŪLMŪĄVCŪNGŠTLJVAZSVĮZLMSSKĮČRACGNĖĘIYMZORKKMIĖAĖESNFGBNKDFGTYODUVAY'), str('STOGAS')))



print('====== 4 =======')

print(decipher_vigenerie_auto(str('EMŪĘIKAFĄĮČŪMBYŽGPĮTBKRPCDTPRSCŲĖPKVUŲŲYŪOSĘMFOAHVMŠĖNŽRAYOEĘJOVJHJĄUOŲŽMĘĮĮLDĖŲMPĖZYVZĖĖLMFŽĄYČSJMČUNŠŲGPUŽĖFCĄLŽDVDĘANPFAĘBTČVNNVIGMNGRAĘZĘĄARĘŲNUATNGĘLOJPRAMCJJŠUJSČJĖSŲIHEŠSYLHSMGOĖŲSCCŲBUKSNĘŪLĘKTFČANBĮŽGZĮNEŽCŠČPAŪSGIŽIJSŪIREIVMCJMZLBUAEJLČOIŽJVOOŠJFNAUGEĖDOĮMŠŽZOTFĖŽGŠDFDHŪISFVSJAFAĮLDIVMTĖOŠCDTBTIMTKY'), str('LIESAS')))


