#include "lista.hpp"

void ListaObavestenja::operator()() const {
    for (auto it = lista.rbegin(); it != lista.rend(); ++it) {
        if (!(*it)->daLiJeProcitano()) {
            std::cout << (**it) << std::endl;
        }
    }
}

int ListaObavestenja::operator+() const {
    int count = 0;
    for (const Obavestenje *obavestenje : lista) {
        if (!obavestenje->daLiJeProcitano()) {
            ++count;
        }
    }
    return count;
}

void ListaObavestenja::operator!() {
    for (Obavestenje *obavestenje : lista) {
        obavestenje->procitaj();
    }
}

const Obavestenje &ListaObavestenja::operator[](int id) const {
    for (const Obavestenje *obavestenje : lista) {
        if (
            !obavestenje->daLiJeProcitano() &&
            obavestenje->identifikator() == id
        ) {
            return *obavestenje;
        }
    }
    throw obavestenje_not_found();
}

void ListaObavestenja::pisi(std::ostream &it) const {
    for (auto itr = lista.rbegin(); itr != lista.rend(); ++itr) {
        it << (**itr) << std::endl;
    }
}

std::ostream &operator<<(std::ostream &it, const ListaObavestenja &lista) {
    lista.pisi(it);
    return it;
}
