#!/bin/sh
set -e
cd "${0%/*}"
gcc -Wall -Wextra -g -o dz5 dz5_load.c dz5_save.c dz5_process.c dz5.c
