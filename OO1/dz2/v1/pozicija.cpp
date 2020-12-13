#include <cstddef>
#include "pozicija.hpp"

std::size_t diff(std::size_t a, std::size_t b) {
    return (a > b) ? (a - b) : (b - a);
}

std::size_t Pozicija::operator-(const Pozicija &b) const {
    return diff(vrsta, b.vrsta) + diff(kolona, b.kolona);
}
