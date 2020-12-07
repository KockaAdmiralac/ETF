#include "slika.hpp"

void Slika::postavi(const Piksel &piksel, const Pozicija &pozicija) {
    matrica[pozicija.dohvatiVrstu()][pozicija.dohvatiKolonu()] = piksel;
}

const Piksel &Slika::operator[](const Pozicija &pozicija) {
    return matrica[pozicija.dohvatiVrstu()][pozicija.dohvatiKolonu()];
}

std::ostream &operator<<(std::ostream &it, const Slika &slika) {
    it << slika.brojBitova();
    for (int y = 0; y < slika.visina; ++y) {
        it << std::endl;
        for (int x = 0; x < slika.sirina; ++x) {
            it << slika.matrica[y][x] << "\t";
        }
    }
    return it;
}
