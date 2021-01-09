#ifndef DESNA_HPP
#define DESNA_HPP
#include "element.hpp"

class DesnaZagrada : public Element {
    public:
        char dohvatiOznaku() const override {
            return ')';
        }
        std::string dohvatiNatpis() const override {
            return ")";
        }
        Element *kopija() const override {
            return new DesnaZagrada(*this);
        }
};


#endif
