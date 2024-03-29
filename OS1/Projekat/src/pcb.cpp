/**
 * pcb.cpp
 *
 * Kernel implementation of threads.
 */
#include <dos.h>
#include <kernel.h>
#include <pcb.h>
#include <schedule.h>
#include <string.h>
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
 * First argument of PCB::copyStack.
 */
PCB* PCB::copyStackFrom = nullptr;

/**
 * Second argument of PCB::copyStack.
 */
PCB* PCB::copyStackTo = nullptr;

/**
 * Initializes the kernel thread's stack and other basic attributes.
 * @param myThread Thread that owns the PCB
 * @param stackSize Size of the kernel thread's stack in bytes, cannot be under
 *                  minimumStackSize and over maximumStackSize
 * @param timeSlice Amount of time in quants (55ms) that can pass before the
 *                  context asynchronously switches, 0 = infinite
 */
PCB::PCB(Thread& myThread, StackSize stackSize, Time timeSlice) :
    myThread(&myThread), timeSlice(timeSlice), children(1), parent(nullptr),
    parentIndex(-1) {
    lockInterrupts("PCB::PCB");
    // We set the ID to -1 so we can properly detect whether the PCB wasn't
    // inserted into the list of PCBs at all.
    id = -1;
    // Initialize the stack.
    if (stackSize < minimumStackSize) {
        stackSize = minimumStackSize;
    } else if (stackSize >= maximumStackSize) {
        stackSize = maximumStackSize - 1;
    }
    stackSize /= sizeof(unsigned);
    // Conversion is safe, because we know this does not exceed
    // the maximum stack size, which fits into an unsigned.
    #pragma warn -sig
    unsigned uStackSize = stackSize;
    #pragma warn .sig
    this->stackSize = uStackSize;
    stack = new unsigned[uStackSize];
    if (ensure(stack != nullptr, "Stack space failed to allocate!")) {
        status = TERMINATING;
        unlockInterrupts("PCB::PCB (1)");
        return;
    }
    // PSW, I = 1
    stack[uStackSize - 1] = 0x200;
    // PC
    stack[uStackSize - 2] = FP_SEG(execute);
    stack[uStackSize - 3] = FP_OFF(execute);
    // BP
    stack[uStackSize - 12] = 0;
    // Leaving enough place for saved registers.
    sp = FP_OFF(stack + uStackSize - 12);
    ss = FP_SEG(stack + uStackSize - 12);
    bp = sp;
    // Registering the PCB in the list of all PCBs and assigning the ID.
    id = allPCBs.put(this);
    if (ensure(id >= 0, "Failed to register the PCB in the list of PCBs!")) {
        status = TERMINATING;
        delete[] stack;
        stack = nullptr;
        unlockInterrupts("PCB::PCB (2)");
        return;
    }
    status = INITIALIZING;
    unlockInterrupts("PCB::PCB (3)");
}

/**
 * Takes the difference between two pointers and applies to another pointer.
 *
 * Basically: oldBase - oldPointer == base - pointer, where `pointer` is the
 * return value.
 * @param oldPointer Pointer to apply the difference to
 * @param base New pointer which the return value should be relative to
 * @param oldBase Old pointer which the input pointer should be relative to
 * @todo Move this to util.h
 */
void* applyPtrDiff(void* oldPointer, unsigned* base, unsigned* oldBase) {
    unsigned long ulBase = (unsigned long) base;
    unsigned long ulOldBase = (unsigned long) oldBase;
    unsigned long ulOldPointer = (unsigned long) oldPointer;
    if (ulBase < ulOldBase) {
        return (void*)(ulOldPointer - (ulOldBase - ulBase));
    } else {
        return (void*)(ulOldPointer + (ulBase - ulOldBase));
    }
}

/**
 * Copies the stack of the PCB in PCB::copyStackFrom into the stack of
 * PCB::copyStackTo.
 *
 * It is assumed that interrupts are already prevented upon calling this
 * function.
 */
void interrupt PCB::copyStack(...) {
    if (ensure(running == copyStackFrom, "PCB::copyStack isn't called from the currently running thread!")) {
        return;
    }
    lockInterrupts("PCB::copyStack");
    // Update PCB fields with running thread values.
    unsigned tsp;
    unsigned tss;
    unsigned tbp;
    asm {
        mov tsp, sp
        mov tss, ss
        mov tbp, bp
    }
    copyStackFrom->sp = tsp;
    copyStackFrom->ss = tss;
    copyStackFrom->bp = tbp;
    // Copy the stack.
    memcpy(copyStackTo->stack, copyStackFrom->stack, copyStackTo->stackSize * sizeof(unsigned));
    // Update stack pointers (SS, SP, BP, old BPs).
    void* oldStackPointer = MK_FP(copyStackFrom->ss, copyStackFrom->sp);
    void* newStackPointer = applyPtrDiff(oldStackPointer, copyStackTo->stack, copyStackFrom->stack);
    copyStackTo->ss = FP_SEG(newStackPointer);
    copyStackTo->sp = FP_OFF(newStackPointer);
    void* oldBasePointer = MK_FP(copyStackFrom->ss, copyStackFrom->bp);
    void* newBasePointer = applyPtrDiff(oldBasePointer, copyStackTo->stack, copyStackFrom->stack);
    copyStackTo->bp = FP_OFF(newBasePointer);
    ensure(FP_SEG(newBasePointer) == copyStackTo->ss, "Segments of stack and base pointers don't match!");
    unsigned oldStackBP = *((unsigned*) newBasePointer);
    while (oldStackBP != 0) {
        oldBasePointer = newBasePointer;
        newBasePointer = applyPtrDiff(MK_FP(copyStackFrom->ss, oldStackBP), copyStackTo->stack, copyStackFrom->stack);
        *((unsigned*) oldBasePointer) = FP_OFF(newBasePointer);
        oldStackBP = *((unsigned*) newBasePointer);
    }
    unlockInterrupts("PCB::copyStack");
}

/**
 * Doesn't do anything because the default constructor is to be used by the
 * main thread's PCB.
 */
PCB::PCB() : children(1) {
    ensure(allPCBs.getSize() == 0, "The default PCB constructor is only to be used by the main thread!");
}

/**
 * Frees resources used by the kernel thread.
 */
PCB::~PCB() {
    lockInterrupts("PCB::~PCB");
    if (id >= 0) {
        allPCBs.remove(id);
        status = TERMINATING;
    }
    if (stack != nullptr) {
        delete[] stack;
        stack = nullptr;
    }
    // Tell the children their parent died.
    for (unsigned i = 0; i < children.getSize(); ++i) {
        PCB* child = (PCB*) children.get(i);
        if (child != nullptr) {
            child->parent = nullptr;
        }
    }
    unlockInterrupts("PCB::~PCB");
}

/**
 * Starts the kernel thread.
 *
 * If the PCB wasn't initialized successfully, this does nothing.
 */
void PCB::start() {
    lockInterrupts("PCB::start");
    if (status == INITIALIZING) {
        status = READY;
        Scheduler::put(this);
    }
    unlockInterrupts("PCB::start");
}

/**
 * Adds the running thread to this thread's waiting queue.
 *
 * On failure, the running thread will remain blocked forever.
 */
void PCB::waitToComplete() {
    if (ensure(running != nullptr, "Running PCB that requested the wait is null!")) {
        return;
    }
    if (ensure(running != this, "You cannot wait for yourself to complete!")) {
        return;
    }
    if (status == INITIALIZING || status == TERMINATING) {
        // The thread has finished or hasn't started.
        // Status cannot be RUNNING at this point.
        return;
    }
    lockInterrupts("PCB::waitToComplete");
    running->status = BLOCKED;
    ensure(blocked.insert((void*) running), "Failed to wait for the thread to complete! The running thread will remain blocked forever.");
    unlockInterrupts("PCB::waitToComplete");
    dispatch();
}

/**
 * Performs necessary cleanup and exits the current thread.
 *
 * The current thread will not be returned to.
 */
void PCB::exit() volatile {
    if (ensure(this == running, "PCB::exit may only be called on the current thread!")) {
        return;
    }
    lockInterrupts("PCB::exit");
    PCB* unblocked = (PCB*) blocked.remove();
    while (unblocked != nullptr) {
        unblocked->status = READY;
        Scheduler::put(unblocked);
        unblocked = (PCB*) blocked.remove();
    }
    status = TERMINATING;
    if (parent != nullptr) {
        parent->children.remove(parentIndex);
        if (
            parent->children.getSize() == 0 &&
            parent->status == MATERNITY_LEAVE
        ) {
            parent->status = READY;
            Scheduler::put(parent);
        }
    }
    // The responsibility for freeing the child is on the user.
    unlockInterrupts("PCB::exit");
    // One does not simply finish a thread.
    dispatch();
}

/**
 * Blocks the thread until all child threads created via fork() have finished
 * executing.
 */
void PCB::waitForChildren() volatile {
    lockInterrupts("PCB::waitForChildren");
    if (children.getSize() == 0) {
        unlockInterrupts("PCB::waitForChildren (1)");
        return;
    }
    status = MATERNITY_LEAVE;
    unlockInterrupts("PCB::waitForChildren (2)");
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
 * DO NOT USE LOCAL VARIABLES OR ARGUMENTS HERE. BP is most likely set to ZERO
 * after returning from the interrupt routine.
 */
void PCB::execute() {
    if (ensure(running != nullptr, "PCB::execute called with no running thread!")) {
        return;
    }
    if (ensure(running->myThread != nullptr, "Associated thread is null! Are you calling this from the main thread?")) {
        return;
    }
    running->myThread->run();
    running->exit();
}
