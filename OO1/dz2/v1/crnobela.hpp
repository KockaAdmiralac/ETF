#ifndef _crnobela_hpp
#define _crnobela_hpp
#include "slika.hpp"

class CrnoBelaSlika : public Slika {
    public:
        using Slika::Slika;
        void postavi(const Piksel &piksel, const Pozicija &pozicija) override;
};

#endif
