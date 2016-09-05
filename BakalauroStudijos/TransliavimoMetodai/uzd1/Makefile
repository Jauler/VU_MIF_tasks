########################################################
# Transliavimo metodai, 2014/2015 m.m. (7 semestras)
# Pirmasis praktinis darbas
# Rytis Karpuška, Donatas Kučinskas, Programų sistemos, 4k., 3 grupė
# Variantas: 111
########################################################
lexer: lexer.yy.c
	gcc -o lexer -lfl lexer.yy.c

lexer.yy.c: lexer.flex
	flex -o lexer.yy.c lexer.flex
