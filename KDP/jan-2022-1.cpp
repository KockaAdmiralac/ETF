#include "common.h"

sem arrived = 1;
sem continued = 0;
int blocked = 0;

const int N = 100;
void work1();
void work2();

void worker() {
    while (true) {
        work1();
        arrived.wait();
        blocked++;
        if (blocked != N) {
            arrived.signal();
            continued.wait();
        }
        blocked--;
        if (blocked > 0) {
            continued.signal();
        } else {
            arrived.signal();
        }
        work2();
    }
}
