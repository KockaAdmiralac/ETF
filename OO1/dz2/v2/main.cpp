#include <iostream>
#include "korisnik.hpp"
#include "obavestenje.hpp"
#include "objava.hpp"
#include "lista.hpp"

int main(void) {
    // Korisnik
    std::string k1ime = "Pera", k2ime = "Žika";
    Korisnik k1(k1ime), k2(k2ime);
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
    // Objava
    std::string o2tekst = "Lorem ipsum dolor sit amet.";
    Objava o2(k2, o2tekst);
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
    } catch (const char *poruka) {
        std::cout << poruka << std::endl;
    }
    return 0;
}
