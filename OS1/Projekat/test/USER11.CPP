/**
 * USER11.CPP
 *
 * Producer/consumer example but with fork().
 */
#include <kernel.h>
#include <semaphor.h>
#include <thread.h>
#include <stdlib.h>
#include <test.h>

void tick() {}

Semaphore sem;

void produce() {
    while (true) {
        syncPrint("Prodooc\n");
        sem.signal();
        dumbSleep(rand() % 1000);
    }
}

void consume() {
    while (true) {
        int waitResult = sem.wait(0);
        if (waitResult) {
            syncPrint("Consoomed %d\n", Thread::getRunningId());
        } else {
            syncPrint("CONSOOM FAILED %d\n", Thread::getRunningId());
        }
        dumbSleep(rand() % 1000);
    }
}

class ForkThread : public Thread {
    public:
        ForkThread() : Thread(1, 1) {}
        ~ForkThread() {
            waitToComplete();
        }
        virtual Thread* clone() const {
            return new ForkThread();
        }
        virtual void run();
};

void ForkThread::run() {
    ID lastId;
    for (unsigned i = 0; i < 11; ++i) {
        lastId = fork();
        if (lastId < 0) {
            syncPrint("Failed to fork on index %u!\n", lastId);
            return;
        } else if (lastId > 0) {
            if (i == 0) {
                produce();
            } else {
                consume();
            }
        }
    }
    waitForForkChildren();
}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    ForkThread t;
    t.start();
    return 0;
}
