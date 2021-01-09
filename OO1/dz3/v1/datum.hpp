#ifndef DATUM_HPP
#define DATUM_HPP
#include <iostream>

class Datum {
    public:
        Datum(unsigned dan=1, unsigned mesec=1, unsigned godina=2021) :
            dan(dan), mesec(mesec), godina(godina) {}
        friend bool operator==(const Datum &d1, const Datum &d2);
        friend std::ostream &operator<<(std::ostream &it, const Datum &datum);
    private:
        int dan, mesec, godina;
        void pisi(std::ostream &it) const;
};

#endif
