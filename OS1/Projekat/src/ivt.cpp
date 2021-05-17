/**
 * ivt.cpp
 *
 * Implementation of IVT utilities.
 */
#include <dos.h>
#include <ivt.h>
#include <util.h>

/**
 * Pointers to registered IVT entries. Index in the array corresponds to the
 * IVT entry number. If null, it means no IVT entry has been registered to that
 * number.
 */
IVTEntry* IVTEntry::entries[256];

/**
 * Initializes an IVT entry.
 * @param entry Entry number to initialize
 * @param routine Routine to call on interrupt
 */
IVTEntry::IVTEntry(IVTNo entry, InterruptRoutine routine) :
    entry(entry), routine(routine), oldRoutine(getvect(entry)) {
    if (assert(entries[entry] == nullptr, "Re-registering existing entry!")) {
        return;
    }
    // Locking interrupts should not be needed since the IVTEntry constructor
    // should be called before main(), however, it is here in case somebody
    // decides it's a good idea to call it afterwards.
    lockInterrupts("IVTEntry::IVTEntry");
    lock
    setvect(entry, routine);
    unlock
    entries[entry] = this;
    unlockInterrupts("IVTEntry::IVTEntry");
}

/**
 * Restores the old interrupt routine when the IVT entry is about to
 * deallocate.
 */
IVTEntry::~IVTEntry() {
    lockInterrupts("IVEntry::~IVTEntry");
    if (oldRoutine != nullptr) {
        lock
        setvect(entry, oldRoutine);
        unlock
    }
    unlockInterrupts("IVTEntry::~IVTEntry");
}

/**
 * Called when an interrupt on the associated entry occurs.
 * @param chain Whether the interrupt routine that was previously in the entry
 *              should be called
 */
void IVTEntry::signal(int chain) {
    lockInterrupts("IVTEntry::signal");
    if (event != nullptr) {
        event->signal();
    }
    if (chain) {
        if (assert(oldRoutine != nullptr, "Old interrupt routine does not exist!")) {
            unlockInterrupts("IVTEntry::signal (1)");
            return;
        }
        oldRoutine();
    }
    unlockInterrupts("IVTEntry::signal (2)");
}
