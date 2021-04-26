/**
 * evt.cpp
 *
 * Implementation of event listeners.
 */
#include <evt.h>
#include <kern_evt.h>
#include <kernel.h>
#include <util.h>

/**
 * Constructs an event listener on a specified IVT entry and redirects the old
 * IVT entry.
 * @param ivtNo Entry number in the IVT
 */
Event::Event(IVTNo ivtNo) {
    lockInterrupts
    myImpl = new KernelEv(ivtNo);
    unlockInterrupts
    assert(myImpl != nullptr, "Kernel event failed to allocate!");
}

/**
 * Frees resources used by the event listener.
 */
Event::~Event() {
    if (myImpl != nullptr) {
        lockInterrupts
        delete myImpl;
        unlockInterrupts
        myImpl = nullptr;
    }
}

/**
 * Waits for the event to occur.
 *
 * May cause a synchronous context switch if the event hasn't occurred yet and
 * the calling thread is the thread which initialized the event.
 */
void Event::wait() {
    if (myImpl != nullptr) {
        myImpl->wait();
    }
}

/**
 * Signals the kernel that the event has occurred.
 *
 * This is a mostly useless method. It can only be called from subclasses and
 * friend classes, none of the friend classes have any use for it, and all it
 * does is call into the kernel implementation of this operation.
 */
void Event::signal() {
    if (myImpl != nullptr) {
        myImpl->signal();
    }
}
