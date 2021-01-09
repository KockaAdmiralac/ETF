#ifndef PREVOZ_HPP
#define PREVOZ_HPP

class Prevoz {
    public:
        Prevoz(Destinacija &destinacija, double cenaKarte) :
            destinacija(destinacija), cenaKarte(cenaKarte) {}
        const Destinacija &dohvatiDestinaciju() const {
            return destinacija;
        }
        virtual double cenaPrevoza() const {
            return cenaKarte;
        }
    private:
        // PRETPOSTAVKA: Videti u Aranžman.
        Destinacija &destinacija;
        double cenaKarte;
};

#endif
