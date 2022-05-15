#include "common.h"
#include <map>
#include <queue>

using namespace std;

struct BarberShop {
    // Додељивање идентификатора муштеријама по реду доласка
    int ticket = 1;
    // Идентификатор особе која седи у седишту, или 0 уколико нико не седи
    int seat[2] = {0};
    // Да ли је берберин завршио са шишањем и чека особу да плати
    bool finished[2] = {false};
    // std::map је подразумевано сортиран
    map<int, int> waitingQueue;
    // Редови чекања за муштерије код Аце, Браце и оне којима је свеједно
    queue<int> barberQueue[3];
};
BarberShop shop;

const int ACA_ID = 0;
const int BRACA_ID = 1;
const int ANY_ID = 2;

void barber(int id) {
    while (true) {
        region (shop) {
            // Спавамо док чекамо да прва особа која дође седне на столицу
            await (shop.seat[id] != 0);
        }
        // Шишање
        region (shop) {
            // Завршено шишање, чекамо на плаћање
            shop.finished[id] = true;
            await (!shop.finished[id]);
            // Узимамо следећу муштерију
            if (!shop.barberQueue[id].empty()) {
                shop.seat[id] = shop.barberQueue[id].front();
                shop.barberQueue[id].pop();
            } else if (!shop.barberQueue[ANY_ID].empty()) {
                shop.seat[id] = shop.barberQueue[ANY_ID].front();
                shop.barberQueue[ANY_ID].pop();
            } else {
                shop.seat[id] = 0;
            }
        }
    }
}

// Да ли је седиште за шишање код одређеног берберина тренутно резервисано за неку особу
int barberEquals(int barberId, int value) {
    if (barberId == ACA_ID && shop.seat[ACA_ID] == value) {
        return ACA_ID;
    }
    if (barberId == BRACA_ID && shop.seat[BRACA_ID] == value) {
        return BRACA_ID;
    }
    if (barberId == ANY_ID) {
        if (shop.seat[ACA_ID] == value) {
            return ACA_ID;
        }
        if (shop.seat[BRACA_ID] == value) {
            return BRACA_ID;
        }
    }
    return -1;
}

int barberFree(int barberId) {
    return barberEquals(barberId, 0);
}

void client(int barberId) {
    region (shop) {
        if (shop.waitingQueue.size() == 15 && barberFree(barberId) == -1) {
            // Особа не може бити услужена
            return;
        }
        int myTicket = shop.ticket++;
        if (barberFree(barberId) != 1) {
            // Без чекања седамо на столицу за шишање
            shop.seat[barberFree(barberId)] = myTicket;
        } else {
            shop.barberQueue[barberId].push(myTicket);
            // Овиме повећавамо shop.waitingQueue.size()
            shop.waitingQueue[myTicket] = shop.waitingQueue.size();
            // Чекамо на столицу за чекање или шишање
            await (shop.waitingQueue[myTicket] < 10 || barberEquals(barberId, myTicket) != -1);
            if (barberEquals(barberId, myTicket) == -1) {
                // Седамо на столицу за чекање
                await (barberEquals(barberId, myTicket) != -1);
            }
            // Устали смо са столице и смањујемо shop.waitingQueue.size
            shop.waitingQueue.erase(myTicket);
            int i = 0;
            for (auto& it : shop.waitingQueue) {
                shop.waitingQueue[it.first] = i++;
            }
        }
        int barber = barberEquals(barberId, myTicket);
        // Чекање током шишања
        await (shop.finished[barber]);
        // Плаћање
        shop.finished[barber] = false;
    }
}
