#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz3-v3 -std=c++17 igrac.cpp tim.cpp privilegovani.cpp mec.cpp main.cpp
