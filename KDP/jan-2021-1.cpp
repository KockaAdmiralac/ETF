#include "common.h"
/**
 * Потребно је реализовати тајмер користећи приватне семафоре
 * и технику предаје штафетне палице. Тајмер има две методе, прва је
 * метода wakeme која омогућава да се дата нит блокирана n јединица
 * времена (ово је аргумент), а друга је метода tick која означава да је
 * истекла једна јединица времена.
 */
class Timer {
    sem* tail = nullptr;
    sem modifySem = 1;
public:
    void wakeme(int n) {
        modifySem.wait();
        sem currSem = 0;
        sem* nextSem = tail;
        tail = &currSem;
        modifySem.signal();
        do {
            currSem.wait();
            if (nextSem != nullptr) {
                nextSem->signal();
            }
        } while (--n > 0);
    }
    void tick() {
        //
    }
};

