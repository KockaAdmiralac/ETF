#ifndef _HEX_FILE_HPP
#define _HEX_FILE_HPP
#include <iostream>
#include <map>
#include <vector>

struct HexFile {
    std::map<uint64_t, std::vector<uint8_t>> contents;
    void write(std::ostream& stream);
    void read(std::istream& stream);
    void addSection(uint64_t start, std::vector<uint8_t>& content);
    uint8_t readMemory(uint64_t addr);
    void writeMemory(uint64_t addr, uint8_t data);
};
#endif
