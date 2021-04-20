#include <setjmp.h>

class Thread {
public:
    Thread(void (*body)(void*));
    void start();
protected:
    Thread();
    virtual void run() {}
};

class Queue {
public:
    void put(Thread*);
    Thread* get();
};

class Semaphore {
public:
    Semaphore(unsigned short init=1) : val(init) {}
    void wait ();
    void signal ();
    int value () const { return val; }
protected:
    void block ();
    void unblock ();
private:
    int val;
    Queue blocked;
};
