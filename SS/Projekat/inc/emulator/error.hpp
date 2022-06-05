#ifndef _ERROR_HPP
#define _ERROR_HPP
#include <stdexcept>

class CPUError : public std::runtime_error {
public:
    CPUError(char const* const message) : std::runtime_error(message) {}
};
#endif
