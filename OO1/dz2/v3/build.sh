#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz2-v3 datum.cpp kvar.cpp garancija.cpp uredjaj.cpp klima.cpp main.cpp
