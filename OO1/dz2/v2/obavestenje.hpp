#ifndef _obavestenje_hpp
#define _obavestenje_hpp
#include <ctime>
#include <iostream>
#include "korisnik.hpp"

class Obavestenje {
    public:
        Obavestenje(Korisnik &korisnik) :
            id(statickiId++), vreme(time(nullptr)),
            procitano(false), korisnik(korisnik) {}
        int identifikator() const {
            return id;
        }
        const Korisnik &dohvatiKorisnika() const {
            return korisnik;
        }
        bool daLiJeProcitano() const {
            return procitano;
        }
        void procitaj();
        friend std::ostream &operator<<(std::ostream &it, const Obavestenje &obavestenje);
    private:
        static int statickiId;
        int id;
        time_t vreme;
        bool procitano;
        Korisnik &korisnik;
        virtual void specificanIspis(std::ostream &) const {}
};

#endif
