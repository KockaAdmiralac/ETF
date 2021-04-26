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
            TERMINATING
        };
        static const StackSize minimumStackSize;
        static const StackSize maximumStackSize;
    // Encapsulation was a mistake.
    protected:
        friend class Thread;
        friend class Kernel;
        friend class KernelSem;
        friend class KernelEv;
        #ifdef KERNEL_DEBUG
        friend void testThreadPrivates();
        #endif

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
        PtrList blocked;
        int semaphoreResult;
        static volatile PCB* running;
        static PtrVector allPCBs;

        virtual void start();
        virtual void waitToComplete();
        static PCB* getPCBById(ID id);
        static void execute();
};

#endif
