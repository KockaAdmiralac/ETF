/**
 * pcb.cpp
 *
 * Kernel implementation of threads.
 */
#include <dos.h>
#include <kernel.h>
#include <pcb.h>
#include <schedule.h>
#include <util.h>

/**
 * Currently running kernel thread.
 */
volatile PCB* PCB::running = nullptr;

/**
 * 1KB minimum stack size of a thread.
 */
const StackSize PCB::minimumStackSize = 1024;

/**
 * 64KB maximum stack size of a thread.
 */
const StackSize PCB::maximumStackSize = 1UL << (sizeof(unsigned) * 8);

/**
 * A vector of all PCBs.
 */
PtrVector PCB::allPCBs;

/**
 * Initializes the kernel thread's stack and other basic attributes.
 * @param myThread Thread that owns the PCB
 * @param stackSize Size of the kernel thread's stack in bytes, cannot be under
 *                  minimumStackSize and over maximumStackSize
 * @param timeSlice Amount of time in quants (55ms) that can pass before the
 *                  context asynchronously switches, 0 = infinite
 */
PCB::PCB(Thread& myThread, StackSize stackSize, Time timeSlice) :
    myThread(&myThread), timeSlice(timeSlice) {
    // Initialize the stack.
    if (stackSize < minimumStackSize) {
        stackSize = minimumStackSize;
    } else if (stackSize > maximumStackSize) {
        stackSize = maximumStackSize-1;
    }
    stackSize /= sizeof(unsigned);
    // Conversion is safe, because we know this does not exceed
    // the maximum stack size, which fits into an unsigned.
    unsigned uStackSize = stackSize;
    lockInterrupts
    stack = new unsigned[uStackSize];
    unlockInterrupts
    if (assert(stack != nullptr, "Stack space failed to allocate!")) {
        status = TERMINATING;
        return;
    }
    // PSW, I = 1
    stack[uStackSize - 1] = 0x200;
    // PC
    stack[uStackSize - 2] = FP_SEG(PCB::execute);
    stack[uStackSize - 3] = FP_OFF(PCB::execute);
    // Leaving enough place for saved registers.
    sp = FP_OFF(stack + uStackSize - 12);
    ss = FP_SEG(stack + uStackSize - 12);
    bp = sp;
    // Registering the PCB in the list of all PCBs and assigning the ID.
    id = allPCBs.put(this);
    if (assert(id >= 0, "Failed to register the PCB in the list of PCBs!")) {
        status = TERMINATING;
        lockInterrupts
        delete stack;
        unlockInterrupts
        stack = nullptr;
        return;
    }
    status = INITIALIZING;
}

/**
 * Doesn't do anything because the default construct is to be used by the main
 * thread's PCB.
 */
PCB::PCB() {
    assert(true, "The default PCB constructor is only to be used by the main thread!");
}

/**
 * Frees resources used by the kernel thread.
 */
PCB::~PCB() {
    if (status != TERMINATING) {
        status = TERMINATING;
        allPCBs.remove(id);
    }
    if (stack != nullptr) {
        lockInterrupts
        delete stack;
        unlockInterrupts
        stack = nullptr;
    }
}

/**
 * Starts the kernel thread.
 *
 * If the PCB wasn't initialized successfully, this does nothing.
 */
void PCB::start() {
    if (status == INITIALIZING) {
        status = READY;
        Scheduler::put(this);
    }
}

/**
 * Adds the running thread to this thread's waiting queue.
 *
 * On failure, the running thread will remain blocked forever.
 * @todo Make it not do that?
 */
void PCB::waitToComplete() {
    if (assert(running != nullptr, "Running PCB that requested the wait is null!")) {
        return;
    }
    if (assert(running != this, "You cannot wait for yourself to complete!")) {
        return;
    }
    if (status != READY) {
        // The thread has finished or hasn't started.
        return;
    }
    running->status = BLOCKED;
    assert(blocked.insert((void*) running), "Failed to wait for the thread to complete! The running thread will remain blocked forever.");
    dispatch();
}

/**
 * Gets a kernel thread with a specified ID.
 * @param id ID of the kernel thread
 * @returns The PCB with a specified ID
 */
PCB* PCB::getPCBById(ID id) {
    return (PCB*) allPCBs.get(id);
}

/**
 * Executes the currently running thread.
 *
 * This is a wrapper function that will be executed upon starting a thread.
 */
void PCB::execute() {
    if (assert(PCB::running != nullptr, "PCB::execute called with no running thread!")) {
        return;
    }
    if (assert(PCB::running->myThread != nullptr, "Associated thread is null! Are you calling this from the main thread?")) {
        return;
    }
    PCB::running->myThread->run();
    PCB* unblocked = (PCB*) PCB::running->blocked.remove();
    while (unblocked != nullptr) {
        if (assert(unblocked != nullptr, "A PCB from the blocked list turned out to be null!")) {
            continue;
        }
        unblocked->status = READY;
        Scheduler::put(unblocked);
        unblocked = (PCB*) PCB::running->blocked.remove();
    }
    PCB::running->status = TERMINATING;
    // One does not simply finish a thread.
    dispatch();
}
