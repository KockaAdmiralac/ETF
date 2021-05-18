/**
 * USER3.CPP
 *
 * Tests threads which simply echo the message passed a specified amount of
 * times in specified intervals.
 */
#include <kernel.h>
#include <thread.h>
#include <test.h>
#include <util.h>

class EchoThread : public Thread {
    public:
        EchoThread(const char* message, unsigned times=1, unsigned delay=1) :
            Thread(1, 20), message(message), times(times), delay(delay) {}
        virtual void run();
        ~EchoThread() {
            waitToComplete();
        }
    private:
        const char* message;
        unsigned times;
        unsigned delay;
};

void EchoThread::run() {
    syncPrint("First message from thread %d\n", getId());
    for (unsigned i = 0; i < times; ++i) {
        syncPrint("%s from thread %d\n", message, getId());
        dumbSleep(delay * 1000);
    }
    syncPrint("Last message from thread %d\n", getId());
}

void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    lockInterrupts("userMain3 (1)");
    EchoThread** threads = new EchoThread*[256];
    unlockInterrupts("userMain3 (1)");
    for (unsigned i = 0; i < 256; ++i) {
        lockInterrupts("userMain3 (2)");
        threads[i] = new EchoThread("ECHO", i % 4, i % 10);
        unlockInterrupts("userMain3 (2)");
        threads[i]->start();
        if (i % 20 == 0) {
            syncPrint("Dispatching main\n");
            dispatch();
        }
    }
    lockInterrupts("userMain3 (3)");
    for (unsigned j = 0; j < 256; ++j) {
        delete threads[j];
    }
    delete[] threads;
    unlockInterrupts("userMain3 (3)");
    return 0;
}
