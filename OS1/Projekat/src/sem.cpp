/**
 * sem.cpp
 *
 * Implementation of semaphores.
 */
#include <kern_sem.h>
#include <sem.h>
#include <util.h>

/**
 * Constructs a new semaphore.
 * @param init Initial semaphore value
 */
Semaphore::Semaphore(int init) {
    //
}

/**
 * Frees resources used by the semaphore.
 */
Semaphore::~Semaphore() {
    delete myImpl;
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
    return false;
}

/**
 * Increases the semaphore value and unblocks threads that were previously
 * blocked by the semaphore.
 */
void Semaphore::signal() {
    //
}

/**
 * Returns the semaphore value.
 */
int Semaphore::val() const {
    return myImpl->value;
}
