/**
 * USER106.cpp
 *
 * Tests whether two threads that block each other cause issues or just
 * activate the idle thread.
 * @see https://drive.google.com/open?id=11uyCIaCpMwSKIyfH7PFRzwGazAMxSnMa
 */
#include <thread.h>
#include <util.h>

class TestThread : public Thread {
    public:
        TestThread(TestThread **thread): Thread(), t(thread) {}
        ~TestThread() {
            waitToComplete();
        }
    protected:
        void run();
    private:
        TestThread **t;
};

void TestThread::run() {
    (*t)->waitToComplete();
}

void tick() {}

int userMain(int argc, char** argv) {
    (void) argc;
    (void) argv;
    syncPrint("Test starts.\n");
    TestThread *t1,*t2;
    t1 = new TestThread(&t2);
    t2 = new TestThread(&t1);
    t1->start();
    t2->start();
    delete t1;
    delete t2;
    syncPrint("Test ends.\n");
    return 0;
}


