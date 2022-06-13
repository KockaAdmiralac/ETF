#include <iomanip>
#include <sstream>
#include "objdump/format.hpp"

std::vector<std::vector<std::string>> formatSymbolTable(SymbolTable& symtab) {
    std::vector<std::vector<std::string>> data;
    size_t num = 0;
    for (Symbol& sym : symtab) {
        std::vector<std::string> row;
        row.push_back(std::to_string(num++));
        row.push_back(std::to_string(sym.value));
        row.push_back(std::to_string(sym.size));
        row.push_back(sym.isSymbol() ? "NOTYP" : "SCTN");
        row.push_back(sym.isGlobal() ? "GLOB" : "LOC");
        row.push_back(sym.isAbsolute() ? "*ABS*" : ((sym.index == 0) ? "UND" : std::to_string(sym.index)));
        row.push_back(sym.symbol);
        data.push_back(row);
    }
    return data;
}

std::string formatRelocationType(RelocationType relType) {
    switch (relType) {
        case REL_ABS: return "REL_ABS";
        case REL_ABS_LE: return "REL_ABS_LE";
        case REL_PC: return "REL_PC";
        default: return "???";
    }
}

std::vector<std::vector<std::string>> formatRelocationTable(RelocationTable& table, SymbolTable& symtab) {
    std::vector<std::vector<std::string>> data;
    for (Relocation& rel : table) {
        std::vector<std::string> row;
        row.push_back(std::to_string(rel.offset));
        row.push_back(formatRelocationType(rel.type));
        row.push_back(std::to_string(rel.symbol) + " (" + symtab.getSymbol(rel.symbol).symbol + ")");
        row.push_back(std::to_string(rel.addend));
        data.push_back(row);
    }
    return data;
}

std::vector<std::vector<std::string>> formatSection(Section& section) {
    std::vector<std::vector<std::string>> data;
    uint8_t count = 0;
    std::stringstream stream;
    for (std::uint8_t byte : section.contents) {
        stream << std::hex << std::setw(2) << std::setfill('0') << uint64_t(byte);
        if (++count == 8) {
            std::stringstream offsetStream;
            offsetStream << std::hex << std::setw(4) << std::setfill('0') << data.size() * 8;
            data.push_back({offsetStream.str(), stream.str()});
            count = 0;
            stream.str("");
        } else {
            stream << " ";
        }
    }
    if (count != 0) {
        std::stringstream offsetStream;
        offsetStream << std::hex << std::setw(4) << std::setfill('0') << data.size() * 8;
        data.push_back({offsetStream.str(), stream.str()});
    }
    return data;
}
