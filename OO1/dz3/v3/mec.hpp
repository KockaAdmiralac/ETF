#ifndef MEC_HPP
#define MEC_HPP
#include <iostream>
#include "tim.hpp"
#include "par.hpp"

class GMecNijeOdigran : public std::exception {
    public:
        const char *what() const noexcept override {
            return "Meč nije odigran!";
        };
};

class Mec {
    enum Ishod {
        POBEDA_DOMACIN,
        NERESENO,
        POBEDA_GOST,
        // KONSULTACIJE: Dozvoljeno da neodigrano stanje čuvamo ovako.
        NEODIGRANO
    };
    public:
        Mec(Tim &tim1, Tim &tim2) :
            timovi(&tim1, &tim2) {}
        void odigraj();
        Par<Tim> dohvatiTimove() const {
            return timovi;
        }
        bool jeOdigran() const {
            return ishod != NEODIGRANO;
        }
        Par<int> poeni() const;
        friend std::ostream &operator<<(std::ostream &it, const Mec &mec);
    private:
        Par<Tim> timovi;
        Ishod ishod = NEODIGRANO;
        void pisi(std::ostream &it) const;
};

#endif
