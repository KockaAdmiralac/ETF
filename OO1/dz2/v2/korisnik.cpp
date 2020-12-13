#include "korisnik.hpp"

void Korisnik::pisi(std::ostream &it) const {
    it << ime;
}

std::ostream &operator<<(std::ostream &it, const Korisnik &korisnik) {
    korisnik.pisi(it);
    return it;
}
