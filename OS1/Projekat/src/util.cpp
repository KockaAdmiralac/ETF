/**
 * util.cpp
 *
 * Implementation of utility functions.
 */
#include <stdarg.h>
#include <stdio.h>
#include <util.h>

/**
 * Simple assertion utility that reports an error if currently debugging the
 * kernel.
 * @param condition Condition to evaluate
 * @param message Message to print if in debug mode
 * @returns Whether an alternate path should be taken if the condition is false
 */
unsigned ensure(unsigned condition, const char* message) {
    if (condition) {
        return false;
    }
    #ifdef KERNEL_DEBUG
    syncPrint("ASSERTION FAILED: %s\n", message);
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
    if (ensure(bit < 16, "The requested bit is over 15!")) {
        return 0;
    }
    return (number >> bit) & 1;
}

/**
 * Wrapper around printf() that is thread-safe.
 *
 * Interrupts are disabled in this function because this may be called from
 * an actual interrupt routine.
 * @param format Output format string
 * @param ... Rest of the arguments
 * @returns The total number of written characters on success, negative on
 *          error
 * @see https://cplusplus.com/reference/cstdio/vprintf/
 */
int syncPrint(const char *format, ...) {
    asm {
        pushf
        cli
    }
    int res;
    va_list args;
    va_start(args, format);
    res = vprintf(format, args);
    va_end(args);
    asm popf
    return res;
}
