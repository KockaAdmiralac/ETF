#include "namirnica.hpp"

bool operator==(const Namirnica &n1, const Namirnica &n2) {
    return n1.naziv == n2.naziv;
}

std::ostream &operator<<(std::ostream &it, const Namirnica &namirnica) {
    namirnica.pisi(it);
    return it;
}

void Namirnica::pisi(std::ostream &it) const {
    it << naziv << " - " << nut;
}
