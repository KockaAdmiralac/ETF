#pragma once
#include <vector>
#include <image.hpp>

class BaseProcessor {
public:
    virtual void add(Image& image, const float value) const = 0;
    virtual void sub(Image& image, const float value) const = 0;
    virtual void invsub(Image& image, const float value) const = 0;
    virtual void mul(Image& image, const float value) const = 0;
    virtual void div(Image& image, const float value) const = 0;
    virtual void invdiv(Image& image, const float value) const = 0;
    virtual void pow(Image& image, const float value) const = 0;
    virtual void log(Image& image, const float value) const = 0;
    virtual void abs(Image& image) const = 0;
    virtual void min(Image& image, const float value) const = 0;
    virtual void max(Image& image, const float value) const = 0;
    virtual void inverse(Image& image) const = 0;
    virtual void grayscale(Image& image) const = 0;
    virtual void filter(Image& image, const uint32_t width, const uint32_t height, const std::vector<float>& value) const = 0;
};
