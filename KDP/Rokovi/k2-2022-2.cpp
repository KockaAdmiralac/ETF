#include "common.h"

struct Boat {
    // Број мушкараца, жена и деце
    int men = 0;
    int women = 0;
    int children = 0;
    // Да ли је вожња готова (да ли је у току искрцавање)
    bool done;
    // Помоћне методе
    int total() {
        return men + women + children;
    }
    int adults() {
        return men + women;
    }
};
Boat boat;

void boatP() {
    while (true) {
        region (boat) {
            boat.done = false;
            await (boat.total() == 10 && boat.men >= 2);
        }
        // Вожња
        region (boat) {
            boat.done = true;
            await (boat.total() == 0);
        }
    }
}

void man() {
    while (true) {
        region (boat) {
            await (!boat.done);
            if (boat.total() < 10) {
                ++boat.men;
                break;
            } else {
                // Нисмо се укрцали, чекамо да се заврши вожња па поново
                await (boat.done);
            }
        }
    }
    // Укрцани смо
    region (boat) {
        await (boat.done);
        // Ако смо последњи одрасли, чекамо да сва деца изађу
        if (boat.adults() == 1 && boat.children > 0) {
            await (boat.children == 0);
        }
        --boat.men;
    }
}

void woman() {
    while (true) {
        region (boat) {
            await (!boat.done);
            if (boat.total() < 10 && boat.total() - boat.men >= 2) {
                ++boat.women;
                break;
            } else {
                // Нисмо се укрцали, чекамо да се заврши вожња па поново
                await (boat.done);
            }
        }
    }
    // Укрцани смо
    region (boat) {
        await (boat.done);
        // Ако смо последњи одрасли, чекамо да сва деца изађу
        if (boat.adults() == 1 && boat.children > 0) {
            await (boat.children == 0);
        }
        --boat.women;
    }
}

void child() {
    while (true) {
        region (boat) {
            await (!boat.done);
            if (boat.total() < 10 && boat.total() - boat.men >= 2 && boat.adults() > 0) {
                ++boat.children;
                break;
            } else {
                // Нисмо се укрцали, чекамо да се заврши вожња па поново
                await (boat.done);
            }
        }
    }
    // Укрцани смо
    region (boat) {
        await (boat.done);
        --boat.children;
    }
}
