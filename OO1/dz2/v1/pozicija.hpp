#ifndef _pozicija_hpp
#define _pozicija_hpp

class Pozicija {
    public:
        Pozicija(std::size_t vrsta, std::size_t kolona) : vrsta(vrsta), kolona(kolona) {}
        std::size_t dohvatiVrstu() const {
            return vrsta;
        }
        std::size_t dohvatiKolonu() const {
            return kolona;
        }
        std::size_t operator-(const Pozicija &b) const;
    private:
        std::size_t vrsta, kolona;
};

#endif
