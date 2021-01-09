#include "osoba.hpp"

std::ostream &operator<<(std::ostream &it, const Osoba &osoba) {
    osoba.pisi(it);
    return it;
}

void Osoba::pisi(std::ostream &it) const {
    it << "O(" << ime << ", " << jmbg << ", " << datum << ")";
}
