/**
 * USER114.cpp
 *
 * Testing a timer.
 * @see https://drive.google.com/open?id=11uyCIaCpMwSKIyfH7PFRzwGazAMxSnMa
 */
#include <kernel.h>

unsigned t = 18;
unsigned seconds = 5;

void secondPast() {
    if (seconds) {
        syncPrint("%d\n", seconds);
    }
    seconds--;
}

void tick() {
    t--;
    if (t == 0) {
        t = 18;
        secondPast();
    }
}

int userMain(int argc, char** argv) {
    (void) argc;
    (void) argv;
    syncPrint("Starting test\n");
    while (seconds);
    syncPrint("Test ends\n");
    return 0;
}
