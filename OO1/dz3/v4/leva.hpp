#ifndef LEVA_HPP
#define LEVA_HPP
#include "element.hpp"

class LevaZagrada : public Element {
    public:
        char dohvatiOznaku() const override {
            return '(';
        }
        std::string dohvatiNatpis() const override {
            return "(";
        }
        Element *kopija() const override {
            return new LevaZagrada(*this);
        }
};

#endif
