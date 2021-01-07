#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz3 -std=c++17 dictionary.cpp keyboard.cpp main.cpp
