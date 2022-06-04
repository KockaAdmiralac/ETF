#ifndef _RELOCATABLE_HPP
#define _RELOCATABLE_HPP
#include "relocation-table.hpp"
#include "section.hpp"
#include "symbol-table.hpp"

struct Relocatable {
    SymbolTable symtab;
    std::vector<RelocationTable> relocations;
    std::vector<Section> sections;
    void write(std::ostream& stream);
    void read(std::istream& stream);
    void merge(Relocatable& r);
};
#endif
