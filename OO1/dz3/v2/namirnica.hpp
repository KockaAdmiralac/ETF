#ifndef NAMIRNICA_HPP
#define NAMIRNICA_HPP
#include <iostream>
#include "nut.hpp"

class Namirnica {
    public:
        Namirnica(std::string naziv, NutritivnaVrednost nut, bool posna) :
            naziv(naziv), nut(nut), posna(posna) {}
        std::string dohvatiNaziv() const {
            return naziv;
        }
        NutritivnaVrednost dohvatiNutritivnuVrednost() const {
            return nut;
        }
        bool jePosna() const {
            return posna;
        }
        friend bool operator==(const Namirnica &n1, const Namirnica &n2);
        friend std::ostream &operator<<(std::ostream &it, const Namirnica &namirnica);
    private:
        std::string naziv;
        NutritivnaVrednost nut;
        bool posna;
        void pisi(std::ostream &it) const;
};

#endif
