/**
 * kernel.h
 *
 * Interface to the most vital kernel functions.
 */
#ifndef _KERNEL_H_
#define _KERNEL_H_
#include <thread.h>
#include <util.h>

#define lockInterrupts(location) if (Kernel::cannotInterrupt + 1 == 0) { \
        syncPrint("Kernel interrupt locks are about to overflow! Location: " location "\n"); \
    } else { \
        ++Kernel::cannotInterrupt; \
    }
#define unlockInterrupts(location) if (Kernel::cannotInterrupt == 0) { \
        syncPrint("Trying to unlock what isn't locked! Location: " location "\n"); \
    } else { \
        --Kernel::cannotInterrupt; \
    } \
    if (!Kernel::cannotInterrupt && Kernel::contextSwitchOnDemand) { \
        dispatch(); \
    }

typedef void interrupt (*InterruptRoutine)(...);

void tick();
int userMain(int argc, char* argv[]);

/**
 * Representation of the thread which executes user code.
 */
class UserMainThread : public Thread {
    public:
        int retval;
        volatile int done;
        UserMainThread(int argc, char* argv[]);
        virtual Thread* clone() const;
    protected:
        virtual void run();
    private:
        int argc;
        char** argv;
};

/**
 * Kernel-related functions that don't belong anywhere else.
 */
class Kernel {
    public:
        static void cleanup();
        static int run(int argc, char* argv[]);
        static void interrupt timer(...);
        static volatile unsigned long cannotInterrupt;
        static volatile int contextSwitchOnDemand;
        static UserMainThread* mainThread;
    private:
        static volatile Time counter;
        static InterruptRoutine oldTimerRoutine;
        static volatile int semaphoreSignalCounter;
        static volatile PCB* loop;
};

#endif
