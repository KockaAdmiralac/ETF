#include "smestaj.hpp"

Smestaj::Smestaj(Destinacija &destinacija, Tip tip, std::string naziv, unsigned brojZvezdica, double cenaPoDanu) :
    destinacija(destinacija), tip(tip), naziv(naziv),
    brojZvezdica(brojZvezdica), cenaPoDanu(cenaPoDanu) {
    if (brojZvezdica < 1 || brojZvezdica > 5) {
        throw GPogresanBrojZvezdica();
    }
}

std::ostream &operator<<(std::ostream &it, const Smestaj &smestaj) {
    smestaj.pisi(it);
    return it;
}

void Smestaj::pisi(std::ostream &it) const {
    if (tip == HOTEL) {
        it << "Hotel";
    } else {
        it << "Apartman";
    }
    it << " " << naziv << " ";
    for (unsigned i = 0; i < brojZvezdica; ++i) {
        it << "*";
    }
}
