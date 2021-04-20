/**
 * t_thread.cpp
 *
 * Test module for threads and PCBs.
 */
#include <test.h>
#include <pcb.h>
#include <thread.h>

void testThreadPrivates() {
    cout << PCB::maximumStackSize << endl;
}

void testThread() {
    cout << "==================================== thrpcb ====================================" << endl;
    testThreadPrivates();
}
