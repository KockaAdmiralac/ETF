#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

size_t BLOCK_SIZE = 1024;
int thread_create(void(*)(void*), void*);
void *

void childcpy(void *context) {
    //
}

void* par_memcpy(void* destination, const void* source, size_t num) {
    int threadCount = ceil(num/BLOCK_SIZE);
    for (int i = 0; i < threadCount; ++i) {
        thread_create(childcpy, source + i * BLOCK_SIZE);
    }
    wait(0);
    return destination;
}
