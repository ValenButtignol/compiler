#!/bin/bash

gcc -w testRunner.c src/*.c extern/*.c tests/utils/src/*.c -o output/tests.out

if [ ! -f "./output/tests.out" ]; then
    echo "Error: Failing compile."
    exit 1
fi


for input_file in tests/inputs/*; do
	if [ -f "$input_file" ]; then
        # Get the base name of the input file
        echo "$input_file";	
        # Run ./a.out with the input file and save the output to outputs folder
		./output/tests.out "$input_file" "type"
	echo "Processed $base_name"
    fi
done

for input_file in tests/inputs/valid*; do
	if [ -f "$input_file" ]; then
        # Get the base name of the input file
        echo "$input_file";	
        # Run ./a.out with the input file and save the output to outputs folder
		./output/tests.out "$input_file" "eval"
	echo "Processed $base_name"
    fi
done

for input_file in tests/inputs/valid*; do
	if [ -f "$input_file" ]; then
        ./scripts/test_file.sh "$input_file" "assemble"
    fi
    echo "Processed $base_name"
done


echo "All files processed."
