/**
 * sem.h
 *
 * Interface to semaphores. Non-cosmetic changes are NOT ALLOWED.
 */
#ifndef _SEM_H_
#define _SEM_H_

typedef unsigned int Time;

class KernelSem;

/**
 * Interface to a standard semaphore.
 */
class Semaphore {
    public:
        Semaphore(int init = 1);
        virtual ~Semaphore();
        virtual int wait(Time maxTimeToWait);
        virtual void signal();
        int val() const;
    private:
        KernelSem* myImpl;
};

#endif
