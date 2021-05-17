/**
 * t_kernel.h
 *
 * Test module for basic kernel functions.
 */
#include <dos.h>
#include <event.h>
#include <ivt.h>
#include <kernel.h>
#include <list.h>
#include <semaphor.h>
#include <stdlib.h>
#include <test.h>
#include <thread.h>
#include <time.h>

void dumbSleep(int delay) {
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < delay; ++j);
    }
}

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
    syncPrint("First message from thread %d\n", getId());
    for (unsigned i = 0; i < times; ++i) {
        syncPrint("%s from thread %d\n", message, getId());
        dumbSleep(delay * 1000);
    }
    syncPrint("Last message from thread %d\n", getId());
}

/**
 * Tests threads which simply echo the message passed a specified amount of
 * times in specified intervals.
 */
void testEchoThreads() {
    lockInterrupts("testEchoThreads (1)");
    EchoThread** threads = new EchoThread*[256];
    unlockInterrupts("testEchoThreads (1)");
    for (unsigned i = 0; i < 256; ++i) {
        lockInterrupts("testEchoThreads (2)");
        threads[i] = new EchoThread("ECHO", i % 4, i % 10);
        unlockInterrupts("testEchoThreads (2)");
        threads[i]->start();
        if (i % 20 == 0) {
            syncPrint("Dispatching main\n");
            dispatch();
        }
    }
    lockInterrupts("testEchoThreads (3)");
    for (unsigned j = 0; j < 256; ++j) {
        delete threads[j];
    }
    delete[] threads;
    unlockInterrupts("testEchoThreads (3)");
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
        lockInterrupts("ListThread::run");
        int number = rand();
        int index = listIndex++;
        listNumbers[index] = number;
        syncPrint("Thread %d generated number %d at index %d\n", getId(), number, index);
        unlockInterrupts("ListThread::run");
        list.insert((void*) &listNumbers[index]);
        dumbSleep(number % 1000);
    }
}

/**
 * Tests threads that insert random data into a list.
 */
void testListThreads() {
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
    syncPrint("THERE SHOULD BE NO THREADS INTERRUPTING\n");
    for (i = 0; i < 256; ++i) {
        int* data = (int*) list.remove();
        if (data == nullptr) {
            syncPrint("Data missing from index %d!\n", i);
            return;
        }
        int number = *data;
        for (unsigned j = 0; j < 256; ++j) {
            if (listNumbers[j] == number) {
                break;
            }
        }
        if (j == 256) {
            syncPrint("Number %d not found!\n", number);
        }
    }
    if (list.remove() != nullptr) {
        syncPrint("More data in list!\n");
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
        syncPrint("Prodooc\n");
        sem.signal();
        dumbSleep(rand() % 1000);
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
        int waitResult = sem.wait(0);
        if (waitResult) {
            syncPrint("Consoomed %d\n", getId());
        } else {
            syncPrint("CONSOOM FAILED %d\n", getId());
        }
        dumbSleep(rand() % 1000);
    }
}

void testProducerConsumer() {
    Producer p;
    Consumer c[10];
    lockInterrupts("testProducerConsumer");
    p.start();
    for (unsigned i = 0; i < 10; ++i) {
        c[i].start();
    }
    unlockInterrupts("testProducerConsumer");
}

PREPAREENTRY(0x9, true)

void testEventListener() {
    Event evt(0x9);
    for (unsigned i = 0; i < 64; ++i) {
        syncPrint("Key %d\n", i);
        evt.wait();
    }
}

Thread* threads[500];

void testThreadOveruse() {
    for (unsigned i = 0; i < 500; ++i) {
        syncPrint("Creating %d\n", i);
        lockInterrupts("testThreadOveruse (1)");
        threads[i] = new EchoThread("This shouldn't be printed");
        unlockInterrupts("testThreadOveruse (1)");
        if (threads[i] == nullptr || threads[i]->getId() == -1) {
            syncPrint("Failed at index %d\n", i);
            if (threads[i] != nullptr) {
                lockInterrupts("testThreadOveruse (2)");
                delete threads[i];
                unlockInterrupts("testThreadOveruse (2)");
            }
            break;
        }
    }
    for (unsigned j = 0; j < i; ++j) {
        lockInterrupts("testThreadOveruse (3)");
        delete threads[j];
        unlockInterrupts("testThreadOveruse (3)");
    }
    syncPrint("Done\n");
}

class ExitThread : public Thread {
    public:
        ExitThread() : Thread(1, 1) {}
        virtual void run();
        ~ExitThread() {
            waitToComplete();
        }
};

void ExitThread::run() {
    syncPrint("Thread %d sleeping\n", getId());
    dumbSleep(rand() % 1000);
    syncPrint("Thread %d exiting\n", getId());
    exit();
}

void testThreadExiting() {
    ExitThread threads[20];
    for (unsigned i = 0; i < 20; ++i) {
        threads[i].start();
    }
    dispatch();
    dispatch();
    dispatch();
    dispatch();
    syncPrint("You've had your chance!\n");
    Thread::exit();
}

class ForkThread : public Thread {
    public:
        ForkThread() : Thread(1, 0) {}
        virtual void run();
        virtual Thread* clone() const {
            return new ForkThread();
        }
        ~ForkThread() {
            waitToComplete();
        }
        static volatile int failedFork;
};

volatile int ForkThread::failedFork = false;

void ForkThread::run() {
    while (!failedFork) {
        ID forked = fork();
        if (forked < 0) {
            syncPrint("Failed to fork in thread %d!\n", getRunningId());
            failedFork = true;
            break;
        } else if (forked == 0) {
            syncPrint("We are in child %d\n", getRunningId());
        } else {
            syncPrint("Cloned thread: %d\n", forked);
        }
    }
    waitForForkChildren();
}

void testThreadClone() {
    ForkThread t;
    t.start();
}

#ifdef KERNEL_DEBUG
void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    syncPrint("userMain\n");
    testThreadClone();
    return 0;
}
#endif

void testKernel() {
    syncPrint("==================================== kernel ====================================\n");
    char* argv[] = {"kernel"};
    Kernel::run(1, argv);
}
