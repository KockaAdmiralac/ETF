#include <iostream>
#include "destinacija.hpp"
#include "smestaj.hpp"
#include "prevoz.hpp"
#include "datum.hpp"
#include "aranzman.hpp"

int main(void) {
    std::cout << "================= Destinacija ================" << std::endl;
    Destinacija d1("Mesto", "Lepo mesto"), d2("Drugo mesto", "Ružno mesto");
    std::cout << "Dohvatanje naziva (Mesto): " << d1.dohvatiNaziv() << std::endl
              << "Dohvatanje opisa (Lepo mesto): " << d1.dohvatiOpis() << std::endl
              << "Prosečna ocena dok je neocenjeno: " << d1.dohvatiProsecnuOcenu() << std::endl;
    d1.oceni(4);
    d1.oceni(5);
    std::cout << "Dohvatanje prosečne ocene (4.5): " << d1.dohvatiProsecnuOcenu() << std::endl
              << "Lepo mesto je veće od ružnog mesta: " << (d1 > d2) << std::endl
              << "Ispis mesta ([4.5] Mesto (Lepo mesto)): " << d1 << std::endl;
    d1.oceni(6);
    std::cout << "Prosečna ocena ostaje ista jer ocena 6 nije validna: " << d1.dohvatiProsecnuOcenu() << std::endl;

    std::cout << "================== Smeštaj ===================" << std::endl;
    Smestaj hotel(d1, Smestaj::HOTEL, "Top Resort", 5, 1000),
            apart(d2, Smestaj::APARTMAN, "Also Top Resort", 3, 200);
    try {
        Smestaj nijeValidan(d1, Smestaj::HOTEL, "Oh No", 6, 0.0);
        std::cout << "Nije se desila greška!" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Desila se greška prilikom inicijalizovanja sa prevelikim brojem zvezdica: " << greska.what() << std::endl;
    }
    std::cout << "Dohvatanje destinacije ([4.5] Mesto (Lepo mesto)): " << hotel.dohvatiDestinaciju() << std::endl
              << "Dohvatanje tipa (0): " << hotel.dohvatiTip() << std::endl
              << "Dohvatanje naziva (Top Resort): " << hotel.dohvatiNaziv() << std::endl
              << "Dohvatanje broja zvezdica (5): " << hotel.dohvatiBrojZvezdica() << std::endl
              << "Dohvatanje cene po danu (1000): " << hotel.dohvatiCenuPoDanu() << std::endl
              << "Ispis hotela (Hotel Top Resort *****): " << hotel << std::endl
              << "Ispis apartmana (Apartman Also Top Resort ***): " << apart << std::endl;

    std::cout << "=================== Prevoz ===================" << std::endl;
    Prevoz p1(d1, 100), p2(d2, 50);
    std::cout << "Dohvatanje destinacije ([4.5] Mesto (Lepo mesto)): " << p1.dohvatiDestinaciju() << std::endl
              << "Dohvatanje cene prevoza (100): " << p1.cenaPrevoza() << std::endl;

    std::cout << "=================== Datum ====================" << std::endl;
    Datum dat1(1, 1, 2021), dat2(1, 1, 2020), dat3(1, 6, 2021), dat4(20, 1, 2021);
    try {
        Datum nvdat(29, 2, 2021);
        std::cout << "Nije se desila greška!" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška prilikom nevalidnog datuma: " << greska.what() << std::endl;
    }
    std::cout << "Dohvatanje dana (1): " << dat1.dohvatiDan() << std::endl
              << "Dohvatanje meseca (1): " << dat1.dohvatiMesec() << std::endl
              << "Dohvatanja godine (2021): " << dat1.dohvatiGodinu() << std::endl
              << "Razlika datuma u istom mesecu (19): " << (dat1 - dat4) << std::endl
              << "Razlika datuma u različitim mesecima (151): " << (dat3 - dat1) << std::endl
              << "Razlika datuma u različitim godinama (366): " << (dat1 - dat2) << std::endl
              << "Ispis datuma (1. 1. 2021.): " << dat1 << std::endl;

    std::cout << "================== Aranžman ==================" << std::endl;
    Aranzman aranz(d1, dat2, dat1);
    try {
        aranz.dodeliPrevoz(p2);
        std::cout << "Nije se desila greška!" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška pri postavljanju prevoza koji nije na istoj destinaciji: " << greska.what() << std::endl;
    }
    aranz.dodeliPrevoz(p1);
    try {
        aranz.dohvatiCenu();
        std::cout << "Nije se desila greška!" << std::endl;
    } catch (std::exception &greska) {
        std::cout << "Greška pri dohvatanju cene kada nisu postavljeni prevoz ili smeštaj: " << greska.what() << std::endl;
    }
    aranz.dodeliSmestaj(hotel);
    std::cout << "Dohvatanje destinacije ([4.5] Mesto (Lepo mesto)): " << aranz.dohvatiDestinaciju() << std::endl
              << "Dohvatanje početnog datuma (1. 1. 2020.): " << aranz.dohvatiPocetak() << std::endl
              << "Dohvatanje krajnjeg datuma (1. 1. 2021.): " << aranz.dohvatiKraj() << std::endl
              << "Dohvatanje trajanja (366): " << aranz.dohvatiTrajanje() << std::endl
              << "Dohvatanje cene (366100): " << aranz.dohvatiCenu() << std::endl
              << "Ispis aranžmana ([4.5] Mesto (Lepo mesto)\\nHotel Top Resort *****\\n366100): " << aranz << std::endl;
    return 0;
}
