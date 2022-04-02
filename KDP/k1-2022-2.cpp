#include "common.h"
#include <list>

using namespace std;

const int N = 100;
const int M = 100;

// Комуникација између аутомобила и особа
sem carSems[N];
sem peopleSems[M];
// Међусобно искључивање при приступу глобалном стању
sem mutex = 1;
// Подаци заштићени mutex-ом:
list<int> freeCars;
list<int> freePeople;
int mutexId;

void car(int carId) {
    int personId;
    while (true) {
        mutex.wait();
        if (freePeople.size() > 0) {
            personId = freePeople.front();
            freePeople.pop_front();
            mutexId = carId;
            peopleSems[personId].signal();
            // Нема ослобађања mutex, чекамо да особа прочита mutexId
            carSems[carId].wait();
        } else {
            freeCars.push_back(carId);
            mutex.signal();
            carSems[carId].wait();
            personId = mutexId;
            // Ослобађамо mutex који је особа закључала
            mutex.signal();
            // Обавештавамо особу да смо прочитали mutexId
            peopleSems[personId].signal();
        }
        // Особа контролише ауто, чекамо да нас особа обавести кад заврши
        carSems[carId].wait();
        // Враћени смо назад
    }
}

void person(int personId) {
    int carId;
    while (true) {
        // Шетамо
        mutex.wait();
        if (freeCars.size() > 0) {
            carId = freeCars.front();
            freeCars.pop_front();
            mutexId = personId;
            carSems[carId].signal();
            // Нема ослобађања mutex, чекамо да аутомобил прочита mutexId
            peopleSems[personId].wait();
        } else {
            freePeople.push_back(personId);
            mutex.signal();
            peopleSems[personId].wait();
            carId = mutexId;
            // Ослобађамо mutex који је аутомобил закључао
            mutex.signal();
            // Обавештавамо аутомобил да смо прочитали mutexId
            carSems[carId].signal();
        }
        // Возимо и на крају обавестимо аутомобил да смо завршили
        carSems[carId].signal();
        // Настављамо шетњу
    }
}

