/*
##########################################################
# Transliavimo metodai, 2014/2015 m.m. (7 semestras)
# Antrasis praktinis darbas
# Rytis Karpuška, Donatas Kučinskas, Programų sistemos, 4k., 3 grupė
# Variantas: 111
##########################################################
*/

%{
#include <stdlib.h>
void yyerror(char *);
#include "parser.tab.h"
%}

%option yylineno

/* Basic */
Newline						[\n\r]
Whitespace					[" ""	"]+
Identifier					([a-zA-Z_][a-zA-Z0-9_]+)

/* Comments */
Single_line_comment			(\/\/[^\n]+)
Multi_line_comment			(\/\*+([^\*]|{Newline}|#|(\*+[^*\/]|{Newline}))*\*+\/)
Comment						({Multi_line_comment}|{Single_line_comment})

/* Compiler directives */
Define						"#define"

/* Keywords */
TypeKeyword					"char"|"unsigned char"|"short"|"unsigned short"|"int"|"unsigned int"|"long"|"unsigned long"|"long int"|"unsigned long int"|"long long"|"unsigned long long"|"long long int"|"unsigned long long int"
Struct						"struct"

/* Constants */
Dec							[0-9]+
Hex							0x[0-9a-fA-F]+
Integer						{Dec}|{Hex}
String						\"[^"]\"

/* Operators */
OperatorSignelChar			"("|")"|"{"|"}"|"*"|"/"|"+"|"-"|","
EndSentence					";"


%%
{Comment}					;
{Whitespace}				;
{Newline}					;

{OperatorSignelChar}		return *yytext;
{Integer}					return INTEGER;
{String}					return STRING;
{Struct}					return STRUCT;
{EndSentence}				return END_SENTENCE;
{TypeKeyword}				return TYPE_KEYWORD;
{Identifier}				return IDENTIFIER;
{Define}					return DEFINE;


%%
yywrap()
{
	return 1;
}


