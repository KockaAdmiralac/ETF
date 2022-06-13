#!/bin/bash

if [ "$#" -lt 2 ]
then
    echo "Must specify at least one input file and an output file."
    exit 1
fi

./tests/build.sh "$@" || exit 1
./emulator "$1.hex" || exit 1
