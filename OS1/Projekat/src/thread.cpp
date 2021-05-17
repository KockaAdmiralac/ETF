/**
 * thread.cpp
 *
 * Implementation of the user interface to kernel threads.
 */
#include <kernel.h>
#include <pcb.h>
#include <schedule.h>
#include <stdlib.h>
#include <thread.h>
#include <util.h>

/**
 * Creates the new execution context and starts the thread.
 */
void Thread::start() {
    if (ensure(myPCB != nullptr, "Cannot start a thread with uninitialized PCB!")) {
        return;
    }
    myPCB->start();
}

/**
 * Blocks the calling thread until this thread has finished.
 */
void Thread::waitToComplete() {
    if (myPCB == nullptr) {
        return;
    }
    myPCB->waitToComplete();
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
        lockInterrupts("Thread::~Thread");
        delete myPCB;
        myPCB = nullptr;
        unlockInterrupts("Thread::~Thread");
    }
}

/**
 * Gets the ID of the thread.
 * @returns ID of the thread, or -1 if the PCB failed to initialize
 */
ID Thread::getId() {
    if (ensure(myPCB != nullptr, "Cannot get ID of uninitialized PCB!")) {
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
    if (ensure(PCB::running != nullptr, "Cannot get ID of running uninitialized PCB!")) {
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
 * Forks the current thread.
 * @returns ID of the newly-created thread, 0 if returning from the child
 *          thread and -1 if an error occurred
 */
ID Thread::fork() {
    if (ensure(PCB::running != nullptr, "Attempted to fork a thread when no thread is running!")) {
        return -1;
    }
    PCB* runningCopy = (PCB*) PCB::running;
    if (ensure(runningCopy->myThread != nullptr, "Cannot fork the main thread!")) {
        return -1;
    }
    Thread* newThread = runningCopy->myThread->clone();
    if (newThread == nullptr || newThread->myPCB == nullptr) {
        return -1;
    }
    lockInterrupts("Thread::fork");
    PCB::copyStackFrom = runningCopy;
    PCB::copyStackTo = newThread->myPCB;
    PCB::copyStack();
    // From now on, we are sure there are two threads running through the same
    // code here.
    if (PCB::running == runningCopy) {
        // Run the child thread.
        newThread->myPCB->parent = runningCopy;
        int index = runningCopy->children.put(newThread->myPCB);
        if (index < 0) {
            delete newThread;
            unlockInterrupts("Thread::fork (1)");
            return -1;
        }
        newThread->myPCB->parentIndex = index;
        newThread->start();
        unlockInterrupts("Thread::fork (2)");
        return newThread->getId();
    }
    // We don't unlock interrupts here because they have already been unlocked
    // by the parent thread returning from this same method.
    return 0;
}

/**
 * Finishes the current thread.
 */
void Thread::exit() {
    if (ensure(PCB::running != nullptr, "Attempted exit when no thread is running!")) {
        return;
    }
    if (ensure(PCB::running->myThread != nullptr, "You cannot exit the loop thread!")) {
        return;
    }
    if (PCB::running->myThread == Kernel::mainThread) {
        // We are exiting the main thread.
        Kernel::cleanup();
        ::exit(0);
    } else {
        PCB::running->exit();
    }
}

/**
 * Waits until all child threads have finished.
 */
void Thread::waitForForkChildren() {
    if (ensure(PCB::running != nullptr, "Attempted waiting for children when no thread is running!")) {
        return;
    }
    PCB::running->waitForChildren();
}

/**
 * Creates a new instance of the current thread.
 *
 * This does not make the cloned thread a child of the original thread,
 * because the responsibility of freeing it is not on the kernel but rather
 * on the user.
 * Also because the method is marked const, duh.
 * @returns Pointer to the cloned thread, or null on error
 */
Thread* Thread::clone() const {
    ensure(false, "Thread::clone() has not been overriden before calling!");
    return nullptr;
}

/**
 * Constructs a thread, but does not run it.
 * @param stackSize Size of the kernel thread's stack in bytes, cannot be under
 *                  minimumStackSize and over maximumStackSize
 * @param timeSlice Amount of time in quants (55ms) that can pass before the
 *                  context asynchronously switches, 0 = infinite
 */
Thread::Thread(StackSize stackSize, Time timeSlice) {
    lockInterrupts("Thread::Thread");
    myPCB = new PCB(*this, stackSize, timeSlice);
    if (ensure(myPCB != nullptr, "PCB failed to allocate!")) {
        unlockInterrupts("Thread::Thread (1)");
        return;
    }
    if (ensure(myPCB->status == PCB::INITIALIZING, "PCB failed to initialize!")) {
        delete myPCB;
        myPCB = nullptr;
        unlockInterrupts("Thread::Thread (2)");
        return;
    }
    unlockInterrupts("Thread::Thread (3)");
}

/**
 * Explicitly initiates a synchronous context switch.
 */
void dispatch() {
    lock
    ensure(!Kernel::cannotInterrupt, "Kernel cannot interrupt during dispatch()!");
    Kernel::contextSwitchOnDemand = true;
    Kernel::timer();
    unlock
}
