/**
 * kernel.cpp
 *
 * Implementation of most vital kernel functions.
 */
#include <dos.h>
#include <iostream.h>
#include <kernel.h>
#include <pcb.h>
#include <schedule.h>
#include <util.h>

/**
 * Representation of the kernel's main thread.
 */
class MainPCB : public PCB {
    public:
        MainPCB();
    protected:
        virtual void waitToComplete();
};

/**
 * Initialization of relevant data for the kernel's main thread.
 *
 * - There is no stack, but the base class handles that along with the case of
 *   stack failing to initialize.
 * - The status is running, because... that's the current thread. For that
 *   reason, we also update the static running member.
 * - Time slice is zero, because we might want to start up all our tasks and
 *   then wait for them to finish. Is there a more reasonable default?
 * - The calling thread should check for a list allocation failure.
 */
MainPCB::MainPCB() {
    myThread = nullptr;
    stack = nullptr;
    timeSlice = 0;
    id = allPCBs.put(this);
    if (assert(id >= 0, "Main thread failed to register!")) {
        status = TERMINATING;
        return;
    }
    status = RUNNING;
    running = this;
}

/**
 * The main thread's completion must not be awaited.
 *
 * This shouldn't happen either way since users don't have access to this
 * thread's PCB through any Thread.
 */
void MainPCB::waitToComplete() {
    assert(false, "The main thread's completion must not be awaited!");
}

/**
 * Representation of the kernel's loop thread.
 */
class LoopThread : public Thread {
    public:
        LoopThread();
    protected:
        virtual void run();
};

/**
 * Calls the base class's default constructor.
 */
LoopThread::LoopThread() : Thread(PCB::minimumStackSize, 1) {}

/**
 * Waits for its time slice to expire so another thread can take over if
 * needed.
 */
void LoopThread::run() {
    while (true);
}

/**
 * Whether the thread is safe to interrupt (1) or is in a critical section (0).
 */
volatile int Kernel::canInterrupt = true;

/**
 * Whether the context switch was forced.
 */
volatile int Kernel::contextSwitchOnDemand = false;

/**
 * Time slices remaining until the current thread finishes.
 */
volatile Time Kernel::counter = 0;

/**
 * Pointer to the loop thread. This thread must not end up in the scheduler!
 */
volatile Thread* Kernel::loop = nullptr;

// Temporary variables for timer interrupt.
unsigned tsp;
unsigned tss;
unsigned tbp;

/**
 * Timer interrupt routine.
 */
void interrupt Kernel::timer(...) {
    // Don't forget to tick()!
    // The context isn't forcibly switched and the current thread does not have
    // infinite time available for use.
    if (!contextSwitchOnDemand && PCB::running->timeSlice != 0) {
        --counter;
    }
    int delayedContextSwitch = false;
    // The time is up or a synchronous context switch occurred.
    if ((counter == 0 && PCB::running->timeSlice != 0) || contextSwitchOnDemand) {
        if (Kernel::canInterrupt) {
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
                PCB::running = PCB::getPCBById(loop->getId());
            } else {
                PCB::running->status = PCB::RUNNING;
            }
            if (assert(PCB::running != nullptr, "Loop thread is null in timer interrupt!")) {
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
        } else {
            delayedContextSwitch = true;
            contextSwitchOnDemand = true;
        }
    }
    // If the context switch wasn't forced, this was a natural timer interrupt.
    if (!contextSwitchOnDemand || delayedContextSwitch) {
        // TODO: Replace with regular function call?
        asm int 60h;
    }
}

/**
 * Main function of the kernel.
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
    // Create loop thread.
    loop = new LoopThread;
    if (assert(loop != nullptr, "Loop thread failed to allocate!")) {
        return 2;
    }
    // Set timer interrupt.
    lock
    setvect(0x60, getvect(0x08));
    setvect(0x08, timer);
    unlock
    // Execute user code.
    int retval = userMain(argc, argv);
    // Reset timer interrupt.
    lock
    setvect(0x08, getvect(0x60));
    unlock
    delete loop;
    loop = nullptr;
    cout << "Happy End" << endl;
    return retval;
}
