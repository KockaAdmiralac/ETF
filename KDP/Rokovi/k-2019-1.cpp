#include "common.h"

const int N = 100;
// Један више како бисмо могли да користимо проверу head == tail
// да бисмо видели да ли је листа празна
sem sems[N + 1];
bool isReader[N + 1];
int head = 0;
int tail = 0;
sem mutex;
// count == -1 => читалац
int count = 0;

void read();
void write();

void reader() {
    mutex.wait();
    if (head == tail && count >= 0) {
        // Ако је листа празна значи да сигурно немамо писаца у њој
        ++count;
        mutex.signal();
    } else {
        int index = tail;
        tail = (tail + 1) % (N + 1);
        isReader[index] = true;
        mutex.signal();
        sems[index].wait();
    }
    read();
    mutex.wait();
    if (--count == 0 && head != tail) {
        // Следећи мора да је писац, јер да је читалац листа би била празна
        count = -1;
        sems[head].signal();
        head = (head + 1) % (N + 1);
    }
    mutex.signal();
}

void writer() {
    mutex.wait();
    if (head == tail && count == 0) {
        // Ако нема читалаца нити писаца и листа је празна, можемо само да прођемо
        --count;
        mutex.signal();
    } else {
        int index = tail;
        tail = (tail + 1) % (N + 1);
        isReader[index] = false;
        mutex.signal();
        sems[index].wait();
    }
    write();
    mutex.wait();
    if (head == tail) {
        // Нико више не чека
        count = 0;
    } else if (isReader[head]) {
        // Чекају читаоци иза писца
        count = 0;
        while (isReader[head] && head != tail) {
            ++count;
            sems[head].signal();
            head = (head + 1) % (N + 1);
        }
    } else {
        // Чека писац иза писца
        sems[head].signal();
        head = (head + 1) % (N + 1);
    }
    mutex.signal();
}
