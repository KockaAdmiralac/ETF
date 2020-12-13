#ifndef _uredjaj_hpp
#define _uredjaj_hpp
#include <iostream>
#include "garancija.hpp"

class Uredjaj {
    public:
        Uredjaj(std::string &proizvodjac) :
            id(jedinstveniId++), proizvodjac(proizvodjac),
            garancija(nullptr) {}
        Uredjaj(std::string &&proizvodjac) :
            id(jedinstveniId++), proizvodjac(proizvodjac),
            garancija(nullptr) {}
        Uredjaj(Uredjaj &) = delete;
        Uredjaj &operator=(const Uredjaj &) = delete;
        const Garancija *dohvatiGaranciju() const {
            return garancija;
        }
        virtual void postaviGaranciju(Datum &pocetak) = 0;
        virtual int brojKvarovaZaIzdavanjeNovog() const = 0;
        bool operator==(const Uredjaj &b) const {
            return proizvodjac == b.proizvodjac;
        }
        friend std::ostream &operator<<(std::ostream &it, const Uredjaj &uredjaj);
        virtual ~Uredjaj() {
            delete garancija;
        }
    protected:
        static int jedinstveniId;
        int id;
        std::string proizvodjac;
        Garancija *garancija;
        virtual void pisi(std::ostream &it) const;
};

#endif
