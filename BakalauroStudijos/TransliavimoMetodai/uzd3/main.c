/*
##########################################################
# Transliavimo metodai, 2014/2015 m.m. (7 semestras)
# Trečiasis praktinis darbas
# Rytis Karpuška, Donatas Kučinskas, Programų sistemos, 4k., 3 grupė
# Variantas: 111
##########################################################
*/

#include "parser.tab.h"
#include <stdio.h>
#include "common.h"
#include "parser.h"

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
	fprintf(yyout, "<html>\n");
	int i;
	
	//defines list
	fprintf(yyout, "<h3>Defines:</h3>\n<ul>\n");
	for (i = 0; i < definesCount; ++i) {
		int id = defines[i];
		fprintf(yyout, "<li>%s", identifiers[id]);
		Define *value = &idValue[id];
		if (value->type == DEFINE_INT) {
			fprintf(yyout, " = %d", value->value.iValue);
		}
		else if (value->type == DEFINE_STRING) {
			fprintf(yyout, " = \"%s\"", value->value.str);
		}
		else if (value->type == DEFINE_TRUE) {
		}
		fprintf(yyout, "</li>\n");
	}
	fprintf(yyout, "</ul>\n");
	
	//functions list
	fprintf(yyout, "<h3>Functions:</h3>\n<ul>\n");
	for (i = 0; i < functionsCount; ++i) {
		Function *f = functions[i];
		fprintf(yyout, "<li>%s", identifiers[f->id]);
		int j;
		fprintf(yyout, "<br/>\nReturns: %s\n", f->returnType);
		if (f->args->length) {
			fprintf(yyout, "<br />\nArguments:\n<ul>\n");
			for (j = 0; j < f->args->length; ++j) {
				Argument *arg = f->args->items[j];
				fprintf(yyout, "<li>");
				if (arg->id != -1) {
					fprintf(yyout, "%s %s\n", arg->type, identifiers[arg->id]);
				}
				else {
					fprintf(yyout, "%s\n", arg->type);
				}
				fprintf(yyout, "</li>");
			}
			fprintf(yyout, "</ul>\n");
		}
		fprintf(yyout, "</li>\n");
	}
	fprintf(yyout, "</ul>\n");

	//structs list
	fprintf(yyout, "<h3>Structures:</h3>\n<ul>\n");
	for (i = 0; i < structsCount; ++i) {
		Struct *s = structs[i];
		fprintf(yyout, "<li>%s", identifiers[s->id]);
		fprintf(yyout, "<ul>\n");
		int j;
		for (j = 0; j < s->declarations->length; ++j) {
			VariableDeclaration *declaration = s->declarations->items[j];
			fprintf(yyout, "<li>");
			fprintf(yyout, "%s %s\n", declaration->type, identifiers[declaration->id]);
			fprintf(yyout, "</li>");
		}
		fprintf(yyout, "</ul>\n");
		fprintf(yyout, "</li>\n");
	}
	fprintf(yyout, "</ul>\n");

	fprintf(yyout, "</html>\n");
	return 0;
}
