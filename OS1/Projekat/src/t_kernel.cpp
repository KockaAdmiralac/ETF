/**
 * t_kernel.h
 *
 * Test module for basic kernel functions.
 */
#include <dos.h>
#include <kernel.h>
#include <list.h>
#include <sem.h>
#include <stdlib.h>
#include <test.h>
#include <thread.h>
#include <time.h>
#include <util.h>

class EchoThread : public Thread {
    public:
        EchoThread(const char* message, unsigned times=1, unsigned delay=1) :
            Thread(1, 20), message(message), times(times), delay(delay) {}
        virtual void run();
        ~EchoThread() {
            waitToComplete();
        }
    private:
        const char* message;
        unsigned times;
        unsigned delay;
};

void EchoThread::run() {
    lockInterrupts
    cout << "First message from thread " << getId() << endl;
    unlockInterrupts
    for (unsigned i = 0; i < times; ++i) {
        lockInterrupts
        cout << message << " from thread " << getId() << endl;
        unlockInterrupts
        sleep(delay);
    }
    lockInterrupts
    cout << "Last message from thread " << getId() << endl;
    unlockInterrupts
}

/**
 * Tests threads which simply echo the message passed a specified amount of
 * times in specified intervals.
 */
void testEchoThreads() {
    lockInterrupts
    EchoThread** threads = new EchoThread*[256];
    unlockInterrupts
    for (unsigned i = 0; i < 256; ++i) {
        lockInterrupts
        threads[i] = new EchoThread("ECHO", i % 4, i % 10);
        unlockInterrupts
        threads[i]->start();
        if (i % 20 == 0) {
            lockInterrupts
            cout << "Dispatching main" << endl;
            unlockInterrupts
            dispatch();
        }
    }
    lockInterrupts
    for (unsigned j = 0; j < 256; ++j) {
        delete threads[j];
    }
    delete threads;
    unlockInterrupts
}

class DumbThread : public Thread {
    public:
        DumbThread() : Thread(1, 20) {}
        virtual void run() {
            getThreadById(1)->waitToComplete();
            dispatch();
        }
        ~DumbThread() {
            waitToComplete();
        }
};

/**
 * Tests a thread which tries to do something dumb.
 */
void testDumbThreads() {
    DumbThread thr;
    thr.start();
}

PtrList list;
volatile int listNumbers[256];
volatile unsigned listIndex = 0;

class ListThread : public Thread {
    public:
        ListThread() : Thread(1, rand() % 10) {}
        virtual void run();
};

void ListThread::run() {
    for (unsigned i = 0; i < 4; ++i) {
        lockInterrupts
        int number = rand();
        int index = listIndex++;
        listNumbers[index] = number;
        cout << "Thread " << getId() << " generated number "
                << number << " at index " << index << endl;
        unlockInterrupts
        list.insert((void*) &listNumbers[index]);
        delay(number % 1000);
    }
}

/**
 * Tests threads that insert random data into a list.
 */
void testListThreads() {
    srand(time(nullptr));
    ListThread thrs[64];
    unsigned i;
    for (i = 0; i < 64; ++i) {
        thrs[i].start();
        if ((i + 1) % 16 == 0) {
            dispatch();
        }
    }
    for (i = 0; i < 64; ++i) {
        thrs[i].waitToComplete();
    }
    cout << "THERE SHOULD BE NO THREADS INTERRUPTING" << endl;
    for (i = 0; i < 256; ++i) {
        int* data = (int*) list.remove();
        if (data == nullptr) {
            cout << "Data missing from index " << i << "!" << endl;
            return;
        }
        int number = *data;
        for (unsigned j = 0; j < 256; ++j) {
            if (listNumbers[j] == number) {
                break;
            }
        }
        if (j == 256) {
            cout << "Number " << number << "not found!" << endl;
        }
    }
    if (list.remove() != nullptr) {
        cout << "More data in list!" << endl;
    }
}

Semaphore sem;

class Producer : public Thread {
    public:
        Producer() : Thread(1, 10) {}
        virtual void run();
        ~Producer() {
            waitToComplete();
        }
};

void Producer::run() {
    while (true) {
        lockInterrupts
        cout << "Prodooc" << endl;
        unlockInterrupts
        sem.signal();
        delay(rand() % 1000);
    }
}

class Consumer : public Thread {
    public:
        Consumer() : Thread(1, 10) {}
        virtual void run();
        ~Consumer() {
            waitToComplete();
        }
};

void Consumer::run() {
    while (true) {
        int waitResult = sem.wait(10000);
        lockInterrupts
        if (waitResult) {
            cout << "Consoomed " << getId() << endl;
        } else {
            cout << "Consom failed :( " << getId() << endl;
        }
        unlockInterrupts
        delay(rand() % 1000);
    }
}

void testProducerConsumer() {
    Producer p;
    Consumer c[10];
    p.start();
    for (unsigned i = 0; i < 10; ++i) {
        c[i].start();
    }
}

#ifdef KERNEL_DEBUG
void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    lockInterrupts
    cout << "userMain" << endl;
    unlockInterrupts
    testProducerConsumer();
    return 0;
}
#endif

void testKernel() {
    cout << "==================================== kernel ====================================" << endl;
    char* argv[] = {"kernel"};
    Kernel::run(1, argv);
}
