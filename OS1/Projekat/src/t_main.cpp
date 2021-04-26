/**
 * t_main.cpp
 *
 * Entry point for test suite.
 */
#include <kernel.h>
#include <test.h>
#include <util.h>

/**
 * Prints out PASS if a test passes or FAIL if a test fails.
 *
 * WARNING: If called from methods where I = 0, a lock is required after this
 * call.
 * @param condition Test result
 */
void testResult(unsigned condition) {
    lockInterrupts
    if (condition) {
        cout << "PASS" << endl;
    } else {
        cout << "FAIL" << endl;
    }
    unlockInterrupts
}

/**
 * Prints out a message, then tests the condition.
 *
 * WARNING: If called from methods where I = 0, a lock is required after this
 * call.
 * @param message Message to print
 * @param condition Condition to test
 */
void testCase(const char* message, unsigned condition) {
    if (!Kernel::canInterrupt) {
        cout << "WARNING: Kernel cannot interrupt in this call! This test might break (others) unexpectedly." << endl;
    }
    lockInterrupts
    cout << message << "... ";
    unlockInterrupts
    testResult(condition);
}

#ifdef KERNEL_DEBUG
int main() {
    testCase("Kernel can interrupt at the beginning of tests", Kernel::canInterrupt);
    testUtil();
    //testVector();
    //testList();
    testThread();
    testKernel();
    testSemaphore();
    testIVT();
    testEvent();
    return 0;
}
#endif
