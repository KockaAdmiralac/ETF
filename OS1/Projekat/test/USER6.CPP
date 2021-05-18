/**
 * USER6.CPP
 *
 * Tests whether a simple keyboard event listener works.
 */
#include <event.h>
#include <kernel.h>

PREPAREENTRY(0x9, true)

void tick() {}

int userMain(int argc, char* argv[]) {
    (void) argc;
    (void) argv;
    Event evt(0x9);
    for (unsigned i = 0; i < 64; ++i) {
        syncPrint("Key %d\n", i);
        evt.wait();
    }
    return 0;
}
