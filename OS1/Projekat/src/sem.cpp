/**
 * sem.cpp
 *
 * Implementation of semaphores.
 */
#include <kern_sem.h>
#include <kernel.h>
#include <sem.h>
#include <util.h>

/**
 * Constructs a new semaphore.
 * @param init Initial semaphore value
 */
Semaphore::Semaphore(int init) {
    lockInterrupts
    myImpl = new KernelSem(init);
    unlockInterrupts
    if (assert(myImpl != nullptr, "Kernel semaphore failed to allocate!")) {
        return;
    }
    if (myImpl->id < 0) {
        lockInterrupts
        delete myImpl;
        myImpl = nullptr;
        unlockInterrupts
    }
}

/**
 * Frees resources used by the semaphore.
 */
Semaphore::~Semaphore() {
    if (myImpl != nullptr) {
        lockInterrupts
        delete myImpl;
        unlockInterrupts
        myImpl = nullptr;
    }
}

/**
 * Waits on the semaphore until the value is above zero or specified time for
 * waiting passes.
 *
 * May cause a synchronous context switch if the value is zero.
 * @param maxTimeToWait Maxiumum amount of time that the semaphore should be
 *                      awaited for, or zero if the waiting time is unlimited
 * @returns Whether the wait was successful
 */
int Semaphore::wait(Time maxTimeToWait = 0) {
    if (myImpl == nullptr) {
        return false;
    }
    return myImpl->wait(maxTimeToWait);
}

/**
 * Increases the semaphore value and unblocks threads that were previously
 * blocked by the semaphore.
 */
void Semaphore::signal() {
    if (myImpl != nullptr) {
        myImpl->signal();
    }
}

/**
 * Returns the semaphore value.
 */
int Semaphore::val() const {
    if (myImpl == nullptr) {
        return 0;
    }
    return (int) myImpl->value;
}
