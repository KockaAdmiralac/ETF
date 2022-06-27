#include "common.h"
#include <map>
#include <queue>

using namespace std;

// Структуре за упућивање захтева запосленом
struct Request {
    int customerId;
    unsigned place;
};
enum RequestType {
    STANDARD_VEHICLE,
    LUXURY_VEHICLE,
    ANY_VEHICLE,
    RETURN_VEHICLE
};

// Монитор
struct CarDealership {
    queue<Request> standardRequests;
    queue<Request> luxuryRequests;
    queue<Request> anyRequests;
    queue<Request> returnRequests;
    map<int, int> rentedCars;
    int place = 1;
};
CarDealership dealership;

// Ова два реда се мењају само из запосленог, тако да не морају да буду у региону.
queue<int> standardCars;
queue<int> luxuryCars;

int rentCar(int customerId, int which) {
    region (dealership) {
        unsigned myPlace = dealership.place++;
        switch (which) {
            case STANDARD_VEHICLE:
                dealership.standardRequests.push({customerId, myPlace});
                break;
            case LUXURY_VEHICLE:
                dealership.luxuryRequests.push({customerId, myPlace});
                break;
            case ANY_VEHICLE:
                dealership.anyRequests.push({customerId, myPlace});
                break;
        }
        await (dealership.rentedCars[customerId]);
    }
}

void returnCar(int customerId) {
    region (dealership) {
        unsigned myPlace = dealership.place++;
        dealership.returnRequests.push({customerId, myPlace});
        await (!dealership.rentedCars[customerId]);
    }
}

void employee() {
    while (true) {
        Request req;
        int request = 0;
        region (dealership) {
            await (
                dealership.standardRequests.size() +
                dealership.luxuryRequests.size() +
                dealership.anyRequests.size() +
                dealership.returnRequests.size() > 0
            );
            unsigned minPlace = -1;
            if (
                !dealership.standardRequests.empty() &&
                !standardCars.empty() &&
                dealership.standardRequests.front().place < minPlace
            ) {
                minPlace = dealership.standardRequests.front().place;
                request = STANDARD_VEHICLE;
            }
            if (
                !dealership.luxuryRequests.empty() &&
                !luxuryCars.empty() &&
                dealership.luxuryRequests.front().place < minPlace
            ) {
                minPlace = dealership.luxuryRequests.front().place;
                request = LUXURY_VEHICLE;
            }
            if (
                !dealership.anyRequests.empty() &&
                (!standardCars.empty() || !luxuryCars.empty()) &&
                dealership.anyRequests.front().place < minPlace
            ) {
                minPlace = dealership.anyRequests.front().place;
                request = ANY_VEHICLE;
            }
            if (!dealership.returnRequests.empty() && dealership.returnRequests.front().place < minPlace) {
                minPlace = dealership.returnRequests.front().place;
                request = RETURN_VEHICLE;
            }
            switch (request) {
                case STANDARD_VEHICLE:
                    req = dealership.standardRequests.front();
                    dealership.standardRequests.pop();
                    break;
                case LUXURY_VEHICLE:
                    req = dealership.luxuryRequests.front();
                    dealership.luxuryRequests.pop();
                    break;
                case ANY_VEHICLE:
                    req = dealership.anyRequests.front();
                    dealership.anyRequests.pop();
                    break;
                case RETURN_VEHICLE:
                    req = dealership.returnRequests.front();
                    dealership.returnRequests.pop();
                    break;
            }
        }
        // Овде запослени ради неки свој посао бележења
        region (dealership) {
            switch (request) {
                case STANDARD_VEHICLE:
                    dealership.rentedCars[req.customerId] = standardCars.front();
                    standardCars.pop();
                    break;
                case LUXURY_VEHICLE:
                    dealership.rentedCars[req.customerId] = luxuryCars.front();
                    luxuryCars.pop();
                    break;
                case ANY_VEHICLE:
                    if (standardCars.empty()) {
                        dealership.rentedCars[req.customerId] = luxuryCars.front();
                        luxuryCars.pop();
                    } else {
                        dealership.rentedCars[req.customerId] = standardCars.front();
                        standardCars.pop();
                    }
                    break;
                case RETURN_VEHICLE:
                    int carId = dealership.rentedCars[req.customerId];
                    dealership.rentedCars[req.customerId] = 0;
                    if (carId > 20) {
                        luxuryCars.push(carId);
                    } else {
                        standardCars.push(carId);
                    }
                    break;
            }
        }
    }
}

int main() {
    for (int i = 0; i < 20; ++i) {
        standardCars.push(i + 1);
    }
    for (int i = 0; i < 10; ++i) {
        luxuryCars.push(i + 21);
    }
    return 0;
}
