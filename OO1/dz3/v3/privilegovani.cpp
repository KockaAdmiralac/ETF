#include "privilegovani.hpp"

void PrivilegovaniTim::prikljuci(Igrac &igrac, int pozicija) {
    if (igrac.dohvatiVrednost() < minimalnaVrednostIgraca) {
        throw GIgracNijeDovoljnoVredan();
    }
    Tim::prikljuci(igrac, pozicija);
}

void PrivilegovaniTim::pisi(std::ostream &it) const {
    // Postoji način da se ovo uradi bez duplikacije koda (virtuelna metoda
    // koja ispisuje samo naziv u osnovnom timu) ali je sa ovakvom metodom
    // rađeno na vežbama.
    bool prvi = true;
    it << naziv << " (" << minimalnaVrednostIgraca << ") [";
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
