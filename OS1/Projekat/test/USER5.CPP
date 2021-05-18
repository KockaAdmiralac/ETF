/**
 * USER5.CPP
 *
 * Tests whether a simple producer-consumer chain works.
 */
#include <kernel.h>
#include <thread.h>
#include <semaphor.h>
#include <stdlib.h>
#include <test.h>

Semaphore sem;

class Producer : public Thread {
    public:
        Producer() : Thread(1, 10) {}
        virtual void run();
        ~Producer() {
            waitToComplete();
        }
};

void Producer::run() {
    while (true) {
        syncPrint("Prodooc\n");
        sem.signal();
        dumbSleep(rand() % 1000);
    }
}

class Consumer : public Thread {
    public:
        Consumer() : Thread(1, 10) {}
        virtual void run();
        ~Consumer() {
            waitToComplete();
        }
};

void Consumer::run() {
    while (true) {
        int waitResult = sem.wait(0);
        if (waitResult) {
            syncPrint("Consoomed %d\n", getId());
        } else {
            syncPrint("CONSOOM FAILED %d\n", getId());
        }
        dumbSleep(rand() % 1000);
    }
}

void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    Producer p;
    Consumer c[10];
    lockInterrupts("userMain5");
    p.start();
    for (unsigned i = 0; i < 10; ++i) {
        c[i].start();
    }
    unlockInterrupts("userMain5");
    return 0;
}
