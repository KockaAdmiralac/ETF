#include "common.h"

const int N = 100;
const int K = 50;

sem sems[2 * N + 1];
int capacity = N;
int entering = 0;
int exiting = 0;
int enterTail = 0;
int enterHead = 0;
int exitTail = 0;
int exitHead = 0;
// true - излаз, false - улаз
bool priority = true;
int passed = 0;
sem& mutex = sems[2 * N];
bool requestEntrance() {
    mutex.wait();
    if (capacity - entering + exiting <= 0) {
        mutex.signal();
        return false;
    }
    ++entering;
    if (entering == 1 && exiting == 0) {
        // Слободан пролаз
        mutex.signal();
        return true;
    }
    int semIndex = enterTail;
    enterTail = (enterTail + 1) % N;
    mutex.signal();
    sems[semIndex].wait();
    return true;
}
void requestExit() {
    mutex.wait();
    ++capacity;
    ++exiting;
    if (entering == 0 && exiting == 1) {
        // Слободан пролаз
        mutex.signal();
        return;
    }
    int semIndex = exitTail + N;
    exitTail = (exitTail + 1) % N;
    mutex.signal();
    sems[semIndex].wait();
}
void entered() {
    mutex.wait();
    --entering;
    --capacity;
    signal();
    mutex.signal();
}
void exited() {
    mutex.wait();
    --exiting;
    signal();
    mutex.signal();
}
void signal() {
    int semIndex = -1;
    bool hasCapacity = (capacity - exiting) < N;
    bool signalExit = (exiting > 0) && (priority || !hasCapacity || entering == 0);
    bool signalEnter = (entering > 0 && hasCapacity) && (!priority || exiting == 0);
    if (signalExit) {
        semIndex = exitHead + N;
        exitHead = (exitHead + 1) % N;
    } else if (signalEnter) {
        semIndex = enterHead;
        enterHead = (enterHead + 1) % N;
    }
    if (semIndex >= 0) {
        if (priority != signalExit) {
            // Ако сада није изашао аутомобил из реда који је имао приоритет,
            // ресетује се бројач узастопних аутомобила
            passed = 0;
        } else {
            ++passed;
        }
        if (passed == K) {
            passed = 0;
            priority = !priority;
        }
        sems[semIndex].signal();
    }
}
void car() {
    while (true) {
        if (requestEntrance()) {
            entered();
            // ...
            requestExit();
            // pay();
            exited();
        }
    }
}
