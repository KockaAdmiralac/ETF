A = src/assembler
L = src/linker
E = src/emulator

# Programs
CC = g++
LEXER = flex
PARSER = bison

# Parser flags
PFLAGS = -Wall -Wcounterexamples -d

# Compiler flags
CFLAGS = -Wall -Wextra
ifdef DEBUG
CFLAGS += -ggdb
endif

# Build rules
.PHONY: default
default: assembler

# Assembler files
AFILES =\
	$A/main.cpp \
	$A/cmd.cpp

# Linker files
LFILES =\
	$L/main.cpp \
	$L/cmd.cpp

EFILES =\
	$E/main.cpp

syntax.tab.cpp syntax.tab.hpp: misc/syntax.ypp
	$(PARSER) $(PFLAGS) misc/syntax.ypp

lex.yy.c: misc/syntax.l syntax.tab.hpp
	$(LEXER) misc/syntax.l

syntax: lex.yy.c syntax.tab.cpp syntax.tab.hpp
	$(CC) $(CFLAGS) -DDEBUG_SYNTAX syntax.tab.cpp lex.yy.c -o syntax

assembler: lex.yy.c syntax.tab.cpp syntax.tab.hpp $(AFILES)
	$(CC) $(CFLAGS) syntax.tab.cpp lex.yy.c $(AFILES) -o assembler

linker: $(LFILES)
	$(CC) $(CFLAGS) $(LFILES) -o linker

emulator: $(EFILES)
	$(CC) $(CFLAGS) $(EFILES) -o emulator

clean:
	rm -f lex.yy.c
	rm -f syntax.tab.cpp
	rm -f syntax.tab.hpp
	rm -f syntax
	rm -f assembler
	rm -f linker
	rm -f emulator
