/**
 * t_util.cpp
 *
 * Test module for project utility functions and macros.
 */
#include <test.h>
#include <util.h>

void testEnsure() {
    syncPrint("Testing ensure():\n");
    testCase("1. Test with true value", !ensure(true, "This should not be printed."));
    testCase("2. Test with false value (assertion should fail)", ensure(false, "This should be printed."));
}

void testGetBit() {
    syncPrint("Testing getBit():\n");
    testCase("1. Test with zero bit", getBit(0, 3) == 0);
    testCase("2. Test with zero bit again", getBit(0xFF, 9) == 0);
    testCase("3. Test with one bit", getBit(0xFFFF, 3) == 1);
    testCase("4. Test with one bit again", getBit(0xFFFF, 9) == 1);
    testCase("5. Test with invalid bit (assertion should fail)", getBit(0, 16) == 0);
}

void testGetPSW() {
    syncPrint("Testing getPSW():\n");
    lock
    testCase("1. Test with I = 0", getBit(getPSW(), 9) == 0);
    unlock
    testCase("2. Test with I = 1", getBit(getPSW(), 9) == 1);
}

void testUtil() {
    syncPrint("===================================== util =====================================\n");
    testEnsure();
    testGetBit();
    testGetPSW();
}
