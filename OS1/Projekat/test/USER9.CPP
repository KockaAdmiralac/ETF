/**
 * USER9.CPP
 *
 * Creates as many child threads as possible and then exits them all.
 * Child threads are never actually removed from memory, only terminated.
 */
#include <kernel.h>
#include <test.h>
#include <thread.h>

class ForkThread : public Thread {
    public:
        ForkThread() : Thread(1, 1) {}
        virtual void run();
        virtual Thread* clone() const {
            return new ForkThread();
        }
        ~ForkThread() {
            waitToComplete();
        }
        static volatile int failedFork;
};

volatile int ForkThread::failedFork = false;

void ForkThread::run() {
    while (!failedFork) {
        ID forked = fork();
        if (forked < 0) {
            syncPrint("Failed to fork in thread %d!\n", getRunningId());
            failedFork = true;
            break;
        } else if (forked == 0) {
            syncPrint("We are in child %d\n", getRunningId());
        } else {
            syncPrint("Cloned thread: %d\n", forked);
            dumbSleep(10000);
        }
    }
    waitForForkChildren();
}

void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    ForkThread t;
    t.start();
    return 0;
}
