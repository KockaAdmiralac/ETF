#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz3-v5 -std=c++17 destinacija.cpp smestaj.cpp datum.cpp aranzman.cpp main.cpp
