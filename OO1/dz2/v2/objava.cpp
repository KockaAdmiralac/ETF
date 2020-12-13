#include "objava.hpp"

void Objava::pisi(std::ostream &it) const {
    Obavestenje::pisi(it);
    it << tekst;
}
