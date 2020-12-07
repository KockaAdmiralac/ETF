#ifndef _slika_hpp
#define _slika_hpp
#include <iostream>
#include <vector>
#include "piksel.hpp"
#include "pozicija.hpp"

const int BROJ_BITOVA_PO_PIKSELU = 24;

class Slika {
    public:
        Slika(int sirina, int visina) : sirina(sirina), visina(visina),
            matrica(visina, std::vector<Piksel>(sirina)) {}
        int dohvatiSirinu() const {
            return sirina;
        }
        int dohvatiVisinu() const {
            return visina;
        }
        int brojBitova() const {
            return sirina * visina * BROJ_BITOVA_PO_PIKSELU;
        }
        virtual void postavi(const Piksel &piksel, const Pozicija &pozicija);
        const Piksel &operator[](const Pozicija &pozicija);
        friend std::ostream &operator<<(std::ostream &it, const Slika &slika);
    private:
        int sirina, visina;
        std::vector<std::vector<Piksel>> matrica;
};

#endif
