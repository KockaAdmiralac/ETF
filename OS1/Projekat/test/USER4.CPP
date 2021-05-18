/**
 * USER4.CPP
 *
 * Tests threads that insert random data into a list.
 */
#include <kernel.h>
#include <list.h>
#include <stdlib.h>
#include <test.h>

PtrList list;
volatile int listNumbers[256];
volatile unsigned listIndex = 0;

class ListThread : public Thread {
    public:
        ListThread() : Thread(1, rand() % 10) {}
        virtual void run();
};

void ListThread::run() {
    for (unsigned i = 0; i < 4; ++i) {
        lockInterrupts("ListThread::run");
        int number = rand();
        int index = listIndex++;
        listNumbers[index] = number;
        syncPrint("Thread %d generated number %d at index %d\n", getId(), number, index);
        unlockInterrupts("ListThread::run");
        list.insert((void*) &listNumbers[index]);
        dumbSleep(number % 1000);
    }
}

void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    ListThread thrs[64];
    unsigned i;
    for (i = 0; i < 64; ++i) {
        thrs[i].start();
        if ((i + 1) % 16 == 0) {
            dispatch();
        }
    }
    for (i = 0; i < 64; ++i) {
        thrs[i].waitToComplete();
    }
    syncPrint("THERE SHOULD BE NO THREADS INTERRUPTING\n");
    for (i = 0; i < 256; ++i) {
        int* data = (int*) list.remove();
        if (data == nullptr) {
            syncPrint("Data missing from index %d!\n", i);
            return 1;
        }
        int number = *data;
        unsigned j = 0;
        for (; j < 256; ++j) {
            if (listNumbers[j] == number) {
                break;
            }
        }
        if (j == 256) {
            syncPrint("Number %d not found!\n", number);
        }
    }
    if (list.remove() != nullptr) {
        syncPrint("More data in list!\n");
    }
    return 0;
}
