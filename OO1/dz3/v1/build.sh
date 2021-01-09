#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz3-v1 -std=c++17 datum.cpp osoba.cpp racun.cpp main.cpp
