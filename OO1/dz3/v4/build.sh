#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz3-v4 -std=c++17 element.cpp generator.cpp main.cpp
