/**
 * USER7.CPP
 *
 * Creates the maximum amount of threads possible within the system memory
 * and frees them, hoping nothing will go wrong.
 */
#include <kernel.h>
#include <thread.h>
#include <util.h>

class OveruseThread : public Thread {
    public:
        OveruseThread() : Thread(1, 20) {}
        virtual void run() {
            syncPrint("This should not happen.\n");
        }
        ~OveruseThread() {
            waitToComplete();
        }
};

void tick() {}

Thread* threads[500];

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    unsigned i = 0;
    for (; i < 500; ++i) {
        syncPrint("Creating %d\n", i);
        lockInterrupts("testThreadOveruse (1)");
        threads[i] = new OveruseThread();
        unlockInterrupts("testThreadOveruse (1)");
        if (threads[i] == nullptr || threads[i]->getId() == -1) {
            syncPrint("Failed at index %d\n", i);
            if (threads[i] != nullptr) {
                lockInterrupts("testThreadOveruse (2)");
                delete threads[i];
                unlockInterrupts("testThreadOveruse (2)");
            }
            break;
        }
    }
    for (unsigned j = 0; j < i; ++j) {
        lockInterrupts("testThreadOveruse (3)");
        delete threads[j];
        unlockInterrupts("testThreadOveruse (3)");
    }
    syncPrint("Done\n");
    return 0;
}
