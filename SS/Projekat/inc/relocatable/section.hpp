#ifndef _SECTION_HPP
#define _SECTION_HPP
#include <string>
#include <vector>

struct Section {
    std::string name;
    std::vector<uint8_t> contents;
    Section(std::string& name);
    void write(std::ostream& file);
    void read(std::istream& file);
    void merge(Section& section);
};
#endif
