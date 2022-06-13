#include "common.h"

const int N = 5;

void philosopher(int i) {
    int left = i;
    int right = (i + 1) % N;
    while (true) {
        // Мислимо
        in("fifo");
        in("permit");
        in("fork", left);
        in("fork", right);
        out("fifo");
        // Једемо
        out("fork", right);
        out("fork", left);
        out("permit");
    }
}

void init() {
    for (int i = 0; i < N; ++i) {
        out("fork", i);
        eval(philosopher, i);
        if (i != N-1) {
            out("permit");
        }
    }
    out("fifo");
}
