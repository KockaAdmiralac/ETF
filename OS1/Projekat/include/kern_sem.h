/**
 * kern_sem.h
 *
 * Interface of the kernel implementation of semaphores.
 */
#ifndef _KERN_SEM_H_
#define _KERN_SEM_H_
#include <kernel.h>
#include <list.h>
#include <sem.h>
#include <vector.h>

/**
 * Kernel implementation of a semaphore.
 */
class KernelSem {
    private:
        friend class Kernel;
        friend class Semaphore;

        KernelSem(int value);
        ~KernelSem();
        int wait(Time maxTimeToWait);
        void signal();

        Semaphore* mySemaphore;
        volatile int value;
        int id;
        PtrWaitingList blocked;
        static PtrVector allSemaphores;
};

#endif
