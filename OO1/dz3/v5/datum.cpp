#include "datum.hpp"

const unsigned Datum::DANI[12] = {31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool godinaJePrestupna(std::size_t godina) {
    return (godina % 4 == 0) &&
           (
               godina % 100 != 0 ||
               godina % 400 == 0
           );
}

Datum::Datum(unsigned dan, unsigned mesec, unsigned godina) :
    dan(dan), mesec(mesec), godina(godina) {
    if (mesec == 0 || dan == 0 || mesec > 12) {
        throw GNeValjaDatum();
    }
    bool jePrestupna = godinaJePrestupna(godina);
    unsigned brojDana;
    if (mesec == 2) {
        brojDana = jePrestupna ? 29 : 28;
    } else {
        brojDana = DANI[mesec-1];
    }
    if (dan > brojDana) {
        throw GNeValjaDatum();
    }
}

std::size_t operator-(const Datum &d1, const Datum &d2) {
    std::size_t dani1 = d1.brojDanaOdRodjenjaHrista(),
                dani2 = d2.brojDanaOdRodjenjaHrista();
    if (dani1 > dani2) {
        return dani1 - dani2;
    } else {
        return dani2 - dani1;
    }
}

std::ostream &operator<<(std::ostream &it, const Datum &datum) {
    datum.pisi(it);
    return it;
}

std::size_t Datum::brojDanaOdRodjenjaHrista() const {
    std::size_t brojDanaProslihMeseci = 0;
    for (unsigned i = 1; i < mesec; ++i) {
        if (i == 2) {
            if (godinaJePrestupna(godina)) {
                brojDanaProslihMeseci += 29;
            } else {
                brojDanaProslihMeseci += 28;
            }
        } else {
            brojDanaProslihMeseci += DANI[i-1];
        }
    }
    std::size_t brojDanaProslihGodina = ((godina-1) - (godina-1)/4) * 365 +
                                        (godina-1) / 4 * 366 -
                                        (godina-1) / 100 +
                                        (godina-1) / 400;
    return dan + brojDanaProslihMeseci + brojDanaProslihGodina;
}

void Datum::pisi(std::ostream &it) const {
    it << dan << ". " << mesec << ". " << godina << ".";
}
