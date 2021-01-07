#include "obavestenje.hpp"

int Obavestenje::statickiId = 0;

Obavestenje::Obavestenje(const Obavestenje &obavestenje) : id(statickiId++),
    vreme(obavestenje.vreme), procitano(obavestenje.procitano),
    korisnik(obavestenje.korisnik) {}

Obavestenje &Obavestenje::operator=(const Obavestenje &obavestenje) {
    korisnik = obavestenje.korisnik;
    id = statickiId++;
    vreme = obavestenje.vreme;
    procitano = obavestenje.procitano;
    return *this;
}

void Obavestenje::procitaj() {
    procitano = true;
}

void Obavestenje::pisi(std::ostream &it) const {
    std::tm *tren = std::localtime(&vreme);
    it << id << "|" << korisnik->dohvatiIme() << "-"
       << tren->tm_hour << ":" << tren->tm_min << ":" << tren->tm_sec
       << std::endl;
}

std::ostream &operator<<(std::ostream &it, const Obavestenje &obavestenje) {
    obavestenje.pisi(it);
    return it;
}
