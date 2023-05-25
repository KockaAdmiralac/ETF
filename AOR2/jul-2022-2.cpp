#include <chrono>
#include <cstdlib>
#include <iostream>
#include <immintrin.h>

const int N = 65530;
const int MIN = 0;
const int MAX = RAND_MAX / 10;

// Унија за приступ појединачним члановима вектора.
union V256I {
    __m256i v;
    int i[8];
};

// Низови за податке који се прослеђују функцијама.
unsigned int niz1[N];
unsigned int niz2[N];

// Оригинални код из задатка.
int elementsInRangeOriginal(const unsigned int* input, unsigned int n, unsigned int min, unsigned int max) {
    int result = 0;

    for (unsigned int i = 0; i < n; i++) {
        if (input[i] >= min && input[i] <= max)
            result = result + 1;
    }

    return result;
}

// SIMD-оптимизован код.
int elementsInRangeSIMD(const unsigned int* input, unsigned int n, unsigned int min, unsigned int max) {
    unsigned int roundedDownN = (n / 8) * 8;
    // Сви вектори потребни за рад функције.
    V256I resultVector;
    resultVector.v = _mm256_set_epi32(0, 0, 0, 0, 0, 0, 0, 0);
    __m256i minVector = _mm256_set_epi32(min, min, min, min, min, min, min, min);
    __m256i maxVector = _mm256_set_epi32(max, max, max, max, max, max, max, max);
    __m256i zeroVector = _mm256_set_epi32(0, 0, 0, 0, 0, 0, 0, 0);
    for (unsigned int i = 0; i < n; i += 8) {
        __m256i inputVector = _mm256_loadu_si256((__m256i*)(input + i));
        // _mm256_cmpgt_epi32 ће поставити све јединице на места где је испуњен
        // услов.
        __m256i minCompareVector = _mm256_cmpgt_epi32(inputVector, minVector);
        __m256i maxCompareVector = _mm256_cmpgt_epi32(maxVector, inputVector);
        // Остављамо све јединице на месту где су испуњена оба услова, и за
        // минимум и за максимум.
        __m256i blendedVector = _mm256_blendv_epi8(zeroVector, maxCompareVector, minCompareVector);
        // Напомена: све јединице заправо означавају број -1, па у овом вектору
        // чувамо негативне бројаче уместо позитивне.
        resultVector.v = _mm256_add_epi32(resultVector.v, blendedVector);
    }
    int result = 0;
    for (unsigned int i = 0; i < 8; ++i) {
        // Пошто смо изнад додавали негативне бројеве на резултат, овде морамо
        // да обрнемо знак да бисмо израчунали крајњи резултат како треба.
        result -= resultVector.i[i];
    }
    // Урачунавамо све преостале елементе у резултат.
    for (unsigned int i = roundedDownN; i < n; ++i) {
        if (input[i] >= min && input[i] <= max) {
            ++result;
        }
    }
    return result;
}

int main() {
    // Пунимо улазне низове насумичним подацима.
    for (int i = 0; i < N; ++i) {
        unsigned int randomNumber = static_cast<unsigned int>(rand());
        niz1[i] = randomNumber;
        niz2[i] = randomNumber;
    }
    // Меримо време колико је потребно оригиналном коду да се изврши.
    std::chrono::steady_clock::time_point beginOriginal = std::chrono::steady_clock::now();
    int resultOriginal = elementsInRangeOriginal(niz1, N, MIN, MAX);
    std::chrono::steady_clock::time_point endOriginal = std::chrono::steady_clock::now();
    std::cout << "Original: " << std::chrono::duration_cast<std::chrono::microseconds>(endOriginal - beginOriginal).count() << "ms" << std::endl;
    // Меримо време колико је потребно SIMD коду да се изврши.
    std::chrono::steady_clock::time_point beginSIMD = std::chrono::steady_clock::now();
    int resultSIMD = elementsInRangeSIMD(niz2, N, MIN, MAX);
    std::chrono::steady_clock::time_point endSIMD = std::chrono::steady_clock::now();
    std::cout << "SIMD:     " << std::chrono::duration_cast<std::chrono::microseconds>(endSIMD - beginSIMD).count() << "ms" << std::endl;
    // Упоређујемо резултате оригиналног и SIMD кода.
    if (resultOriginal != resultSIMD) {
        std::cerr << "Result mismatch (original: " << resultOriginal << ", SIMD: " << resultSIMD << ")" << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
