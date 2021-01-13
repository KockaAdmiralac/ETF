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
    Izraz i1, i2, i3, i4, i5, i6;
    Operand a("a"), b("b"), c("c");
    LevaZagrada lz;
    DesnaZagrada dz;
    Sabiranje s;
    GeneratorIzrazaUPostfiksnomObliku &generator = GeneratorIzrazaUPostfiksnomObliku::dohvatiGenerator();
    // i = a + (b + c)
    i1 += a;
    i1 += s;
    i1 += lz;
    i1 += b;
    i1 += s;
    i1 += c;
    i1 += dz;
    std::cout << generator(i1) << std::endl;
    // i = a + (b + )
    i2 += a;
    i2 += s;
    i2 += lz;
    i2 += b;
    i2 += s;
    i2 += dz;
    try {
        std::cout << generator(i2) << std::endl;
        std::cout << "Nije došlo do greške! (Postfiks nije validan)" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom generisanja postfiksa: " << greska.what() << std::endl;
    }
    // i = a + (b c)
    i3 += a;
    i3 += s;
    i3 += lz;
    i3 += b;
    i3 += c;
    i3 += dz;
    try {
        std::cout << generator(i3) << std::endl;
        std::cout << "Nije došlo do greške! (Postfiks nije validan)" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom generisanja postfiksa: " << greska.what() << std::endl;
    }
    // i = a + b + c)
    i4 += a;
    i4 += s;
    i4 += b;
    i4 += c;
    i4 += dz;
    try {
        std::cout << generator(i4) << std::endl;
        std::cout << "Nije došlo do greške! (Postfiks nije validan)" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom generisanja postfiksa: " << greska.what() << std::endl;
    }
    // i = a + (b + c
    i5 += a;
    i5 += s;
    i5 += lz;
    i5 += b;
    i5 += s;
    i5 += c;
    try {
        std::cout << generator(i5) << std::endl;
        std::cout << "Nije došlo do greške! (Postfiks nije validan)" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom generisanja postfiksa: " << greska.what() << std::endl;
    }
    // i = a + b + c
    i6 += a;
    i6 += s;
    i6 += b;
    i6 += s;
    i6 += c;
    std::cout << generator(i6) << std::endl;
    return 0;
}
