#ifndef _objava_hpp
#define _objava_hpp
#include "obavestenje.hpp"

class Objava : public Obavestenje {
    public:
        Objava(Korisnik &korisnik, std::string &tekst) :
            Obavestenje(korisnik), tekst(tekst) {}
        Objava(Korisnik &korisnik, std::string &&tekst) :
            Obavestenje(korisnik), tekst(tekst) {}
        void pisi(std::ostream &it) const override;
    private:
        std::string tekst;
};

#endif
