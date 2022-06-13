#include <algorithm>
#include "hex/hex-file.hpp"
#include "linker/place.hpp"

void place(Relocatable& r, std::unordered_map<std::string, uint64_t>& places, std::ostream& stream) {
    // Check how long is each section
    std::unordered_map<std::string, Section*> sections;
    for (Section& s : r.sections) {
        sections[s.name] = &s;
    }
    // Assign values to sections specified in arguments
    std::vector<std::pair<std::string, uint64_t>> pairs;
    for (auto& it : places) {
        pairs.push_back(it);
    }
    std::sort(pairs.begin(), pairs.end(), [](std::pair<std::string, uint64_t>& a, std::pair<std::string, uint64_t>& b) {
        return a.second < b.second;
    });
    uint64_t lastPlace = 0;
    std::string lastSection = "???";
    for (std::pair<std::string, uint64_t>& place : pairs) {
        if (place.second < lastPlace) {
            throw std::runtime_error("Sections " + lastSection + " and " + place.first + " overlap.");
        }
        std::string symbolName = "." + place.first;
        if (!r.symtab.hasSymbol(symbolName)) {
            throw std::runtime_error("Section speciifed in -place does not exist: " + symbolName);
        }
        r.symtab.getSymbol(symbolName).value = place.second;
        lastSection = place.first;
        lastPlace = place.second + sections[place.first]->contents.size();
    }
    // Assign values to sections not specified in arguments
    for (Section& s : r.sections) {
        if (places.find(s.name) != places.end()) {
            // Already assigned
            continue;
        }
        std::string symbolName = "." + s.name;
        r.symtab.getSymbol(symbolName).value = lastPlace;
        pairs.push_back({s.name, lastPlace});
        lastPlace += s.contents.size();
    }
    // Assign values to all other symbols
    for (Symbol& s : r.symtab) {
        if (!s.isSymbol() || s.isAbsolute() || !s.isGlobal()) {
            // Already assigned
            continue;
        }
        if (s.isUndefined()) {
            throw std::runtime_error("Undefined symbol: " + s.symbol);
        }
        s.value += r.symtab.getSymbol(s.index).value;
    }
    // Patch sections based on relocation tables
    for (size_t i = 0; i < r.sections.size(); ++i) {
        Section& s = r.sections[i];
        for (Relocation& rel : r.relocations[i]) {
            int64_t value;
            int64_t destValue;
            int64_t srcValue;
            std::string sectionSymbol;
            switch (rel.type) {
                case REL_ABS:
                    value = r.symtab.getSymbol(rel.symbol).value + rel.addend;
                    break;
                case REL_ABS_LE:
                    value = r.symtab.getSymbol(rel.symbol).value + rel.addend;
                    value = ((value & 0xFF00) >> 8) | ((value & 0xFF) << 8);
                    break;
                case REL_PC:
                    sectionSymbol = "." + s.name;
                    destValue = r.symtab.getSymbol(rel.symbol).value + rel.addend;
                    srcValue = r.symtab.getSymbol(sectionSymbol).value + rel.offset;
                    value = destValue - srcValue;
                    break;
                default:
                    throw std::runtime_error("Unknown relocation type encountered.");
                    break;
            }
            s.contents[rel.offset] = (value & 0xFF00) >> 8;
            s.contents[rel.offset + 1] = value & 0xFF;
        }
    }
    // Write to file
    HexFile file;
    uint64_t startAddr = 0x10000;
    std::vector<uint8_t> content;
    for (std::pair<std::string, uint64_t>& place : pairs) {
        if (startAddr + content.size() != place.second) {
            if (!content.empty()) {
                file.addSection(startAddr, content);
                content.clear();
            }
            startAddr = place.second;
        }
        content.insert(content.end(), sections[place.first]->contents.begin(), sections[place.first]->contents.end());
    }
    if (!content.empty()) {
        file.addSection(startAddr, content);
    }
    file.write(stream);
}
