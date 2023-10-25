#!/bin/bash

gcc -w testRunner.c src/*.c extern/*.c tests/utils/src/*.c -o output/tests.out

if [ ! -f "./output/tests.out" ]; then
    echo "Error: Failing compile."
    exit 1
fi


for input_file in tests/inputs/checkAssembly*; do
	if [ -f "$input_file" ]; then
        ./scripts/test_file.sh "$input_file" "assemble"
    fi
    echo "Processed $base_name"
done


echo "All files processed."
