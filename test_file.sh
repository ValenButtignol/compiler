#!/bin/bash

gcc  -w testRunner.c src/*.c extern/*.c tests/utils/src/*.c -o output/tests.out

input_file=$1
test_type=$2

if [ ! -f "./output/tests.out" ]; then
    echo "Error: Failing compile."
    exit 1
fi



if [ -f "$input_file" ]; then
    # Get the base name of the input file
    echo "$input_file";	
    # Run ./a.out with the input file and save the output to outputs folder
	./output/tests.out "$input_file" "$test_type"
fi

echo "File processed."
