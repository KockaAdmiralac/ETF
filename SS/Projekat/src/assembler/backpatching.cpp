#include "assembler/backpatching.hpp"
#include "assembler/context.hpp"

void BackpatchingTable::addPatch(std::string& symbol, uint64_t section, uint64_t offset, RelocationType relType) {
    symbols[symbol].push_back({section, offset, relType});
}

void BackpatchingTable::patch(std::string& symbol, Context& context) {
    for (Patch& p : symbols[symbol]) {
        Symbol& sym = context.r.symtab.getSymbol(symbol);
        if (sym.isUndefined()) {
            throw std::runtime_error("Tried to apply patches for an undefined symbol: " + sym.symbol);
        }
        if (sym.isAbsolute()) {
            context.r.sections[p.section].contents[p.offset] = ((sym.value & 0xFF00) >> 8);
            context.r.sections[p.section].contents[p.offset + 1] = sym.value & 0xFF;
        } else {
            int64_t addend;
            uint64_t symbolIndex;
            if (sym.isGlobal()) {
                addend = 0;
                symbolIndex = context.r.symtab.getSymbolIndex(symbol);
            } else {
                addend = sym.value;
                symbolIndex = sym.index;
            }
            if (p.relType == REL_PC) {
                addend -= 2;
            }
            context.r.relocations[p.section].addRelocation(p.offset, p.relType, symbolIndex, addend);
        }
    }
    symbols.erase(symbol);
}

bool BackpatchingTable::empty() const {
    return symbols.empty();
}
