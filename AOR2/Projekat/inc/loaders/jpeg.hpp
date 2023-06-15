#pragma once
#include <string>
#include <image.hpp>
#include "loader.hpp"

class JPEGLoader: public BaseLoader {
public:
    virtual Image load(const std::string& filename) const override;
    virtual void save(const std::string& filename, const Image& image) const override;
};
