#include "tim.hpp"

Tim &Tim::operator=(const Tim &tim) {
    if (&tim != this) {
        brisi();
        kopiraj(tim);
    }
    return *this;
}

Tim &Tim::operator=(Tim &&tim) {
    if (&tim != this) {
        brisi();
        premesti(tim);
    }
    return *this;
}

int Tim::dohvatiBrojIgraca() const {
    // PRETPOSTAVKA: Dohvatanje broja igrača je O(n). Ovo je napravljeno ovako
    // jer nigde nije naglašeno da broj igrača treba da bude polje klase, i
    // dodavanje u tim ne bi radilo da jeste (osim ako to polje ne označimo kao
    // mutable, što samo po sebi nije toliko dobro).
    // U SUPROTNOM: bi trebalo da dodamo mutable int brojIgraca; kao polje
    // klase i ovde samo vraćamo taj broj. Taj broj bi se povećavao u prikljuci
    // svaki put kad se priključi igrač na poziciju koja nije nullptr.
    int brojIgraca = 0;
    for (int i = 0; i < maksimalniBrojIgraca; ++i) {
        if (igraci[i] != nullptr) {
            ++brojIgraca;
        }
    }
    return brojIgraca;
}

void Tim::prikljuci(Igrac &igrac, int pozicija) const {
    if (pozicija < maksimalniBrojIgraca) {
        // PRETPOSTAVKA: Tim je vlasnik igrača.
        if (igraci[pozicija] != nullptr) {
            delete igraci[pozicija];
        }
        igraci[pozicija] = new Igrac(igrac);
    }
}

double Tim::dohvatiVrednostTima() const {
    double suma = 0;
    int brojIgraca = 0;
    for (int i = 0; i < maksimalniBrojIgraca; ++i) {
        if (igraci[i] != nullptr) {
            suma += igraci[i]->dohvatiVrednost();
            ++brojIgraca;
        }
    }
    if (brojIgraca == 0) {
        return 0;
    }
    return suma / brojIgraca;
}

bool operator==(const Tim &tim1, const Tim &tim2) {
    if (tim1.naziv != tim2.naziv || tim1.maksimalniBrojIgraca != tim2.maksimalniBrojIgraca) {
        return false;
    }
    for (int i = 0; i < tim1.maksimalniBrojIgraca; ++i) {
        if (
            (tim1.igraci[i] == nullptr) != (tim2.igraci[i] == nullptr) ||
            (
                tim1.igraci[i] != nullptr &&
                !((*tim1.igraci[i]) == (*tim2.igraci[i]))
            )
        ) {
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &it, const Tim &tim) {
    tim.pisi(it);
    return it;
}

void Tim::pisi(std::ostream &it) const {
    bool prvi = true;
    it << naziv << " [";
    for (int i = 0; i < maksimalniBrojIgraca; ++i) {
        if (igraci[i] != nullptr) {
            if (prvi) {
                prvi = false;
            } else {
                it << ", ";
            }
            it << (*igraci[i]);
        }
    }
    it << "]";
}

void Tim::kopiraj(const Tim &tim) {
    naziv = tim.naziv;
    maksimalniBrojIgraca = tim.maksimalniBrojIgraca;
    igraci = new Igrac*[maksimalniBrojIgraca]();
    for (int i = 0; i < maksimalniBrojIgraca; ++i) {
        if (tim.igraci[i] != nullptr) {
            igraci[i] = new Igrac(*tim.igraci[i]);
        }
    }
}

void Tim::premesti(Tim &tim) {
    naziv = tim.naziv;
    maksimalniBrojIgraca = tim.maksimalniBrojIgraca;
    igraci = tim.igraci;
    tim.igraci = nullptr;
    tim.maksimalniBrojIgraca = 0;
}

void Tim::brisi() {
    for (int i = 0; i < maksimalniBrojIgraca; ++i) {
        if (igraci[i] != nullptr) {
            delete igraci[i];
        }
    }
    delete[] igraci;
}
