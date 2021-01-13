#ifndef DESTINACIJA_HPP
#define DESTINACIJA_HPP
#include <iostream>

class Destinacija {
    public:
        Destinacija(std::string naziv, std::string opis) :
            naziv(naziv), opis(opis) {}
        void oceni(unsigned ocena);
        std::string dohvatiNaziv() const {
            return naziv;
        }
        std::string dohvatiOpis() const {
            return opis;
        }
        double dohvatiProsecnuOcenu() const {
            return prosecnaOcena;
        }
        friend bool operator>(const Destinacija &dest1, const Destinacija &dest2);
        friend std::ostream &operator<<(std::ostream &it, const Destinacija &dest);
    private:
        std::string naziv, opis;
        double prosecnaOcena = 0;
        unsigned brojOcena = 0;
        void pisi(std::ostream &it) const;
};

#endif
