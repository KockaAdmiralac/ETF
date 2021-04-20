#include <cstdio>
#include <string.h>
#include "../../kernel.h"

class DoubleBuffer {
public:
    DoubleBuffer (size_t size, size_t chunkSizeProd, size_t chunkSizeCons);
    void put(const char* buffer);
    void get(char* buffer);
private:
    size_t size, chunkSizeProd, chunkSizeCons, chunkLeftProd, chunkLeftCons;
    char *buffProd, *buffCons;
    Semaphore semProd, semCons;
};

DoubleBuffer::DoubleBuffer(size_t size, size_t chunkSizeProd, size_t chunkSizeCons) :
    size(size), chunkSizeCons(chunkSizeCons), chunkSizeProd(chunkSizeProd) {
    buffProd = new char[size];
    buffCons = new char[size];
    chunkLeftProd = size / chunkSizeProd;
    chunkLeftCons = size / chunkSizeCons;
}

void DoubleBuffer::put(const char* buffer) {
    semProd.wait();
    --chunkLeftProd;
    memcpy(buffProd + (chunkLeftProd * chunkSizeProd), buffer, chunkSizeProd);
    while (chunkLeftProd == 0 && chunkLeftCons != 0) {
        semCons.wait();
        if (chunkLeftProd == 0 && chunkLeftCons == 0) {
            char *buffTmp = buffProd;
            buffProd = buffCons;
            buffCons = buffProd;
            chunkLeftProd = size / chunkSizeProd;
            chunkLeftCons = size / chunkSizeCons;
        }
        semCons.signal();
    }
    semProd.signal();
}

void DoubleBuffer::get(char *buffer) {
    semCons.wait();
    --chunkLeftCons;
    memcpy(buffer, buffCons + (chunkLeftCons * chunkSizeCons), chunkSizeCons);
    while (chunkLeftProd != 0 && chunkLeftCons == 0) {
        semProd.wait();
        if (chunkLeftProd == 0 && chunkLeftCons == 0) {
            char *buffTmp = buffProd;
            buffProd = buffCons;
            buffCons = buffProd;
            chunkLeftProd = size / chunkSizeProd;
            chunkLeftCons = size / chunkSizeCons;
        }
        semProd.signal();
    }
    semCons.signal();
}
