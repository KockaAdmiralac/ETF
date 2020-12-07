#include "piksel.hpp"

Piksel Piksel::operator+(const Piksel &b) {
    return {
        kanal((crvena + b.crvena) / 2),
        kanal((zelena + b.zelena) / 2),
        kanal((plava  + b.plava)  / 2)
    };
}

bool Piksel::operator==(const Piksel &b) {
    return crvena == b.crvena && zelena == b.zelena && plava == b.plava;
}

std::ostream &operator<<(std::ostream &it, const Piksel &piksel) {
    return it << "(" << int(piksel.crvena) << ", "
                     << int(piksel.zelena) << ", "
                     << int(piksel.plava)  << ")";
}
