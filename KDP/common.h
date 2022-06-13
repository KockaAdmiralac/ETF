#include <string>
#include <utility>
#include <vector>
#define region(state)
#define await(condition)
#define EOS -1

using namespace std;

struct sem {
    sem(int);
    void wait();
    void signal();
};

template<typename T>
struct chan {
    void send(T data);
    T receive();
    bool empty();
};

void skip();
template<typename T> bool CAS(T a, T b, T c);
template<typename T> void SWAP(T var1, T var2);
bool TS(bool var);

struct Node {
    Node* next;
    bool locked;
};

void out(...);
void eval(...);
void in(const char* tag, ...);
void rd(const char* tag, ...);
bool inp(const char* tag, ...);
bool rdp(const char* tag, ...);
