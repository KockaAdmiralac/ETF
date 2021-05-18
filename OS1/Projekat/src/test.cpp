/**
 * test.cpp
 *
 * Testing utilities.
 */
#include <kernel.h>
#include <test.h>

/**
 * Prints out PASS if a test passes or FAIL if a test fails.
 * @param condition Test result
 */
void testResult(unsigned condition) {
    if (condition) {
        syncPrint("PASS\n");
    } else {
        syncPrint("FAIL\n");
    }
}

/**
 * Prints out a message, then tests the condition.
 * @param message Message to print
 * @param condition Condition to test
 */
void testCase(const char* message, unsigned condition) {
    if (Kernel::cannotInterrupt) {
        syncPrint("WARNING: Kernel cannot interrupt in this call! This test might break (others) unexpectedly.\n");
    }
    syncPrint("%s... ", message);
    testResult(condition);
}

/**
 * Loops for a certain amount of time.
 * @param delay The amount of loops to perform, in units of 1000 loops
 */
void dumbSleep(int delay) {
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < delay; ++j);
    }
}
