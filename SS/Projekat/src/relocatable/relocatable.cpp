#include <string>
#include "relocatable/file-utils.hpp"
#include "relocatable/relocatable.hpp"

void Relocatable::write(std::ostream& stream) {
    relocWrite(stream, 1 + relocations.size() + sections.size());
    symtab.write(stream);
    for (RelocationTable& rt : relocations) {
        rt.write(stream);
    }
    for (Section& section : sections) {
        section.write(stream);
    }
}

void Relocatable::read(std::istream& stream) {
    std::size_t size = relocRead<std::size_t>(stream);
    for (std::size_t index = 0; index < size; ++index) {
        std::string name = readString(stream);
        if (name == ".symtab") {
            symtab.read(stream);
        } else if (name.rfind(".rela.", 0) == 0) {
            RelocationTable rt(name.substr(6));
            rt.read(stream);
            relocations.push_back(rt);
        } else {
            std::string sectionName = name.substr(1);
            Section section(sectionName);
            section.read(stream);
            sections.push_back(section);
        }
    }
}

void Relocatable::merge(Relocatable& r) {
    std::unordered_map<std::string, uint64_t> sectionIndices;
    std::unordered_map<std::string, uint64_t> offsets;
    uint64_t index = 0;
    for (Section& s : sections) {
        sectionIndices[s.name] = index++;
        offsets[s.name] = s.contents.size();
    }
    symtab.merge(r.symtab, offsets);
    for (Section& s : r.sections) {
        if (sectionIndices.find(s.name) != sectionIndices.end()) {
            sections[sectionIndices[s.name]].merge(s);
        } else {
            sections.push_back(s);
        }
    }
    for (RelocationTable& rt : r.relocations) {
        rt.patch(r.symtab, symtab, offsets);
        if (sectionIndices.find(rt.getName()) != sectionIndices.end()) {
            relocations[sectionIndices[rt.getName()]].merge(rt, offsets[rt.getName()]);
        } else {
            relocations.push_back(rt);
        }
    }
}
