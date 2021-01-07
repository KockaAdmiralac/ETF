#ifndef _siva_hpp
#define _siva_hpp
#include "crnobela.hpp"

class SlikaUNijansamaSive : public Slika {
    public:
        using Slika::Slika;
        void postavi(const Piksel &piksel, const Pozicija &pozicija) override;
        operator CrnoBelaSlika() const {
            CrnoBelaSlika crnobela(sirina, visina, vreme);
            for (std::size_t i = 0; i < visina; ++i) {
                for (std::size_t j = 0; j < sirina; ++j) {
                    crnobela.postavi(matrica[i][j], {i, j});
                }
            }
            return crnobela;
        }
};

#endif
