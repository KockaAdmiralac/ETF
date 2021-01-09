#ifndef SMESTAJ_HPP
#define SMESTAJ_HPP
#include <exception>
#include <iostream>
#include "destinacija.hpp"

class GPogresanBrojZvezdica : public std::exception {
    public:
        const char *what() const noexcept override {
            return "Pogrešan broj zvezdica!";
        }
};

class Smestaj {
    public:
        enum Tip {HOTEL, APARTMAN};
        Smestaj(Destinacija &destinacija, Tip tip, std::string naziv, unsigned brojZvezdica, double cenaPoDanu);
        const Destinacija &dohvatiDestinaciju() const {
            return destinacija;
        }
        Tip dohvatiTip() const {
            return tip;
        }
        std::string dohvatiNaziv() const {
            return naziv;
        }
        int dohvatiBrojZvezdica() const {
            return brojZvezdica;
        }
        double dohvatiCenuPoDanu() const {
            return cenaPoDanu;
        }
        friend std::ostream &operator<<(std::ostream &it, const Smestaj &smestaj);
    private:
        // PRETPOSTAVKA: Videti u Aranžman.
        Destinacija &destinacija;
        Tip tip;
        std::string naziv;
        unsigned brojZvezdica;
        double cenaPoDanu;
        void pisi(std::ostream &it) const;
};

#endif
