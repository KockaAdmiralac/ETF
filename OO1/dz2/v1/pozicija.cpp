#include <cmath>
#include "pozicija.hpp"

int Pozicija::operator-(const Pozicija &b) {
    return std::abs(vrsta - b.vrsta) + std::abs(kolona - b.kolona);
}
