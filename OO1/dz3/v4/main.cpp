#include <iostream>
#include "lista.hpp"
#include "element.hpp"
#include "operand.hpp"
#include "operator.hpp"
#include "sabiranje.hpp"
#include "leva.hpp"
#include "desna.hpp"
#include "izraz.hpp"
#include "generator.hpp"

int main(void) {
    // Ovde se u suštini testira samo generator. Pošto generator sam po sebi
    // poziva sve moguće metode iz ostalih delova zadatka, smatra se da se na
    // ovaj način efektivno testiraju sve klase.
    Izraz i;
    Operand a("a"), b("b"), c("c");
    LevaZagrada lz;
    DesnaZagrada dz;
    Sabiranje s;
    GeneratorIzrazaUPostfiksnomObliku &generator = GeneratorIzrazaUPostfiksnomObliku::dohvatiGenerator();
    // i = a + (b + c)
    i += a;
    i += s;
    i += lz;
    i += b;
    i += s;
    i += c;
    i += dz;
    std::cout << generator(i) << std::endl;
    // i = a + (b + )
    i += a;
    i += s;
    i += lz;
    i += b;
    i += s;
    i += dz;
    try {
        std::cout << generator(i) << std::endl;
        std::cout << "Nije došlo do greške! (Postfiks nije validan)" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom generisanja postfiksa: " << greska.what() << std::endl;
        std::cout << "Preostalo: " << i << std::endl;
    }
    // i = a + (b c)
    i += a;
    i += s;
    i += lz;
    i += b;
    i += c;
    i += dz;
    try {
        std::cout << generator(i) << std::endl;
        std::cout << "Nije došlo do greške! (Postfiks nije validan)" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom generisanja postfiksa: " << greska.what() << std::endl;
        std::cout << "Preostalo: " << i << std::endl;
    }
    // i = a + b + c)
    i += a;
    i += s;
    i += b;
    i += c;
    i += dz;
    try {
        std::cout << generator(i) << std::endl;
        std::cout << "Nije došlo do greške! (Postfiks nije validan)" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom generisanja postfiksa: " << greska.what() << std::endl;
        std::cout << "Preostalo: " << i << std::endl;
    }
    // i = a + (b + c
    i += a;
    i += s;
    i += lz;
    i += b;
    i += s;
    i += c;
    try {
        std::cout << generator(i) << std::endl;
        std::cout << "Nije došlo do greške! (Postfiks nije validan)" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom generisanja postfiksa: " << greska.what() << std::endl;
        std::cout << "Preostalo: " << i << std::endl;
    }
    // i = a + b + c
    i += a;
    i += s;
    i += b;
    i += s;
    i += c;
    std::cout << generator(i) << std::endl;
    return 0;
}
