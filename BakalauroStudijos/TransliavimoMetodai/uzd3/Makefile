########################################################
# Transliavimo metodai, 2014/2015 m.m. (7 semestras)
# Trečiasis praktinis darbas
# Rytis Karpuška, Donatas Kučinskas, Programų sistemos, 4k., 3 grupė
# Variantas: 111
########################################################
parser: lexer.yy.c parser.tab.c main.c
	gcc -o parser lexer.yy.c parser.tab.c main.c

lexer.yy.c: lexer.flex parse.tab.h common.h
	flex -o lexer.yy.c lexer.flex

parse.tab.h: parser.y common.h
	bison -d parser.y


