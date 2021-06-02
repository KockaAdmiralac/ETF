/**
 * USER103.cpp
 *
 * Tests getting threads by ID.
 * @see https://drive.google.com/open?id=11uyCIaCpMwSKIyfH7PFRzwGazAMxSnMa
 */
#include <thread.h>
#include <util.h>

const int n = 16;

void tick() {}

class TestThread : public Thread {
    public:
        TestThread(): Thread(4096, 2) {}
        ~TestThread() {
            waitToComplete();
        }
    protected:
        void run();
};

void TestThread::run() {
    int buffer = 2;
    for (int i = 0; i < 32000; i++) {
        buffer = 4096/2048;
        for (int j = 0; j < 1024; j++) {
            buffer = buffer * 2;
            if (buffer % 2) {
                buffer = 2;
            }
        }
    }
}

int userMain(int argc, char** argv) {
    (void) argc;
    (void) argv;
    syncPrint("Test starts: %d threads.\n", n);
    int i;
    TestThread threads[n];
    for (i = 0; i < n; i++) {
        threads[i].start();
    }
    for (i = 0; i < n; i++) {
        threads[i].waitToComplete();
        syncPrint("%d. Done!\n", Thread::getThreadById(i + 2)->getId());
    }
    syncPrint("Test ends.\n");
    return 0;
}
