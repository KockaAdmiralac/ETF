#!/bin/sh
set -e
cd "${0%/*}"
gcc -Wall -Wextra -g -o dz3 util.c graph.c input.c options.c main.c
