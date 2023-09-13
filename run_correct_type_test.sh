#!/bin/bash

cd extern
flex lexicon.l
bison -d syntax.y
gcc lex.yy.c syntax.tab.c ../src/*.c ../tests/testCheckCorrectTypes.c -w -o ../output/output.out
cd ..
# ./output/output.out input/input.txt

input_files=$(ls ~/Documents/compiler2023/compiler/tests/inputs/correctTypeInput*.txt)
for input_file in $input_files; do
    echo "Input file $input_file"
    ./output/output.out $input_file
done