#include "../../../kernel.h"

class Resource {
public:
    Resource();
    int acquire();
    void release();
protected:
    void block();
    void deblock();
private:
    Thread *curr = nullptr;
    unsigned long timestamp = -1;
    Queue blocked;
};

int Resource::acquire() {
    lock();
    if (curr == nullptr) {
        curr = Thread::currentThread;
        timestamp = Thread::timestamp;
        unlock();
        return 1;
    } else if (Thread::timestamp < timestamp) {
        timestamp = Thread::timestamp;
        block();
        curr = Thread::currentThread;
        unlock();
        return 1;
    } else {
        unlock();
        return 0;
    }
}

void Resource::release() {
    lock();
    Thread *thr = blocked.first();
    if (thr == nullptr) {
        curr = nullptr;
        timestamp = -1;
    } else {
        deblock();
    }
    unlock();
}
