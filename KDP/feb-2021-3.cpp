#include "common.h"

void process() {
    chan<int> in;
    chan<int> out;
    int numReceived = 0;
    int input;
    int mem[2];
    while ((input = in.receive()) != EOS) {
        if (numReceived < 2) {
            mem[numReceived++] = input;
        } else {
            if (input <= mem[0] && input <= mem[1]) {
                out.send(input);
            } else if (mem[0] <= input && mem[0] <= mem[1]) {
                out.send(mem[0]);
                mem[0] = input;
            } else {
                out.send(mem[1]);
                mem[1] = input;
            }
        }
    }
    out.send(mem[0] + mem[1]);
    out.send(EOS);
}
