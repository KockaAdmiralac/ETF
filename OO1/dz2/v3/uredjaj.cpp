#include "uredjaj.hpp"

int Uredjaj::jedinstveniId = 0;

std::ostream &operator<<(std::ostream &it, const Uredjaj &uredjaj) {
    return it << uredjaj.proizvodjac << ":" << uredjaj.id;
}
