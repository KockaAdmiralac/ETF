#include "korisnik.hpp"

std::ostream &operator<<(std::ostream &it, const Korisnik &korisnik) {
    it << korisnik.ime;
    korisnik.specificanIspis(it);
    return it;
}
