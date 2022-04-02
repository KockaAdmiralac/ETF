#include "common.h"

const int N = 100;
int buffer[N];
sem empty = N;
sem full = 0;
sem mutexFull = 1;
sem mutexEmpty = 1;
int head = 0;
int tail = 0;

int produce();
void consume(int product);

void producer() {
    while (true) {
        int product = produce();
        empty.wait();
        mutexEmpty.wait();
        buffer[tail] = product;
        tail = (tail + 1) % N;
        mutexEmpty.signal();
        full.signal();
    }
}

void consumer() {
    while (true) {
        full.wait();
        mutexFull.wait();
        int product = buffer[head];
        head = (head + 1) % N;
        mutexFull.signal();
        empty.signal();
        consume(product);
    }
}
