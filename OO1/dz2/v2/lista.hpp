#ifndef _lista_hpp
#define _lista_hpp
#include <iostream>
#include <vector>
#include "obavestenje.hpp"

class ListaObavestenja {
    public:
        ListaObavestenja() = default;
        ListaObavestenja(ListaObavestenja&) = delete;
        ListaObavestenja(ListaObavestenja&&) = delete;
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
};

#endif
