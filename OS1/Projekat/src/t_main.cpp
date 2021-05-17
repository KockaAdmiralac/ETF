/**
 * t_main.cpp
 *
 * Entry point for test suite.
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

/*
unsigned tbpm;
unsigned tssm;
unsigned tspm;
void *tptr;

#include <dos.h>
void testFunc() {
    asm {
        mov tbpm, bp
        mov tssm, ss
    }
    cout << "BP value: " << tbpm << endl;
    while (tbpm != 0) {
        tptr = MK_FP(tssm, tbpm);
        tbpm = *((unsigned*) tptr);
        cout << "BP value: " << tbpm << endl;
    }
}

void testFunc2() {
    testFunc();
}

void testFunc3() {
    testFunc2();
}
*/

#ifdef KERNEL_DEBUG
int main() {
    testCase("Kernel can interrupt at the beginning of tests", Kernel::cannotInterrupt == 0);
    testUtil();
    //testVector();
    //testList();
    testKernel();
    return 0;
}
#endif
