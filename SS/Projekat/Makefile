A = src/assembler
L = src/linker
E = src/emulator

# Programs
CC = g++
LEXER = flex
PARSER = bison

# Parser flags
PFLAGS = -Wall -d

# Compiler flags
CFLAGS = -Wall -Wextra -Iinc -I. -std=c++17
ifdef DEBUG
CFLAGS += -ggdb -DDEBUG -O0
endif

# Build rules
.PHONY: default
default: assembler linker emulator objdump

syntax.tab.cpp syntax.tab.hpp: misc/syntax.ypp
	$(PARSER) $(PFLAGS) misc/syntax.ypp

lex.yy.c: misc/syntax.l syntax.tab.hpp
	$(LEXER) misc/syntax.l

syntax: lex.yy.c syntax.tab.cpp syntax.tab.hpp
	$(CC) $(CFLAGS) -DDEBUG_SYNTAX syntax.tab.cpp lex.yy.c -o syntax

assembler: lex.yy.c syntax.tab.cpp syntax.tab.hpp src/assembler/*.cpp src/relocatable/*.cpp
	$(CC) $(CFLAGS) syntax.tab.cpp lex.yy.c src/assembler/*.cpp src/relocatable/*.cpp -o assembler

linker: src/linker/*.cpp src/relocatable/*.cpp src/hex/*.cpp
	$(CC) $(CFLAGS) src/linker/*.cpp src/relocatable/*.cpp src/hex/*.cpp -o linker

emulator: src/emulator/*.cpp src/hex/*.cpp
	$(CC) $(CFLAGS) src/emulator/*.cpp src/hex/*.cpp -o emulator

objdump: src/objdump/*.cpp src/relocatable/*.cpp
	$(CC) $(CFLAGS) src/objdump/*.cpp src/relocatable/*.cpp -o objdump

clean:
	rm -f lex.yy.c
	rm -f syntax.tab.cpp
	rm -f syntax.tab.hpp
	rm -f syntax
	rm -f assembler
	rm -f linker
	rm -f emulator
	rm -f objdump
