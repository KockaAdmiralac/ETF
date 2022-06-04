#ifndef _HEX_FILE_HPP
#define _HEX_FILE_HPP
#include <iostream>
#include <unordered_map>
#include <vector>

struct HexFile {
    std::unordered_map<uint64_t, std::vector<uint8_t>> contents;
    void write(std::ostream& stream);
    void read(std::istream& stream);
    void addSection(uint64_t start, std::vector<uint8_t>& content);
    uint8_t readMemory(uint64_t addr);
};
#endif
