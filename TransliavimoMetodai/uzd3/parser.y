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
#include <stdio.h>

#include "common.h"
#include "parser.h"


int yylineno;
char *yytext;
int yylex(void);
void yyerror(char *);



//Identifiers
int identifiers_count;
char *identifiers[10000];
int idValueExists[MAX_IDENTIFIERS];
Define idValue[MAX_IDENTIFIERS];


Define getIdentifierValue(int id) {
	if (id < 0 || id >= identifiers_count)
		yyerror("Unknown identifier id\n");
	if (idValueExists[id]) {
		return idValue[id];
	}
	yyerror("Trying to use variable without setting value.");
}

int getIdentifierIntValue(int id) {
	Define val = getIdentifierValue(id);
	if (val.type != DEFINE_INT) {
		yyerror("Incompatible type.");
	}
	return val.value.iValue;
}

nodeType *getConst(int value) {
	nodeType *c = malloc(sizeof(conNodeType));
	if (c == NULL)
		yyerror("Out of memory.");
	c->type = typeCon;
	c->con.value = value;
	return c;
}



//Defines
int definesCount = 0;
int defines[MAX_DEFINES];

//Structs
int structsCount = 0;
Struct *structs[1000];


void addDefine(int id) {
	if (!idValueExists[id])
		defines[definesCount++] = id;
	idValueExists[id] = 1;
}

void defineString(int id, char *value) {
	addDefine(id);
	idValue[id].type = DEFINE_STRING;
	idValue[id].value.str = value;
}

void defineInt(int id, int value) {
	addDefine(id);
	idValue[id].type = DEFINE_INT;
	idValue[id].value.iValue = value;
}

void defineTrue(int id) {
	addDefine(id);
	idValue[id].type = DEFINE_TRUE;
}


void addStruct(Struct *s) {
	structs[structsCount++] = s;
}

//Functions
int functionsCount;
Function *functions[MAX_FUNCTIONS];


List *createList() {
	List *list = malloc(sizeof(List));
	list->length = 0;
	return list;
}

void addItem(List *list, void *item) {
	list->items[list->length++] = item;
}

Argument *makeArgument(VariableType type, int id) {
	Argument *arg = malloc(sizeof(Argument));
	if (arg == NULL) {
		yyerror("Out of memory.");
	}
	arg->type = type;
	arg->id = id;
	return arg;
}


int makeOperation(int first, OperationOperator operation, int second) {
	if (operation == OP_ADD)
		return first + second;
	if (operation == OP_SUB)
		return first - second;
	if (operation == OP_MUL)
		return first * second;
		return first / second;

}

%}

%code requires {
	#include "common.h"
	#include "parser.h"
}

%union {
	int iValue;//constant
	char *strValue;//string constant
	int id;//identifier
	char *vType;//type keyword

	List *list;
	Argument *arg;
	VariableDeclaration *vDeclaration;

	OperationOperator opOperator;
};

%token <id> IDENTIFIER
%token <vType> TYPE_KEYWORD
%token <opOperator>OPERATION_OPERATOR
%token END_SENTENCE
%token OPERATOR
%token STRUCT
%token DEFINE
%token IFNDEF
%token <iValue> INTEGER
%token <strValue> STRING
%left '+' '-'
%left '*' '/'

%type <arg> argument
%type <list> argument_list
%type <list> arguments

%type <iValue> operation
%type <vDeclaration> struct_variable
%type <list> struct_variable_list

%%

program: program_parts

program_parts:
	program_parts variable
	| program_parts function
	| program_parts struct
	| program_parts directive
	|
	;


variable:
	TYPE_KEYWORD IDENTIFIER END_SENTENCE
	;


function:
	TYPE_KEYWORD IDENTIFIER argument_list END_SENTENCE
	{
		Function *f = malloc(sizeof(Function));
		f->returnType = $1;
		f->id = $2;
		f->args = $3;
		functions[functionsCount++] = f;
	}
	;
argument_list:
	'('')' { $$ = createList(); }
	| '(' arguments ')' { $$ = $2; }
	;
arguments:
	argument
	{
		List *args = createList();
		addItem(args, $1);
		$$ = args;
	}
	| arguments ',' argument
	{
		addItem($1, $3);
		$$ = $1;
	}
	;
argument:
	TYPE_KEYWORD IDENTIFIER
	{
		$$ = makeArgument($1, $2);
	}
	| TYPE_KEYWORD
	{
		$$ = makeArgument($1, -1);
	}
	| STRUCT IDENTIFIER IDENTIFIER
	{
	}
	;


struct:
	STRUCT IDENTIFIER '{' struct_variable_list '}' END_SENTENCE
	{
		Struct *s = malloc(sizeof(Struct));
		s->id = $2;
		s->declarations = $4;
		addStruct(s);
	}
	;
struct_variable_list:
	struct_variable
	{
		List *list = createList();
		addItem(list, $1);
		$$ = list;
	}
	| struct_variable_list struct_variable
	{
		addItem($1, $2);
		$$ = $1;
	}
	;
struct_variable:
	TYPE_KEYWORD IDENTIFIER END_SENTENCE
	{
		VariableDeclaration *var = malloc(sizeof(VariableDeclaration));
		var->type = $1;
		var->id = $2;
		$$ = var;
	}


directive:
	DEFINE IDENTIFIER
	| DEFINE IDENTIFIER STRING
	{
		defineString($2, $3);
	}
	| DEFINE IDENTIFIER operation
	{
		defineInt($2, $3);
	}
	| IFNDEF IDENTIFIER
	;
operation:
	INTEGER
	| IDENTIFIER { $$ = getIdentifierIntValue($1); }
	| operation OPERATION_OPERATOR operation { $$ = makeOperation($1, $2, $3); }
	| '(' operation ')' { $$ = $2; }
	;


%%


void yyerror(char *s) {
	fprintf(stderr, "Error at line %d: %s: %s\n", yylineno, s, yytext);
	return;
}

