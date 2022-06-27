#include "common.h"

const int N = 5;

void barber() {
    int current = 0;
    int currPeople;
    in("people", &currPeople);
    out("people", currPeople);
    while (true) {
        if (currPeople == 0) {
            in("wakeup");
        }
        out("current", current++);
        in("sat");
        // Берберин шиша муштерију
        in("people", &currPeople);
        --currPeople;
        out("people", currPeople);
        out("finished");
    }
}

bool customer() {
    int currPeople;
    in("people", &currPeople);
    if (currPeople == 0) {
        // Муштерија буди берберина
        out("wakeup");
    } else if (currPeople == N + 1) {
        // Муштерија одлази
        out("people", currPeople);
        return false;
    }
    int myTicket;
    in("ticket", &myTicket);
    out("ticket", myTicket + 1);
    out("people", currPeople + 1);
    // Муштерија чека на свој ред
    in("current", myTicket);
    out("sat");
    in("finished");
    return true;
}

void initialize() {
    out("ticket", 0);
    out("people", 0);
}
