#include <chrono>
#include <cstdlib>
#include <iostream>
#include <immintrin.h>
#define N 65530

// Унија за приступ појединачним члановима вектора.
union V256 {
    __m256 v;
    float f[8];
};

// Напомена: битно је да се ови низови нађу на адреси која је поравната на
// 32 бита, иначе ће `_mm256_load_ps` бацити грешку.
// Овим редом су поређани како би евентуална прекорачења граница низа у SIMD
// имплементацији била ухваћена током провере једнакости низова.
float niz2[N];
float niz1[N];

// Оригинални код из задатка.
void scaleOriginal(float* input, int n) {
    float max = input[0];

    for (int i = 1; i < n; i++) {
        if (input[i] > max)
            max = input[i];
    }

    for (int i = 0; i < n; i++) {
        input[i] = input[i] / max;
    }
}

// SIMD-оптимизован код.
void scaleSIMD(float* input, int n) {
    if (n < 8) {
        // За мање од 8 елемената нема потребе ништа да паралелизујемо.
        scaleOriginal(input, n);
    } else {
        int roundedDownN = (n / 8) * 8;
        // Рачунамо максимуме осам-по-осам елемената низа.
        V256 maxVector;
        maxVector.v = _mm256_load_ps(input);
        for (int i = 8; i < roundedDownN; i += 8) {
            __m256 inputVector = _mm256_load_ps(input + i);
            maxVector.v = _mm256_max_ps(maxVector.v, inputVector);
        }
        // За извучене максимуме рачунамо који је од њих осам је прави максимум.
        float max = maxVector.f[0];
        for (int i = 1; i < 8; ++i) {
            if (maxVector.f[i] > max) {
                max = maxVector.f[i];
            }
        }
        // За преостале чланове низа такође рачунамо максимум.
        for (int i = roundedDownN; i < n; ++i) {
            if (input[i] > max) {
                max = input[i];
            }
        }
        // Како је на овом року дата документација за векторску инструкцију
        // множења, а не и за векторску инструкцију дељења, дељење максимумом
        // сводимо на множење са реципрочном вредношћу.
        float inverseMax = 1 / max;
        __m256 inverseMaxVector = _mm256_set_ps(inverseMax, inverseMax, inverseMax, inverseMax, inverseMax, inverseMax, inverseMax, inverseMax);
        for (int i = 0; i < roundedDownN; i += 8) {
            __m256 inputVector = _mm256_load_ps(input + i);
            __m256 multipliedVector = _mm256_mul_ps(inputVector, inverseMaxVector);
            _mm256_storeu_ps(input + i, multipliedVector);
        }
        // Процесирамо преостале елементе.
        for (int i = roundedDownN; i < n; ++i) {
            input[i] = input[i] / max;
        }
    }
}

int main() {
    // Пунимо улазне низове насумичним подацима.
    for (int i = 0; i < N; ++i) {
        float randomNumber = static_cast<float>(rand());
        niz1[i] = randomNumber;
        niz2[i] = randomNumber;
    }
    // Меримо време колико је потребно оригиналном коду да се изврши.
    std::chrono::steady_clock::time_point beginOriginal = std::chrono::steady_clock::now();
    scaleOriginal(niz1, N);
    std::chrono::steady_clock::time_point endOriginal = std::chrono::steady_clock::now();
    std::cout << "Original: " << std::chrono::duration_cast<std::chrono::microseconds>(endOriginal - beginOriginal).count() << "ms" << std::endl;
    // Меримо време колико је потребно SIMD коду да се изврши.
    std::chrono::steady_clock::time_point beginSIMD = std::chrono::steady_clock::now();
    scaleSIMD(niz2, N);
    std::chrono::steady_clock::time_point endSIMD = std::chrono::steady_clock::now();
    std::cout << "SIMD:     " << std::chrono::duration_cast<std::chrono::microseconds>(endSIMD - beginSIMD).count() << "ms" << std::endl;
    // Упоређујемо резултате оригиналног и SIMD кода.
    for (int i = 0; i < N; ++i) {
        if (abs(niz1[i] - niz2[i]) > 0.0001) {
            std::cerr << "Mismatch at index " << i << " (original: " << niz1[i] << ", SIMD: " << niz2[i] << ")" << std::endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
