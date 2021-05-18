/**
 * USER102.cpp
 *
 * Tests asynchronous context switching.
 * @see https://drive.google.com/open?id=11uyCIaCpMwSKIyfH7PFRzwGazAMxSnMa
 */
#include <thread.h>
#include <util.h>

class TestThread : public Thread {
    public:
        TestThread(): Thread() {};
        ~TestThread() {
            waitToComplete();
        }
    protected:
        void run();
};

void TestThread::run() {
    syncPrint("Thread %d: loop1 starts\n", getId());
    for (int i = 0; i < 320; i++) {
        for (int j = 0; j < 320; j++);
    }
    syncPrint("Thread %d: loop1 ends, dispatch\n",getId());
    dispatch();
    for (int k = 0; k < 2000; k++);
    syncPrint("Thread %d: loop2 ends\n",getId());
}

void tick() {}

int userMain(int argc, char** argv) {
    (void) argc;
    (void) argv;
    syncPrint("User main starts\n");
    TestThread t1;
    TestThread t2;
    t1.start();
    t2.start();
    syncPrint("User main ends\n");
    return 16;
}
