#ifndef _FORMAT_HPP
#define _FORMAT_HPP
#include <string>
#include <vector>
#include "relocatable/relocation-table.hpp"
#include "relocatable/section.hpp"
#include "relocatable/symbol-table.hpp"

std::vector<std::vector<std::string>> formatSymbolTable(SymbolTable& symtab);
std::vector<std::vector<std::string>> formatRelocationTable(RelocationTable& table, SymbolTable& symtab);
std::vector<std::vector<std::string>> formatSection(Section& section);
#endif
