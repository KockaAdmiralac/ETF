/**
 * USER111.cpp
 *
 * Waiting on semaphores test 3.
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
        TestThread(Time WT): Thread(), waitTime(WT){}
        ~TestThread() {
            waitToComplete();
        }
    protected:
        void run();
    private:
        Time waitTime;
};

void TestThread::run() {
    syncPrint("Thread %d waits for %d units of time.\n",getId(),waitTime);
    int r = s.wait(waitTime);
    s.signal();
    syncPrint("Thread %d finished: r = %d\n", getId(),r);
}

void tick() {}

Semaphore* mutex = 0;

class Znak : public Thread {
    public:
        Znak(char znak, int n) : Thread(), znak(znak), n(n) {}
        virtual ~Znak() {
            waitToComplete();
        }
        void run();
    private:
        char znak;
        int n;
};

void Znak::run() {
    for (long i = 0; i < 1000; i++) {
        if (mutex->wait(n)) {
            cout << znak;
            mutex->signal();
        }
    }
    if (mutex->wait(n)) {
        cout << endl << znak << " finished" << endl;
        mutex->signal();
    }
}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    mutex = new Semaphore(1);
    Znak* a = new Znak('a', 10);
    Znak* b = new Znak('b', 15);
    Znak* c = new Znak('c', 20);
    a->start();
    b->start();
    c->start();
    delete a;
    delete b;
    delete c;
    if (mutex->wait(1)) {
        cout << endl << "userMain finished" << endl;
        mutex->signal();
    }
    delete mutex;
    return 0;
}
