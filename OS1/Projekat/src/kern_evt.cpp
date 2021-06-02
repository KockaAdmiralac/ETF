/**
 * kern_evt.cpp
 *
 * Kernel implementation of event listeners.
 */
#include <kern_evt.h>
#include <schedule.h>
#include <util.h>

/**
 * Initializes a kernel implementation of an event listener.
 * @param ivtNo IVT entry number to listen on for events
 */
KernelEv::KernelEv(IVTNo ivtNo) :
    value(false), blocked(false), owner((PCB*) PCB::running), entry(ivtNo) {
    if (ensure(IVTEntry::entries[entry] != nullptr, "Initialized event with an uninitialized IVT entry!")) {
        return;
    }
    lockInterrupts("KernelEv::KernelEv");
    IVTEntry::entries[entry]->event = this;
    unlockInterrupts("KernelEv::KernelEv");
}

/**
 * Frees resources used by the kernel implementation of an event listener.
 */
KernelEv::~KernelEv() {
    lockInterrupts("KernelEv::~KernelEv");
    IVTEntry* ivtEntry = IVTEntry::entries[entry];
    if (ivtEntry != nullptr && ivtEntry->event == this) {
        IVTEntry::entries[entry]->event = nullptr;
    }
    unlockInterrupts("KernelEv::~KernelEv");
}

/**
 * Blocks the current thread on the event listener until the event occurs,
 * unless the event has already occurred.
 */
void KernelEv::wait() {
    if (PCB::running != owner) {
        return;
    }
    lockInterrupts("KernelEv::wait");
    if (value) {
        value = false;
        unlockInterrupts("KernelEv::wait (1)");
        return;
    }
    owner->status = PCB::BLOCKED;
    blocked = true;
    unlockInterrupts("KernelEv::wait (2)");
    dispatch();    
}

/**
 * Called from the interrupt routine to signal that the event has occurred.
 */
void KernelEv::signal() {
    lockInterrupts("KernelEv::signal");
    if (!value) {
        if (blocked) {
            blocked = false;
            owner->status = PCB::READY;
            Scheduler::put(owner);
        } else {
            value = true;
        }
    }
    unlockInterrupts("KernelEv::signal");
}
