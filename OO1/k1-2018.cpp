#include <iostream>
#include <string>

using namespace std;

class Artikal {
    const string naziv;
    const double cena;
    const int popust;
    public:
        Artikal(string nazivArtikla, double cenaArtikla, int popustArtikla=0) :
            naziv(nazivArtikla), cena(cenaArtikla), popust(popustArtikla) {}
        string getNaziv() const {
            return naziv;
        }
        double getCenaSaPopustom() const {
            return cena * (100 - popust) / 100;
        }
        int getPopust() const {
            return popust;
        }
};

ostream &operator<<(ostream &out, const Artikal &a) {
    return out << a.getNaziv() << '(' << a.getCenaSaPopustom() << ')';
}

class Stavka {
    const Artikal artikal;
    const int kolicina;
    int redniBroj;
    friend ostream &operator<<(ostream &out, const Stavka &s);
    public:
        Stavka(Artikal artikalStavke, int kolicinaStavke) :
            artikal(artikalStavke), kolicina(kolicinaStavke) {};
        void dodajNaRacun(int broj) {
            redniBroj = broj;
        }
        double iznos() const {
            return artikal.getCenaSaPopustom() * kolicina;
        }
        const Artikal &getArtikal() const {
            return artikal;
        }
};

ostream &operator<<(ostream &out, const Stavka &s) {
    return out << 'S' << s.redniBroj << '(' << s.artikal << "):" << s.kolicina << '|' << s.iznos();
}

class Racun {
    struct Elem {
        Stavka stavka;
        Elem *next;
        Elem(Stavka s) : stavka(s), next(nullptr) {}
    };
    Elem *prvaStavka = nullptr, *poslednjaStavka = nullptr;
    int brojStavki = 0, dodatniPopust = 0;
    friend ostream &operator<<(ostream &out, const Racun &r);
    public:
        Racun &dodajStavku(Stavka s);
        double iznos() const;
        void postaviPopust(int dp) {
            dodatniPopust = dp;
        }
};

Racun &Racun::dodajStavku(Stavka s) {
    Elem *e = new Elem(s);
    ++brojStavki;
    s.dodajNaRacun(brojStavki);
    if (prvaStavka == nullptr) {
        prvaStavka = poslednjaStavka = e;
    } else {
        poslednjaStavka->next = e;
    }
    poslednjaStavka = e;
    return *this;
}

double Racun::iznos() const {
    double ret = 0;
    Elem *p = prvaStavka;
    while (p != nullptr) {
        if (p->stavka.getArtikal().getPopust() == 0) {
            ret += p->stavka.iznos() * (100 - dodatniPopust) / 100;
        } else {
            ret += p->stavka.iznos();
        }
        p = p->next;
    }
    return ret;
}

ostream &operator<<(ostream &out, const Racun &r) {
    out << "Racun:" << r.iznos() << endl;
    for (auto elem = r.prvaStavka; elem != nullptr; elem = elem->next) {
        out << elem->stavka << '[' << (elem->stavka.iznos() * (100 - r.dodatniPopust) / 100) << ']' << endl;
    }
    return out;
}

int main() {
    Artikal a1("Mleko", 100), a2("Hleb", 50), a3("Sir", 200, 20);
    Stavka s1(a1, 2), s2(a2, 3), s3(a3, 1);
    Racun r;
    r.dodajStavku(s1).dodajStavku(s2).dodajStavku(s3);
    Racun novi = r;
    novi.postaviPopust(20);
    cout << r;
    cout << novi;
} 
