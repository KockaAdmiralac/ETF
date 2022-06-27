#include "common.h"

const int N = 100;
bool flag[N];
int tail = 0;

int addAndGet(int var, int incr);

void worker() {
    while (true) {
        int index = (addAndGet(tail, 1) - 1) % N;
        while (!flag[index]) skip();
        /* critical section */
        flag[index] = false;
        flag[(index + 1) % N] = true;
        /* non-critical section */
    }
}
