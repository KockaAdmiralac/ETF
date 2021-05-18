/**
 * USER8.CPP
 *
 * Waits for a few threads to exit and then explicitly exits the program.
 */
#include <kernel.h>
#include <stdlib.h>
#include <test.h>
#include <thread.h>

class ExitThread : public Thread {
    public:
        ExitThread() : Thread(1, 1) {}
        virtual void run();
        ~ExitThread() {
            waitToComplete();
        }
};

void ExitThread::run() {
    syncPrint("Thread %d sleeping\n", getId());
    dumbSleep(rand() % 1000);
    syncPrint("Thread %d exiting\n", getId());
    exit();
}

void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    ExitThread threads[20];
    for (unsigned i = 0; i < 20; ++i) {
        threads[i].start();
    }
    dispatch();
    dispatch();
    dispatch();
    dispatch();
    syncPrint("You've had your chance!\n");
    Thread::exit();
    return 0;
}
