/**
 * USER109.cpp
 *
 * Waiting on semaphores test.
 * @see https://drive.google.com/open?id=11uyCIaCpMwSKIyfH7PFRzwGazAMxSnMa
 */
#include <iostream.h>
#include <semaphor.h>
#include <stdlib.h>
#include <thread.h>
#include <util.h>

const int n = 1;
int t = -1;

Semaphore s(0);

class TestThread : public Thread {
    public:
        TestThread(): Thread() {}
        ~TestThread() {
            waitToComplete();
        }
    protected:
        void run();
};

void TestThread::run() {
    syncPrint("Thread waits for 10 units of time...\n");
    t = 0;
    s.wait(10);
    syncPrint("Thread finished.\n");
    s.signal();
}

void tick() {
    t++;
    if (t) {
        syncPrint("%d\n", t);
    }
}

int userMain(int argc, char** argv) {
    (void) argc;
    (void) argv;
    syncPrint("Test starts.\n");
    TestThread t[n];
    int i;
    for(i = 0; i < n; i++) {
        t[i].start();
    }
    for(i = 0; i < n; i++) {
        t[i].waitToComplete();
    }
    syncPrint("Test ends.\n");
    return 0;
}
