/**
 * USER108.cpp
 *
 * Basic semaphore test.
 * @see https://drive.google.com/open?id=11uyCIaCpMwSKIyfH7PFRzwGazAMxSnMa
 */
#include <iostream.h>
#include <semaphor.h>
#include <stdlib.h>
#include <thread.h>
#include <util.h>

const int n = 5;
int count = 10;

Semaphore s(2);

class TestThread : public Thread {
    public:
        TestThread() : Thread(1, 1) {}
        ~TestThread() {
            waitToComplete();
        }
    protected:
        void run();
};

void TestThread::run() {
    s.wait(0);
    cout << "Thread " << getId() << " in critical section." << endl;
    for (unsigned int i = 0; i < 640; i++) {
        for (unsigned int j = 0; j < 640; j++);
    }
    s.signal();
}

void tick() {}

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
