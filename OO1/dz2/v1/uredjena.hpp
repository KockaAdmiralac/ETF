#ifndef _uredjena_hpp
#define _uredjena_hpp
#include <algorithm>
#include "galerija.hpp"

class UredjenaGalerija : public Galerija {
    public:
        using Galerija::Galerija;
        Galerija &operator+=(const Slika &slika) override {
            Galerija::operator+=(slika);
            std::sort(slike.begin(), slike.end(), UredjenaGalerija::uredi);
            return *this;
        }
    private:
        static bool uredi(const Slika *slika1, const Slika *slika2) {
            return slika1->dohvatiVreme() < slika2->dohvatiVreme();
        }
};

#endif
