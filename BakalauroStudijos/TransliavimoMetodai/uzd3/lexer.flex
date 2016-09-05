/*
##########################################################
# Transliavimo metodai, 2014/2015 m.m. (7 semestras)
# Trečiasis praktinis darbas
# Rytis Karpuška, Donatas Kučinskas, Programų sistemos, 4k., 3 grupė
# Variantas: 111
##########################################################
*/

%{
#include <stdlib.h>

#include "parser.tab.h"
#include "common.h"

void yyerror(char *);

int parseInt(char *a, int length) {
	if (length > 2 && a[0] == '0' && a[1] == 'x') {
		//hex
		int value = 0;
		int i;
		for (i = 2; i < length; ++i) {
			int curr;
			char c = a[i];
			if (c >= 'A' && c <= 'F')
				curr = c - 'A' + 10;
			else if (c >= '0' && c <= '9')
				curr = c - '0';
			else
				return 0;
			value *= 16;
			value += curr;
		}
		return value;
	}
	else {
		//dec
		return atoi(a);
	}
}

char *copyString(char *string, int length) {
	char *copy = malloc(length);
	if (copy == NULL)
		yyerror("Out of memory.");
	strncpy(copy, string, length);
	return copy;
}


int getIdentifierId(char *identifier, int length) {
	int index;
	for (index = 0; index < identifiers_count; ++index) {
		if (!strcmp(identifiers[index], identifier)) {
			break;
		}
	}
	if (index == identifiers_count) {
		identifiers[identifiers_count++] = copyString(identifier, length);
	}
	return index;
}


VariableType parseVariableType(char *s, int length) {
	return copyString(s, length);
}

OperationOperator parseOperationOperator(char operation) {
	if (operation == '+')
		return OP_ADD;
	if (operation == '-')
		return OP_SUB;
	if (operation == '*')
		return OP_MUL;
	return OP_DIV;
}

%}

%option yylineno

/* Basic */
Newline						[\n\r]
Whitespace					[ 	]+
Identifier					([a-zA-Z_][a-zA-Z0-9_]+)

/* Comments */
Single_line_comment			(\/\/[^\n]+)
Multi_line_comment			(\/\*+([^\*]|{Newline}|#|(\*+[^*\/]|{Newline}))*\*+\/)
Comment						({Multi_line_comment}|{Single_line_comment})

/* Compiler directives */
Define						"#define"
IfNDef						"#ifndef"
EndIf						"#endif"

/* Keywords */
TypeKeyword					"char"|"unsigned char"|"short"|"unsigned short"|"int"|"unsigned int"|"long"|"unsigned long"|"long int"|"unsigned long int"|"long long"|"unsigned long long"|"long long int"|"unsigned long long int"
Struct						"struct"

/* Constants */
Dec							[0-9]+
Hex							0x[0-9a-fA-F]+
Integer						{Dec}|{Hex}
String						\"[^\"]*\"

/* Operators */
OperationOperator			"*"|"/"|"+"|"-"
OtherOperator				"("|")"|"{"|"}"|","
EndSentence					";"


%%
{Comment}					;
{Whitespace}				;
{Newline}					;

{OperationOperator}			{
								yylval.opOperator = parseOperationOperator(yytext[0]);
								return OPERATION_OPERATOR;
							}
{OtherOperator}				return *yytext;
{Integer}					{
								yylval.iValue = parseInt(yytext, yyleng);
								return INTEGER;
							}
{String}					{
	yylval.strValue = copyString(yytext+1, yyleng-2);
	return STRING;
}
{Struct}					return STRUCT;
{EndSentence}				return END_SENTENCE;
{TypeKeyword}				{
								yylval.vType = parseVariableType(yytext, yyleng);
								return TYPE_KEYWORD;
							}
{Identifier}				{
								yylval.id = getIdentifierId(yytext, yyleng);
								return IDENTIFIER;
							}
{Define}					return DEFINE;

{IfNDef}					return IFNDEF;

%%
int yywrap()
{
	return 1;
}


