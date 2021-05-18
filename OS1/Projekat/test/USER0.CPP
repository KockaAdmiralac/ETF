/**
 * USER0.CPP
 *
 * Default kernel test that does nothing.
 */
#include <kernel.h>

void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    return 0;
}
