#include "mec.hpp"

void Mec::odigraj() {
    Tim *domacin = timovi.dohvatiPrvi(),
        *gost = timovi.dohvatiDrugi(),
        *pobednik, *gubitnik;
    double vrednostDomacina = domacin->dohvatiVrednostTima(),
           vrednostGosta = gost->dohvatiVrednostTima();
    if (vrednostDomacina > vrednostGosta) {
        ishod = POBEDA_DOMACIN;
        pobednik = domacin;
        gubitnik = gost;
    } else if (vrednostDomacina < vrednostGosta) {
        ishod = POBEDA_GOST;
        pobednik = gost;
        gubitnik = domacin;
    } else {
        ishod = NERESENO;
    }
    if (ishod != NERESENO) {
        int krajnjiIndeksPobednik = pobednik->dohvatiBrojIgraca(),
            krajnjiIndeksGubitnik = gubitnik->dohvatiBrojIgraca();
        for (int i = 0; i < krajnjiIndeksPobednik; ++i) {
            if ((*pobednik)[i] == nullptr) {
                ++krajnjiIndeksPobednik;
            } else {
                (*pobednik)[i]->promeniVrednost(10);
            }
        }
        for (int i = 0; i < krajnjiIndeksGubitnik; ++i) {
            if ((*gubitnik)[i] == nullptr) {
                ++krajnjiIndeksGubitnik;
            } else {
                (*gubitnik)[i]->promeniVrednost(-10);
            }
        }
    }
}

Par<int> Mec::poeni() const {
    switch (ishod) {
        // PRETPOSTAVKA: Poeni vraćeni odavde se alociraju na hipu. Ovo je loše
        // jer se dealokacija ove memorije ostavlja korisniku. Bolji način bi
        // bio da postoji polje klase u kojem se čuvaju bodovi, te se to polje
        // izračunava pri igranju meča, u ovoj metodi samo vraća, a u
        // destruktoru dealocira. Ovaj pristup nije uzet jer se nigde u zadatku
        // ne implicira da poeni treba da budu polje klase. Još bolji način bi
        // bio da se u Par ne čuvaju samo pokazivači do podataka. Još bolji
        // način bi bio da koristimo std::pair.
        case POBEDA_DOMACIN: return {new int(3), new int(0)};
        case POBEDA_GOST: return {new int(0), new int(3)};
        case NERESENO: return {new int(1), new int(1)};
        default: throw GMecNijeOdigran();
    }
}

std::ostream &operator<<(std::ostream &it, const Mec &mec) {
    mec.pisi(it);
    return it;
}

void Mec::pisi(std::ostream &it) const {
    it << timovi << ", ishod: ";
    if (ishod == NEODIGRANO) {
        it << "neodigrano";
    } else if (ishod == POBEDA_DOMACIN) {
        it << "domaćin je pobedio";
    } else if (ishod == POBEDA_GOST) {
        it << "gost je pobedio";
    } else {
        it << "nerešeno";
    }
}
