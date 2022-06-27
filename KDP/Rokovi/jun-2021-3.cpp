#include "common.h"

const int N = 100;
chan<pair<int, int>> values[N];

void process(int i, int v) {
    int min = v;
    int max = v;
    pair<int, int> newPair;
    if (i == 0) {
        // Први процес прво шаље, прима коначни резултат и прослеђује
        values[0].send({min, max});
        newPair = values[N-1].receive();
    } else {
        // Остали процеси прво примају, израчунавају, шаљу даље, примају коначни резултат и прослеђују
        newPair = values[i-1].receive();
        if (newPair.first < min) {
            min = newPair.first;
        }
        if (newPair.second > max) {
            max = newPair.second;
        }
        values[i].send({min, max});
        newPair = values[i-1].receive();
    }
    min = newPair.first;
    max = newPair.second;
    if (i != N-1) {
        // Ако смо последњи процес не треба да шаљемо првом опет, јер неће примити
        values[i].send({min, max});
    }
}
