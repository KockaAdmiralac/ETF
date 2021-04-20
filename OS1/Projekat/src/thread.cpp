/**
 * thread.cpp
 *
 * Implementation of the user interface to kernel threads.
 */
#include <kernel.h>
#include <pcb.h>
#include <thread.h>
#include <util.h>

/**
 * Creates the new execution context and starts the thread.
 */
void Thread::start() {
    if (assert(myPCB != nullptr, "Cannot start a thread with uninitialized PCB!")) {
        return;
    }
    myPCB->start();
}

/**
 * Blocks the calling thread until this thread has finished.
 */
void Thread::waitToComplete() {
    if (assert(myPCB != nullptr, "Cannot await a thread with uninitialized PCB!")) {
        return;
    }
    myPCB->waitToComplete();
    dispatch();
}

/**
 * Frees the PCB after the thread has finished.
 *
 * This needs to wait for the thread to finish because the call to start() is
 * non-blocking, and the calling thread would free the thread's resources while
 * they are still in use.
 */
Thread::~Thread() {
    if (myPCB != nullptr) {
        lockInterrupts
        delete myPCB;
        unlockInterrupts
        myPCB = nullptr;
    }
}

/**
 * Gets the ID of the thread.
 * @returns ID of the thread, or -1 if the PCB failed to initialize
 */
ID Thread::getId() {
    if (assert(myPCB != nullptr, "Cannot get ID of uninitialized PCB!")) {
        return -1;
    }
    return myPCB->id;
}

/**
 * Gets the ID of the currently running thread.
 * @returns ID of the currently running thread, or -1 if the PCB failed to
 *          initialize
 */
ID Thread::getRunningId() {
    if (assert(PCB::running != nullptr, "Cannot get ID of running uninitialized PCB!")) {
        return -1;
    }
    return PCB::running->id;
}

/**
 * Gets a thread with a specified ID.
 * @param id ID of the thread to get
 * @returns The thread with the specified ID, or nullptr if it doesn't exist
 */
Thread* Thread::getThreadById(ID id) {
    PCB* pcb = PCB::getPCBById(id);
    if (pcb == nullptr) {
        return nullptr;
    }
    return pcb->myThread;
}

/**
 * Constructs a thread, but does not run it.
 * @param stackSize Size of the kernel thread's stack in bytes, cannot be under
 *                  minimumStackSize and over maximumStackSize
 * @param timeSlice Amount of time in quants (55ms) that can pass before the
 *                  context asynchronously switches, 0 = infinite
 */
Thread::Thread(StackSize stackSize, Time timeSlice) {
    lockInterrupts
    myPCB = new PCB(*this, stackSize, timeSlice);
    unlockInterrupts
    if (assert(myPCB != nullptr, "PCB failed to allocate!")) {
        return;
    }
    if (assert(myPCB->status == PCB::INITIALIZING, "PCB failed to initialize!")) {
        lockInterrupts
        delete myPCB;
        unlockInterrupts
        return;
    }
}

/**
 * Explicitly initiates a synchronous context switch.
 */
void dispatch() {
    lock
    Kernel::contextSwitchOnDemand = true;
    Kernel::timer();
    unlock
}
