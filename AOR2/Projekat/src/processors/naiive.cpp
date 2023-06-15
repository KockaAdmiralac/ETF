#include <cmath>
#include <cstdlib>
#include <processors/naiive.hpp>

void NaiiveProcessor::add(Image& image, const float value) const {
    for (float& pixel : image.data) {
        pixel += value;
    }
}

void NaiiveProcessor::sub(Image& image, const float value) const {
    for (float& pixel : image.data) {
        pixel -= value;
    }
}

void NaiiveProcessor::invsub(Image& image, const float value) const {
    for (float& pixel : image.data) {
        pixel = value - pixel;
    }
}

void NaiiveProcessor::mul(Image& image, const float value) const {
    for (float& pixel : image.data) {
        pixel *= value;
    }
}

void NaiiveProcessor::div(Image& image, const float value) const {
    for (float& pixel : image.data) {
        pixel /= value;
    }
}

void NaiiveProcessor::invdiv(Image& image, const float value) const {
    for (float& pixel : image.data) {
        pixel = value / pixel;
    }
}

void NaiiveProcessor::pow(Image& image, const float value) const {
    for (float& pixel : image.data) {
        pixel = ::powf(pixel, value);
    }
}

void NaiiveProcessor::log(Image& image, const float value) const {
    for (float& pixel : image.data) {
        pixel = ::logf(pixel) / ::logf(value);
    }
}

void NaiiveProcessor::abs(Image& image) const {
    for (float& pixel : image.data) {
        pixel = std::abs(pixel);
    }
}

void NaiiveProcessor::min(Image& image, const float value) const {
    for (float& pixel : image.data) {
        pixel = std::min(pixel, value);
    }
}

void NaiiveProcessor::max(Image& image, const float value) const {
    for (float& pixel : image.data) {
        pixel = std::max(pixel, value);
    }
}

void NaiiveProcessor::inverse(Image& image) const {
    for (float& pixel : image.data) {
        pixel = 1.0f - pixel;
    }
}

void NaiiveProcessor::grayscale(Image& image) const {
    for (uint32_t i = 0; i < image.data.size(); i += 3) {
        float grayR = image.data[i + 0] * 0.299f;
        float grayG = image.data[i + 1] * 0.587f;
        float grayB = image.data[i + 2] * 0.144f;
        float gray = std::min(grayR + grayG + grayB, 1.0f);
        image.data[i + 0] = gray;
        image.data[i + 1] = gray;
        image.data[i + 2] = gray;
    }
}

void NaiiveProcessor::filter(Image& image, const uint32_t width, const uint32_t height, const std::vector<float>& value) const {
    std::vector<float> newPixels;
    newPixels.resize(image.data.size());
    const uint32_t widthHalf = width / 2;
    const uint32_t heightHalf = height / 2;
    const uint32_t widthMinusOneHalf = (width - 1) / 2;
    const uint32_t heightMinusOneHalf = (height - 1) / 2;
    for (uint32_t y = heightHalf; y < image.height - heightMinusOneHalf; ++y) {
        for (uint32_t x = widthHalf; x < image.width - widthMinusOneHalf; ++x) {
            float valueR = 0.0f;
            float valueG = 0.0f;
            float valueB = 0.0f;
            for (uint32_t filterY = 0; filterY < height; ++filterY) {
                for (uint32_t filterX = 0; filterX < width; ++filterX) {
                    uint32_t coeffY = y - heightHalf + filterY;
                    uint32_t coeffX = x - widthHalf + filterX;
                    float coeff = value[filterY * width + filterX];
                    valueR += image.data[coeffY * image.width * 3 + coeffX * 3 + 0] * coeff;
                    valueG += image.data[coeffY * image.width * 3 + coeffX * 3 + 1] * coeff;
                    valueB += image.data[coeffY * image.width * 3 + coeffX * 3 + 2] * coeff;
                }
            }
            newPixels[y * image.width * 3 + x * 3 + 0] = valueR;
            newPixels[y * image.width * 3 + x * 3 + 1] = valueG;
            newPixels[y * image.width * 3 + x * 3 + 2] = valueB;
        }
    }
    for (uint32_t y = heightHalf; y < image.height - heightMinusOneHalf; ++y) {
        for (uint32_t x = widthHalf; x < image.width - widthMinusOneHalf; ++x) {
            image.data[y * image.width * 3 + x * 3 + 0] = newPixels[y * image.width * 3 + x * 3 + 0];
            image.data[y * image.width * 3 + x * 3 + 1] = newPixels[y * image.width * 3 + x * 3 + 1];
            image.data[y * image.width * 3 + x * 3 + 2] = newPixels[y * image.width * 3 + x * 3 + 2];
        }
    }
}
