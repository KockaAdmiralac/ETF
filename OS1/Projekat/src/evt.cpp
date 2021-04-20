/**
 * evt.cpp
 *
 * Implementation of event listeners.
 */
#include <evt.h>

/**
 * Constructs an event listener on a specified IVT entry and redirects the old
 * IVT entry.
 * @param ivtNo Entry number in the IVT
 */
Event::Event(IVTNo ivtNo) {
    //
}

/**
 * Frees resources used by the event listener.
 */
Event::~Event() {
    //
}

/**
 * Waits for the event to occur.
 *
 * May cause a synchronous context switch if the event hasn't occurred yet and
 * the calling thread is the thread which initialized the event.
 */
void Event::wait() {
    //
}

/**
 * Signals the kernel that the event has occurred.
 */
void Event::signal() {
    //
}
