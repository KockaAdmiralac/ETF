#include <stdexcept>
#include "relocatable/file-utils.hpp"
#include "relocatable/symbol-table.hpp"

bool Symbol::isUndefined() {
    return flags & SYM_UNDEF;
}

bool Symbol::isGlobal() {
    return (flags & SYM_GLOBAL) && !(flags & SYM_NONGLOBAL);
}

bool Symbol::isSymbol() {
    return flags & SYM_ISSYM;
}

bool Symbol::isExternal() {
    return flags & SYM_EXTERN;
}

bool Symbol::isAbsolute() {
    return flags & SYM_ABS;
}

Symbol::Symbol(std::string symbol, const uint8_t flags, uint64_t index, uint64_t size, int64_t value) :
    symbol(symbol), value(value), flags(flags), index(index), size(size) {}

SymbolTable::SymbolTable() {
    symbols.push_back({"", Symbol::SYM_UNDEF | Symbol::SYM_ISSYM, 0, 0, 0});
}

uint64_t SymbolTable::size() {
    return symbols.size();
}

uint64_t SymbolTable::addSymbol(Symbol& symbol) {
    if (hasSymbol(symbol.symbol)) {
        throw std::runtime_error("Duplicate symbol: " + symbol.symbol);
    }
    indices[symbol.symbol] = symbols.size();
    symbols.push_back(symbol);
    return indices[symbol.symbol];
}

bool SymbolTable::hasSymbol(const std::string& symbol) {
    return indices.find(symbol) != indices.end();
}

Symbol& SymbolTable::getSymbol(const std::string& symbol) {
    if (!hasSymbol(symbol)) {
        throw std::runtime_error("Unknown symbol: " + symbol);
    }
    return symbols[indices[symbol]];
}

Symbol& SymbolTable::getSymbol(uint64_t symbol) {
    return symbols[symbol];
}

uint64_t SymbolTable::getSymbolIndex(const std::string& symbol) {
    return indices[symbol];
}

void SymbolTable::write(std::ostream& stream) {
    std::string sectionName = ".symtab";
    writeString(stream, sectionName);
    relocWrite(stream, symbols.size());
    for (Symbol& symbol : symbols) {
        writeString(stream, symbol.symbol);
        relocWrite(stream, symbol.value);
        relocWrite(stream, symbol.flags);
        relocWrite(stream, symbol.index);
        relocWrite(stream, symbol.size);
    }
}

void SymbolTable::read(std::istream& stream) {
    // Remove duplicate undefined marker symbol.
    symbols.clear();
    std::size_t size = relocRead<std::size_t>(stream);
    for (uint64_t index = 0; index < size; ++index) {
        std::string symbol = readString(stream);
        int64_t value = relocRead<int64_t>(stream);
        uint8_t flags = relocRead<uint8_t>(stream);
        uint64_t ind = relocRead<uint64_t>(stream);
        uint64_t size = relocRead<uint64_t>(stream);
        symbols.push_back({symbol, flags, ind, size, value});
        indices[symbol] = index;
    }
}

void SymbolTable::merge(SymbolTable& symtab, std::unordered_map<std::string, uint64_t>& offsets, std::string& filename) {
    std::vector<std::string> symbolsToPatch;
    std::unordered_map<uint64_t, uint64_t> sectionMap;
    for (Symbol& sym : symtab.symbols) {
        if (!sym.isGlobal() && sym.isSymbol()) {
            // Local symbol, rename it so it definitely gets inserted
            // as a new symbol.
            if (sym.symbol == "") {
                continue;
            }
            sym.symbol = filename + "+" + sym.symbol;
        }
        if (hasSymbol(sym.symbol)) {
            // Merging two symbols
            Symbol& oldSym = getSymbol(sym.symbol);
            if (sym.isSymbol() && oldSym.isSymbol()) {
                if (!sym.isUndefined() && !oldSym.isUndefined()) {
                    throw std::runtime_error("Duplicate definition of symbol: " + sym.symbol);
                }
                if (sym.isUndefined()) {
                    // New symbol is already defined
                    continue;
                }
                if (oldSym.isUndefined()) {
                    oldSym.flags = sym.flags;
                    oldSym.value = sym.value;
                    // Will be inaccurate
                    oldSym.index = sym.index;
                    if (!oldSym.isAbsolute()) {
                        symbolsToPatch.push_back(oldSym.symbol);
                    }
                }
                // The symbol can also remain undefined
            } else if (!sym.isSymbol() && !oldSym.isSymbol()) {
                sectionMap[sym.index] = oldSym.index;
            } else if (oldSym.isUndefined()) {
                oldSym.flags = sym.flags;
                // Will be inaccurate
                oldSym.index = sym.index;
                symbolsToPatch.push_back(oldSym.symbol);
            } else if (!sym.isUndefined()) {
                throw std::runtime_error("Duplicate definition of symbol with different types: " + sym.symbol);
            }
        } else {
            uint64_t newIndex = addSymbol(sym);
            if (!sym.isSymbol()) {
                sectionMap[sym.index] = newIndex;
            }
            if (!sym.isAbsolute() && !sym.isUndefined()) {
                symbolsToPatch.push_back(sym.symbol);
            }
        }
    }
    for (std::string& sym : symbolsToPatch) {
        Symbol& symbol = getSymbol(sym);
        symbol.index = sectionMap[symbol.index];
        symbol.value += offsets[getSymbol(symbol.index).symbol.substr(1)];
    }
}

std::vector<Symbol>::iterator SymbolTable::begin() {
    return symbols.begin();
}

std::vector<Symbol>::iterator SymbolTable::end() {
    return symbols.end();
}
