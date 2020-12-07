#ifndef _uredjaj_hpp
#define _uredjaj_hpp
#include <iostream>
#include "garancija.hpp"

class Uredjaj {
    public:
        Uredjaj(std::string proizvodjac) :
            id(jedinstveniId++), proizvodjac(proizvodjac),
            garancija(nullptr) {}
        Uredjaj(Uredjaj &) = delete;
        Uredjaj(Uredjaj &&) = delete;
        const Garancija *dohvatiGaranciju() const {
            return garancija;
        }
        virtual void postaviGaranciju(Datum) {
            throw "Metoda nije implementirana.";
        }
        virtual int brojKvarovaZaIzdavanjeNovog() const {
            throw "Metoda nije implementirana.";
        }
        bool operator==(const Uredjaj &b) const {
            return proizvodjac == b.proizvodjac;
        }
        friend std::ostream &operator<<(std::ostream &it, const Uredjaj &uredjaj);
    protected:
        static int jedinstveniId;
        int id;
        std::string proizvodjac;
        Garancija *garancija;
};

#endif
