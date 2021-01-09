#include "datum.hpp"

bool operator==(const Datum &d1, const Datum &d2) {
    return d1.dan == d2.dan &&
           d1.mesec == d2.mesec &&
           d1.godina == d2.godina;
}

std::ostream &operator<<(std::ostream &it, const Datum &datum) {
    datum.pisi(it);
    return it;
}

void Datum::pisi(std::ostream &it) const {
    it << dan << ". " << mesec << ". " << godina << ".";
}
