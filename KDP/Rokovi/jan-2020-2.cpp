#include "common.h"
#include <list>
#include <cstdlib>

using namespace std;

struct Floor {
    list<sem*> peopleEntering;
    sem mutexEntering = 1;
    list<sem*> peopleExiting;
    sem mutexExiting = 1;
};

const int N = 10;
Floor floors[N];
sem liftSem = 0;

void person() {
    sem personSem = 0;
    int currentFloorIndex = rand() % N;
    while (true) {
        // Особа може да каже да хоће да изађе на истом спрату као тренутном
        // Претпоставка: особа није глупа
        int nextFloorIndex = rand() % N;
        Floor& currentFloor = floors[currentFloorIndex];
        Floor& nextFloor = floors[nextFloorIndex];
        currentFloor.mutexEntering.wait();
        currentFloor.peopleEntering.push_back(&personSem);
        currentFloor.mutexEntering.signal();
        // Чекамо да дође лифт
        personSem.wait();
        // Улазимо у лифт и бирамо на којем спрату стајемо
        nextFloor.mutexExiting.wait();
        nextFloor.peopleExiting.push_back(&personSem);
        nextFloor.mutexExiting.signal();
        liftSem.signal();
        // Чекамо да лифт стигне на наш спрат
        personSem.wait();
        // Излазимо из лифта
        liftSem.signal();
    }
}

void lift() {
    int currentFloorIndex = 0;
    bool goingUp = true;
    while (true) {
        // Одређивање следећег спрата
        // Претпоставка: лифт све време иде горе-доле, без обзира да ли га је неко звао
        int nextFloor;
        if (goingUp) {
            if (++currentFloorIndex == N-1) {
                goingUp = false;
            }
        } else {
            if (--currentFloorIndex == 0) {
                goingUp = true;
            }
        }
        Floor& floor = floors[nextFloor];
        // Не морамо да чекамо на mutexExiting, јер се он заузима само када путници улазе
        // што тренутно није случај
        int countPeopleExiting = floor.peopleExiting.size();
        // Задржавамо mutexEntering док не испразнимо листу, како нам не би ушао неочекивани путник
        floor.mutexEntering.wait();
        int countPeopleEntering = floor.peopleEntering.size();
        if (countPeopleExiting == 0 && countPeopleEntering == 0) {
            // Не стајемо на овом спрату
            floor.mutexEntering.signal();
            continue;
        }
        // Стајемо на овом спрату
        // Пуштамо људе да изађу
        for (int i = 0; i < countPeopleExiting; ++i) {
            sem* personSem = floor.peopleExiting.front();
            personSem->signal();
            floor.peopleExiting.pop_front();
        }
        for (int i = 0; i < countPeopleExiting; ++i) {
            liftSem.wait();
        }
        // Пуштамо људе да уђу
        for (int i = 0; i < countPeopleEntering; ++i) {
            sem* personSem = floor.peopleEntering.front();
            personSem->signal();
            floor.peopleEntering.pop_front();
        }
        for (int i = 0; i < countPeopleEntering; ++i) {
            liftSem.wait();
        }
        floor.mutexEntering.signal();
        // Настављамо на следећи спрат
    }
}
