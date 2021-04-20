#include "../../kernel.h"

class RowAdder : public Thread {
public:
    RowAdder (int arr[], int cnt, int* res, Semaphore* sem) :
        a(arr), n(cnt), r(res), s(sem) {}
protected:
    void run() override;
private:
    int *a, n, *r;
    Semaphore* s;
};
void RowAdder::run () {
    *r = 0;
    for (int i=0; i<n; i++) *r += a[i];
    if (s) s->signal();
}

const int M = 20, N = 30;
int mat[M][N];
int res[M];

void mat_add() {
    Semaphore *s[M];
    RowAdder *ra[M];
    for (int i = 0; i < M; ++i) {
        s[i] = new Semaphore(0);
        ra[i] = new RowAdder(mat[i], N, &res[i], s[i]);
        ra[i]->start();
    }
    for (int i = 0; i < M; ++i) {
        s[i]->wait();
        delete s[i];
        delete ra[i];
    }
}
