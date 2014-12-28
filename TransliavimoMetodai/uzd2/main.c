/*
##########################################################
# Transliavimo metodai, 2014/2015 m.m. (7 semestras)
# Antrasis praktinis darbas
# Rytis Karpuška, Donatas Kučinskas, Programų sistemos, 4k., 3 grupė
# Variantas: 111
##########################################################
*/

#include "parser.tab.h"
#include <stdio.h>

extern FILE *yyin;
extern FILE *yyout;

int main(int argc, char *argv[])
{
	//Check argument count
	if(argc != 3){
		fprintf(stderr, "Usage: parser <Input file> <Output file>\n");
		return 0;
	}

	//Try to open input file
	if(!(yyin = fopen(argv[1], "r"))){
		fprintf(stderr, "Error: Could not read input\n");
		return 0;
	}

	//Try to open output file
	if(!(yyout = fopen(argv[2], "w"))){
		fprintf(stderr, "Error: Could not write output\n");
		return 0;
	}

	yyparse();
	return 0;
}
