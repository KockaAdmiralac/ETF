struct sem {
    sem(int);
    void wait();
    void signal();
};

void skip();
template<typename T> bool CAS(T a, T b, T c);
template<typename T> void SWAP(T var1, T var2);
bool TS(bool var);

struct Node {
    Node* next;
    bool locked;
};
