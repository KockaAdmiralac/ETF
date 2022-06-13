#include <fstream>
#include <sstream>
#include <stdexcept>
#include "assembler/context.hpp"

void Context::addSymbol(std::string& symbol, int64_t value, uint8_t flags) {
    flags |= Symbol::SYM_ISSYM;
    Symbol sym(symbol, flags, sectionIndex, 0, value);
    if (sym.isAbsolute() || sym.isUndefined()) {
        sym.index = 0;
    }
    r.symtab.addSymbol(sym);
    ust.resolveAll(*this);
}

void Context::addLabel(std::string& label) {
    if (r.symtab.hasSymbol(label)) {
        Symbol& sym = r.symtab.getSymbol(label);
        if (sym.isUndefined() && sym.isSymbol()) {
            sym.flags &= ~(Symbol::SYM_UNDEF | Symbol::SYM_EXTERN);
            sym.value = locationCounter();
            sym.index = sectionIndex;
            bt.patch(label, *this);
            ust.resolveAll(*this);
        } else {
            throw std::runtime_error("Label " + label + " duplicates another symbol.");
        }
    } else {
        addSymbol(label, locationCounter());
    }
}

void Context::addSection(std::string& section) {
    std::string sectionSymbol = "." + section;
    if (r.symtab.hasSymbol(sectionSymbol)) {
        Symbol& sym = r.symtab.getSymbol(sectionSymbol);
        if (!sym.isUndefined()) {
            throw std::runtime_error("Section " + sectionSymbol + " duplicates another symbol.");
        }
        sym.flags = 0;
        sym.index = r.symtab.getSymbolIndex(sectionSymbol);
        bt.patch(sectionSymbol, *this);
        ust.resolveAll(*this);
    } else {
        Symbol sec(sectionSymbol, 0, r.symtab.size(), 0, 0);
        sectionIndex = r.symtab.addSymbol(sec);
        ust.resolveAll(*this);
    }
    r.sections.push_back({section});
    r.relocations.push_back({section});
}

void Context::addData(int64_t data, bool invert) {
    if (!invert) {
        currentSection().contents.push_back((data & 0xFF00) >> 8);
    }
    currentSection().contents.push_back(data & 0xFF);
    if (invert) {
        currentSection().contents.push_back((data & 0xFF00) >> 8);
    }
}

void Context::write(std::string& filename) {
    if (!bt.empty()) {
        std::stringstream errorStream;
        errorStream << "There are unapplied patches in the backpatching table:";
        for (std::string patch : bt.getPendingPatches()) {
            errorStream << std::endl << "- " << patch;
        }
        throw std::runtime_error(errorStream.str());
    }
    if (!ust.empty()) {
        std::stringstream errorStream;
        errorStream << "There are unresolved symbols in the unresolved symbol table:";
        for (std::string symbol : ust.getPendingSymbols()) {
            errorStream << std::endl << "- " << symbol;
        }
        throw std::runtime_error(errorStream.str());
    }
    std::ofstream file(filename, std::ios::binary);
    if (file.fail()) {
        throw std::runtime_error("Failed to open output file: " + filename);
    }
    r.write(file);
}

Section& Context::currentSection() {
    if (r.sections.empty()) {
        throw std::runtime_error("currentSection() called with no current section!");
    }
    return r.sections[r.sections.size() - 1];
}

RelocationTable& Context::currentRelocationTable() {
    if (r.relocations.empty()) {
        throw std::runtime_error("currentRelocationTable() called with no current relocation table!");
    }
    return r.relocations[r.relocations.size() - 1];
}

uint64_t Context::locationCounter() {
    if (r.sections.empty()) {
        return 0;
    }
    return currentSection().contents.size();
}

int64_t Context::resolveSymbol(std::string& symbol, RelocationType relType) {
    if (!r.symtab.hasSymbol(symbol)) {
        addSymbol(symbol, 0, Symbol::SYM_UNDEF);
    }
    Symbol& sym = r.symtab.getSymbol(symbol);
    if (sym.isUndefined() && !sym.isExternal()) {
        bt.addPatch(symbol, r.sections.size() - 1, locationCounter(), relType);
        return 0;
    }
    if (sym.isAbsolute()) {
        return sym.value;
    }
    int64_t addend;
    uint64_t symbolIndex;
    if (sym.isGlobal()) {
        addend = 0;
        symbolIndex = r.symtab.getSymbolIndex(symbol);
    } else {
        addend = sym.value;
        symbolIndex = sym.index;
    }
    if (relType == REL_PC) {
        addend -= 2;
    }
    currentRelocationTable().addRelocation(locationCounter(), relType, symbolIndex, addend);
    return 0;
}