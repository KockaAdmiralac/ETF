#ifndef _BACKPATCHING_HPP
#define _BACKPATCHING_HPP
#include <string>
#include <unordered_map>
#include <vector>
#include "relocatable/relocation-table.hpp"

class Context;
struct Patch {
    uint64_t section;
    uint64_t offset;
    RelocationType relType;
};
class BackpatchingTable {
public:
    void addPatch(std::string& symbol, uint64_t section, uint64_t offset, RelocationType relType);
    void patch(std::string& symbol, Context& context);
    bool empty() const;
private:
    std::unordered_map<std::string, std::vector<Patch>> symbols;
};
#endif
