/**
 * USER12.CPP
 *
 * 3rd task on first colloquium, march 2015.
 */
#include <kernel.h>
#include <semaphor.h>
#include <thread.h>
#include <stdlib.h>
#include <test.h>
#include <iostream.h>

void tick() {}

void writer(char* c, int* flag) {
    while (1) {
        while (*flag == 1);
        cin >> (*c);
        *flag = 1;
    }
}

void reader(char* c, int* flag) {
    while (1) {
        while (*flag == 0);
        cout << (*c);
        *flag = 0;
    }
}

void pipe() {
    static char c;
    static int flag = 0;
    if (Thread::fork()) {
        writer(&c,&flag);
    } else {
        reader(&c,&flag);
    }
}

class ForkThread : public Thread {
    public:
        ForkThread() : Thread(1, 1) {}
        ~ForkThread() {
            waitToComplete();
        }
        virtual Thread* clone() const {
            return new ForkThread();
        }
        virtual void run() {
            pipe();
        }
};

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    ForkThread t;
    t.start();
    return 0;
}
