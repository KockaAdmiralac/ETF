#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz2-v2 -std=c++17 obavestenje.cpp objava.cpp lista.cpp korisnik.cpp main.cpp
