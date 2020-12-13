#ifndef _klima_hpp
#define _klima_hpp
#include <iostream>
#include "uredjaj.hpp"

class Klima : public Uredjaj {
    public:
        Klima(std::string &proizvodjac, int brojKvadrata) :
            Uredjaj(proizvodjac), brojKvadrata(brojKvadrata) {}
        Klima(std::string &&proizvodjac, int brojKvadrata) :
            Uredjaj(proizvodjac), brojKvadrata(brojKvadrata) {}
        void postaviGaranciju(Datum &datumPocetka) override {
            garancija = new Garancija(
                datumPocetka,
                Datum(
                    datumPocetka["dan"],
                    datumPocetka["mesec"],
                    datumPocetka["godina"] + 5
                )
            );
        }
        int brojKvarovaZaIzdavanjeNovog() const override {
            return 2;
        }
        bool operator==(const Klima &klima2) {
            return brojKvadrata == klima2.brojKvadrata &&
                   Uredjaj::operator==(klima2);
        }
    private:
        int brojKvadrata;
        void pisi(std::ostream &it) const override;
};

#endif
