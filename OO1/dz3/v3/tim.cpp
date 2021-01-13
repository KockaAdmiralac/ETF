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

void Tim::prikljuci(Igrac &igrac, int pozicija) {
    if (pozicija < maksimalniBrojIgraca) {
        // MEJL@Adrian: Tim je vlasnik igrača.
        if (igraci[pozicija] == nullptr) {
            ++brojIgraca;
        } else {
            delete igraci[pozicija];
        }
        igraci[pozicija] = new Igrac(igrac);
    }
}

double Tim::dohvatiVrednostTima() const {
    if (brojIgraca == 0) {
        return 0;
    }
    double suma = 0;
    for (int i = 0; i < maksimalniBrojIgraca; ++i) {
        if (igraci[i] != nullptr) {
            suma += igraci[i]->dohvatiVrednost();
        }
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
    brojIgraca = tim.brojIgraca;
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
    brojIgraca = tim.brojIgraca;
    igraci = tim.igraci;
    tim.igraci = nullptr;
    tim.maksimalniBrojIgraca = 0;
    tim.brojIgraca = 0;
}

void Tim::brisi() {
    for (int i = 0; i < maksimalniBrojIgraca; ++i) {
        if (igraci[i] != nullptr) {
            delete igraci[i];
        }
    }
    delete[] igraci;
}
