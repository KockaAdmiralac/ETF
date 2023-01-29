#include "pp1.hpp"

char input;

void terminal(char t) {
    if (input == t) {
        input = advance();
    } else {
        reject();
    }
}

void A() {
    terminal('a');
    terminal('b');
    B();
    terminal('b');
}

void C() {
    switch (input) {
        case 'c':
            terminal('c');
            C();
            break;
        case 'a':
            break;
        default:
            reject();
    }
}

void D() {
    terminal('d');
}

void B() {
    switch (input) {
        case 'a':
        case 'c':
            C();
            terminal('a');
            break;
        case 'd':
            D();
            C();
            terminal('a');
            break;
        case 'b':
        case EOF:
            break;
        default:
            reject();
    }
}

void S() {
    A();
    terminal('a');
    B();
}

void main() {
    input = advance();
    S();
    terminal(EOF);
}
