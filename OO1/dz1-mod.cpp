#include <iostream>
#include <string>

class Pilot {
    public:
        Pilot(std::string ime, int brojSatiLetenja, bool letiLi = false) :
            ime(ime), brojSatiLetenja(brojSatiLetenja), letiLi(letiLi) {}
        Pilot(const Pilot&) = delete;
        const std::string &dohvatiIme() const {
            return ime;
        }
        int dohvatiBrojSatiLetenja() const {
            return brojSatiLetenja;
        }
        bool daLiLeti() const {
            return letiLi;
        }
        void povecajBrojSatiLetenja(int kolicina);
        void postaviDaLiLeti(bool letiLi);
        void pisi() const;
    private:
        std::string ime;
        int brojSatiLetenja;
        bool letiLi;
};

void Pilot::povecajBrojSatiLetenja(int kolicina) {
    brojSatiLetenja += kolicina;
}

void Pilot::postaviDaLiLeti(bool letiLi) {
    this->letiLi = letiLi;
}

void Pilot::pisi() const {
    std::cout << ime << " (" << brojSatiLetenja << ") - "
              << (letiLi ? 'L' : 'N');
}

class Avion {
    public:
        Avion(std::string naziv, int maksimalanBrojPutnika) :
            naziv(naziv), kapetan(nullptr), kopilot(nullptr),
            maksimalanBrojPutnika(maksimalanBrojPutnika) {}
        Avion(const Avion&) = delete;
        const std::string &dohvatiNaziv() const {
            return naziv;
        }
        Pilot *dohvatiKapetana() const {
            return kapetan;
        }
        Pilot *dohvatiKopilota() const {
            return kopilot;
        }
        int dovhatiMaksimalanBrojPutnika() const {
            return maksimalanBrojPutnika;
        }
        void postaviKapetana(Pilot *kapetan);
        void postaviKopilota(Pilot *kopilot);
        void pisi() const;
    private:
        std::string naziv;
        Pilot *kapetan, *kopilot;
        int maksimalanBrojPutnika;
};

void Avion::postaviKapetana(Pilot *kapetan) {
    if (kapetan == nullptr || kapetan->dohvatiBrojSatiLetenja() <= 100) {
        throw "Kapetan mora imati barem 100 sati letenja.";
    }
    this->kapetan = kapetan;
    kapetan->postaviDaLiLeti(true);
}

void Avion::postaviKopilota(Pilot *kopilot) {
    if (kopilot == nullptr) {
        throw "Nije dozvoljeno postavljanje nepostojećeg kopilota.";
    }
    this->kopilot = kopilot;
    kopilot->postaviDaLiLeti(true);
}

void Avion::pisi() const {
    std::cout << "AVION: " << naziv << " - " << maksimalanBrojPutnika;
}

class Flota {
    public:
        struct AvionFlote {
            Avion &avion;
            AvionFlote *sledeci;
            AvionFlote(Avion &avion) : avion(avion), sledeci(nullptr) {}
        };
        Flota(std::string naziv) : naziv(naziv), prvi(nullptr),
            poslednji(nullptr), brojAvionaFlote(0) {}
        ~Flota() {
            brisi();
        }
        int brojAviona() const;
        int maksimalanBrojPutnika() const;
        Avion &avionSaMaksimalnimBrojemPutnika() const;
        AvionFlote *avioniSaBrojemPutnika(int min, int max) const;
        void pisi() const;
        void dodajAvion(Avion &avion);
        void izbaciAvion(const std::string &naziv);
    private:
        std::string naziv;
        AvionFlote *prvi, *poslednji;
        int brojAvionaFlote;
        void brisi();
};

int Flota::brojAviona() const {
    return brojAvionaFlote;
}

int Flota::maksimalanBrojPutnika() const {
    int zbir = 0;
    for (AvionFlote *af = prvi; af != nullptr; af = af->sledeci) {
        zbir += af->avion.dovhatiMaksimalanBrojPutnika();
    }
    return zbir;
}

Avion &Flota::avionSaMaksimalnimBrojemPutnika() const {
    if (prvi == nullptr) {
        throw "Ne postoji nijedan avion u floti.";
    }
    AvionFlote *maksAvion = prvi;
    for (AvionFlote *af = prvi->sledeci; af != nullptr; af = af->sledeci) {
        if (af->avion.dovhatiMaksimalanBrojPutnika() > maksAvion->avion.dovhatiMaksimalanBrojPutnika()) {
            maksAvion = af;
        }
    }
    return maksAvion->avion;
}

Flota::AvionFlote *Flota::avioniSaBrojemPutnika(int min, int max) const {
    AvionFlote *prvi = nullptr, *poslednji = nullptr;
    for (AvionFlote *af = this->prvi; af != nullptr; af = af->sledeci) {
        if (af->avion.dovhatiMaksimalanBrojPutnika() >= min && af->avion.dovhatiMaksimalanBrojPutnika() <= max) {
            AvionFlote *lista = new AvionFlote(af->avion);
            if (prvi == nullptr) {
                prvi = lista;
                poslednji = lista;
            } else {
                poslednji->sledeci = lista;
                poslednji = lista;
            }
        }
    }
    return prvi;
}

void Flota::pisi() const {
    std::cout << naziv;
    for (AvionFlote *af = prvi; af != nullptr; af = af->sledeci) {
        std::cout << std::endl;
        af->avion.pisi();
    }
}

void Flota::dodajAvion(Avion &avion) {
    AvionFlote *noviAvion = new AvionFlote(avion);
    if (prvi == nullptr) {
        prvi = noviAvion;
        poslednji = noviAvion;
    } else {
        poslednji->sledeci = noviAvion;
        poslednji = noviAvion;
    }
}

void Flota::brisi() {
    AvionFlote *prev = prvi;
    for (AvionFlote *af = prvi->sledeci; af != nullptr; af = af->sledeci) {
        delete prev;
        prev = af;
    }
    delete prev;
}

void Flota::izbaciAvion(const std::string &naziv) {
    AvionFlote *prev = nullptr;
    for (AvionFlote *af = prvi; af != nullptr; af = af->sledeci) {
        if (naziv == af->avion.dohvatiNaziv()) {
            if (prev == nullptr) {
               prvi = af->sledeci;
            } else {
                prev->sledeci = af->sledeci;
            }
            if (af->sledeci == nullptr) {
                poslednji = prev;
            }
            delete af;
            return;
        }
        prev = af;
    }
    throw "Ne postoji avion sa zadatim nazivom.";
}

class Let {
    public:
        Let(std::string polaziste, std::string dolaziste, Avion &avion) :
            polaziste(polaziste), dolaziste(dolaziste), id(globalId++), avion(avion) {}
        int dohvatiId() const {
            return id;
        }
        const std::string &dohvatiPolaziste() {
            return polaziste;
        }
        const std::string &dohvatiDolaziste() {
            return dolaziste;
        }
        Avion &dohvatiAvion() {
            return avion;
        }
        void pisi() const;
    private:
        static int globalId;
        std::string polaziste, dolaziste;
        int id;
        Avion &avion;
};

int Let::globalId = 0;

void Let::pisi() const {
    std::cout << "LET - " << polaziste << " : " << dolaziste << " - ";
    avion.pisi();
}

class Arhiva {
    public:
        struct LetArhive {
            Let &let;
            LetArhive *sledeci;
            LetArhive(Let &let) : let(let), sledeci(nullptr) {}
        };
        Arhiva() : prvi(nullptr), poslednji(nullptr) {}
        ~Arhiva() {
            brisi();
        }
        void dodajLet(Let &let);
        LetArhive *dohvatiLetoveSaDolazistem(std::string &dolaziste) const;
        LetArhive *dohvatiLetoveSaPolazistem(std::string &polaziste) const;
        LetArhive *dohvatiLetoveSaPolazistemIDolazistem(std::string &polaziste, std::string &dolaziste) const;
        void pisi() const;
    private:
        LetArhive *prvi, *poslednji;
        void brisi();
};

void Arhiva::dodajLet(Let &let) {
    LetArhive *la = new LetArhive(let);
    if (prvi == nullptr) {
        prvi = la;
        poslednji = la;
    } else {
        poslednji->sledeci = la;
        poslednji = la;
    }
}

Arhiva::LetArhive *Arhiva::dohvatiLetoveSaDolazistem(std::string &dolaziste) const {
    LetArhive *prvi = nullptr, *poslednji = nullptr;
    for (LetArhive *la = this->prvi; la != nullptr; la = la->sledeci) {
        if (la->let.dohvatiDolaziste() == dolaziste) {
            LetArhive *lista = new LetArhive(la->let);
            if (prvi == nullptr) {
                prvi = lista;
                poslednji = lista;
            } else {
                poslednji->sledeci = lista;
                poslednji = lista;
            }
        }
    }
    return prvi;
}

Arhiva::LetArhive *Arhiva::dohvatiLetoveSaPolazistem(std::string &polaziste) const {
    LetArhive *prvi = nullptr, *poslednji = nullptr;
    for (LetArhive *la = this->prvi; la != nullptr; la = la->sledeci) {
        if (la->let.dohvatiPolaziste() == polaziste) {
            LetArhive *lista = new LetArhive(la->let);
            if (prvi == nullptr) {
                prvi = lista;
                poslednji = lista;
            } else {
                poslednji->sledeci = lista;
                poslednji = lista;
            }
        }
    }
    return prvi;
}

Arhiva::LetArhive *Arhiva::dohvatiLetoveSaPolazistemIDolazistem(std::string &polaziste, std::string &dolaziste) const {
    LetArhive *prvi = nullptr, *poslednji = nullptr;
    for (LetArhive *la = this->prvi; la != nullptr; la = la->sledeci) {
        if (la->let.dohvatiPolaziste() == polaziste && la->let.dohvatiDolaziste() == dolaziste) {
            LetArhive *lista = new LetArhive(la->let);
            if (prvi == nullptr) {
                prvi = lista;
                poslednji = lista;
            } else {
                poslednji->sledeci = lista;
                poslednji = lista;
            }
        }
    }
    return prvi;
}

void Arhiva::pisi() const {
    std::cout << "ARHIVA";
    for (LetArhive *la = prvi; la != nullptr; la = la->sledeci) {
        std::cout << std::endl;
        la->let.pisi();
    }
}

void Arhiva::brisi() {
    LetArhive *prev = prvi;
    for (LetArhive *la = prvi->sledeci; la != nullptr; la = la->sledeci) {
        delete prev;
        prev = la;
    }
    delete prev;
}

int main() {
    Pilot mika("Mika Mikić", 0);
    Pilot pera("Pera Perić", 101, false);
    Avion av1("SI Airways 404", 1);
    Avion av2("SI Airways 505", 100);
    Flota flota("SI Airways");
    av1.postaviKapetana(&pera);
    av1.postaviKopilota(&mika);
    av2.postaviKapetana(&pera);
    av2.postaviKopilota(&mika);
    flota.dodajAvion(av1);
    flota.dodajAvion(av2);
    std::string nazivZaIzbacivanje = "SI Airways 505";
    flota.izbaciAvion(nazivZaIzbacivanje);
    flota.pisi();
    std::cout << std::endl << "Avion sa maksimalnim brojem putnika: ";
    flota.avionSaMaksimalnimBrojemPutnika().pisi();
    std::cout << std::endl;

    // Modifikacija
    Let let1("Pol1", "Dol1", av1);
    Let let2("Pol1", "Dol2", av2);
    Let let3("Pol2", "Dol2", av1);
    Arhiva arhiva;
    arhiva.dodajLet(let1);
    arhiva.dodajLet(let2);
    arhiva.dodajLet(let3);
    arhiva.pisi();
    std::cout << std::endl << "Dohvatanje sa dolazištem:" << std::endl;
    Arhiva::LetArhive *prev = nullptr;
    std::string dolaziste = "Dol2";
    for (Arhiva::LetArhive *lista = arhiva.dohvatiLetoveSaDolazistem(dolaziste); lista != nullptr; lista = lista->sledeci) {
        delete prev;
        lista->let.pisi();
        std::cout << std::endl;
        prev = lista;
    }
    delete prev;
    return 0;
}
