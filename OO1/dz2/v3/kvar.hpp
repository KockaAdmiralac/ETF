#ifndef _kvar_hpp
#define _kvar_hpp
#include <iostream>
#include "datum.hpp"

class Kvar {
    public:
        Kvar(std::string &opis, Datum &datum) :
            opis(opis), datum(datum), otklonjen(false) {}
        Kvar(std::string &&opis, Datum &&datum) :
            opis(opis), datum(datum), otklonjen(false) {}
        const std::string &dohvatiOpis() const {
            return opis;
        }
        const Datum &dohvatiDatum() const {
            return datum;
        }
        void postaviOtklonjen(bool jeste) {
            otklonjen = jeste;
        }
        bool otklonjenJe() const {
            return otklonjen;
        }
        friend std::ostream &operator<<(std::ostream &it, const Kvar &kvar);
    private:
        std::string opis;
        Datum datum;
        bool otklonjen;
        void pisi(std::ostream &it) const;
};

#endif
