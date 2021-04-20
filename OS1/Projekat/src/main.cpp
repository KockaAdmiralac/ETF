/**
 * main.cpp
 *
 * Simply runs the kernel.
 */
#ifndef KERNEL_DEBUG
#include <kernel.h>

int main(int argc, char* argv[]) {
    return Kernel::run(argc, argv);
}
#endif
