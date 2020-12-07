#ifndef _korisnik_hpp
#define _korisnik_hpp
#include <iostream>

class Obavestenje;

class Korisnik {
    public:
        Korisnik(std::string &ime) : ime(ime) {}
        Korisnik(Korisnik&) = delete;
        const std::string &dohvatiIme() const {
            return ime;
        }
        friend std::ostream &operator<<(std::ostream &it, const Korisnik &korisnik);
        virtual void posalji(Korisnik &) {}
        virtual void primi(Obavestenje &) {}
    private:
        std::string ime;
        virtual void specificanIspis(std::ostream &) const {}
};

#endif
