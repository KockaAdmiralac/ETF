#ifndef OPERAND_HPP
#define OPERAND_HPP
#include <string>
#include "element.hpp"

class Operand : public Element {
    public:
        Operand(std::string natpis) : natpis(natpis) {}
        char dohvatiOznaku() const override {
            return 'D';
        }
        std::string dohvatiNatpis() const override {
            return natpis;
        }
        Element *kopija() const override {
            return new Operand(*this);
        }
    private:
        std::string natpis;
};

#endif
