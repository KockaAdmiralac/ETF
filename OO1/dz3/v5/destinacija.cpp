#include "destinacija.hpp"

void Destinacija::oceni(unsigned ocena) {
    if (ocena > 5) {
        return;
    }
    double zbirOcena = prosecnaOcena * brojOcena + ocena;
    ++brojOcena;
    prosecnaOcena = zbirOcena / brojOcena;
}

bool operator>(const Destinacija &dest1, const Destinacija &dest2) {
    return dest1.prosecnaOcena > dest2.prosecnaOcena;
}

std::ostream &operator<<(std::ostream &it, const Destinacija &dest) {
    dest.pisi(it);
    return it;
}

void Destinacija::pisi(std::ostream &it) const {
    it << "[" << prosecnaOcena << "] " << naziv << " (" << opis << ")";
}
