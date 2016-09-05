#!/usr/bin/python
#Trecias Bioinformatikos laboratorinis darbas
#Rytis Karpuska PS1

import os
import time
import string
import Bio.SubsMat.MatrixInfo
import Bio.Blast.NCBIWWW
import Bio.Blast.NCBIXML
from Bio import Entrez

#run ncbi blast
print "Running Blast..."
fasta_seq_file = open("3uzd_seq.fasta", "r");
fasta_seq = fasta_seq_file.read();
fasta_seq_file.close()

#make actual blast request
ncbi = Bio.Blast.NCBIWWW.qblast(program = "blastn",
                                database = "nr",
                                sequence = fasta_seq,
                                hitlist_size = 1000)
blast = Bio.Blast.NCBIXML.read(ncbi)

#Build up a list of IDs for FASTA download
str_ids = "";
for alignment in blast.alignments:
    str_id = alignment.hit_id.split("|")[3]
    if str_ids == "":
        str_ids = str_id
    else:
        str_ids = str_ids + "," + str_id


#Retreive sequences of aligned records:
print "Retreiving sequencess..."
Entrez.email = 'A.N.Other@example.com'
handle = Entrez.efetch(db="nucleotide", id=str_ids, retmode="xml");
records = Entrez.read(handle)

#Remove old data from folder
for the_file in os.listdir("seqs"):
    file_path = os.path.join("seqs", the_file)
    if os.path.isfile(file_path):
        os.unlink(file_path)

#Writing received sequences in fasta formats in seqs folder
print "Parsing retreived sequences..."
for record in records:
    #figure out what type this virus is
    type_str = None
    def_strs = record["GBSeq_definition"].split(" ")
    for idx, def_str in enumerate(def_strs):
        def_str = def_str.lower()
        if "type" in def_str:
            try:
                type_str = def_strs[idx + 1]
            except:
                continue
            break

    #just in case if we did not found type
    if type_str == None:
        continue

    #remove punctuation from type
    exclude = set(string.punctuation)
    tmp_str = ''.join(ch for ch in type_str if ch not in exclude)
    type_str = tmp_str

    #make actual file write
    f = open("seqs/Human_papillomavirus_type_" + type_str, "a")
    f.write(">gi|" + record["GBSeq_primary-accession"] +  "|" + record["GBSeq_definition"] + "\n" + record["GBSeq_sequence"].upper() + "\n")


#run cd-hit for every file in directory
print "Running cd-hit"
files = os.listdir("seqs")
for the_file in files:
    cmd = "cd-hit -i seqs/" + the_file + " -o seqs/cd-hit_output_" + the_file + ".cdout -c 0.9 -n 5"
    os.system(cmd);

#combine all cd-hit results in two files one for dangerous viruses, one for not dangerous
print "Combining cd-hit results..."
files = os.listdir("seqs")
dout_f = open("seqs/all_dangerous_seqs.fasta", "w")
sout_f = open("seqs/all_safe_seqs.fasta", "w")
for the_file in files:
    #do not care about clstr files and files which do not end in cdout
    if ".cdout" not in the_file:
        continue
    if ".clstr" in the_file:
        continue

    #write cd-hit output file contents into all_seqs file
    f = open("seqs/" + the_file, "r")
    if("type 16" in the_file or
            "type 18" in the_file or
            "type 31" in the_file or
            "type 33" in the_file or
            "type 35" in the_file or
            "type 51" in the_file or
            "type 52" in the_file):
        dout_f.write(f.read())
    else:
        sout_f.write(f.read())
    f.close();
dout_f.close();
sout_f.close();

#combine viruses to one file, first dangerous, then not dangerous
dout_f = open("seqs/all_dangerous_seqs.fasta", "r")
sout_f = open("seqs/all_safe_seqs.fasta", "r")
out_f = open("seqs/all_seqs.fasta", "w");
out_f.write(dout_f.read());
out_f.write(sout_f.read());
dout_f.close();
sout_f.close();
out_f.close();

#run mafft on all_seqs.fasta file
print "Running mafft..."
os.system("mafft --quiet seqs/all_seqs.fasta > seqs/all_seqs_after_mafft.fasta")

print "Done."




