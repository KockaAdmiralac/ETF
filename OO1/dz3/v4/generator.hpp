#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <exception>
#include "izraz.hpp"

class GPostfiks : public std::exception {
    public:
        const char *what() const noexcept override {
            return "Nije moguće generisati ispravan izraz u postfiksnom obliku.";
        }
};

class GeneratorIzrazaUPostfiksnomObliku {
    public:
        GeneratorIzrazaUPostfiksnomObliku(GeneratorIzrazaUPostfiksnomObliku &) = delete;
        GeneratorIzrazaUPostfiksnomObliku &operator=(GeneratorIzrazaUPostfiksnomObliku &) = delete;
        static GeneratorIzrazaUPostfiksnomObliku &dohvatiGenerator();
        Izraz operator()(Izraz &infiks);
    private:
        GeneratorIzrazaUPostfiksnomObliku() {}
};

#endif
