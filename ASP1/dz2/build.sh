#!/bin/sh
set -e
cd "${0%/*}"
gcc -Wall -Wextra -g -o dz2 util.c tree.c stack.c queue.c input.c options.c main.c -lm
