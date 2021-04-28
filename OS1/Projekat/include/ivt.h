/**
 * ivt.h
 *
 * Interrupt Vector Table related utilities.
 */
#ifndef _IVT_H_
#define _IVT_H_
#include <kern_evt.h>
#include <kernel.h>

/**
 * Prepares an IVT entry for listening on an event
 * @param entry The entry to listen on
 * @param chain Whether to chain the old routine
 */
#define PREPAREENTRY(entry, chain) \
    void interrupt interruptRoutine##entry(...); \
    IVTEntry ivtEntry##entry(entry, interruptRoutine##entry); \
    void interrupt interruptRoutine##entry(...) { \
        ivtEntry##entry.signal(chain); \
    }

/**
 * Represents an entry in the Interrupt Vector Table.
 */
class IVTEntry {
    public:
        IVTEntry(IVTNo entry, InterruptRoutine routine);
        ~IVTEntry();
        void signal(int chain);
    private:
        friend class KernelEv;

        IVTNo entry;
        InterruptRoutine routine;
        InterruptRoutine oldRoutine;
        KernelEv* event;
        static IVTEntry* entries[];
};

#endif
