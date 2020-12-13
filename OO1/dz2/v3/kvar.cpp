#include "kvar.hpp"

void Kvar::pisi(std::ostream &it) const {
    it << datum << "-" << opis;
}

std::ostream &operator<<(std::ostream &it, const Kvar &kvar) {
    kvar.pisi(it);
    return it;
}
