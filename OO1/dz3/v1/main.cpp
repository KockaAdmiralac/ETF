#include <iostream>
#include "datum.hpp"
#include "osoba.hpp"
#include "racun.hpp"
#include "dinarski.hpp"

int main(void) {
    std::cout << "=================== Datum ====================" << std::endl;
    Datum d1, d2, d3(13, 4);
    std::cout << "Ispis podrazumevanog datuma (1. 1. 2021.): " << d1 << std::endl
              << "Ispis novog datuma (13. 4. 2021.): " << d3 << std::endl
              << "Poređenje istih datuma: " << (d1 == d2) << std::endl
              << "Poređenje različitih datuma: " << (d1 == d3) << std::endl;

    std::cout << "=================== Osoba ====================" << std::endl;
    Osoba o1("Pera", "0000000000000", d1), o2("Žika", "1111111111111", d3);
    std::cout << "Dohvatanje imena (Pera): " << o1.dohvatiIme() << std::endl
              << "Dohvatanje JMBG (0000000000000): " << o1.dohvatiJmbg() << std::endl
              << "Dohvatanje datuma (1. 1. 2021.): " << o1.dohvatiDatum() << std::endl
              << "Ispis osobe (O(Pera, 0000000000000, 1. 1. 2021.)): " << o1 << std::endl;

    std::cout << "=================== Računi ===================" << std::endl;
    DinarskiRacun r1(o1, 0), r2(o2, 1);
    std::cout << "Dohvatanje vlasnika (O(Pera, 0000000000000, 1. 1. 2021.)): " << r1.dohvatiVlasnika() << std::endl
              << "Dohvatanje broja računa (0): " << r1.dohvatiBroj() << std::endl
              << "Dohvatanje iznosa (0): " << r1.dohvatiIznos() << std::endl
              << "Valuta (RSD): " << r1.dohvatiValutu() << std::endl
              << "Račun nakon uplate 1000 dinara: " << (r1 += 1000) << std::endl
              << "Uspešan prenos: " << r1.prenesi(r2, 1000) << std::endl
              << "Neuspešan prenos: " << r1.prenesi(r2, 1000) << std::endl
              << "Ispis računa (R: 1 :=: 1000 - RSD): " << r2 << std::endl;
    
    return 0;
}
