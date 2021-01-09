#ifndef ELEMENT_HPP
#define ELEMENT_HPP
#include <iostream>

class Element {
    public:
        virtual char dohvatiOznaku() const = 0;
        virtual std::string dohvatiNatpis() const = 0;
        virtual Element *kopija() const = 0;
        friend std::ostream &operator<<(std::ostream &it, const Element &element);
        virtual ~Element() = 0;
    protected:
        virtual void pisi(std::ostream &it) const;
};

#endif
