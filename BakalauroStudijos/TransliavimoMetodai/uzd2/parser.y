/*
##########################################################
# Transliavimo metodai, 2014/2015 m.m. (7 semestras)
# Antrasis praktinis darbas
# Rytis Karpuška, Donatas Kučinskas, Programų sistemos, 4k., 3 grupė
# Variantas: 111
##########################################################
*/

%{
	#include <stdio.h>
	int yylineno;
	char *yytext;
	int yylex(void);
	void yyerror(char *);
%}


%token IDENTIFIER
%token TYPE_KEYWORD
%token END_SENTENCE
%token OPERATOR
%token STRUCT
%token DEFINE
%token INTEGER
%token STRING
%left '+' '-'
%left '*' '/'

%%


program:
	program variable
	| program function
	| program struct
	| program directive
	|
	;


variable:
	TYPE_KEYWORD IDENTIFIER END_SENTENCE
	;


function:
	TYPE_KEYWORD IDENTIFIER argument_list END_SENTENCE
	;
argument_list:
	'('')'
	| '(' arguments ')'
	;
arguments:
	argument
	| arguments ',' argument
	;
argument:
	TYPE_KEYWORD IDENTIFIER
	| TYPE_KEYWORD
	| STRUCT IDENTIFIER IDENTIFIER
	;


struct:
	STRUCT IDENTIFIER '{' struct_variable_list '}' END_SENTENCE
	;
struct_variable_list:
	struct_variable
	| struct_variable_list struct_variable
	;
struct_variable:
	TYPE_KEYWORD IDENTIFIER END_SENTENCE


directive:
	DEFINE IDENTIFIER
	| DEFINE IDENTIFIER STRING
	| DEFINE IDENTIFIER operation
	;
operation:
	INTEGER
	| IDENTIFIER
	| operation '+' operation
	| operation '-' operation
	| operation '*' operation
	| operation '/' operation
	| '(' operation ')'
	;


%%


void yyerror(char *s) {
	fprintf(stderr, "Error at line %d: %s: %s\n", yylineno, s, yytext);
	return;
}

