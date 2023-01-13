#include "pp1.hpp"

char input;

void A(int x, int& y, int& z) {
    switch (input) {
        case 'a':
            input = advance();
            int q = getInputValue();
            out('c', x - q);
            int u;
            A(x, z, u);
            int t;
            A(u, t, y);
            break;
        case 'd':
            input = advance();
            out('b', x);
            input = advance();
            y = z = getInputValue();
            break;
    }
}
