#ifndef IGRAC_HPP
#define IGRAC_HPP
#include <iostream>

class Igrac {
    public:
        Igrac(std::string ime, int vrednost=1000) :
            ime(ime), vrednost(vrednost) {}
        std::string dohvatiIme() const {
            return ime;
        }
        int dohvatiVrednost() const {
            return vrednost;
        }
        void promeniVrednost(double procenat) {
            vrednost += vrednost * procenat / 100;
        }
        friend bool operator==(const Igrac &igr1, const Igrac &igr2);
        friend std::ostream &operator<<(std::ostream &it, const Igrac &igr);
    private:
        std::string ime;
        int vrednost;
        void pisi(std::ostream &it) const;
};

#endif
