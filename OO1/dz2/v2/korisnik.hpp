#ifndef _korisnik_hpp
#define _korisnik_hpp
#include <iostream>

class Obavestenje;

class Korisnik {
    public:
        Korisnik(std::string &ime) : ime(ime) {}
        Korisnik(std::string &&ime) : ime(ime) {}
        Korisnik(Korisnik &) = delete;
        Korisnik &operator=(Korisnik &) = delete;
        const std::string &dohvatiIme() const {
            return ime;
        }
        // Nisu čiste virtuelne funkcije kako bi bilo moguće testiranje
        // kroz glavni program.
        virtual void posalji(Korisnik &) {};
        virtual void primi(Obavestenje &) {};
        friend std::ostream &operator<<(std::ostream &it, const Korisnik &korisnik);
    private:
        std::string ime;
        virtual void pisi(std::ostream &it) const;
};

#endif
