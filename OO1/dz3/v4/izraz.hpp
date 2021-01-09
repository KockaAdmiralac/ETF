#ifndef IZRAZ_HPP
#define IZRAZ_HPP
#include "element.hpp"
#include "lista.hpp"

class Izraz : public Lista<Element> {
    public:
        Izraz() = default;
        Izraz(const Izraz &izraz) : Lista<Element>() {
            kopiraj(izraz);
        }
        Izraz &operator=(const Izraz &izraz);
        void operator+=(Element &element) {
            Lista<Element>::operator+=(element.kopija());
        }
        void operator+=(Element *element) {
            Lista<Element>::operator+=(element->kopija());
        }
    protected:
        void kopiraj(const Izraz &izraz);
};

#endif
