#include <exception>
#include "slika.hpp"

void Slika::postavi(const Piksel &piksel, const Pozicija &pozicija) {
    matrica[pozicija.dohvatiVrstu()][pozicija.dohvatiKolonu()] = piksel;
}

const Piksel &Slika::operator[](const Pozicija &pozicija) const {
    if (
        pozicija.dohvatiKolonu() >= sirina ||
        pozicija.dohvatiVrstu() >= visina
    ) {
        throw std::out_of_range("Pristupa se pikselu van ograničenja.");
    }
    return matrica[pozicija.dohvatiVrstu()][pozicija.dohvatiKolonu()];
}

void Slika::pisi(std::ostream &it) const {
    it << brojBitova();
    for (std::size_t y = 0; y < visina; ++y) {
        it << std::endl;
        for (std::size_t x = 0; x < sirina; ++x) {
            it << matrica[y][x] << "\t";
        }
    }
}

std::ostream &operator<<(std::ostream &it, const Slika &slika) {
    slika.pisi(it);
    return it;
}
