#include "kvar.hpp"

std::ostream &operator<<(std::ostream &it, const Kvar &kvar) {
    return it << kvar.datum << "-" << kvar.opis;
}
