/**
 * pcb.h
 *
 * Interface to the kernel implementation of threads.
 */
#ifndef _PCB_H_
#define _PCB_H_
#include <list.h>
#include <thread.h>
#include <vector.h>

/**
 * Kernel implementation of a thread.
 */
class PCB {
    public:
        PCB(Thread& myThread, StackSize stackSize, Time timeSlice);
        enum Status {
            INITIALIZING,
            RUNNING,
            READY,
            BLOCKED,
            TERMINATING
        };
        ~PCB();
        static const StackSize minimumStackSize;
        static const StackSize maximumStackSize;
    // Encapsulation was a mistake.
    protected:
        friend class Thread;
        friend class Kernel;
        #ifdef KERNEL_DEBUG
        friend void testThreadPrivates();
        #endif

        // This should be overwritten by subclasses.
        PCB();

        Thread* myThread;
        ID id;
        unsigned bp;
        unsigned sp;
        unsigned ss;
        Status status;
        unsigned* stack;
        int timeSlice;
        PtrList blocked;
        static volatile PCB* running;
        static PtrVector allPCBs;

        virtual void start();
        virtual void waitToComplete();
        static PCB* getPCBById(ID id);
        static void execute();
};

#endif
