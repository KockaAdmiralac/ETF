#include "common.h"
#include <list>

using namespace std;

const int N = 100;

sem carCount = N;
list<pair<sem*, sem*>> freeCars;
sem carMutex = 1;

void car() {
    sem carSem = 0;
    sem visitorSem = 0;
    while (true) {
        // Враћамо се назад на место (први пут, ово служи за иницијализацију)
        carMutex.wait();
        freeCars.push_back({&carSem, &visitorSem});
        carMutex.signal();
        carCount.signal();
        carSem.wait();
        // Посетилац се вози по парку
        visitorSem.signal();
        // Готова вожња по парку
        carSem.wait();
    }
}

void visitor() {
    while (true) {
        // Обилазак музеја
        carCount.wait();
        carMutex.wait();
        sem* carSem = freeCars.front().first;
        sem* visitorSem = freeCars.front().second;
        freeCars.pop_front();
        carSem->signal();
        carMutex.signal();
        // Вожња по парку
        visitorSem->wait();
        // Готова вожња по парку
        carSem->signal();
        // Посетилац је напустио парк и можда се некад врати
    }
}
