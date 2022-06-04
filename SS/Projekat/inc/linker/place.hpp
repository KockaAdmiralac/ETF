#ifndef _PLACE_HPP
#define _PLACE_HPP
#include <iostream>
#include <unordered_map>
#include "relocatable/relocatable.hpp"

void place(Relocatable& r, std::unordered_map<std::string, uint64_t>& places, std::ostream& stream);
#endif
