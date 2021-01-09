#include "aranzman.hpp"

void Aranzman::dodeliSmestaj(Smestaj &smestaj) {
    if (&smestaj.dohvatiDestinaciju() != &destinacija) {
        throw GNijeVezanZaDestinaciju();
    }
    this->smestaj = &smestaj;
}

void Aranzman::dodeliPrevoz(Prevoz &prevoz) {
    if (prevoz.dohvatiDestinaciju().dohvatiNaziv() != destinacija.dohvatiNaziv()) {
        throw GNijeVezanZaDestinaciju();
    }
    this->prevoz = &prevoz;
}

double Aranzman::dohvatiCenu() const {
    if (smestaj == nullptr || prevoz == nullptr) {
        throw GNisuDodeljeniSmestajIliPrevoz();
    }
    return smestaj->dohvatiCenuPoDanu() * dohvatiTrajanje() + prevoz->cenaPrevoza();
}

std::ostream &operator<<(std::ostream &it, const Aranzman &aranz) {
    aranz.pisi(it);
    return it;
}

void Aranzman::pisi(std::ostream &it) const {
    it << destinacija << std::endl << (*smestaj) << std::endl << dohvatiCenu();
}
