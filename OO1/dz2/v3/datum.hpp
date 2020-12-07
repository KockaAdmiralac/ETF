#ifndef _datum_hpp
#define _datum_hpp
#include <iostream>

class Datum {
    public:
        Datum(int dan=30, int mesec=11, int godina=2019) :
            dan(dan), mesec(mesec), godina(godina) {}
        int operator[](std::string tip) const;
        bool operator<(Datum &datum2) const;
        friend std::ostream &operator<<(std::ostream &it, const Datum &datum);
    private:
        int dan, mesec, godina;
};

#endif
