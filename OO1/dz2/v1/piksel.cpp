#include "piksel.hpp"

Piksel Piksel::operator+(const Piksel &b) const {
    return {
        kanal((crvena + b.crvena) / 2),
        kanal((zelena + b.zelena) / 2),
        kanal((plava  + b.plava)  / 2)
    };
}

bool Piksel::operator==(const Piksel &b) const {
    return crvena == b.crvena && zelena == b.zelena && plava == b.plava;
}

void Piksel::pisi(std::ostream &it) const {
    it << "(" << int(crvena) << ", "
              << int(zelena) << ", "
              << int(plava)  << ")";
}

std::ostream &operator<<(std::ostream &it, const Piksel &piksel) {
    piksel.pisi(it);
    return it;
}
