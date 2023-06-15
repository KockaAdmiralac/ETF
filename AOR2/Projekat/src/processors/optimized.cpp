#include <cmath>
#include <cstdlib>
#include <cstring>
#include <immintrin.h>
#include <processors/optimized.hpp>
#include <stdexcept>
#include <vectorclass/vectormath_exp.h>

OptimizedProcessor::OptimizedProcessor() {
    // Intel:
    // uint32_t eax = 4;
    // AMD:
    uint32_t eax = 0x8000001D;
    uint32_t ebx;
    uint32_t ecx = 0;
    uint32_t edx;
    __asm__("cpuid" : "+a" (eax), "=b" (ebx), "+c" (ecx), "=d" (edx));
    int cacheType = eax & 0x1F;
    if (cacheType != 1) {
        throw std::runtime_error("FATAL: retrieved cache info is not for the data cache!");
    }
    cacheInfo.sets = ecx + 1;
    cacheInfo.lineSize = (ebx & 0xFFF) + 1;
    cacheInfo.physicalLinePartitions = ((ebx >>= 12) & 0x3FF) + 1;
    cacheInfo.ways = ((ebx >>= 10) & 0x3FF) + 1;
}

void OptimizedProcessor::add(Image& image, const float value) const {
    __m256 addVector = _mm256_set_ps(value, value, value, value, value, value, value, value);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        __m256 addedVector = _mm256_add_ps(dataVector, addVector);
        _mm256_store_ps(data + i, addedVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] += value;
    }
}

void OptimizedProcessor::sub(Image& image, const float value) const {
    __m256 subVector = _mm256_set_ps(value, value, value, value, value, value, value, value);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        __m256 subtractedVector = _mm256_sub_ps(dataVector, subVector);
        _mm256_store_ps(data + i, subtractedVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] -= value;
    }
}

void OptimizedProcessor::invsub(Image& image, const float value) const {
    __m256 subVector = _mm256_set_ps(value, value, value, value, value, value, value, value);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        __m256 subtractedVector = _mm256_sub_ps(subVector, dataVector);
        _mm256_store_ps(data + i, subtractedVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] = value - image.data[i];
    }
}

void OptimizedProcessor::mul(Image& image, const float value) const {
    __m256 mulVector = _mm256_set_ps(value, value, value, value, value, value, value, value);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        __m256 multipliedVector = _mm256_mul_ps(dataVector, mulVector);
        _mm256_store_ps(data + i, multipliedVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] *= value;
    }
}

void OptimizedProcessor::div(Image& image, const float value) const {
    __m256 divVector = _mm256_set_ps(value, value, value, value, value, value, value, value);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        __m256 dividedVector = _mm256_div_ps(dataVector, divVector);
        _mm256_store_ps(data + i, dividedVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] /= value;
    }
}

void OptimizedProcessor::invdiv(Image& image, const float value) const {
    __m256 divVector = _mm256_set_ps(value, value, value, value, value, value, value, value);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        __m256 dividedVector = _mm256_div_ps(divVector, dataVector);
        _mm256_store_ps(data + i, dividedVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] = value / image.data[i];
    }
}

// Optimization GOD
void OptimizedProcessor::pow(Image& image, const float value) const {
    // __m256 powVector = _mm256_set_ps(value, value, value, value, value, value, value, value);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        __m256 powerVector = ::pow(dataVector, value);
        _mm256_store_ps(data + i, powerVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] = ::powf(image.data[i], value);
    }
}

void OptimizedProcessor::log(Image& image, const float value) const {
    __m256 logVector = _mm256_set_ps(value, value, value, value, value, value, value, value);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        __m256 naturalLogarithmVector = ::log(dataVector);
        __m256 logarithmBaseVector = ::log(logVector);
        __m256 logarithmVector = _mm256_div_ps(naturalLogarithmVector, logarithmBaseVector);
        _mm256_store_ps(data + i, logarithmVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] = ::logf(image.data[i]) / ::logf(value);
    }
}

void OptimizedProcessor::abs(Image& image) const {
    __m256 compareVector = _mm256_set_ps(0, 0, 0, 0, 0, 0, 0, 0);
    __m256 negateVector = _mm256_set_ps(-1, -1, -1, -1, -1, -1, -1, -1);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        // 1 where data is negative, 0 where positive
        __m256 comparisonVector = _mm256_cmp_ps(dataVector, compareVector, _CMP_LT_OQ);
        __m256 negatedVector = _mm256_mul_ps(dataVector, negateVector);
        __m256 absVector = _mm256_blendv_ps(dataVector, negatedVector, comparisonVector);
        _mm256_store_ps(data + i, absVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] = std::abs(image.data[i]);
    }
}

void OptimizedProcessor::min(Image& image, const float value) const {
    __m256 minVector = _mm256_set_ps(value, value, value, value, value, value, value, value);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        __m256 minimizedVector = _mm256_min_ps(dataVector, minVector);
        _mm256_store_ps(data + i, minimizedVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] = std::min(image.data[i], value);
    }
}

void OptimizedProcessor::max(Image& image, const float value) const {
    __m256 maxVector = _mm256_set_ps(value, value, value, value, value, value, value, value);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 8) * 8;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 8) {
        __m256 dataVector = _mm256_load_ps(data + i);
        __m256 maximizedVector = _mm256_max_ps(dataVector, maxVector);
        _mm256_store_ps(data + i, maximizedVector);
    }
    for (size_t i = dataSizeRoundedDown; i < image.data.size(); ++i) {
        image.data[i] = std::min(image.data[i], value);
    }
}

void OptimizedProcessor::inverse(Image& image) const {
    invsub(image, 1.0f);
}

void OptimizedProcessor::grayscale(Image& image) const {
    __m256 grayscaleCoeffVector1 = _mm256_set_ps(0.587f, 0.299f, 0.144f, 0.587f, 0.299f, 0.144f, 0.587f, 0.299f);
    __m256 grayscaleCoeffVector2 = _mm256_set_ps(0.299f, 0.144f, 0.587f, 0.299f, 0.144f, 0.587f, 0.299f, 0.144f);
    __m256 grayscaleCoeffVector3 = _mm256_set_ps(0.144f, 0.587f, 0.299f, 0.144f, 0.587f, 0.299f, 0.144f, 0.587f);
    float* data = image.data.data();
    size_t dataSizeRoundedDown = (image.data.size() / 24) * 24;
    for (size_t i = 0; i < dataSizeRoundedDown; i += 24) {
        __m256 dataVector1 = _mm256_load_ps(data + i + 0);
        __m256 dataVector2 = _mm256_load_ps(data + i + 8);
        __m256 dataVector3 = _mm256_load_ps(data + i + 16);
        __m256 multipliedVector1 = _mm256_mul_ps(dataVector1, grayscaleCoeffVector1);
        __m256 multipliedVector2 = _mm256_mul_ps(dataVector2, grayscaleCoeffVector2);
        __m256 multipliedVector3 = _mm256_mul_ps(dataVector3, grayscaleCoeffVector3);
        float gray1 = std::min(multipliedVector1[0] + multipliedVector1[1] + multipliedVector1[2], 1.0f);
        float gray2 = std::min(multipliedVector1[3] + multipliedVector1[4] + multipliedVector1[5], 1.0f);
        float gray3 = std::min(multipliedVector1[6] + multipliedVector1[7] + multipliedVector2[0], 1.0f);
        float gray4 = std::min(multipliedVector2[1] + multipliedVector2[2] + multipliedVector2[3], 1.0f);
        float gray5 = std::min(multipliedVector2[4] + multipliedVector2[5] + multipliedVector2[6], 1.0f);
        float gray6 = std::min(multipliedVector2[7] + multipliedVector3[0] + multipliedVector3[1], 1.0f);
        float gray7 = std::min(multipliedVector3[2] + multipliedVector3[3] + multipliedVector3[4], 1.0f);
        float gray8 = std::min(multipliedVector3[5] + multipliedVector3[6] + multipliedVector3[7], 1.0f);
        __m256 grayVector1 = _mm256_set_ps(gray3, gray3, gray2, gray2, gray2, gray1, gray1, gray1);
        __m256 grayVector2 = _mm256_set_ps(gray6, gray5, gray5, gray5, gray4, gray4, gray4, gray3);
        __m256 grayVector3 = _mm256_set_ps(gray8, gray8, gray8, gray7, gray7, gray7, gray6, gray6);
        _mm256_store_ps(data + i + 0, grayVector1);
        _mm256_store_ps(data + i + 8, grayVector2);
        _mm256_store_ps(data + i + 16, grayVector3);
    }
    for (uint32_t i = dataSizeRoundedDown; i < image.data.size(); i += 3) {
        float grayR = image.data[i + 0] * 0.299f;
        float grayG = image.data[i + 1] * 0.587f;
        float grayB = image.data[i + 2] * 0.144f;
        float gray = std::min(grayR + grayG + grayB, 1.0f);
        image.data[i + 0] = gray;
        image.data[i + 1] = gray;
        image.data[i + 2] = gray;
    }
}

void OptimizedProcessor::filter(Image& image, const uint32_t width, const uint32_t height, const std::vector<float>& value) const {
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
    memcpy(image.data.data(), newPixels.data(), newPixels.size() * sizeof(float));
}
