#ifndef OPERATOR_HPP
#define OPERATOR_HPP
#include "element.hpp"

class Operator : public Element {
    public:
        virtual int dohvatiPrioritet() const = 0;
        char dohvatiOznaku() const override {
            return 'O';
        }
        friend bool operator>(const Operator &op1, const Operator &op2) {
            return op1.dohvatiPrioritet() > op2.dohvatiPrioritet();
        }
};

#endif
