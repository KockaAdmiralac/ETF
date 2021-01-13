#ifndef ARANZMAN_HPP
#define ARANZMAN_HPP
#include <exception>
#include <iostream>
#include "destinacija.hpp"
#include "smestaj.hpp"
#include "prevoz.hpp"
#include "datum.hpp"

class GNijeVezanZaDestinaciju : public std::exception {
    public:
        const char *what() const noexcept override {
            return "Smeštaj ili prevoz nije vezan za destinaciju!";
        }
};

class GNisuDodeljeniSmestajIliPrevoz : public std::exception {
    public:
        const char *what() const noexcept override {
            return "Nisu dodeljeni smeštaj ili prevoz!";
        }
};

class Aranzman {
    public:
        Aranzman(Destinacija &destinacija, Datum pocetak, Datum kraj) :
            destinacija(destinacija), pocetak(pocetak), kraj(kraj) {}
        void dodeliSmestaj(Smestaj &smestaj);
        void dodeliPrevoz(Prevoz &prevoz);
        const Destinacija &dohvatiDestinaciju() const {
            return destinacija;
        }
        Datum dohvatiPocetak() const {
            return pocetak;
        }
        Datum dohvatiKraj() const {
            return kraj;
        }
        std::size_t dohvatiTrajanje() const {
            return kraj - pocetak;
        }
        double dohvatiCenu() const;
        friend std::ostream &operator<<(std::ostream &it, const Aranzman &aranz);
    private:
        // MEJL@Marko: Radi poređenja na jednakost, možemo porediti adrese
        // destinacija i pretpostaviti da postoji samo jedna destinacija u
        // memoriji.
        Destinacija &destinacija;
        Datum pocetak, kraj;
        // MEJL@Marko: Aranžman nije vlasnik smeštaja i prevoza.
        Smestaj *smestaj = nullptr;
        Prevoz *prevoz = nullptr;
        void pisi(std::ostream &it) const;
};

#endif
