#!/usr/bin/python3.5

import sys
import re
import os
from os import listdir
from os.path import isfile, join

def count_words(filename, wordlist = []):

    #read whole mail file into text variable
    f = open(filename, "r")
    text = f.read();

    # if provided a list, build a dictionary (key->word, value->count) of all zeros
    attrs = {}
    if len(wordlist) > 0:
        for word in wordlist:
            attrs[word] = 0;

    # split all text by this regular expression
    words = re.split(' |\t|\r|\n|>|<|=|"|/|#|%|}|{|\\\\|,|\'|:|;|\\(|\\)', text);
    for word in words:
        #limit word length to 30
        if len(word) > 30 or len(word) < 2:
            continue

        # if wordlist provided - check if it is in set
        if len(wordlist) > 0 and word not in wordlist:
            continue

        # increment count of the word
        if word not in attrs:
            attrs[word] = 1;
        else:
            attrs[word] += 1;

    f.close();
    return attrs;

def build_attribute_names(maildir, maxCount):
    mailfiles = sorted([os.path.join(maildir, f) for f in listdir(maildir) if os.path.isfile(os.path.join(maildir, f))])

    # for all mail files build a list of words and how many times that word repeats
    # dictionary key->word, value->number of occureances
    wordcount = {}
    for f in mailfiles:
        try:
            attrs = count_words(f)
        except:
            continue

        for word, count in attrs.items():
            if word in wordcount:
                wordcount[word] += count
            else:
                wordcount[word] = count

    # sort by popularit and clip last words.
    # ensure what SPAM marker is in the list
    keys_sorted = sorted(wordcount, key=wordcount.get, reverse=True)
    keys_clipped = keys_sorted[:maxCount - 1]
    if '' in keys_clipped:
        keys_clipped.remove('')
    if "UniqueWordDifferentiatingSPAM" not in keys_clipped:
        keys_clipped.append('UniqueWordDifferentiatingSPAM')

    return keys_clipped

def count_attribute_values(maildir, attribute_names):
    mailfiles = sorted([os.path.join(maildir, f) for f in listdir(maildir) if os.path.isfile(os.path.join(maildir, f))])
    mailvalues = []
    for mailfile in mailfiles:
        try:
            attrs = count_words(mailfile, set(attribute_names))
        except:
            continue

        mailvalues.append(attrs)

    return mailvalues

def write_to_arff(data):
    # write header
    f = open("data.arff", "w")

    f.write("@relation mail.data\n\n");

    for attribute in data[0]:
        if str(attribute) == "UniqueWordDifferentiatingSPAM":
            f.write("@attribute SPAM {0,1}\n")
        else:
            f.write("@attribute " + str(attribute) + " numeric\n")

    f.write("\n@data\n");
    for item in data:
        first = True
        for attribute, count in item.items():
            if (first):
                f.write(str(count))
            else:
                f.write("," + str(count))
            first = False
        f.write("\n");




if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: " + sys.argv[0] + " <path to mail files>")
        exit(0)

    attributes = build_attribute_names(sys.argv[1], 1024)
    data = count_attribute_values(sys.argv[1], attributes);
    write_to_arff(data)

