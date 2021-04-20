/**
 * ivt.h
 *
 * Interrupt Vector Table related utilities.
 */
#ifndef _IVT_H_
#define _IVT_H_

/**
 * Prepares an IVT entry for listening on an event
 * @param entry The entry to listen on
 * @param chain Whether to chain the old routine
 */
#define PREPAREENTRY(entry, chain) asm nop

/**
 * Represents an entry in the Interrupt Vector Table.
 */
class IVTEntry {
    //
};

#endif
