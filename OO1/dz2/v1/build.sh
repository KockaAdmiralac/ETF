#!/bin/sh
set -e
cd "${0%/*}"
g++ -Wall -Wextra -g -o dz2-v1 slika.cpp pozicija.cpp piksel.cpp crnobela.cpp main.cpp
