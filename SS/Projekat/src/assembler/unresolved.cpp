#include "assembler/context.hpp"
#include "assembler/unresolved.hpp"
#include <stdexcept>

void UnresolvedSymbolTable::addUnresolved(std::string& symbol, std::vector<std::pair<std::string, int>> operands) {
    this->operands[symbol] = operands;
}

bool UnresolvedSymbolTable::resolve(std::string& symbol, Context& context) {
    SymbolTable& symtab = context.r.symtab;
    if (!operands.contains(symbol)) {
        throw std::runtime_error("Symbol cannot be resolved, as it is not unresolved: " + symbol);
    }
    std::vector<std::pair<std::string, int>> operands = this->operands[symbol];
    // Determine whether all symbols in the expression are resolved.
    for (std::pair<std::string, int>& operand : operands) {
        Symbol& sym = symtab.getSymbol(operand.first);
        if (sym.isUndefined() && !sym.isExternal()) {
            return false;
        }
    }
    this->operands.erase(symbol);
    // Determine symbol classification index and evaluate the expression.
    uint64_t nextUniqueSymbol = symtab.size();
    int64_t value = 0;
    std::unordered_map<uint64_t, uint64_t> sectionIndex;
    for (std::pair<std::string, int>& operand : operands) {
        Symbol& sym = symtab.getSymbol(operand.first);
        uint64_t index = sym.isExternal() ? (++nextUniqueSymbol) : sym.index;
        if (operand.second > 0) {
            value += sym.value;
            ++sectionIndex[index];
        } else {
            value -= sym.value;
            --sectionIndex[index];
        }
    }
    bool classified = false;
    uint64_t classificationIndex = 0;
    for (std::pair<const uint64_t, uint64_t>& pair : sectionIndex) {
        if (pair.second != 0) {
            if (classified) {
                throw std::runtime_error("Invalid classification index for symbol " + symbol);
            }
            classified = true;
            classificationIndex = pair.first;
        }
    }
    // Update symbol table.
    Symbol& sym = symtab.getSymbol(symbol);
    sym.flags &= ~Symbol::SYM_UNDEF;
    sym.index = classificationIndex;
    sym.value = value;
    if (classificationIndex == 0) {
        sym.flags |= Symbol::SYM_ABS;
    }
    context.bt.patch(symbol, context);
    return true;
}
