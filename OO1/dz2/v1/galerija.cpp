#include "galerija.hpp"

std::size_t Galerija::brojBitova() const {
    std::size_t bitovi = 0;
    for (std::size_t i = 0; i < slike.size(); ++i) {
        bitovi += slike[i]->brojBitova();
    }
    return bitovi;
}

void Galerija::pisi(std::ostream &it) const {
    for (std::size_t i = 0; i < slike.size(); ++i) {
        it << (*slike[i]) << std::endl;
    }
}

std::ostream &operator<<(std::ostream &it, const Galerija &galerija) {
    galerija.pisi(it);
    return it;
}
