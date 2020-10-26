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
            naziv(naziv), maksimalanBrojPutnika(maksimalanBrojPutnika),
            kapetan(nullptr), kopilot(nullptr) {}
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
        Flota(std::string naziv) : naziv(naziv), prvi(nullptr),
            poslednji(nullptr), brojAvionaFlote(0) {}
        ~Flota() {
            brisi();
        }
        int brojAviona() const;
        int maksimalanBrojPutnika() const;
        Avion &avionSaMaksimalnimBrojemPutnika() const;
        void pisi() const;
        void dodajAvion(Avion &avion);
    private:
        struct AvionFlote {
            Avion &avion;
            AvionFlote *sledeci;
            AvionFlote(Avion &avion) : avion(avion), sledeci(nullptr) {}
        };
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
    flota.pisi();
    std::cout << std::endl << "Avion sa maksimalnim brojem putnika: ";
    flota.avionSaMaksimalnimBrojemPutnika().pisi();
    std::cout << std::endl;
    return 0;
}
