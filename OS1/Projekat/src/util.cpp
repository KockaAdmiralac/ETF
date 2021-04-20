/**
 * util.cpp
 *
 * Implementation of utility functions.
 */
#include <iostream.h>
#include <util.h>

/**
 * Simple assertion utility that reports an error if currently debugging the
 * kernel.
 * @param condition Condition to evaluate
 * @param message Message to print if in debug mode
 * @returns Whether an alternate path should be taken if the condition is false
 */
unsigned assert(unsigned condition, const char* message) {
    if (condition) {
        return false;
    }
    #ifdef KERNEL_DEBUG
    // This prevents all interrupts, but that is fine in debug mode.
    asm {
        pushf
        cli
    }
    cout << "ASSERTION FAILED: " << message << endl;
    asm popf
    return true;
    #else
    (void *) message;
    return true;
    #endif
}

/**
 * Reads the processor Program Status Word (PSW).
 *
 * The PSW has the following format: XXXXODIT|SZXAXPXC
 * - X: unused
 * - O: overflow
 * - D: Direction (DMA, input/output)
 * - I: Interrupt enable
 * - T: Trap enable
 * - S: Sign flag
 * - Z: Zero flag
 * - A: Auxilliary carry flag
 * - P: Parity flag
 * - C: Carry flag
 * @returns The PSW
 */
unsigned getPSW() {
    unsigned tpsw;
    asm {
        pushf
        pop tpsw
    }
    return tpsw;
}

/**
 * Extracts a specified bit from a number.
 *
 * Mostly useful as a debug utility.
 * @param number Number to extract the bit from
 * @param bit Zero-based position of the bit to extract
 * @returns Extracted bit
 */
unsigned getBit(unsigned number, unsigned bit) {
    if (assert(bit < 16, "The requested bit is over 15!")) {
        return 0;
    }
    return (number >> bit) & 1;
}
