#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz2-v3 -std=c++17 datum.cpp kvar.cpp garancija.cpp uredjaj.cpp klima.cpp main.cpp
