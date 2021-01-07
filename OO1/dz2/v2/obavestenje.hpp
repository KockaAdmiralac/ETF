#ifndef _obavestenje_hpp
#define _obavestenje_hpp
#include <ctime>
#include <iostream>
#include "korisnik.hpp"

class Obavestenje {
    public:
        Obavestenje(Korisnik &korisnik) :
            id(statickiId++), vreme(time(nullptr)),
            procitano(false), korisnik(&korisnik) {}
        Obavestenje(const Obavestenje &obavestenje);
        // Ovo se vraća na podrazumevani jer ID pri premeštanju ostaje isti -
        // - stari objekat postaje nevalidan pa tehnički ne postoje dva validna
        // objekta sa istim ID-em. Pošto identitet objekta ostaje isti, nema
        // potrebe za generisanjem novog ID-a.
        Obavestenje(Obavestenje &&obavestenje) = default;
        Obavestenje &operator=(const Obavestenje &obavestenje);
        // Isto kao za premeštajući konstruktor
        Obavestenje &operator=(Obavestenje &&) = default;
        int identifikator() const {
            return id;
        }
        const Korisnik &dohvatiKorisnika() const {
            return *korisnik;
        }
        bool daLiJeProcitano() const {
            return procitano;
        }
        void procitaj();
        friend std::ostream &operator<<(std::ostream &it, const Obavestenje &obavestenje);
    protected:
        virtual void pisi(std::ostream &it) const;
    private:
        static int statickiId;
        int id;
        time_t vreme;
        bool procitano;
        Korisnik *korisnik;
};

#endif
