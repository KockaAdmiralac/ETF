/**
 * USER10.CPP
 *
 * Creates as many child threads as possible and then exits them all.
 * Same as USER9.CPP but forks the main thread instead.
 */
#include <kernel.h>
#include <thread.h>

volatile int failedFork = false;

void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    while (!failedFork) {
        ID forked = Thread::fork();
        if (forked < 0) {
            syncPrint("Failed to fork in thread %d!\n", Thread::getRunningId());
            failedFork = true;
            break;
        } else if (forked == 0) {
            syncPrint("We are in child %d\n", Thread::getRunningId());
        } else {
            syncPrint("Cloned thread: %d\n", forked);
        }
    }
    Thread::waitForForkChildren();
    return 0;
}
