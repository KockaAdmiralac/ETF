#ifndef SASTOJAK_HPP
#define SASTOJAK_HPP
#include <iostream>
#include "namirnica.hpp"

class Sastojak {
    public:
        Sastojak(Namirnica namirnica, double kolicina) :
            namirnica(namirnica), kolicina(kolicina) {}
        Namirnica dohvatiNamirnicu() const {
            return namirnica;
        }
        double dohvatiKolicinu() const {
            return kolicina;
        }
        NutritivnaVrednost nutritivnaVrednost() const;
        double brojKalorija() const;
        friend std::ostream &operator<<(std::ostream &it, const Sastojak &sastojak);
    private:
        Namirnica namirnica;
        double kolicina;
        void pisi(std::ostream &it) const;
};

#endif
