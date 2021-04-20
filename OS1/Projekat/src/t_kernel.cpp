/**
 * t_kernel.h
 *
 * Test module for basic kernel functions.
 */
#include <kernel.h>
#include <test.h>
#include <util.h>

#ifdef KERNEL_DEBUG
int userMain(int argc, char* argv[]) {
    lockInterrupts
    cout << "userMain" << endl;
    unlockInterrupts
    return 0;
}
#endif

void testKernel() {
    cout << "==================================== kernel ====================================" << endl;
    char* argv[] = {"kernel"};
    Kernel::run(1, argv);
}
