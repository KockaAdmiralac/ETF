#include "pp1.hpp"
#include <algorithm>

using namespace std;

char input;

void terminal(char t) {
    if (input == t) {
        input = advance();
    } else {
        reject();
    }
}

void parse() {
    input = advance();
    int depth;
    S(depth);
}

void S(int& depth) {
    switch (input) {
        case 'a':
            terminal('a');
            depth = 0;
            break;
        case '(':
            terminal('(');
            int d1;
            L(d1);
            depth = d1;
            terminal(')');
        default: reject();
    }
}

void L(int& depth) {
    switch (input) {
        case '(':
        case 'a':
            int d1;
            int d2;
            S(d1);
            L1(d2);
            depth = max(d1, d2);
            break;
        default: reject();
    }
}

void L1(int& depth) {
    switch (input) {
        case ',':
            terminal(',');
            int d1;
            int d2;
            S(d1);
            L1(d2);
            depth = max(d1, d2);
            break;
        case ')':
            depth = 0;
            break;
        default: reject();
    }
}
