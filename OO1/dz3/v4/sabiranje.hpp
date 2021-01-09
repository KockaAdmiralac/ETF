#ifndef SABIRANJE_HPP
#define SABIRANJE_HPP
#include "operator.hpp"

class Sabiranje : public Operator {
    public:
        int dohvatiPrioritet() const override {
            return 1;
        }
        std::string dohvatiNatpis() const override {
            return "+";
        }
        Element *kopija() const override {
            return new Sabiranje(*this);
        }
};

#endif
