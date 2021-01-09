#ifndef OSOBA_HPP
#define OSOBA_HPP
#include <iostream>
#include "datum.hpp"

class Osoba {
    public:
        Osoba(std::string ime, std::string jmbg, Datum datum) :
            ime(ime), jmbg(jmbg), datum(datum) {}
        Osoba(Osoba &) = delete;
        Osoba &operator=(Osoba &) = delete;
        std::string dohvatiIme() const {
            return ime;
        }
        std::string dohvatiJmbg() const {
            return jmbg;
        }
        Datum dohvatiDatum() const {
            return datum;
        }
        friend std::ostream &operator<<(std::ostream &it, const Osoba &osoba);
    private:
        std::string ime, jmbg;
        Datum datum;
        void pisi(std::ostream &it) const;
};

#endif
