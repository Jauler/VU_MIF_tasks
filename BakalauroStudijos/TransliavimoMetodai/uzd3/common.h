/*
##########################################################
# Transliavimo metodai, 2014/2015 m.m. (7 semestras)
# Trečiasis praktinis darbas
# Rytis Karpuška, Donatas Kučinskas, Programų sistemos, 4k., 3 grupė
# Variantas: 111
##########################################################
*/

#ifndef INCLUDE_COMMON_H
#define INCLUDE_COMMON_H

#include <stdio.h>

#define MAX_IDENTIFIERS 10000


extern FILE *yyin;
extern FILE *yyout;

typedef enum {
	DEFINE_TRUE,
	DEFINE_STRING,
	DEFINE_INT
} defineType;

typedef union {
	int iValue;
	char *str;
} defineValue;

typedef struct {
	defineType type;
	defineValue value;
} Define;

typedef enum {
	typeCon,
	typeId
} nodeEnum;

//constants
typedef struct {
	nodeEnum type;
	int value;
} conNodeType;

//variable declarations
typedef struct {
	nodeEnum type;
	int id;
} idNodeType;

typedef enum {
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV
} OperationOperator;

typedef char* VariableType;

typedef union nodeTypeTag {
	nodeEnum type;
	conNodeType con;
	idNodeType id;
} nodeType;

typedef struct {
	int isSet;
	char *name;
	Define value;
} Variable;

extern int identifiers_count;
//extern Variable *variables[MAX_IDENTIFIERS];
extern char *identifiers[MAX_IDENTIFIERS];
extern int idValueExists[MAX_IDENTIFIERS];
extern Define idValue[MAX_IDENTIFIERS];


#endif
