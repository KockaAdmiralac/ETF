#include <iostream>
#include <string>

using namespace std;

class Par {
    int sifra;
    string opis;
    double kvote[3];
    int ishod = NEODREDJEN;
    public:
        static const int NEODREDJEN = -1;
        static const int JEDAN = 0;
        static const int IKS = 1;
        static const int DVA = 2;
        static int sifraS;
        friend ostream &operator<<(ostream &out, Par &par);
        Par(const char *op, double kv[3]) : opis(op), sifra(sifraS++) {
            kvote[0] = kv[0];
            kvote[1] = kv[1];
            kvote[2] = kv[2];
        }
        Par(const Par &) = delete;
        double operator[](int ishod) const {
            return kvote[ishod];
        }
        void operator()(int stvarniIshod) {
            ishod = stvarniIshod;
        }
        int operator()() const {
            return ishod;
        }
};

ostream &operator<<(ostream &out, Par &par) {
    out << par.sifra << " - " << par.opis << " (";
    if (par() == Par::JEDAN) {
        out << "T";
    }
    out << par[Par::JEDAN] << ", ";
    if (par() == Par::IKS) {
        out << "T";
    }
    out << par[Par::IKS] << ", ";
    if (par() == Par::DVA) {
        out << "T";
    }
    out << par[Par::DVA] << ")";
    return out;
}

class Tiket {
    protected:
        struct Elem {
            Par &par;
            int zeljeniIshod;
            Elem *next;
            Elem(Par &p, int zi) : par(p), zeljeniIshod(zi), next(nullptr) {}
        };
        int uplata;
        Elem *prviPar = nullptr, *poslednjiPar = nullptr;
        friend ostream &operator<<(ostream &out, Tiket &tiket);
    public:
        Tiket(int u) : uplata(u) {}
        Tiket(Tiket &stari);
        ~Tiket();
        Tiket &dodajPar(Par &par, int zeljeniIshod);
        double operator*();
        bool operator~();
        int getUplata() const {
            return uplata;
        }
};

Tiket::Tiket(Tiket &stari) {
    uplata = stari.uplata;
    prviPar = nullptr;
    poslednjiPar = nullptr;
    for (Elem *e = stari.prviPar; e != nullptr; e = e->next) {
        Elem *newE = new Elem(e->par, e->zeljeniIshod);
        if (prviPar == nullptr) {
            prviPar = poslednjiPar = newE;
        } else {
            poslednjiPar->next = newE;
        }
        poslednjiPar = newE;
    }
}

Tiket &Tiket::dodajPar(Par &par, int zeljeniIshod) {
    Elem *e = new Elem(par, zeljeniIshod);
    if (prviPar == nullptr) {
        prviPar = poslednjiPar = e;
    } else {
        poslednjiPar->next = e;
    }
    poslednjiPar = e;
    return *this;
}

Tiket::~Tiket() {
    Elem *next;
    for (Elem *e = prviPar; e != nullptr; e = next) {
        next = e->next;
        delete e;
    }
}

double Tiket::operator*() {
    return 0;
}

bool Tiket::operator~() {
    return false;
}

ostream &operator<<(ostream &out, Tiket &tiket) {
    out << "Tiket - " << ~tiket << " : (" << tiket.uplata << endl;
    for (Tiket::Elem *e = tiket.prviPar; e != nullptr; e = e->next) {
        out << e->par << " | " << e->zeljeniIshod << endl;
    }
    return out;
}

class Obican : public Tiket {
    public:
        using Tiket::Tiket;
        double operator*();
        bool operator~();
};

double Obican::operator*() {
    double total = 0;
    for (Elem *e = prviPar; e != nullptr; e = e->next) {
        if (e->zeljeniIshod == e->par()) {
            total += e->par[e->zeljeniIshod] * uplata;
        } else {
            return 0;
        }
    }
    return total;
}

bool Obican::operator~() {
    for (Elem *e = prviPar; e != nullptr; e = e->next) {
        if (e->zeljeniIshod != e->par()) {
            return false;
        }
    }
    return false;
}

class Kladionica {
    const char *naziv;
    friend ostream &operator<<(ostream &out, Kladionica &kladza);
    struct Elem {
        Tiket &tiket;
        Elem *next;
        Elem(Tiket &t) : tiket(t), next(nullptr) {}
    };
    Elem *prviTiket = nullptr, *poslednjiTiket = nullptr;
    public:
        Kladionica(const char *n) : naziv(n) {}
        Kladionica(const Kladionica &) = delete;
        void operator+=(Tiket t);
        double operator++();
};

void Kladionica::operator+=(Tiket t) {
    Elem *e = new Elem(t);
    if (prviTiket == nullptr) {
        prviTiket = poslednjiTiket = e;
    } else {
        poslednjiTiket->next = e;
    }
    poslednjiTiket = e;
}

double Kladionica::operator++() {
    double total = 0;
    for (Elem *e = prviTiket; e != nullptr; e = e->next) {
        total += e->tiket.getUplata() - *(e->tiket);
    }
    return total;
}

ostream &operator<<(ostream &out, Kladionica &kladza) {
    out << kladza.naziv << " : " << ++kladza << endl;
    for (Kladionica::Elem *e = kladza.prviTiket; e != nullptr; e = e->next) {
        out << e->tiket << endl;
    }
    return out;
}

int Par::sifraS = 0;
int main() {
    Kladionica k("MaleroznaKladionica");
    double kvote3[3] = { 2.55, 3.15, 2.85 };
    Par par3("New - Whu", kvote3);
    double kvote4[3] = { 4.2, 3.5, 1.9 };
    Par par4("Sou - Utd", kvote4);
    Obican t1(500);
    t1.dodajPar(par3, Par::DVA);
    Obican t2(100);
    t2.dodajPar(par3, Par::JEDAN).dodajPar(par4, Par::IKS);
    k += t1;
    k += t2;
    par3(Par::JEDAN);
    par4(Par::IKS);
    cout << k;
}
