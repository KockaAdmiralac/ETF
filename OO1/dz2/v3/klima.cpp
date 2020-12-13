#include "klima.hpp"

void Klima::pisi(std::ostream &it) const {
    Uredjaj::pisi(it);
    it << "#klima#-" << brojKvadrata;
}
