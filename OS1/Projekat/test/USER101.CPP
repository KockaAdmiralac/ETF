/**
 * USER101.cpp
 *
 * Tests whether waiting for other threads works.
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
    for(int i = 0; i < 32000; i++) {
        for (int j = 0; j < 32000; j++);
    }
    syncPrint("Thread %d: loop1 ends, dispatch\n",getId());
    dispatch();
    syncPrint("Thread %d: loop2 starts\n",getId());
    for (int k = 0; k < 20000; k++);
    syncPrint("Thread %d: loop2 ends\n",getId());
}

class WaitThread: public Thread {
    public:
        WaitThread(TestThread* t1, TestThread* t2): Thread(), t1(t2), t2(t2) {}
        ~WaitThread() {
            waitToComplete();
        }
    protected:
        void run() {
            syncPrint("Starting tests...\n");
            t1->waitToComplete();
            syncPrint("Test 1 completed!\n");
            t2->waitToComplete();
            syncPrint("Test 2 completed!\n");
        }
    private:
        TestThread* t1;
        TestThread* t2;
};

void tick() {}

int userMain(int argc, char** argv) {
    (void) argc;
    (void) argv;
    syncPrint("User main starts\n");
    TestThread t1,t2;
    WaitThread w(&t1, &t2);
    t1.start();
    t2.start();
    w.start();
    syncPrint("User main ends\n");
    return 16;
}
