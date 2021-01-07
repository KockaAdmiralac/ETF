#include <iostream>
#include "korisnik.hpp"
#include "obavestenje.hpp"
#include "objava.hpp"
#include "lista.hpp"

int main(void) {
    // Korisnik
    Korisnik k1("Pera"), k2("Žika");
    k1.posalji(k2);
    std::cout << k2.dohvatiIme() << " " << k2 << std::endl;
    // Obaveštenje
    Obavestenje o1(k1), o3(k2);
    std::cout << o1.daLiJeProcitano() << " "
              << o1.dohvatiKorisnika() << " "
              << o1.identifikator() << " ";
    o1.procitaj();
    k2.primi(o1);
    std::cout << o1.daLiJeProcitano() << std::endl
              << o1 << std::endl;
    Obavestenje kopirano(o1);
    std::cout << kopirano << std::endl;
    kopirano = o3;
    std::cout << kopirano << std::endl;
    Obavestenje premesteno(std::move(kopirano));
    std::cout << premesteno << std::endl;
    o3 = std::move(premesteno);
    std::cout << o3 << std::endl;
    // Objava
    Objava o2(k2, "Lorem ipsum dolor sit amet.");
    std::cout << o2 << std::endl;
    // Lista obaveštenja
    ListaObavestenja l;
    l += o2;
    l();
    ~l;
    std::cout << l;
    l += o2;
    std::cout << +l << " ";
    !l;
    l += o3;
    std::cout << +l << std::endl << l;
    std::cout << l[o3.identifikator()] << std::endl;
    try {
        l[o1.identifikator()];
    } catch (obavestenje_not_found &exc) {
        std::cout << exc.what() << std::endl;
    }
    return 0;
}
