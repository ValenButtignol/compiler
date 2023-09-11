#!/bin/bash

cd extern
flex lexicon.l
bison -d syntax.y
gcc lex.yy.c syntax.tab.c ../src/*.c -o ../output/output.out
cd ..
./output/output.out input/input.txt