#ifndef TIM_HPP
#define TIM_HPP
#include <iostream>
#include "igrac.hpp"

class Tim {
    public:
        Tim(std::string naziv, int maksimalniBrojIgraca) :
            naziv(naziv), maksimalniBrojIgraca(maksimalniBrojIgraca),
            igraci(new Igrac*[maksimalniBrojIgraca]()) {}
        Tim(const Tim &tim) {
            kopiraj(tim);
        }
        Tim(Tim &&tim) {
            premesti(tim);
        }
        ~Tim() {
            brisi();
        }
        Tim &operator=(const Tim &tim);
        Tim &operator=(Tim &&tim);
        virtual void prikljuci(Igrac &igrac, int pozicija);
        int dohvatiBrojIgraca() const {
            return brojIgraca;
        }
        // MEJL@Adrian: Dozvoljeno je da odavde vraćamo pokazivač kako bismo
        // znali da li igrač na toj poziciji postoji.
        Igrac *operator[](int pozicija) {
            return igraci[pozicija];
        }
        // Ovo je glupo, ali je na konsultacijama rečeno da moramo da imamo dve
        // varijante ovog operatora.
        const Igrac *operator[](int pozicija) const {
            return igraci[pozicija];
        }
        double dohvatiVrednostTima() const;
        friend bool operator==(const Tim &tim1, const Tim &tim2);
        friend std::ostream &operator<<(std::ostream &it, const Tim &tim);
    protected:
        std::string naziv;
        // MEJL@Adrian: Dozvoljeno je da broj igrača čuvamo kao polje klase.
        int maksimalniBrojIgraca, brojIgraca = 0;
        Igrac **igraci;
        virtual void pisi(std::ostream &it) const;
        void kopiraj(const Tim &tim);
        void premesti(Tim &tim);
        void brisi();
};

#endif
