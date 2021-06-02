/**
 * kern_sem.cpp
 *
 * Kernel implementation of semaphores.
 */
#include <kern_sem.h>
#include <pcb.h>
#include <schedule.h>
#include <util.h>

/**
 * All registered semaphores. This is used by the kernel for ticking.
 */
PtrVector KernelSem::allSemaphores;

/**
 * Constructs a kernel semaphore.
 * @param init Initial semaphore value
 */
KernelSem::KernelSem(int value) : value(value) {
    id = allSemaphores.put(this);
    ensure(id >= 0, "Failed to register kernel semaphore! Semaphore will not be able to wait.");
}

/**
 * De-registers a kernel semaphore.
 */
KernelSem::~KernelSem() {
    if (id >= 0) {
        allSemaphores.remove(id);
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
int KernelSem::wait(Time maxTimeToWait) {
    lockInterrupts("KernelSem::wait");
    if (--value >= 0) {
        // We needn't wait.
        unlockInterrupts("KernelSem::wait (1)");
        return true;
    }
    PCB::running->status = PCB::BLOCKED;
    if (ensure(blocked.insert((void*) PCB::running, maxTimeToWait), "Failed to wait for the semaphore to signal!")) {
        ++value;
        PCB::running->status = PCB::RUNNING;
        unlockInterrupts("KernelSem::wait (2)");
        return false;
    }
    unlockInterrupts("KernelSem::wait (3)");
    dispatch();
    return PCB::running->semaphoreResult;
}

/**
 * Increases the semaphore value and unblocks threads that were previously
 * blocked by the semaphore.
 */
void KernelSem::signal() {
    lockInterrupts("KernelSem::signal");
    if (++value <= 0) {
        PCB* unblocked = (PCB*) blocked.remove();
        if (ensure(unblocked != nullptr, "Unblocked thread in signal() is null!")) {
            unlockInterrupts("KernelSem::signal (1)");
            return;
        }
        unblocked->status = PCB::READY;
        unblocked->semaphoreResult = true;
        Scheduler::put(unblocked);
    }
    unlockInterrupts("KernelSem::signal (2)");
}
