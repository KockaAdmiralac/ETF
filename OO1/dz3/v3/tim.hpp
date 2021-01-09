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
        virtual void prikljuci(Igrac &igrac, int pozicija) const;
        int dohvatiBrojIgraca() const;
        // PRETPOSTAVKA: Ovde se vraća pokazivač do igrača umesto reference
        // jer igrač kome se pristupa može da ne postoji, te je lakše
        // korisniku vratiti nullptr umesto bacati grešku.
        Igrac *operator[](int pozicija) const {
            return igraci[pozicija];
        }
        double dohvatiVrednostTima() const;
        friend bool operator==(const Tim &tim1, const Tim &tim2);
        friend std::ostream &operator<<(std::ostream &it, const Tim &tim);
    protected:
        std::string naziv;
        int maksimalniBrojIgraca;
        Igrac **igraci;
        virtual void pisi(std::ostream &it) const;
        void kopiraj(const Tim &tim);
        void premesti(Tim &tim);
        void brisi();
};

#endif
