/**
 * USER105.cpp
 *
 * Tests whether frequently dispatching threads causes issues.
 * @see https://drive.google.com/open?id=11uyCIaCpMwSKIyfH7PFRzwGazAMxSnMa
 */
#include <thread.h>
#include <util.h>

const int n = 10;

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
    for (int i = 0; i < 32000; i++) {
        for (int j = 0; j < 16; j++) {
            dispatch();
            syncPrint(".");
        }
    }
}

void tick() {}

int userMain(int argc, char** argv) {
    (void) argc;
    (void) argv;
    syncPrint("Test starts.\n");
    TestThread t[n];
    int i;
    for (i = 0; i < n; i++) {
        t[i].start();
    }
    for (i = 0; i < n; i++) {
        t[i].waitToComplete();
    }
    syncPrint("Test ends.\n");
    return 0;
}
