#include "common.h"

int ticket = 0;
int current = 0;
int ticketMutex = 0;

void worker() {
    while (true) {
        do {
            while (ticketMutex) skip();
        } while (TS(ticketMutex));
        int slot = ticket++;
        ticketMutex = 0;
        while (current != ticket) skip();
        // Критична секција
        current++;
        // Некритична секција
    }
}
