#include <cstring>

typedef unsigned long ulong;

class SymbolTable {
    public:
        static ulong resolveSymbol(char* symbol);
};
int errorSymbolUndefined(char* symbol);

int resolveSymbols(char* inputObj, char* output) {
    ulong contentOffset = *((ulong*)inputObj);
    char* content = inputObj + contentOffset;
    ulong n = *(((ulong*)inputObj) + 1);
    char* table = inputObj + sizeof(ulong) * 2;
    for (ulong i = 0; i < n; ++i) {
        ulong symbolOffset = SymbolTable::resolveSymbol(table);
        if (symbolOffset == 0) {
            return errorSymbolUndefined(table);
        }
        ulong len = strlen(table);
        table += len + 1;
        ulong offset = *((ulong*)table);
        table += sizeof(ulong);
        while (offset != 0) {
            *((ulong*)(output + offset)) = symbolOffset;
            offset = *((ulong*)(content + offset));
        }
    }
    return 0;
}
