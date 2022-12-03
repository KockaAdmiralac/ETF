#include "pp1.hpp"
#define BIT 1

char input;

int terminal(char t) {
    if (input == t) {
        input = advance();
        // Za dobijanje vrednosti terminala BIT.
        return getInputValue();
    } else {
        reject();
    }
}

void parse() {
    int n;
    input = advance();
    niz(n);
    terminal(EOF);
}

void niz(int& n) {
    switch (input) {
        case BIT: 
            int p;
            int e;
            broj(p, e);
            int n1;
            niz1(n1);
            n = n1 + p;
            break;
        default: reject();
    }
}

void niz1(int& n) {
    switch (input) {
        case ',':
            terminal(',');
            int p;
            int e;
            broj(p, e);
            int n1;
            niz1(n1);
            n = n1 + p;
            break;
        case EOF:
            n = 0;
            break;
        default: reject();
    }
}

void broj(int& p, int& e) {
    switch (input) {
        case BIT:
            e = 0;
            int v = terminal(BIT);
            int p1;
            int e1;
            broj1(p1, e1);
            p = p1;
            if (e1) {
                p = v;
            }
            break;
        default: reject();
    }
}

void broj1(int& p, int& e) {
    switch (input) {
        case BIT:
            e = 0;
            int v = terminal(BIT);
            int p1;
            int e1;
            broj1(p1, e1);
            p = p1;
            if (e1) {
                p = v;
            }
            break;
        case ',':
        case EOF:
            p = 0;
            e = 1;
            break;
        default: reject();
    }
}

