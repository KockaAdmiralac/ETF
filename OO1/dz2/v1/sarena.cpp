#include <exception>
#include "sarena.hpp"

SarenaSlika::SarenaSlika(std::size_t sirina, std::size_t visina, const Vreme &vreme) :
    Slika(sirina, visina, vreme) {
    for (std::size_t i = 0; i < visina; ++i) {
        for (std::size_t j = 0; j < sirina; ++j) {
            bool postavljen = false;
            while (!postavljen) {
                Piksel saren(
                    ((double)rand()) * 256 / RAND_MAX,
                    ((double)rand()) * 256 / RAND_MAX,
                    ((double)rand()) * 256 / RAND_MAX
                );
                Pozicija pozicija(i, j);
                if (uporediSaOkolinom(pozicija, saren)) {
                    continue;
                }
                matrica[i][j] = saren;
                postavljen = true;
            }
        }
    }
}

SarenaSlika::SarenaSlika(Slika &slika1, Slika &slika2) :
    Slika(
        slika1.dohvatiSirinu(),
        slika1.dohvatiVisinu(),
        (slika1.dohvatiVreme() > slika2.dohvatiVreme()) ?
            slika1.dohvatiVreme() :
            slika2.dohvatiVreme()
    ) {
    if (
        slika1.dohvatiSirinu() != slika2.dohvatiSirinu() ||
        slika1.dohvatiVisinu() != slika2.dohvatiVisinu()
    ) {
        throw slike_nisu_istih_dimenzija();
    }
    for (std::size_t i = 0; i < visina; ++i) {
        for (std::size_t j = 0; j < sirina; ++j) {
            Pozicija pozicija(i, j);
            matrica[i][j] = slika1[pozicija] + slika2[pozicija];
        }
    }
}

bool SarenaSlika::uporediSaOkolinom(const Pozicija &pozicija, const Piksel &piksel) const {
    for (std::size_t i = 0; i < visina; ++i) {
        for (std::size_t j = 0; j < sirina; ++j) {
            if (pozicija - Pozicija(i, j) == 1 && matrica[i][j] == piksel) {
                return true;
            }
        }
    }
    return false;
}

void SarenaSlika::postavi(const Piksel &piksel, const Pozicija &pozicija) {
    if (uporediSaOkolinom(pozicija, piksel)) {
        return;
    }
    Slika::postavi(piksel, pozicija);
}
