#include "klima.hpp"

std::ostream &operator<<(std::ostream &it, const Klima &klima) {
    return it << klima.proizvodjac << ":" << klima.id << "#klima#-"
              << klima.brojKvadrata;
}
