#ifndef _pozicija_hpp
#define _pozicija_hpp

class Pozicija {
    public:
        Pozicija(int vrsta, int kolona) : vrsta(vrsta), kolona(kolona) {}
        int dohvatiVrstu() const {
            return vrsta;
        }
        int dohvatiKolonu() const {
            return kolona;
        }
        int operator-(const Pozicija &b);
    private:
        int vrsta, kolona;
};

#endif
