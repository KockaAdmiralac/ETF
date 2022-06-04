#include <iostream>
#include "relocatable/file-utils.hpp"
#include "relocatable/section.hpp"

Section::Section(std::string& name) : name(name) {}

void Section::write(std::ostream& file) {
    std::string sectionName = "." + name;
    writeString(file, sectionName);
    writeVector(file, contents);
}

void Section::read(std::istream& file) {
    // Name has already been read.
    readVector(file, contents);
}

void Section::merge(Section& section) {
    contents.insert(contents.end(), section.contents.begin(), section.contents.end());
}
