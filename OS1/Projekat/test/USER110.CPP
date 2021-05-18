/**
 * USER110.cpp
 *
 * Waiting on semaphores test 2.
 * @see https://drive.google.com/open?id=11uyCIaCpMwSKIyfH7PFRzwGazAMxSnMa
 */
#include <iostream.h>
#include <semaphor.h>
#include <stdlib.h>
#include <thread.h>
#include <util.h>

int t = -1;

Semaphore s(0);

class TestThread : public Thread {
    public:
        TestThread(Time wt): Thread(), waitTime(wt) {}
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
    s.signal();
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
    TestThread t1(15);
    TestThread t2(10);
    TestThread t3(30);
    t1.start();
    t2.start();
    t3.start();
    s.wait(5);
    s.signal();
    s.wait(0);
    s.signal();
    syncPrint("Test ends.\n");
    return 0;
}


