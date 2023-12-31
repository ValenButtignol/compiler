#!/bin/bash

gcc -w testsMain.c src/*/*.c parser/*.c tests/utils/src/*.c -o output/tests.out

if [ ! -f "./output/tests.out" ]; then
    echo "Error: Failing compile."
    exit 1
fi


for input_file in tests/inputs/checkTypes/*; do
	if [ -f "$input_file" ]; then
        # Get the base name of the input file
        echo "$input_file";	
        # Run ./a.out with the input file and save the output to outputs folder
		./output/tests.out "$input_file" "type"
	echo "Processed $base_name"
    fi
done

echo "All files processed."
