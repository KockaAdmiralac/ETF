#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz3-v2 -std=c++17 nut.cpp namirnica.cpp sastojak.cpp main.cpp
