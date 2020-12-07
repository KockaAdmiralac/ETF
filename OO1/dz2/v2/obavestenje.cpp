#include "obavestenje.hpp"

int Obavestenje::statickiId = 0;

void Obavestenje::procitaj() {
    procitano = true;
}

std::ostream &operator<<(std::ostream &it, const Obavestenje &obavestenje) {
    std::tm *vreme = std::localtime(&obavestenje.vreme);
    it << obavestenje.id << "|" << obavestenje.korisnik.dohvatiIme() << "-"
       << vreme->tm_hour << ":" << vreme->tm_min << ":" << vreme->tm_sec
       << std::endl;
    obavestenje.specificanIspis(it);
    return it;
}
