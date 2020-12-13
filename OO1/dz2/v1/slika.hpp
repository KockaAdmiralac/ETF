#ifndef _slika_hpp
#define _slika_hpp
#include <iostream>
#include <vector>
#include "piksel.hpp"
#include "pozicija.hpp"

class Slika {
    public:
        Slika(std::size_t sirina, std::size_t visina) : sirina(sirina), visina(visina),
            matrica(visina, std::vector<Piksel>(sirina)) {}
        std::size_t dohvatiSirinu() const {
            return sirina;
        }
        std::size_t dohvatiVisinu() const {
            return visina;
        }
        std::size_t brojBitova() const {
            return sirina * visina * BROJ_BITOVA_PO_PIKSELU;
        }
        virtual void postavi(const Piksel &piksel, const Pozicija &pozicija);
        const Piksel &operator[](const Pozicija &pozicija) const;
        friend std::ostream &operator<<(std::ostream &it, const Slika &slika);
    private:
        static const std::size_t BROJ_BITOVA_PO_PIKSELU = 24;
        std::size_t sirina, visina;
        std::vector<std::vector<Piksel>> matrica;
        void pisi(std::ostream &it) const;
};

#endif
