#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz2-v2 obavestenje.cpp lista.cpp korisnik.cpp main.cpp
