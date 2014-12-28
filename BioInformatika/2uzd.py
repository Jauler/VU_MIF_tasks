#!/usr/bin/python

import os
import time
import Bio.SubsMat.MatrixInfo
import Bio.Blast.NCBIWWW
import Bio.Blast.NCBIXML
from Bio import Entrez

#run ncbi blast
entrez_query = '"serum albumin"[Protein name] AND mammals[Organism]'
ncbi = Bio.Blast.NCBIWWW.qblast(program = "blastp",
                                database = "swissprot",
                                sequence = "4502027",
                                entrez_query = entrez_query,
                                hitlist_size = 500,
                                expect = 100.0)
#ncbi = open("/home/rytis/Downloads/740B49S001R-Alignment.xml", "r")
blast = Bio.Blast.NCBIXML.read(ncbi)

#2.a Filter results to only leave 80+% coverage
#Build up a list of elements whose coverage is below 80
popping = []
for seq in blast.alignments:
    cover_percentage = 0
    for hsps in seq.hsps:
        cover_percentage += ((hsps.query_end - hsps.query_start) *
                                        100.0 / blast.query_length)
    if cover_percentage < 80.0:
        popping.append(seq)
#now pop all those elements
for pop in popping:
    blast.alignments.remove(pop)

#save FASTAs to file
f = open("BlastSequences", "w")
for seq in blast.alignments:
    #use windows line endings just in case
    f.write(">" + str(seq.hit_id) + " " + str(seq.hit_def) + "\n\r")
    f.write(str(seq.hsps[0].sbjct) + "\n\r")
f.close()

#Use Mafft program
os.system("mafft --quiet BlastSequences > MultipleAlignedSequences")



#figure out most unique and most mamalian sequences of amino-acids
#we will use blosum62 and conservation estimate for this
blosum62 = Bio.SubsMat.MatrixInfo.blosum62
conservation = [0] * blast.query_length #at first initiate to all zeros

#Now go through each sequence each and sum up blosum62 scores
for seq in blast.alignments:
    #use only best matches
    hsp = seq.hsps[0]
    for index in range(len(hsp.query)):
        cons_idx = index + hsp.query_start - 1

        if hsp.query[index] == "-":
            continue

        if hsp.sbjct[index] == "-":
            continue

        try:
            conservation[cons_idx] += blosum62[(hsp.query[index],
                                    hsp.sbjct[index])]
        except KeyError:
            #Other way round
            conservation[cons_idx] += blosum62[(hsp.sbjct[index],
                                    hsp.query[index])]

#now we search for continuous sequence of aminoacids whose conservation
#values are highest (lowest)
highest_sum = None
lowest_sum = None
highest_idx = None
lowest_idx = None

for index in range(len(conservation) - 15):
    cons_sum = sum(conservation[index : index + 15])

    #save if higher than previous highest
    if highest_sum == None:
        highest_idx = index
        highest_sum = cons_sum
    elif highest_sum < cons_sum:
        highest_idx = index
        highest_sum = cons_sum

    #save if lower than previous lowest
    if lowest_sum == None:
        lowest_idx = index
        lowest_sum = cons_sum
    elif lowest_sum > cons_sum:
        lowest_idx = index
        lowest_sum = cons_sum

#Retrive full FASTA of the original protein
Entrez.email = "A.N.Other@xample.com"
handle = Entrez.efetch(db = "Protein", id="NP_000468.1",
                        rettype = "fasta", retmode="xml")
record = Entrez.read(handle)

#print the results
highest_str = "Labiausiai panasi seka prasideda: "
highest_str += str(highest_idx)
highest_str += " Baigiasi: "
highest_str += str(highest_idx + 14)
highest_str += " Seka: "
highest_str += record[0]["TSeq_sequence"][highest_idx : highest_idx + 15]
print highest_str

lowest_str = "Labiausiai nepanasi seka prasideda: "
lowest_str += str(lowest_idx)
lowest_str += " Baigiasi: "
lowest_str += str(lowest_idx + 14)
lowest_str += " Seka: "
lowest_str += record[0]["TSeq_sequence"][lowest_idx : lowest_idx + 15]
print lowest_str











