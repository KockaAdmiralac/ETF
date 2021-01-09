#include "igrac.hpp"

bool operator==(const Igrac &igr1, const Igrac &igr2) {
    return igr1.ime == igr2.ime && igr1.vrednost == igr2.vrednost;
}

std::ostream &operator<<(std::ostream &it, const Igrac &igr) {
    igr.pisi(it);
    return it;
}

void Igrac::pisi(std::ostream &it) const {
    it << ime << "#" << vrednost;
}
