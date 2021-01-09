#ifndef DINARSKI_HPP
#define DINARSKI_HPP
#include <iostream>
#include "racun.hpp"

class DinarskiRacun : public Racun {
    public:
        using Racun::Racun;
        const char *dohvatiValutu() const override {
            return "RSD";
        }
};

#endif
