#ifndef _UNRESOLVED_HPP
#define _UNRESOLVED_HPP
#include <string>
#include <unordered_map>
#include <vector>

class Context;
class UnresolvedSymbolTable {
public:
    void addUnresolved(std::string& symbol, std::vector<std::pair<std::string, int>> expression);
    bool resolve(std::string& symbol, Context& context);
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> operands;
};
#endif
