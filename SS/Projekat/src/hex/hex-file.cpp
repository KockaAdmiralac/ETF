#include <iomanip>
#include "hex/hex-file.hpp"

void HexFile::write(std::ostream& stream) {
    uint64_t lastPos = 0;
    uint64_t count = 0;
    for (std::pair<const uint64_t, std::vector<uint8_t>>& content : contents) {
        if (lastPos != content.first) {
            lastPos = content.first;
            count = 0;
        }
        for (uint8_t byte : content.second) {
            if (count == 0) {
                stream << std::hex << std::setw(8) << std::setfill('0') << lastPos << ":";
            }
            stream << " " << std::hex << std::setw(2) << std::setfill('0') << uint64_t(byte);
            if (++count == 8) {
                count = 0;
                stream << std::endl;
            }
            ++lastPos;
        }
    }
}

void HexFile::read(std::istream& stream) {
    // TODO
}

void HexFile::addSection(uint64_t start, std::vector<uint8_t>& content) {
    contents[start] = content;
}

uint8_t HexFile::readMemory(uint64_t addr) {
    for (std::pair<const uint64_t, std::vector<uint8_t>>& content : contents) {
        if (addr >= content.first && addr < content.first + content.second.size()) {
            return content.second[addr - content.first];
        }
    }
    return 0;
}
