#!/bin/bash

cd extern
flex lexicon.l
bison -d syntax.y
gcc lex.yy.c syntax.tab.c ../src/*.c
./a.out input.txt
cd ..