#ifndef _garancija_hpp
#define _garancija_hpp
#include <iostream>
#include <vector>
#include "kvar.hpp"

class Garancija {
    public:
        // Prenos po vrednosti kako ne bismo morali da pravimo četiri
        // varijante konstruktora
        Garancija(Datum pocetak, Datum istek) :
            pocetak(pocetak), istek(istek) {}
        void dodajKvar(Kvar &kvar);
        const Kvar &poslednjiKvar() const;
        std::size_t brojKvarova() const {
            return kvarovi.size();
        }
        friend std::ostream &operator<<(std::ostream &it, const Garancija &garancija);
    private:
        Datum pocetak, istek;
        std::vector<Kvar> kvarovi;
        void pisi(std::ostream &it) const;
};

#endif
