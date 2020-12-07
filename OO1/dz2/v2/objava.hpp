#ifndef _objava_hpp
#define _objava_hpp
#include "obavestenje.hpp"

class Objava : public Obavestenje {
    public:
        Objava(Korisnik &korisnik, std::string &tekst) :
            Obavestenje(korisnik), tekst(tekst) {}
            void specificanIspis(std::ostream &it) const override {
                it << tekst;
            }
    private:
        std::string &tekst;
};

#endif
