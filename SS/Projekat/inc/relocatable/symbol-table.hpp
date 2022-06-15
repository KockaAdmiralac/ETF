#ifndef _SYMBOL_TABLE_HPP
#define _SYMBOL_TABLE_HPP
#include <unordered_map>
#include <string>
#include <vector>

struct Symbol {
    static const uint8_t SYM_UNDEF = 1;
    static const uint8_t SYM_GLOBAL = 2;
    static const uint8_t SYM_ISSYM = 4;
    static const uint8_t SYM_EXTERN = 8;
    static const uint8_t SYM_ABS = 16;
    static const uint8_t SYM_NONGLOBAL = 32;
    std::string symbol;
    int64_t value;
    uint8_t flags;
    uint64_t index;
    uint64_t size;
    bool isUndefined();
    bool isGlobal();
    bool isSymbol();
    bool isExternal();
    bool isAbsolute();
    Symbol(std::string symbol, const uint8_t flags, uint64_t index, uint64_t size, int64_t value);
};

class SymbolTable {
public:
    SymbolTable();
    uint64_t size();
    uint64_t addSymbol(Symbol& symbol);
    bool hasSymbol(const std::string& symbol);
    Symbol& getSymbol(const std::string& symbol);
    Symbol& getSymbol(uint64_t symbol);
    uint64_t getSymbolIndex(const std::string& symbol);
    void write(std::ostream& stream);
    void read(std::istream& stream);
    void merge(SymbolTable& symtab, std::unordered_map<std::string, uint64_t>& offsets, std::string& filename);
    std::vector<Symbol>::iterator begin();
    std::vector<Symbol>::iterator end();
private:
    std::vector<Symbol> symbols;
    std::unordered_map<std::string, uint64_t> indices;
};
#endif
