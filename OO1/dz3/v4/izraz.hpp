#ifndef IZRAZ_HPP
#define IZRAZ_HPP
#include "element.hpp"
#include "lista.hpp"

class Izraz : public Lista<Element> {
    public:
        Izraz() = default;
        virtual Izraz *kopija() const {
            return new Izraz(*this);
        }
};

#endif
