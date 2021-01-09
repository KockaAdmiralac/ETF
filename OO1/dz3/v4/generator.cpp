#include "generator.hpp"
#include "operator.hpp"

GeneratorIzrazaUPostfiksnomObliku &GeneratorIzrazaUPostfiksnomObliku::dohvatiGenerator() {
    static GeneratorIzrazaUPostfiksnomObliku generator;
    return generator;
}

Izraz GeneratorIzrazaUPostfiksnomObliku::operator()(Izraz &infiks) {
    Izraz stek, postfiks;
    int rang = 0;
    Element *sledeci, *stekSledeci;
    while (infiks.dohvatiBrojPodataka() > 0) {
        sledeci = *infiks;
        switch (sledeci->dohvatiOznaku()) {
            case 'D':
                // Operand
                postfiks += sledeci;
                ++rang;
                break;
            case '(':
                stek += sledeci;
                break;
            case ')':
                while (true) {
                    if (stek.dohvatiBrojPodataka() == 0) {
                        delete sledeci;
                        throw GPostfiks();
                    }
                    stekSledeci = -stek;
                    if (stekSledeci->dohvatiOznaku() == '(') {
                        delete stekSledeci;
                        break;
                    } else {
                        postfiks += stekSledeci;
                        if (--rang < 1) {
                            delete sledeci;
                            delete stekSledeci;
                            throw GPostfiks();
                        }
                    }
                    delete stekSledeci;
                }
                break;
            default:
                // Operator
                Operator *op = dynamic_cast<Operator *>(sledeci);
                if (op == nullptr) {
                    delete sledeci;
                    throw GPostfiks();
                }
                while (stek.dohvatiBrojPodataka() > 0) {
                    stekSledeci = -stek;
                    if (stekSledeci->dohvatiOznaku() != 'O') {
                        stek += stekSledeci;
                        delete stekSledeci;
                        break;
                    }
                    Operator *opss = dynamic_cast<Operator *>(stekSledeci);
                    if (opss == nullptr) {
                        delete sledeci;
                        delete stekSledeci;
                        throw GPostfiks();
                    }
                    if (op->dohvatiPrioritet() > opss->dohvatiPrioritet()) {
                        stek += stekSledeci;
                        delete stekSledeci;
                        break;
                    }
                    postfiks += sledeci;
                    if (--rang < 1) {
                        delete sledeci;
                        delete stekSledeci;
                        throw GPostfiks();
                    }
                    delete stekSledeci;
                }
                stek += sledeci;
                break;
        }
        delete sledeci;
    }
    while (stek.dohvatiBrojPodataka() > 0) {
        stekSledeci = -stek;
        if (stekSledeci->dohvatiOznaku() != 'O') {
            delete stekSledeci;
            throw GPostfiks();
        }
        postfiks += stekSledeci;
        delete stekSledeci;
        --rang;
    }
    if (rang != 1) {
        throw GPostfiks();
    }
    return postfiks;
}
