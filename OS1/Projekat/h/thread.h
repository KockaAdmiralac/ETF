/**
 * thread.h
 *
 * Interface to threads. Non-cosmetic changes are NOT ALLOWED.
 */
#ifndef _THREAD_H_
#define _THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4 * 1024; // 4KB
typedef unsigned int Time;
const Time defaultTimeSlice = 2; // default = 2 * 55ms
typedef int ID;

class PCB;

/**
 * User interface to kernel threads.
 */
class Thread {
    public:
        void start();
        void waitToComplete();
        virtual ~Thread();
        ID getId();
        static ID getRunningId();
        static Thread* getThreadById(ID id);
        static ID fork();
        static void exit();
        static void waitForForkChildren();
        virtual Thread* clone() const;
    protected:
        friend class PCB;
        Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
        /**
         * Executes subclass-specific thread operations.
         */
        virtual void run() {}
    private:
        PCB* myPCB;
};

void dispatch();

#endif
