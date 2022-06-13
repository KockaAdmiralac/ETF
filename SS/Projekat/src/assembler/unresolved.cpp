#include <algorithm>
#include "assembler/context.hpp"
#include "assembler/unresolved.hpp"
#include <stdexcept>

void UnresolvedSymbolTable::addUnresolved(std::string& symbol, std::vector<std::pair<std::string, int>> operands) {
    this->operands[symbol] = operands;
}

bool UnresolvedSymbolTable::resolve(const std::string& symbol, Context& context) {
    SymbolTable& symtab = context.r.symtab;
    if (operands.find(symbol) == operands.end()) {
        throw std::runtime_error("Symbol cannot be resolved, as it is not unresolved: " + symbol);
    }
    std::vector<std::pair<std::string, int>> operands = this->operands[symbol];
    // Determine whether all symbols in the expression are resolved.
    for (std::pair<std::string, int>& operand : operands) {
        if (operand.first == "") {
            continue;
        }
        if (!symtab.hasSymbol(operand.first)) {
            return false;
        }
        Symbol& sym = symtab.getSymbol(operand.first);
        if (sym.isUndefined() && !sym.isExternal()) {
            return false;
        }
    }
    this->operands.erase(symbol);
    // Determine symbol classification index and evaluate the expression.
    int64_t value = 0;
    std::unordered_map<uint64_t, uint64_t> sectionIndex;
    for (std::pair<std::string, int>& operand : operands) {
        if (operand.first == "") {
            value += operand.second;
        } else {
            Symbol& sym = symtab.getSymbol(operand.first);
            uint64_t index = sym.isExternal() ? context.r.symtab.getSymbolIndex(operand.first) : sym.index;
            if (operand.second > 0) {
                value += sym.value;
                ++sectionIndex[index];
            } else {
                value -= sym.value;
                --sectionIndex[index];
            }
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
    } else if (context.r.symtab.getSymbol(classificationIndex).isSymbol()) {
        sym.flags |= Symbol::SYM_NONGLOBAL;
    }
    context.bt.patch(symbol, context);
    resolveAll(context);
    return true;
}

void UnresolvedSymbolTable::resolveAll(Context& context) {
    bool retry;
    do {
        retry = false;
        for (auto pair : operands) {
            if (resolve(pair.first, context)) {
                retry = true;
                break;
            }
        }
    } while (retry);
}

bool UnresolvedSymbolTable::empty() const {
    return operands.empty();
}

std::vector<std::string> UnresolvedSymbolTable::getPendingSymbols() const {
    std::vector<std::string> symbols(operands.size());
    std::transform(operands.begin(), operands.end(), symbols.begin(), [](auto& pair) {return pair.first;});
    return symbols;
}
