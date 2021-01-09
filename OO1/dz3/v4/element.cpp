#include "element.hpp"

std::ostream &operator<<(std::ostream &it, const Element &element) {
    element.pisi(it);
    return it;
}

void Element::pisi(std::ostream &it) const {
    it << dohvatiNatpis();
}

Element::~Element() {}
