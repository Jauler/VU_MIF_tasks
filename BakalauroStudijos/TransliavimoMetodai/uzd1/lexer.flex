/*
##########################################################
# Transliavimo metodai, 2014/2015 m.m. (7 semestras)
# Pirmasis praktinis darbas
# Rytis Karpuška, Donatas Kučinskas, Programų sistemos, 4k., 3 grupė
# Variantas: 111
##########################################################
*/

/* Basic */
Newline						[\n\r]
Whitespace					[" ""	"]+
Identificator				([a-zA-Z0-9_]+)

/* Comments */
Single_line_comment			(\/\/[^\n]+)
Multi_line_comment			(\/\*+([^\*]|{Newline}|#|(\*+[^*\/]|{Newline}))*\*+\/)
Comment						({Multi_line_comment}|{Single_line_comment})

/* Compiler directives */
CDefine						"#define"
CIf							"#if"
CIfdef						"#ifdef"
CIfndef						"#ifndef"
CElse						"#else"
CEndif						"#endif"
CPragma						"#pragma"
CUndef						"#undef"

/* Keywords */
TChar						"char"
TUnsignedChar				"unsigned char"
TShort						"short"
TUnsignedShort				"unsigned short"
TInt						"int"
TUnsignedInt				"unsigned int"
TLong						"long"
TUnsignedLong				"unsigned long"
TLongInt					"long int"
TUnsignedLongInt			"unsigned long int"
TLongLong					"long long"
TUnsignedLongLon			"unsigned long long"
TLongLongInt				"long long int"
TUnsignedLongLongInt		"unsigned long long int"
TTypedef					"Typedef"
TStruct						"struct"
TUnion						"union"

/* Constants */
Dec							[0-9]+
Hex							0x[0-9a-fA-F]+
String						\"[^"]\"

/* Operators */
OOpen						"("
OClose						")"
OOpenCurly					"{"
OCloseCurly					"}"
OOpenSquare					"["
OCloseSquare				"]"
OMultiply					"*"
ODivide						"/"
OAdd						"+"
OSubtract					"-"
OModulo						"%"
OBitwiseAnd					"&"
OLogicalAnd					"&&"
OBitwiseOr					"|"
OLogicalOr					"||"
OBitwiseNot					"^"
OLogicalNot					"!"
OLeftShift					"<<"
ORightShift					">>"
OLess						"<"
OMore						">"
OEqual						"=="
OLessOrEqual				"<="
OMoreOrEqual				">="
OAssign						"="
OInlineIf					"?"
OInlineElse					":"
OEndSentence				";"
OComma						","
OVaargs						"..."
ODot						"."
OMacroConcat				"##"
OEscape						"\\"

%%
{Comment}					;
{Whitespace}				;
{Newline}					;
{Hex}						printf("c00");
{Dec}						printf("c01");
{String}					printf("c02");

{CDefine}					printf("p00");
{CIf}						printf("p01");
{CIfdef}					printf("p02");
{CIfndef}					printf("p03");
{CElse}						printf("p04");
{CEndif}					printf("p05");
{CPragma}					printf("p06");
{CUndef}					printf("p07");

{TChar}						printf("t00");
{TUnsignedChar}				printf("t01");
{TShort}					printf("t02");
{TUnsignedShort}			printf("t03");
{TInt}						printf("t04");
{TUnsignedInt}				printf("t05");
{TLong}						printf("t06");
{TUnsignedLong}				printf("t07");
{TLongInt}					printf("t08");
{TUnsignedLongInt}			printf("t09");
{TLongLong}					printf("t10");
{TUnsignedLongLon}			printf("t11");
{TLongLongInt}				printf("t12");
{TUnsignedLongLongInt}		printf("t13");
{TTypedef}					printf("t14");
{TStruct}					printf("t15");
{TUnion}					printf("t16");

{OOpen}						printf("o00");
{OClose}					printf("o01");
{OOpenCurly}				printf("o02");
{OCloseCurly}				printf("o03");
{OOpenSquare}				printf("o04");
{OCloseSquare}				printf("o05");
{OMultiply}					printf("o06");
{ODivide}					printf("o07");
{OAdd}						printf("o08");
{OSubtract}					printf("o09");
{OModulo}					printf("o10");
{OBitwiseAnd}				printf("o11");
{OLogicalAnd}				printf("o12");
{OBitwiseOr}				printf("o13");
{OLogicalOr}				printf("o14");
{OBitwiseNot}				printf("o15");
{OLogicalNot}				printf("o16");
{OLeftShift}				printf("o17");
{ORightShift}				printf("o18");
{OLess}						printf("o19");
{OMore}						printf("o20");
{OEqual}					printf("o21");
{OLessOrEqual}				printf("o22");
{OMoreOrEqual}				printf("o23");
{OAssign}					printf("o24");
{OInlineIf}					printf("o25");
{OInlineElse}				printf("o26");
{OEndSentence}				printf("o27");
{OComma}					printf("o28");
{OVaargs}					printf("o29");
{ODot}						printf("o30");
{OMacroConcat}				printf("o31");
{OEscape}					printf("o32");

{Identificator}				printf("i00");
%%
yywrap()
{
	return 1;
}

