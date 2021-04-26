/**
 * kernel.cpp
 *
 * Implementation of most vital kernel functions.
 */
#include <dos.h>
#include <iostream.h>
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
    lockInterrupts
    cout << "Starting loop" << endl;
    unlockInterrupts
    while (true) {
        lockInterrupts
        cout << "Loopin'" << endl;
        unlockInterrupts
        sleep(1);
    }
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
 * Whether the context switch was forced.
 */
volatile int Kernel::semaphoreSignalCounter = 0;

/**
 * Pointer to the loop thread. This thread must not end up in the scheduler!
 */
volatile Thread* Kernel::loop = nullptr;

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
        ++semaphoreSignalCounter;
        if (canInterrupt) {
            for (unsigned i = 0; i < KernelSem::allSemaphores.getSize(); ++i) {
                KernelSem* sem = (KernelSem*) KernelSem::allSemaphores.get(i);
                if (sem == nullptr) {
                    continue;
                }
                //cout << "Ticking list" << endl;
                //lock
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
                        //cout << "Unblocking thread " << unblocked->id << endl;
                        //lock
                        Scheduler::put(unblocked);
                    } while (tr.more);
                }
            }
            semaphoreSignalCounter = 0;
        }
    }
    int delayedContextSwitch = false;
    // The time is up or a synchronous context switch occurred.
    if ((counter == 0 && PCB::running->timeSlice != 0) || contextSwitchOnDemand) {
        if (canInterrupt) {
            cout << "Kernel can interrupt" << endl;
            lock
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
                cout << "Getting loop" << loop->getId() << endl;
                lock
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
            cout << "Kernel cannot interrupt" << endl;
            lock
            delayedContextSwitch = true;
            contextSwitchOnDemand = true;
        }
    }
    // If the context switch wasn't forced, this was a natural timer interrupt.
    if (!contextSwitchOnDemand || delayedContextSwitch) {
        tick();
        // TODO: Replace with regular function call?
        oldTimerRoutine();
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
    oldTimerRoutine = getvect(0x08);
    setvect(0x08, timer);
    unlock
    // Execute user code.
    int retval = userMain(argc, argv);
    // Reset timer interrupt.
    lock
    setvect(0x08, oldTimerRoutine);
    unlock
    delete loop;
    loop = nullptr;
    cout << "Happy End" << endl;
    return retval;
}
