#include <iomanip>
#include "hex/hex-file.hpp"

void HexFile::write(std::ostream& stream) {
    uint64_t lastPos = 0;
    uint64_t count = 0;
    for (std::pair<const uint64_t, std::vector<uint8_t>>& content : contents) {
        if (lastPos != content.first) {
            lastPos = content.first;
            if (count % 8 != 0) {
                stream << std::endl;
            }
            count = 0;
        }
        for (uint8_t byte : content.second) {
            if (count == 0) {
                stream << std::hex << std::setw(4) << std::setfill('0') << lastPos << ":";
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
    uint64_t currentOffset = 0x10000;
    std::vector<uint8_t> contents;
    uint8_t count = 0;
    while (!stream.eof()) {
        if (count == 0) {
            uint64_t offset;
            stream >> std::hex >> offset;
            if (offset != currentOffset + contents.size()) {
                if (!contents.empty()) {
                    addSection(currentOffset, contents);
                }
                currentOffset = offset;
            }
            char c;
            stream >> c;
        } else {
            uint64_t data;
            stream >> std::hex >> data;
            contents.push_back(uint8_t(data));
        }
        if (++count == 9) {
            count = 0;
        }
    }
    if (!contents.empty()) {
        addSection(currentOffset, contents);
    }
}

void HexFile::addSection(uint64_t start, std::vector<uint8_t>& content) {
    contents[start] = content;
}

uint8_t HexFile::readMemory(uint64_t addr) {
    addr &= 0xFFFF;
    for (std::pair<const uint64_t, std::vector<uint8_t>>& content : contents) {
        if (addr >= content.first && addr < content.first + content.second.size()) {
            // Reading from a section
            return content.second[addr - content.first];
        }
        if (addr < content.first) {
            // There are no more sections in a valid range for reading
            break;
        }
    }
    return 0;
}

void HexFile::writeMemory(uint64_t addr, uint8_t data) {
    addr &= 0xFFFF;
    for (std::pair<const uint64_t, std::vector<uint8_t>>& content : contents) {
        if (addr >= content.first && addr < content.first + content.second.size()) {
            // Writing to a section
            content.second[addr - content.first] = data;
            return;
        }
        if (addr == content.first + content.second.size()) {
            // Expanding a section
            content.second.push_back(data);
            return;
        }
        if (addr < content.first) {
            // There are no more sections in a valid range for writing
            break;
        }
    }
    std::vector<uint8_t> newSectionContent = {data};
    addSection(addr, newSectionContent);
}
