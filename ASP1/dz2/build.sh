#!/bin/sh
set -e
cd "${0%/*}"
gcc -o dz2 util.c tree.c stack.c input.c options.c main.c
