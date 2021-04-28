/**
 * kern_evt.h
 *
 * Interface of the kernel implementation of event listeners.
 */
#ifndef _KERN_EVT_H_
#define _KERN_EVT_H_
#include <event.h>
#include <ivt.h>
#include <kernel.h>
#include <pcb.h>

/**
 * Kernel implementation of event listeners.
 */
class KernelEv {
    private:
        friend class Event;
        friend class IVTEntry;
        friend class Kernel;

        KernelEv(IVTNo ivtNo);
        ~KernelEv();
        void wait();
        void signal();

        volatile int value;
        volatile int blocked;
        IVTNo entry;
        PCB* owner;
};

#endif
