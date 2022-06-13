#!/bin/bash

if [ "$#" -lt 2 ]
then
    echo "Must specify at least one input file and an output file."
    exit 1
fi

program_name="$1.hex"
shift
arr=()
for test in "$@"
do
    ./assembler -o "$test.o" "tests/$test.s" || exit 1
    arr+=("$test.o")
done
./linker -hex -place=ivt@0x0000 -o "$program_name" "${arr[@]}" || exit 1
# ./linker -relocatable -o "$program_name.o" "${arr[@]}"