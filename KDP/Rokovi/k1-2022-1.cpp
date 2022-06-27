#include "common.h"

const int N = 100;
int slot = 0;
bool slots[N];

void worker(int id) {
    while (true) {
        int myslot = slot;
        while (!CAS(myslot, myslot % N + 1, slot)) skip();
        while (!slots[myslot]) skip();
        // Критична секција
        slots[myslot] = false;
        slots[myslot % N + 1] = true;
        // Некритична секција
    }
}
