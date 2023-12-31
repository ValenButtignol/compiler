#!/bin/bash

gcc  -w testsMain.c src/*/*.c parser/*.c tests/utils/src/*.c -o tests/output/tests.out

input_file=$1
test_type=$2

if [ ! -f "./tests/output/tests.out" ]; then
    echo "Error: Failing compile."
    exit 1
fi

if [ -f "$input_file" ]; then
    if [ "$test_type" = "assemble" ]; then
        make compile_test OUTFILE=tests/output/out.txt IN_FILE="$input_file"
        # Run ./a.out with the input file and save the output to outputs folder
        ./tests/output/tests.out "$input_file" "$test_type"
        # rm out.txt
    else
        # Get the base name of the input file
        # Run ./a.out with the input file and save the output to outputs folder
        ./tests/output/tests.out "$input_file" "$test_type"
    fi
fi

echo "File processed."
