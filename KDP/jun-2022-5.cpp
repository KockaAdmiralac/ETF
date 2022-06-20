#include "common.h"

void philosopher(int ID, chan<string> release, chan<char> forkL, chan<char> forkR) {
    while (true) {
        // Филозофирамо
        if (ID % 2 == 0) {
            forkL.send('R');
            forkR.send('L');
        } else {
            forkR.send('L');
            forkL.send('R');
        }
        // Једемо
        release.receive();
        release.receive();
    }
}

void fork(chan<char> acquire, chan<string> philL, chan<string> philR) {
    while (true) {
        char dir = acquire.receive();
        if (dir == 'L') {
            philL.send("release");
        } else {
            philR.send("release");
        }
    }
}
