#include "izraz.hpp"

void Izraz::kopiraj(const Izraz &izraz) {
    brojPodataka = izraz.brojPodataka;
    Elem *trenutni = izraz.prvi;
    while (trenutni != nullptr) {
        (*this) += trenutni->podatak->kopija();
        trenutni = trenutni->sledeci;
    }
}

Izraz &Izraz::operator=(const Izraz &izraz) {
    if (&izraz != this) {
        brisi();
        kopiraj(izraz);
    }
    return *this;
}
