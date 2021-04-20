/**
 * kern_sem.h
 *
 * Interface of the kernel implementation of semaphores.
 */
#ifndef _KERN_SEM_H_
#define _KERN_SEM_H_
#include <sem.h>

/**
 * Kernel implementation of a semaphore.
 */
class KernelSem {
    private:
        friend class Semaphore;
        Semaphore* mySemaphore;
        int value;
};

#endif
