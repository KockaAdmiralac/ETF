#ifndef _CONTEXT_HPP
#define _CONTEXT_HPP
#include <cstdint>
#include "relocatable/relocatable.hpp"
#include "assembler/backpatching.hpp"
#include "assembler/unresolved.hpp"

struct Context {
    uint64_t sectionIndex = 0;
    Relocatable r;
    BackpatchingTable bt;
    UnresolvedSymbolTable ust;
    bool theEnd = false;
    void addSymbol(std::string& symbol, int64_t value, uint8_t flags = Symbol::SYM_ISSYM);
    void addLabel(std::string& symbol);
    void addSection(std::string& section);
    void addData(int64_t data);
    void write(std::string& filename);
    Section& currentSection();
    RelocationTable& currentRelocationTable();
    uint64_t locationCounter();
    int64_t resolveSymbol(std::string& symbol, RelocationType relType = REL_ABS);
};
#endif
