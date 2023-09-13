#!/bin/bash

cd extern
flex lexicon.l
bison -d syntax.y
gcc lex.yy.c syntax.tab.c ../src/*.c ../tests/testCheckIncorrectTypes.c -w -o ../output/output.out
cd ..
# ./output/output.out input/input.txt

input_files=$(ls ~/Documents/compiler2023/compiler/tests/inputs/incorrectTypeInput*.txt)
for input_file in $input_files; do
    echo -e "\033[1;34m--------------------------------------------------------------------------------------------------\033[0m"
    echo -e "Input file \033[1;35m$input_file\033[0m"
    ./output/output.out $input_file
done