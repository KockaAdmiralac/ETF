/**
 * pcb.h
 *
 * Interface to the kernel implementation of threads.
 */
#ifndef _PCB_H_
#define _PCB_H_
#include <list.h>
#include <kern_evt.h>
#include <kern_sem.h>
#include <thread.h>
#include <vector.h>

/**
 * Kernel implementation of a thread.
 */
class PCB {
    public:
        enum Status {
            INITIALIZING,
            RUNNING,
            READY,
            BLOCKED,
            TERMINATING,
            MATERNITY_LEAVE
        };
        static const StackSize minimumStackSize;
        static const StackSize maximumStackSize;
    // Encapsulation was a mistake.
    protected:
        friend class Thread;
        friend class Kernel;
        friend class KernelSem;
        friend class KernelEv;

        PCB(Thread& myThread, StackSize stackSize, Time timeSlice);
        // This should be overwritten by subclasses.
        PCB();
        ~PCB();

        Thread* myThread;
        ID id;
        unsigned bp;
        unsigned sp;
        unsigned ss;
        Status status;
        unsigned* stack;
        int timeSlice;
        unsigned stackSize;
        PtrList blocked;
        int semaphoreResult;
        PCB* parent;
        int parentIndex;
        PtrVector children;
        static volatile PCB* running;
        static PtrVector allPCBs;
        static PCB* copyStackFrom;
        static PCB* copyStackTo;

        virtual void start();
        virtual void waitToComplete();
        void exit() volatile;
        void waitForChildren() volatile;
        static PCB* getPCBById(ID id);
        static void execute();
        static void interrupt copyStack(...);
};

#endif
