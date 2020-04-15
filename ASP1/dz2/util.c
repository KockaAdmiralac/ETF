#include "util.h"

/**
 * Čišćenje ekrana realizovano korišćenjem VT100 komandi.
 * @see https://www.csie.ntu.edu.tw/~r92094/c++/VT100.html
 */
void clear() {
    printf("%c[2J%c[f", VT100_ESCAPE, VT100_ESCAPE);
}
