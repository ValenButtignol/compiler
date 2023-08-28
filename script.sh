#!/bin/bash

flex lexer/lexicon.l 
bison -d parser/syntax.y
gcc lex.yy.c syntax.tab.c
./a.out input.txt