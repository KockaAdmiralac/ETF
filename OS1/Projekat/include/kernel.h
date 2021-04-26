/**
 * kernel.h
 *
 * Interface to the most vital kernel functions.
 */
#ifndef _KERNEL_H_
#define _KERNEL_H_
#include <thread.h>

// TODO: Replace with methods?
#define lockInterrupts Kernel::canInterrupt = false;
#define unlockInterrupts \
    Kernel::canInterrupt = true; \
    if (Kernel::contextSwitchOnDemand) { \
        dispatch(); \
    }

typedef void interrupt (*InterruptRoutine)(...);

void tick();
int userMain(int argc, char* argv[]);

/**
 * Kernel-related functions that don't belong anywhere else.
 */
class Kernel {
    public:
        static int run(int argc, char* argv[]);
        static void interrupt timer(...);
        static volatile int canInterrupt;
        static volatile int contextSwitchOnDemand;
        static volatile int semaphoreSignalCounter;
        static volatile Thread* loop;
    private:
        static volatile Time counter;
        static InterruptRoutine oldTimerRoutine;
};

#endif
