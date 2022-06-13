#include "common.h"

const int FINAL_TIME = 100;
const int INITIAL_VALUE = 50;
const int RESERVE_VALUE = 100;

int getBid();
void sleep(unsigned int seconds);

void vodjaLicitacije() {
    out("value", INITIAL_VALUE, -1);
    in("time out");
    int value;
    int user;
    in("value", &value, &user);
    out("ended", value > RESERVE_VALUE);
    out("value", value, user);
}

void ucesnikULicitaciji(int i) {
    int value;
    int user;
    int bid = getBid();
    bool success;
    in("value", &value, &user);
    if (rdp("ended") || value > bid) {
        out("value", value, user);
    } else {
        out("value", bid, i);
    }
    rd("ended", &success);
    rd("value", &value, &user);
    if (success && user == i) {
        // Ми добијамо лицитацију
    }
}

void tick() {
    int time = 0;
    while (true) {
        sleep(1);
        if (++time == FINAL_TIME) {
            out("time out");
        }
    }
}
