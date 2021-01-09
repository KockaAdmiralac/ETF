#ifndef DATUM_HPP
#define DATUM_HPP
#include <exception>
#include <iostream>

class GNeValjaDatum : public std::exception {
    public:
        const char *what() const noexcept override {
            return "Nije unesen validan datum!";
        }
};

class Datum {
    public:
        Datum(unsigned dan, unsigned mesec, unsigned godina);
        unsigned dohvatiDan() const {
            return dan;
        }
        unsigned dohvatiMesec() const {
            return mesec;
        }
        unsigned dohvatiGodinu() const {
            return godina;
        }
        friend std::size_t operator-(const Datum &d1, const Datum &d2);
        friend std::ostream &operator<<(std::ostream &it, const Datum &datum);
    private:
        static const unsigned DANI[12];
        unsigned dan, mesec, godina;
        std::size_t brojDanaOdRodjenjaHrista() const;
        void pisi(std::ostream &it) const;
};

#endif
