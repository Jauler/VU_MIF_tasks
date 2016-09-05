/*
##########################################################
# Transliavimo metodai, 2014/2015 m.m. (7 semestras)
# Trečiasis praktinis darbas
# Rytis Karpuška, Donatas Kučinskas, Programų sistemos, 4k., 3 grupė
# Variantas: 111
##########################################################
*/

#ifndef INCLUDE_PARSER_H
#define INCLUDE_PARSER_H

#include <stdlib.h>

#include "common.h"

#define MAX_ARGS 256
#define MAX_DEFINES 1000
#define MAX_FUNCTIONS 4096
#define MAX_LIST_ITEMS 1000

typedef struct Argument {
	VariableType type;
	int id;
	//TODO: default value?
} Argument;


typedef struct {
	int length;
	void *items[MAX_LIST_ITEMS];
} List;


typedef struct {
	int id;
	VariableType returnType;
	List *args;
} Function;


typedef struct {
	VariableType type;
	int id;
} VariableDeclaration;

typedef struct {
	int id;
	List *declarations;
} Struct;


extern int definesCount;
extern int defines[MAX_DEFINES];

extern int functionsCount;
extern Function *functions[MAX_FUNCTIONS];

extern int structsCount;
extern Struct *structs[1000];

#endif
