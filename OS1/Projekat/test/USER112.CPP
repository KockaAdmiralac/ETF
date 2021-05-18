/**
 * USER113.cpp
 *
 * Waiting on semaphores test 4.
 * @see https://drive.google.com/open?id=11uyCIaCpMwSKIyfH7PFRzwGazAMxSnMa
 */
#include <iostream.h>
#include <semaphor.h>
#include <stdlib.h>
#include <thread.h>
#include <util.h>

int t = -1;
const int n = 15;
Semaphore s(1);

class TestThread : public Thread {
    public:
        TestThread(Time wt) : Thread(), waitTime(wt) {}
        ~TestThread() {
            waitToComplete();
        }
    protected:
        void run();
    private:
        Time waitTime;
};

void TestThread::run() {
    syncPrint("Thread %d waits for %d units of time.\n", getId(), waitTime);
    int r = s.wait(waitTime);
    if (getId() % 2) {
        s.signal();
    }
    syncPrint("Thread %d finished: r = %d\n", getId(), r);
}

void tick() {
    t++;
    if (t) {
        syncPrint("%d\n",t);
    }
}

int userMain(int argc, char** argv) {
    (void) argc;
    (void) argv;
    syncPrint("Test starts.\n");
    TestThread* t[n];
    int i;
    for (i = 0; i < n; i++) {
        t[i] = new TestThread(5 * (i + 1));
        t[i]->start();
    }
    for(i = 0; i < n; i++) {
        t[i]->waitToComplete();
    }
    delete t;
    syncPrint("Test ends.\n");
    return 0;
}


