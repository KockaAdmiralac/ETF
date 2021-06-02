/**
 * kernel.cpp
 *
 * Implementation of most vital kernel functions.
 */
#include <dos.h>
#include <kernel.h>
#include <list.h>
#include <pcb.h>
#include <schedule.h>
#include <kern_sem.h>
#include <util.h>

/**
 * Representation of the kernel's main thread.
 */
class MainPCB : public PCB {
    public:
        MainPCB();
};

/**
 * Initialization of relevant data for the kernel's main thread.
 *
 * - There is no stack, but the base class handles that along with the case of
 *   stack failing to initialize.
 * - The status is initializing, because this thread should never be picked
 *   from the scheduler, unless there are no other threads to be picked.
 * - Time slice is one, because this is the loop thread. We don't want to be
 *   busy waiting for too long.
 * - The calling thread should check for a list allocation failure.
 */
MainPCB::MainPCB() {
    myThread = nullptr;
    stack = nullptr;
    timeSlice = 1;
    stackSize = 0;
    parent = nullptr;
    parentIndex = -1;
    id = allPCBs.put(this);
    if (ensure(id >= 0, "Main thread failed to register!")) {
        status = TERMINATING;
        return;
    }
    status = INITIALIZING;
    running = this;
}

/**
 * Initializes the user main thread.
 * - Sets the parameters to userMain as thread fields
 * - Allocates the maximum stack and gives it infinite execution time
 * @param argc Number of command-line arguments
 * @param argv Command-line arguments
 */
UserMainThread::UserMainThread(int argc, char* argv[]) :
    Thread(PCB::maximumStackSize, 0), argc(argc), argv(argv), done(false) {}

/**
 * Waits for the user main thread to complete before destruction, just in case.
 */
UserMainThread::~UserMainThread() {
    waitToComplete();
}

/**
 * Runs the user main function with arguments from main().
 */
void UserMainThread::run() {
    retval = userMain(argc, argv);
    done = true;
}

/**
 * Clones the main thread.
 * @returns The cloned thread
 */
Thread* UserMainThread::clone() const {
    return new UserMainThread(argc, argv);
}

/**
 * Whether it's safe to switch to another thread (0) or the current thread is
 * in a critical section (every other value).
 */
volatile unsigned long Kernel::cannotInterrupt = 0;

/**
 * Whether the context switch was forced.
 */
volatile int Kernel::contextSwitchOnDemand = false;

/**
 * Time slices remaining until the current thread finishes.
 */
volatile Time Kernel::counter = 0;

/**
 * Counts how many ticks passed since semaphores could be signalled.
 */
volatile unsigned Kernel::semaphoreSignalCounter = 0;

/**
 * Pointer to the loop thread. This thread must not end up in the scheduler!
 */
volatile PCB* Kernel::loop = nullptr;

/**
 * Pointer to the user main thread.
 */
UserMainThread* Kernel::mainThread = nullptr;

/**
 * The interrupt routine on 08h (timer interrupt routine) before the kernel
 * replaced it.
 */
InterruptRoutine Kernel::oldTimerRoutine = nullptr;

// Temporary variables for timer interrupt.
unsigned tsp;
unsigned tss;
unsigned tbp;

/**
 * Timer interrupt routine.
 */
void interrupt Kernel::timer(...) {
    // The context isn't forcibly switched.
    if (!contextSwitchOnDemand) {
        if (PCB::running->timeSlice != 0) {
            --counter;
        }
        if (!ensure(semaphoreSignalCounter < semaphoreSignalCounter + 1, "Semaphore signal counter is overflowing!")) {
            ++semaphoreSignalCounter;
        }
        if (cannotInterrupt == 0) {
            for (unsigned i = 0; i < KernelSem::allSemaphores.getSize(); ++i) {
                KernelSem* sem = (KernelSem*) KernelSem::allSemaphores.get(i);
                if (sem == nullptr) {
                    continue;
                }
                PtrWaitingList::TickResult tr;
                for (unsigned j = 0; j < semaphoreSignalCounter; ++j) {
                    do {
                        tr = sem->blocked.tick();
                        if (tr.data == nullptr) {
                            break;
                        }
                        PCB* unblocked = (PCB*) tr.data;
                        unblocked->status = PCB::READY;
                        unblocked->semaphoreResult = false;
                        ++sem->value;
                        Scheduler::put(unblocked);
                    } while (tr.more);
                }
            }
            semaphoreSignalCounter = 0;
        }
        // If the context switch wasn't forced, this was a natural timer interrupt.
        tick();
        oldTimerRoutine();
    }
    // The time is up or a synchronous context switch occurred.
    if ((counter == 0 && PCB::running->timeSlice != 0) || contextSwitchOnDemand) {
        if (cannotInterrupt) {
            contextSwitchOnDemand = true;
        } else {
            contextSwitchOnDemand = false;
            // Saving thread context.
            asm {
                mov tsp, sp
                mov tss, ss
                mov tbp, bp
            }
            PCB::running->sp = tsp;
            PCB::running->ss = tss;
            PCB::running->bp = tbp;
            if (PCB::running->status == PCB::RUNNING) {
                PCB::running->status = PCB::READY;
                Scheduler::put((PCB*) PCB::running);
            }
            PCB::running = Scheduler::get();
            if (PCB::running == nullptr) {
                PCB::running = loop;
            } else {
                PCB::running->status = PCB::RUNNING;
            }
            if (ensure(PCB::running != nullptr, "Loop thread is null in timer interrupt!")) {
                return;
            }
            tsp = PCB::running->sp;
            tss = PCB::running->ss;
            tbp = PCB::running->bp;
            counter = PCB::running->timeSlice;
            asm {
                mov sp, tsp
                mov ss, tss
                mov bp, tbp
            }
        }
    }
}

/**
 * Cleans up kernel resources before ending the program.
 *
 * Exiting the program is left to the user.
 */
void Kernel::cleanup() {
    // Reset timer interrupt.
    lock
    setvect(0x08, oldTimerRoutine);
    unlock
    #ifdef KERNEL_DEBUG
    syncPrint("Happy End\n");
    #endif
}

/**
 * Main function of the kernel.
 *
 * While this is a separate function from the real main(), it isn't really
 * atomic as the return to main() isn't guaranteed.
 * @param argc Number of command-line arguments
 * @param argv Command-line arguments
 * @returns Exit code
 */
int Kernel::run(int argc, char* argv[]) {
    // Register main thread as a PCB.
    MainPCB mainPCB;
    if (mainPCB.status == PCB::TERMINATING) {
        return 1;
    }
    loop = &mainPCB;
    // Create the user main thread.
    UserMainThread userMainThread(argc, argv);
    if (userMainThread.getId() == -1) {
        return 2;
    }
    mainThread = &userMainThread;
    userMainThread.start();
    // Set timer interrupt.
    lock
    oldTimerRoutine = getvect(0x08);
    setvect(0x08, timer);
    unlock
    // Wait for user code to finish executing.
    dispatch();
    while (!userMainThread.done);
    // This will not execute if the user main thread has been exited using
    // Thread::exit();
    cleanup();
    return userMainThread.retval;
}
