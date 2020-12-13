#ifndef _lista_hpp
#define _lista_hpp
#include <iostream>
#include <vector>
#include "obavestenje.hpp"

class obavestenje_not_found : std::exception {
    public:
        const char *what() const noexcept override {
            return "Ne postoji obaveštenje.";
        }
};

class ListaObavestenja {
    public:
        ListaObavestenja() = default;
        ListaObavestenja(ListaObavestenja &) = delete;
        ListaObavestenja &operator=(const ListaObavestenja &) = delete;
        // Pretpostavlja se da će obaveštenja živeti duže od liste kako bi
        // mogla da pojedinačno budu označavana kao pročitana
        void operator+=(Obavestenje &obavestenje) {
            lista.push_back(&obavestenje);
        }
        void operator()() const;
        int operator+() const;
        void operator!();
        void operator~() {
            lista.clear();
        }
        const Obavestenje &operator[](int id) const;
        friend std::ostream &operator<<(std::ostream &it, const ListaObavestenja &lista);
    private:
        std::vector<Obavestenje*> lista;
        void pisi(std::ostream &it) const;
};

#endif
