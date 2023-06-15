#pragma once
#include <string>
#include <image.hpp>

class BaseLoader {
public:
    virtual Image load(const std::string& filename) const = 0;
    virtual void save(const std::string& filename, const Image& image) const = 0;
};
