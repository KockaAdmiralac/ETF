#include <cstring>
#include <iostream>
#include "relocatable/file-utils.hpp"
#include "relocatable/relocation-table.hpp"

RelocationTable::RelocationTable(std::string name) : name(name) {}

void RelocationTable::addRelocation(uint64_t offset, RelocationType type, uint64_t symbol, int64_t addend) {
    // Valgrind complains about uninitialized bytes here
    Relocation r;
    memset(&r, 0, sizeof(Relocation));
    r = {offset, type, symbol, addend};
    relocations.push_back(r);
}

void RelocationTable::write(std::ostream& file) {
    std::string sectionName = ".rela." + name;
    writeString(file, sectionName);
    writeVector(file, relocations);
}

void RelocationTable::read(std::istream& file) {
    // Name has already been read
    readVector(file, relocations);
}

void RelocationTable::patch(SymbolTable& oldSymtab, SymbolTable& newSymtab, std::unordered_map<std::string, uint64_t>& offsets) {
    for (Relocation& r : relocations) {
        r.symbol = newSymtab.getSymbolIndex(oldSymtab.getSymbol(r.symbol).symbol);
        Symbol& sym = newSymtab.getSymbol(r.symbol);
        if (!sym.isSymbol()) {
            r.addend += offsets[sym.symbol.substr(1)];
        }
    }
}

void RelocationTable::merge(RelocationTable& table, uint64_t offset) {
    for (Relocation& r : table.relocations) {
        r.offset += offset;
        relocations.push_back(r);
    }
}

bool RelocationTable::empty() const {
    return relocations.empty();
}

std::string RelocationTable::getName() const {
    return name;
}

std::vector<Relocation>::iterator RelocationTable::begin() {
    return relocations.begin();
}

std::vector<Relocation>::iterator RelocationTable::end() {
    return relocations.end();
}
