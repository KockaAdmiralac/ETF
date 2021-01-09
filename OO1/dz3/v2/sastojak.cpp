#include "sastojak.hpp"

NutritivnaVrednost Sastojak::nutritivnaVrednost() const {
    // KONSULTACIJE@Uroš: Radi se skaliranje nutritivne vrednosti na količinu.
    NutritivnaVrednost nv = namirnica.dohvatiNutritivnuVrednost();
    double uh = nv.dohvatiUgljeneHidrate(),
            masti = nv.dohvatiMasti(),
            proteini = nv.dohvatiProteine();
    return {
        uh / 100 * kolicina,
        masti / 100 * kolicina,
        proteini / 100 * kolicina
    };
}

double Sastojak::brojKalorija() const {
    return namirnica.dohvatiNutritivnuVrednost().brojKalorija() / 100 * kolicina;
}

std::ostream &operator<<(std::ostream &it, const Sastojak &sastojak) {
    sastojak.pisi(it);
    return it;
}

void Sastojak::pisi(std::ostream &it) const {
    it << "[" << brojKalorija() / 1000 << "kcal] " << kolicina << "g x " << namirnica;
}
