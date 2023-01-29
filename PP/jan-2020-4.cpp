#include "pp1.hpp"

char input;

void terminal(char c) {
    if (input == c) {
        input = advance();
    } else {
        reject();
    }
}

void S2() {
    switch (input) {
        case 'a':
            terminal('a');
            S2();
            break;
        case 'c':
        case EOF:
            break;
        default:
            reject();
    }
}

void S();

void S1() {
    switch (input) {
        case 'a':
        case 'b':
            S();
            break;
        case 'c':
            break;
        default:
            reject();
    }
}

void S() {
    switch (input) {
        case 'a':
            terminal('a');
            S();
            terminal('b');
            S2();
            break;
        case 'b':
            terminal('b');
            S1();
            terminal('c');
            S2();
            break;
        default:
            reject();
    }
}

void main() {
    input = advance();
    S();
    terminal(EOF);
}
