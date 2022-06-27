#include "common.h"

const int N = 100;
const int M = 100;
const int K = 50;

// Одређују са које станице на коју станицу иду путници
// Претпоставља се да један путник неће ићи са једне на ту исту станицу
int getStationIdFrom();
int getStationIdTo();

struct Station {
    // Број путника који чекају на станици
    int numPassengers = 0;
    // Број путника који треба да провере свој статус
    // пре него што аутобус настава
    int passengersChecking = 0;
    // Овим бројем ће бити ажуриран број путника у аутобусу
    // након што сви путници провере свој статус
    int busPassengers = 0;
    // Редослед доласка аутобуса на станицу
    int currTicket = 0;
    int nextTicket = 0;
    // Аутобус који је тренутно на станици
    int busId = -1;
    // Број путника који треба да изађу на станици
    // из одређеног аутобуса
    int passengersExiting[M] = {0};
};
Station stations[N];

void bus(int busId) {
    int stationId = 0;
    int numPassengers = 0;
    while (true) {
        Station& station = stations[stationId];
        region (station) {
            int myTicket = station.nextTicket++;
            // Чекамо ред на станици
            await (station.currTicket == myTicket);
            station.busId = busId;
            station.passengersChecking = station.numPassengers + station.passengersExiting[busId];
            station.busPassengers = numPassengers;
            // Чекамо да сви путници који улазе или излазе провере свој статус
            await (station.passengersChecking == 0);
            station.busId = -1;
            numPassengers = station.busPassengers;
            // Пуштамо следећи аутобус
            ++station.currTicket;
        }
        // Путујемо
        // Бирамо следећу станицу по кружном принципу
        stationId = (stationId + 1) % N;
    }
}

void passenger() {
    while (true) {
        Station& stationFrom = stations[getStationIdFrom()];
        Station& stationTo = stations[getStationIdTo()];
        bool entranceSuccessful = false;
        int currentBusId;
        while (!entranceSuccessful) {
            region (stationFrom) {
                // Дошли смо на станицу
                ++stationFrom.numPassengers;
                if (stationFrom.busId == -1) {
                    // Чекамо аутобус
                    await (stationFrom.busId != -1);
                } else {
                    // Аутобус је већ био ту, проверавамо статус
                    ++stationFrom.passengersChecking;
                }
                currentBusId = stationFrom.busId;
                if (stationFrom.busPassengers < K) {
                    // Успели смо да уђемо у аутобус
                    ++stationFrom.busPassengers;
                    --stationFrom.numPassengers;
                    entranceSuccessful = true;
                }
            }
            region (stationTo) {
                if (entranceSuccessful) {
                    ++stationTo.passengersExiting[currentBusId];
                }
            }
            region (stationFrom) {
                // Проверили смо свој статус и ажурирали бројеве
                --stationFrom.passengersChecking;
            }
        }
        // Путујемо
        region (stationTo) {
            // Чекамо док аутобус не дође на станицу
            await (stationTo.busId == currentBusId);
            --stationTo.passengersExiting[currentBusId];
            --stationTo.busPassengers;
            --stationTo.passengersChecking;
        }
    }
}

