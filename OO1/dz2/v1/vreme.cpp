#include "vreme.hpp"

bool Vreme::operator<(const Vreme &vreme2) const {
    return sat < vreme2.sat || (
        sat == vreme2.sat &&
        minut < vreme2.minut
    ) || (
        sat == vreme2.sat &&
        minut == vreme2.minut &&
        sekund < vreme2.sekund
    );
}

bool Vreme::operator==(const Vreme &vreme2) const {
    return sat == vreme2.sat &&
           minut == vreme2.minut &&
           sekund == vreme2.sekund;
}

void Vreme::pisi(std::ostream &it) const {
    it << sat << ":" << minut << ":" << sekund;
}

std::ostream &operator<<(std::ostream &it, const Vreme &vreme) {
    vreme.pisi(it);
    return it;
}
