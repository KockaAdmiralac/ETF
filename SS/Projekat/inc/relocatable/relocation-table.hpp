#ifndef _RELOCATION_TABLE_HPP
#define _RELOCATION_TABLE_HPP
#include <cstdint>
#include <iostream>
#include <vector>
#include "relocatable/symbol-table.hpp"

enum RelocationType {
    REL_ABS,
    REL_PC,
    REL_ABS_LE
};
struct Relocation {
    uint64_t offset;
    RelocationType type;
    uint64_t symbol;
    int64_t addend;
};
class RelocationTable {
public:
    void addRelocation(uint64_t offset, RelocationType type, uint64_t symbol, int64_t addend);
    void write(std::ostream& file);
    void read(std::istream& file);
    void patch(SymbolTable& oldSymtab, SymbolTable& newSymtab, std::unordered_map<std::string, uint64_t>& offsets);
    void merge(RelocationTable& table, uint64_t offset);
    bool empty() const;
    std::string getName() const;
    RelocationTable(std::string name);
    std::vector<Relocation>::iterator begin();
    std::vector<Relocation>::iterator end();
private:
    std::string name;
    std::vector<Relocation> relocations;
};
#endif
