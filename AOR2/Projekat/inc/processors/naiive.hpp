#pragma once
#include "processor.hpp"

class NaiiveProcessor: public BaseProcessor {
public:
    virtual void add(Image& image, const float value) const override;
    virtual void sub(Image& image, const float value) const override;
    virtual void invsub(Image& image, const float value) const override;
    virtual void mul(Image& image, const float value) const override;
    virtual void div(Image& image, const float value) const override;
    virtual void invdiv(Image& image, const float value) const override;
    virtual void pow(Image& image, const float value) const override;
    virtual void log(Image& image, const float value) const override;
    virtual void abs(Image& image) const override;
    virtual void min(Image& image, const float value) const override;
    virtual void max(Image& image, const float value) const override;
    virtual void inverse(Image& image) const override;
    virtual void grayscale(Image& image) const override;
    virtual void filter(Image& image, const uint32_t width, const uint32_t height, const std::vector<float>& value) const override;
};
