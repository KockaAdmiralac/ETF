#ifndef _sarena_hpp
#define _sarena_hpp
#include <ctime>
#include <exception>
#include <iostream>
#include "slika.hpp"

class slike_nisu_istih_dimenzija : public std::exception {
    const char *what() const noexcept override {
        return "Slike nisu istih dimenzija.";
    }
};

class SarenaSlika : public Slika {
    public:
        SarenaSlika(std::size_t sirina, std::size_t visina, const Vreme &vreme);
        SarenaSlika(Slika &slika1, Slika &slika2);
        void postavi(const Piksel &piksel, const Pozicija &pozicija) override;
    private:
        bool uporediSaOkolinom(const Pozicija &pozicija, const Piksel &piksel) const;
};

#endif
