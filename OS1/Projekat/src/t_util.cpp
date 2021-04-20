/**
 * t_util.cpp
 *
 * Test module for project utility functions and macros.
 */
#include <test.h>
#include <util.h>

void testAssert() {
    cout << "Testing assert():" << endl;
    cout << "1. Test with true value... ";
    testResult(!assert(true, "This should not be printed."));
    cout << "2. Test with false value (assertion should fail)... ";
    testResult(assert(false, "This should be printed."));
}

void testGetBit() {
    cout << "Testing getBit():" << endl;
    cout << "1. Test with zero bit... ";
    testResult(getBit(0, 3) == 0);
    cout << "2. Test with zero bit again... ";
    testResult(getBit(0xFF, 9) == 0);
    cout << "3. Test with one bit... ";
    testResult(getBit(0xFFFF, 3) == 1);
    cout << "4. Test with one bit again... ";
    testResult(getBit(0xFFFF, 9) == 1);
    cout << "5. Test with invalid bit (assertion should fail)... ";
    testResult(getBit(0, 16) == 0);
}

void testGetPSW() {
    cout << "Testing getPSW():" << endl;
    lock
    cout << "1. Test with I = 0... ";
    testResult(getBit(getPSW(), 9) == 0);
    unlock
    cout << "2. Test with I = 1... ";
    testResult(getBit(getPSW(), 9) == 1);
}

void testUtil() {
    cout << "===================================== util =====================================" << endl;
    testAssert();
    testGetBit();
    testGetPSW();
}
