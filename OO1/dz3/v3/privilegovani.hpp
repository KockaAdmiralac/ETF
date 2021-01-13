#ifndef PRIVILEGOVANI_HPP
#define PRIVILEGOVANI_HPP
#include <exception>
#include <iostream>
#include "tim.hpp"

class GIgracNijeDovoljnoVredan : public std::exception {
    public:
        const char *what() const noexcept override {
            return "Vrednost igrača je manja od minimalne potrebne "
                   "za priključivanje timu!";
        }
};

class PrivilegovaniTim : public Tim {
    public:
        PrivilegovaniTim(std::string naziv, int maksimalniBrojIgraca, int minimalnaVrednostIgraca) :
            Tim(naziv, maksimalniBrojIgraca),
            minimalnaVrednostIgraca(minimalnaVrednostIgraca) {}
        void prikljuci(Igrac &igrac, int pozicija) override;
        void pisi(std::ostream &it) const override;
    private:
        int minimalnaVrednostIgraca;
};

#endif
