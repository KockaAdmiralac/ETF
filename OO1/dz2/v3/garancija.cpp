#include "garancija.hpp"

const Kvar &Garancija::poslednjiKvar() const {
    if (brojKvarova() == 0) {
        throw "Nema kvarova.";
    }
    return kvarovi[kvarovi.size()-1];
}

void Garancija::dodajKvar(Kvar &kvar) {
    if (
        kvar.dohvatiDatum() < istek &&
        (
            brojKvarova() == 0 ||
            poslednjiKvar().otklonjenJe()
        )
    ) {
        kvarovi.push_back(kvar);
    } else {
        throw "Ne može se dodati kvar.";
    }
}

std::ostream &operator<<(std::ostream &it, const Garancija &garancija) {
    return it << garancija.pocetak << "-" << garancija.istek
              << " - broj kvarova: " << garancija.brojKvarova();
}
