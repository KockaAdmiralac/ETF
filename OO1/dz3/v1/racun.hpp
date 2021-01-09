#ifndef RACUN_HPP
#define RACUN_HPP
#include <iostream>
#include "osoba.hpp"

class Racun {
    public:
        Racun(Osoba &vlasnik, int broj) :
            vlasnik(vlasnik), broj(broj) {}
        Racun(Racun &) = delete;
        Racun &operator=(Racun &) = delete;
        const Osoba &dohvatiVlasnika() const {
            return vlasnik;
        }
        int dohvatiBroj() const {
            return broj;
        }
        int dohvatiIznos() const {
            return iznos;
        }
        bool prenesi(Racun &drugi, std::size_t iznos);
        Racun &operator+=(std::size_t iznos);
        virtual const char *dohvatiValutu() const = 0;
        friend std::ostream &operator<<(std::ostream &it, const Racun &racun);
    private:
        Osoba &vlasnik;
        int broj;
        int iznos = 0;
        virtual void pisi(std::ostream &it) const;
};

#endif
