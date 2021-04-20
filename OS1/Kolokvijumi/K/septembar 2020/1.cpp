#include <cstdlib>
#include <setjmp.h>
#include <string.h>
#include <exception>

class ThreadCreationException : std::exception {
};

class Thread {
public:
    static Thread *running;
    jmp_buf context;
    size_t sp;
    void *stack;
    Thread(void (*body)(void*));
};

class Scheduler {
public:
    static void put(Thread*);
};

const size_t STACK_SIZE = sizeof(char) * 64;

void new_thread(void*) {
    longjmp(Thread::running->context, 1);
}

Thread *t_fork() {
    Thread *newThread = new Thread(new_thread);
    newThread->stack = malloc(STACK_SIZE * sizeof(char));
    if (newThread->stack == NULL) {
        throw ThreadCreationException();
    }
    size_t currStackSize = Thread::running->sp * sizeof(int) / sizeof(char);
    memcpy(newThread->stack - currStackSize, Thread::running->stack - currStackSize, currStackSize);
    Scheduler::put(newThread);
    int sjmp = setjmp(newThread->context);
    if (sjmp == 0) {
        return newThread;
    } else if (sjmp == 1) {
        return NULL;
    } else {
        throw ThreadCreationException();
    }
}
