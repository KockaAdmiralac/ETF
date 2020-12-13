#include "datum.hpp"

int Datum::operator[](std::string tip) const {
    if (tip == "dan") {
        return dan;
    } else if (tip == "mesec") {
        return mesec;
    } else if (tip == "godina") {
        return godina;
    }
    return -1;
}

bool Datum::operator<(Datum &datum2) const {
    return godina < datum2.godina ||
           (
               godina == datum2.godina &&
               mesec < datum2.mesec
           ) ||
           (
               godina == datum2.godina &&
               mesec == datum2.mesec &&
               dan < datum2.dan
           );
}

void Datum::pisi(std::ostream &it) const {
    it << dan << "." << mesec << "." << godina << ".";
}

std::ostream &operator<<(std::ostream &it, const Datum &datum) {
    datum.pisi(it);
    return it;
}
