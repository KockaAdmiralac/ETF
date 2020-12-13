#include "uredjaj.hpp"

int Uredjaj::jedinstveniId = 0;

void Uredjaj::pisi(std::ostream &it) const {
    it << proizvodjac << ":" << id;
}

std::ostream &operator<<(std::ostream &it, const Uredjaj &uredjaj) {
    uredjaj.pisi(it);
    return it;
}
