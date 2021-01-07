#ifndef _slika_hpp
#define _slika_hpp
#include <iostream>
#include <vector>
#include "piksel.hpp"
#include "pozicija.hpp"
#include "vreme.hpp"

class Slika {
    public:
        Slika(std::size_t sirina, std::size_t visina, const Vreme &vreme) : sirina(sirina), visina(visina),
            matrica(visina, std::vector<Piksel>(sirina)), vreme(vreme) {}
        std::size_t dohvatiSirinu() const {
            return sirina;
        }
        std::size_t dohvatiVisinu() const {
            return visina;
        }
        std::size_t brojBitova() const {
            return sirina * visina * BROJ_BITOVA_PO_PIKSELU;
        }
        const Vreme &dohvatiVreme() const {
            return vreme;
        }
        virtual void postavi(const Piksel &piksel, const Pozicija &pozicija);
        const Piksel &operator[](const Pozicija &pozicija) const;
        friend std::ostream &operator<<(std::ostream &it, const Slika &slika);
    protected:
        std::size_t sirina, visina;
        std::vector<std::vector<Piksel>> matrica;
        Vreme vreme;
        void pisi(std::ostream &it) const;
    private:
        static const std::size_t BROJ_BITOVA_PO_PIKSELU = 24;
};

#endif
