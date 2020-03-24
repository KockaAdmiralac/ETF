#include <stdio.h>

int main() {
    int N, max = 0, repeat = 0, curr, prev, dir = 0, diff, acc = 0;
    scanf("%d", &N);
    if (N < 2) {
        return 0;
    }
    scanf("%d", &prev);
    for (int i = 1; i < N; ++i) {
        scanf("%d", &curr);
        diff = curr - prev;
        if (dir == -1) {
            // Was descending
            if (diff < 0) {
                // Continued descending
                acc -= diff;
            } else {
                // Is now ascending
                if (acc > max) {
                    max = acc;
                    repeat = 1;
                } else if (acc == max) {
                    ++repeat;
                }
                dir = 1;
                acc = 0;
            }
        } else if (dir == 1) {
            // Was ascending
            if (diff > 0) {
                // Continued ascending
                // Do nothing about it.
            } else {
                // Is now descending
                dir = -1;
                acc = -diff;
            }
        } else {
            if (diff > 0) {
                dir = 1;
            } else {
                dir = -1;
                acc = diff;
            }
        }
        prev = curr;
    }
    if (acc > max) {
        max = acc;
        repeat = 1;
    } else if (acc == max) {
        ++repeat;
    }
    printf("Najduži spust: %d\nBroj pojavljivanja: %d\n", max, repeat);
    return 0;
}
