#include "common.h"

sem entry = 1;
sem readerSem = 0;
sem writerSem = 0;
int numReaders = 0;
int numWriters = 0;
int blockedReaders = 0;
int blockedWriters = 0;

void read();
void write();

void reader() {
    while (true) {
        entry.wait();
        if (numWriters > 0) {
            ++blockedReaders;
            entry.signal();
            readerSem.wait();
            ++numReaders;
        } else {
            ++numReaders;
            entry.signal();
        }
        readerSem.signal();
        read();
        entry.wait();
        if (--numReaders == 0 && blockedWriters > 0) {
            --blockedWriters;
            writerSem.signal();
        }
        entry.signal();
    }
}

void writer() {
    while (true) {
        entry.wait();
        if (numWriters > 0 || numReaders > 0) {
            ++blockedWriters;
            writerSem.wait();
        }
        ++numWriters;
        entry.signal();
        write();
        entry.wait();
        --numWriters;
        if (blockedWriters > 0) {
            --blockedWriters;
            writerSem.signal();
        } else if (blockedReaders > 0) {
            --blockedReaders;
            readerSem.signal();
        }
        entry.signal();
    }
}
