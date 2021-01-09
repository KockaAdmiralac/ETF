#include "racun.hpp"

bool Racun::prenesi(Racun &drugi, std::size_t iznos) {
    if (this->iznos < 0 || iznos > (std::size_t)this->iznos) {
        return false;
    }
    drugi += iznos;
    this->iznos -= iznos;
    return true;
}

Racun &Racun::operator+=(std::size_t iznos) {
    this->iznos += iznos;
    return *this;
}

std::ostream &operator<<(std::ostream &it, const Racun &racun) {
    racun.pisi(it);
    return it;
}

void Racun::pisi(std::ostream &it) const {
    it << "R: " << broj << " :=: " << iznos << " - " << dohvatiValutu();
}
