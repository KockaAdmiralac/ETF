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
    if (assert(IVTEntry::entries[entry] != nullptr, "Initialized event with an uninitialized IVT entry!")) {
        return;
    }
    lockInterrupts
    IVTEntry::entries[entry]->event = this;
    unlockInterrupts
}

/**
 * Frees resources used by the kernel implementation of an event listener.
 * @todo Use list for registering events? Don't unregister if not registered?
 */
KernelEv::~KernelEv() {
    if (IVTEntry::entries[entry] != nullptr) {
        lockInterrupts
        IVTEntry::entries[entry]->event = nullptr;
        unlockInterrupts
    }
}

/**
 * Blocks the current thread on the event listener until the event occurs,
 * unless the event has already occurred.
 */
void KernelEv::wait() {
    if (PCB::running != owner) {
        return;
    }
    if (value) {
        lockInterrupts
        value = false;
        unlockInterrupts
    } else {
        lockInterrupts
        owner->status = PCB::BLOCKED;
        blocked = true;
        unlockInterrupts
        dispatch();
    }
    
}

/**
 * Called from the interrupt routine to signal that the event has occurred.
 */
void KernelEv::signal() {
    if (!value) {
        lockInterrupts
        if (blocked) {
            blocked = false;
            owner->status = PCB::READY;
            Scheduler::put(owner);
        } else {
            value = true;
        }
        unlockInterrupts
    }
}
